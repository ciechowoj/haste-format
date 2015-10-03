#include <haste/_format.hpp>
#include <stdexcept>
#include <algorithm>
#include <cstring>

namespace haste {

using std::min;
using std::max;

// replacement_field ::=  "{" [field_name] ["!" conversion] [":" format_spec] "}"
// field_name        ::=  integer ("[" element_index "]")*
// element_index     ::=  integer | index_string
// index_string      ::=  <any source character except "]"> +
// conversion        ::=  "r" | "s" | "a"
// format_spec       ::=  <described in the next section>
//
// format_spec ::=  [[fill]align][sign][#][0][width][,][.precision][type]
// fill        ::=  <a character other than '{' or '}'>
// align       ::=  "<" | ">" | "=" | "^"
// sign        ::=  "+" | "-" | " "
// width       ::=  integer
// precision   ::=  integer
// type        ::=  "b" | "c" | "d" | "e" | "E" | "f" | "F" | "g" | "G" | "n" | "o" | "s" | "x" | "X" | "%"

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

const char* _format_parse_spec(
	_format_spec_t& spec, 
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
				spec.fill.assign(itr, jtr);
				spec.align = *jtr;
				itr = jtr + 1;
			}
		}

		if (itr < end && is_sign(*itr)) {
			spec.sign = *itr;
			++itr;
		}

		if (itr < end && *itr == '#') {
			spec.hash = true;
			++itr;
		}

		if (itr < end && *itr == '0') {
			spec.zero = true;
			++itr;
		}

		while (itr < end && is_digit(*itr)) {
			spec.width *= 10;
			spec.width += ord(*itr);
			++itr;
		}

		while (itr < end && *itr == ',') {
			spec.comma = true;
			++itr;
		}

		if (itr < end && *itr == '.') {
			++itr;

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
			spec.type = *itr;
			++itr;
		}
	}

	return itr;
}

const char* _format_parse_field(
	int& index, 
	vector<_format_index_t>& indices, 
	char& conv, 
	_format_spec_t& spec, 
	const char* begin, 
	const char* end)
{
	const char* itr = begin;
	itr = _format_parse_name(index, indices, itr, end);
	itr = _format_parse_conv(conv, itr, end);
	itr = _format_parse_spec(spec, itr, end);
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
		const char* jtr = ++itr;

		while (itr < end && *itr != '{' && *itr != '}') {
			++itr;
		}
		
		spec_begin = jtr;
		spec_begin = itr;
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

const char* _replace_field(
	string& result,
	int& automatic,
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

	if (index == -1) {
		index = ++automatic;
	}
	else if (automatic != -1) {
		throw std::invalid_argument("Cannot switch from automatic to manual field numbering.");
	}

	if (params_begin + index < params_end) {

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
	int automatic = -1;
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
						automatic,
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
