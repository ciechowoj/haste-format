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

inline size_t ord(char c) {
	return size_t(c - '0');
}

inline bool is_digit(char c) {
	return '0' <= c && c <= '9';
}

const char* _format_parse_name(
	size_t& index, 
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

const char* _format_parse_spec(_format_spec_t& spec, 
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


}

const char* _replace_field(string& result, const char* itr, const _format_params_desc& desc) {
	const char* end = desc.format_end;

	end = end;

	return ++itr;
}

string _format(const _format_params_desc& desc) {
	const char* begin = desc.format_begin;
	const char* end = desc.format_end;

	string result;
	result.reserve(end - begin);

	const char* itr = begin;

	while (itr < end) {

		const char* jtr = itr;

		while (jtr < end && *jtr != '{' && *jtr != '}') {
			++jtr;
		}

		result.append(itr, jtr);
		itr = jtr;

		if (jtr < end) {
			if(*jtr == '{') {
				if (jtr + 1 < end && jtr[1] == '{') {
					result.push_back('{');
					itr = jtr + 2;
				}
				else {
					itr = _replace_field(result, itr, desc);
				}
			}
			else if (*jtr == '}') {
				if (jtr + 1 < end && jtr[1] == '}') {
					result.push_back('}');
					itr = jtr + 2;
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
