#pragma once
#include <vector>
#include <haste/format.hpp>

namespace haste {

using std::vector;

struct _format_spec_t {
	string fill;
	int width;
	int precision;
	char align;
	char sign;
	char type;
};

struct _format_index_t {
	const char* begin = nullptr;
	const char* end = nullptr;
	bool is_integer = true;
};

const char* _format_parse_name(
	size_t& index, 
	vector<_format_index_t>& indices, 
	const char* begin, 
	const char* end);

const char* _format_parse_conv(
	char& conv, 
	const char* begin, 
	const char* end);

const char* _format_parse_spec(
	_format_spec_t& spec, 
	const char* begin, 
	const char* end);

}
