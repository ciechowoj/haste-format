#include <haste/_format.hpp>
#include <stdexcept>
#include <algorithm>
#include <cstring>
#include <cstdint>

namespace haste {

using std::min;
using std::max;

static const int unknown_mode = -1;
static const int auto_mode = 0;
static const int manual_mode = 1;

static const char* type_names[] = {
	"std::nullptr_t",
	"bool",
	"char",
	"signed char",
	"unsigned char",
	"char16_t",
	"char32_t",
	"wchar_t",
	"short",
	"unsigned short",
	"int",
	"unsinged int",
	"long",
	"unsigned long",
	"long long",
	"unsinged long long",
	"float",
	"double",
	"std::string",
	"const char*",
};

inline size_t utf8len(const char* begin, const char* end) {
	return end - begin;
}

inline void utf8trim(
	size_t& size, 
	const char*& trimmed, 
	size_t width, 
	const char* begin, 
	const char* end) 
{
	size_t full_size = end - begin;
	size = min(width, full_size);
	trimmed = begin + size;
}

static char* _char32_to_utf8(char* buffer, char32_t c) {
	using namespace std;

	static const int s = 8;
	uint32_t x = std::uint32_t(c);
	uint8_t* b = (uint8_t*)buffer;

	if (x < 0x80) {
		b[s - 1] = uint8_t(x);
		return buffer + s - 1;
	}
	else {
		int i = s;
		uint8_t m = 0x80u;
		while (x != 0) {
			--i;
			b[i] = (x & 0x3fu) | 0x80u;
			x >>= 6;
			m = m >> 1 | 0x80u;
		}

		if (m & 0x7fu & b[i]) {
			b[--i] = m;
		}
		else {
			b[i] |= m << 1;
		}

		return buffer + i;
	}
}

inline unsigned char ord(char c) {
	return (unsigned char)(c - '0');
}

inline bool is_digit(char c) {
	return '0' <= c && c <= '9';
}

const char* _format_parse_name(
	int& index, 
	vector<_format_index_t>& indices, 
	const char* begin, 
	const char* end)
{
	// field_name        ::=  integer ("[" element_index "]")*
	// element_index     ::=  integer | index_string
	// index_string      ::=  <any source character except "]"> +

	const char* itr = begin;

	if (itr < end && is_digit(*itr)) {
		index = ord(*itr);
		++itr;

		while (itr < end && is_digit(*itr)) {
			index *= 10;
			index += ord(*itr);
			++itr;
		}
	}

	while (itr < end && *itr == '[') {
		++itr;

		_format_index_t index;
		index.begin = itr;

		while (itr < end && *itr != ']') {
			index.is_integer = index.is_integer && is_digit(*itr);
			++itr;
		}

		if (itr < end) {
			if (index.begin != itr) {
				index.end = itr;
				indices.push_back(index);
				++itr;
			}
			else
			{
				throw std::invalid_argument("Expected key before ']'.");		
			}
		}
		else {
			throw std::invalid_argument("Expected ']' before end of string.");
		}
	}

	return itr;
}

inline bool is_conv(char c) {
	return c == 'r' || c == 's' || c == 'a';
}

const char* _format_parse_conv(
	char& conv, 
	const char* begin, 
	const char* end)
{
	// replacement_field ::=  "{" [field_name] ["!" conversion] [":" format_spec] "}"
	// conversion        ::=  "r" | "s" | "a"

	const char* itr = begin;

	if (itr < end && *itr == '!') {
		++itr;

		if (itr < end && is_conv(*itr)) {
			conv = *itr;
			++itr;
		}
		else {
			throw std::invalid_argument("Expected conversion flag after '!'.");
		}
	}

	return itr;
}

inline bool is_align(char c) {
	return c == '<' || c == '>' || c == '=' || c == '^';
}

inline bool is_sign(char c) {
	return c == '+' || c == '-' || c == ' ';
}

inline bool is_type(char c) {
	static char const begin[] = "bcdeEfFgGnos%xX";
	static char const *const end = begin + sizeof(begin);

	for (const char* itr = begin; itr < end; ++itr) {
		if (*itr == c) {
			return true;
		}
	}

	return false;
}

inline const char* skip_utf8(const char* begin, const char* end) {
	if (begin < end) {
		return begin + 1;
	}
	else {
		return begin;
	}
}

inline void _throw_cannot_specify_equal(int id) {
	throw std::invalid_argument("Cannot specify '=' for '" + string(type_names[id]) + "' type.");
}

inline void _throw_cannot_specify_comma(int id) {
	throw std::invalid_argument("Cannot specify ',' for '" + string(type_names[id]) + "' type.");
}

inline void _throw_cannot_specify_hash(int id) {
	throw std::invalid_argument("Cannot specify '#' for '" + string(type_names[id]) + "' type.");
}

inline void _throw_cannot_specify_sign(int id, char sign) {
	throw std::invalid_argument(
		string("Cannot specify '") +
		sign +
		"' for '" + 
		string(type_names[id]) + 
		"' type.");
}

inline void _throw_cannot_specify_type(int id, char type) {
	throw std::invalid_argument(
		string("Cannot specify '") +
		type +
		"' for '" + 
		string(type_names[id]) + 
		"' type.");
}

inline void _throw_cannot_specify_precision(int id) {
	throw std::invalid_argument(
		"Cannot specify '.precision' for '" + 
		string(type_names[id]) + "' type.");
}

inline bool is_numeric(int id) {
	return short_id <= id && id <= double_id;
}

inline bool is_integer(int id) {
	return short_id <= id && id <= ullong_id;
}

inline bool types_match(int id, char type) {
	return true;
}

const char* _format_parse_spec(
	_format_spec_t& spec, 
	int id,
	const char* begin, 
	const char* end)
{
	// replacement_field ::=  "{" [field_name] ["!" conversion] [":" format_spec] "}"

	// format_spec ::=  [[fill]align][sign][#][0][width][,][.precision][type]
	// fill        ::=  <a character other than '{' or '}'>
	// align       ::=  "<" | ">" | "=" | "^"
	// sign        ::=  "+" | "-" | " "
	// width       ::=  integer
	// precision   ::=  integer
	// type        ::=  "b" | "c" | "d" | "e" | "E" | "f" | "F" | "g" | "G" | "n" | "o" | "s" | "x" | "X" | "%"

	const char* itr = begin;

	if (itr < end && *itr == ':') {
		++itr;

		const char* jtr = skip_utf8(itr, end);
		if (jtr < end && is_align(*jtr)) {
			if (*itr != '{' && *itr != '}') {
				if (*jtr == '=' && !is_numeric(id)) {
					_throw_cannot_specify_equal(id);
				}

				spec.fill.assign(itr, jtr);
				spec.align = *jtr;
				itr = jtr + 1;
			}
		}
		else if(itr < end && is_align(*itr)) {
			if (*itr == '=' && !is_numeric(id)) {
				_throw_cannot_specify_equal(id);
			}

			spec.align = *itr;
			++itr;
		}

		if (itr < end && is_sign(*itr)) {

			if (!is_numeric(id)) {
				_throw_cannot_specify_sign(id, *itr);
			}

			spec.sign = *itr;
			++itr;
		}

		if (itr < end && *itr == '#') {
			if (!is_numeric(id)) {
				_throw_cannot_specify_hash(id);
			}

			spec.hash = true;
			++itr;
		}

		if (itr < end && *itr == '0') {
			if (spec.fill.empty()) {
				spec.fill = "0";
			}
			if (spec.align == 0) {
				spec.align = '=';
			}

			spec.zero = true;
			++itr;
		}

		if (itr < end && is_digit(*itr)) {
			if (spec.fill.empty()) {
				spec.fill = " ";
			}

			spec.width = ord(*itr);
			++itr;

			while (itr < end && is_digit(*itr)) {
				spec.width *= 10;
				spec.width += ord(*itr);
				++itr;
			}
		}

		while (itr < end && *itr == ',') {
			if (!is_numeric(id)) {
				_throw_cannot_specify_comma(id);
			}

			spec.comma = true;
			++itr;
		}

		if (itr < end && *itr == '.') {
			if (is_integer(id)) {
				_throw_cannot_specify_precision(id);
			}

			++itr;
			spec.dot = true;

			if (itr < end && is_digit(*itr)) {
				spec.precision = ord(*itr);
				++itr;

				while (itr < end && is_digit(*itr)) {
					spec.precision *= 10;
					spec.precision += ord(*itr);
					++itr;
				}
			}
			else {
				throw std::invalid_argument("Expected precision after '.'.");
			}
		}

		if (itr < end && is_type(*itr)) {
			if (!types_match(id, *itr)) {
				_throw_cannot_specify_type(id, *itr);
			}

			spec.type = *itr;
			++itr;
		}
	}

	return itr;
}

const char* _format_preparse_field(
	int& index, 
	vector<_format_index_t>& indices, 
	char& conv, 
	const char*& spec_begin,
	const char*& spec_end,
	const char* begin, 
	const char* end)
{
	const char* itr = begin;
	itr = _format_parse_name(index, indices, itr, end);
	itr = _format_parse_conv(conv, itr, end);

	if (itr < end && *itr == ':') {
		const char* jtr = itr;

		while (itr < end && *itr != '{' && *itr != '}') {
			++itr;
		}
		
		spec_begin = jtr;
		spec_end = itr;
	}

	if (itr < end) {
		if (*itr != '}') {
			throw std::invalid_argument("Expected '}' after replacement field.");
		}
		++itr;
	}
	else {
		throw std::invalid_argument("Expected '}' before end of string.");
	}

	return itr;
}

static void _append_fill(
	string& result,
	const string& fill,
	size_t size) {
	for (size_t i = 0; i < size; ++i) {
		result.append(fill);
	}
}

static void _replace_string_str(
	string& result,
	const _format_spec_t& spec,
	const char* begin,
	const char* end)
{
	size_t size;
	const char* trimmed;

	if (spec.dot) {
		utf8trim(size, trimmed, spec.precision, begin, end);
	}
	else {
		size = utf8len(begin, end);
		trimmed = end;
	}

	if (size < size_t(spec.width)) {
		switch(spec.align) {
		default:
		case '<':
			result.append(begin, trimmed);
			_append_fill(result, spec.fill, size_t(spec.width) - size);
			break;
		case '>':
			_append_fill(result, spec.fill, size_t(spec.width) - size);
			result.append(begin, trimmed);
			break;
		case '^':
			size_t left = (size_t(spec.width) - size) / 2;
			size_t right = size_t(spec.width) - size - left;
			_append_fill(result, spec.fill, left);
			result.append(begin, trimmed);
			_append_fill(result, spec.fill, right);
			break;
		}
	}
	else {
		result.append(begin, trimmed);
	}
}

static void _replace_nullptr_t(
	string& result,
	char conv,
	const _format_spec_t& spec,
	const _format_param_base& param
	)
{
	const char null[] = "nullptr";
	_replace_string_str(result, spec, null, null + sizeof(null) - 1);
}

static void _replace_bool(
	string& result,
	char conv,
	const _format_spec_t& spec,
	const _format_param_base& param)
{
	const char _true[] = "true";
	const char _false[] = "false";

	if (param._int) {
		_replace_string_str(result, spec, _true, _true + sizeof(_true) - 1);
	}
	else {
		_replace_string_str(result, spec, _false, _false + sizeof(_false) - 1);
	}
}

inline char hex(unsigned x) {
	return x < 10 ? x + '0' : x - 10 + 'a';
}

static void _replace_char_ascii(
	string& result,
	const _format_spec_t& spec,
	const _format_param_base& param)
{
	using namespace std;

	char buffer[16];
	char* itr = buffer;

	uint32_t x = (uint32_t)param._char;

	*itr = '\''; ++itr;
	if (x < 32) {
		*itr = '\\'; ++itr;

		if (x == '\t') {
			*itr = 't'; ++itr;
		}
		else if (x == '\r') {
			*itr = 'r'; ++itr;
		}
		else if (x == '\n') {
			*itr = 'n'; ++itr;
		}
		else {
			*itr = 'x'; ++itr;
			*itr = hex(x >> 4); ++itr;
			*itr = hex(x & 0x0fu); ++itr;
		}
	}
	else if (x < 127) {
		*itr = x; ++itr;
	}
	else if (x < 0x100) {
		*itr = '\\'; ++itr;
		*itr = 'x'; ++itr;
		*itr = hex(x >> 4); ++itr;
		*itr = hex(x & 0x0fu); ++itr;
	}
	else if (x < 0x10000) {
		*itr = '\\'; ++itr;
		*itr = 'u'; ++itr;
		*itr = hex(x >> 12 & 0x0fu); ++itr;
		*itr = hex(x >> 8 & 0x0fu); ++itr;
		*itr = hex(x >> 4 & 0x0fu); ++itr;
		*itr = hex(x >> 0 & 0x0fu); ++itr;
	}
	else {
		*itr = '\\'; ++itr;
		*itr = 'U'; ++itr;
		for (int i = 7; 0 <= i; --i) {
			*itr = hex(x >> i * 4 & 0x0fu); ++itr;
		}
	}

	*itr = '\''; ++itr;
	_replace_string_str(result, spec, buffer, itr);
}

static void _replace_char(
	string& result,
	char conv,
	const _format_spec_t& spec,
	const _format_param_base& param)
{
	char buffer[10];
	char* begin = nullptr;

	switch(conv) {
	default:
	case 's':
		begin = _char32_to_utf8(buffer, param._char);
		_replace_string_str(result, spec, begin, buffer + 8);
		break;
	case 'r':
		begin = _char32_to_utf8(buffer, param._char);
		begin[-1] = '\'';
		buffer[8] = '\'';
		_replace_string_str(result, spec, begin - 1, buffer + 9);
		break;
	case 'a':
		_replace_char_ascii(result, spec, param);
	}
}

static void _replace_field(
	string& result,
	const vector<_format_index_t>& indices,
	char conv,
	const char* spec_begin,
	const char* spec_end,
	const _format_param_base& param)
{
	_format_spec_t spec;

	if (param.id <= c_string_id) {
		if (!indices.empty()) {
			throw std::invalid_argument(string(type_names[param.id]) + " is not indexable.");
		}

		_format_parse_spec(
			spec,
			param.id,
			spec_begin,
			spec_end);
	}

	switch(param.id) {
	case null_id: _replace_nullptr_t(result, conv, spec, param); break;
	case bool_id: _replace_bool(result, conv, spec, param); break;
	case char_id:
	case schar_id:
	case uchar_id:
	case char16_t_t:
	case char32_t_t: _replace_char(result, conv, spec, param); break;
	case wchar_t_t: break;
	case short_id: break;
	case ushort_id: break;
	case int_id: break;
	case uint_id: break;
	case long_id: break;
	case ulong_id: break;
	case llong_id: break;
	case ullong_id: break;
	case float_id: break;
	case double_id: break;
	case std_string_id: break;
	case c_string_id: break;
	case to_string_id: break;
	}
}

static const char* _replace_field(
	string& result,
	int& prev,
	int& mode,
	const char* format_begin,
	const char* format_end,
	const _format_param_base* params_begin,
	const _format_param_base* params_end)
{
	const char* itr = format_begin;

	int index = -1;
	vector<_format_index_t> indices; 
	char conv = 0;
	const char* spec_begin = nullptr;
	const char* spec_end = nullptr;
	
	itr = _format_preparse_field(
		index,
		indices,
		conv,
		spec_begin,
		spec_end,
		format_begin,
		format_end);

	if (index == -1 && mode != manual_mode) {
		index = ++prev;
		mode = auto_mode;
	}
	else if (index != -1 && mode != auto_mode) {
		mode = manual_mode;
	}
	else {
		throw std::invalid_argument("Cannot switch between automatic and manual field numbering.");
	}

	if (params_begin + index < params_end) {
		_replace_field(
			result, 
			indices,
			conv,
			spec_begin,
			spec_end,
			params_begin[index]);
	}
	else {
		throw std::out_of_range("Too few params passed.");
	}

	return itr;
}

string _format(const _format_params_desc& desc) {
	const char* begin = desc.format_begin;
	const char* end = desc.format_end;

	string result;
	int prev = -1;
	int mode = unknown_mode;
	result.reserve(end - begin);

	const char* itr = begin;

	while (itr < end) {

		const char* jtr = itr;

		while (jtr < end && *jtr != '{' && *jtr != '}') {
			++jtr;
		}

		result.append(itr, jtr);
		itr = jtr;

		if (itr < end) {
			if(*itr == '{') {
				if (itr + 1 < end && itr[1] == '{') {
					result.push_back('{');
					itr = itr + 2;
				}
				else {
					itr = _replace_field(
						result,
						prev,
						mode,
						itr + 1,
						end,
						desc.params_begin,
						desc.params_end);
				}
			}
			else if (*itr == '}') {
				if (itr + 1 < end && itr[1] == '}') {
					result.push_back('}');
					itr += 2;
				}
				else {
					throw std::invalid_argument("Single '}' encountered in format string.");
				}
			}
		}
	}

	return result;
}

size_t _strlen(const char* _string)
{
	return std::strlen(_string);
}

}
