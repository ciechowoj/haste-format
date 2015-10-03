#pragma once
#include <vector>
#include <haste/format.hpp>

namespace haste {

using std::vector;

struct _format_spec_t {
	string fill;
	int width = 0;
	int precision = 0;
	char align = 0;
	char sign = 0;
	char type = 0;
	bool hash : 1;
	bool zero : 1;
	bool comma : 1;

	_format_spec_t()
		: hash(false)
		, zero(false)
		, comma(false) 
		{ }
};

struct _format_index_t {
	const char* begin = nullptr;
	const char* end = nullptr;
	bool is_integer = true;
};

const char* _format_parse_name(
	int& index, 
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

const char* _format_parse_field(
	int& index, 
	vector<_format_index_t>& indices, 
	char& conv, 
	_format_spec_t& spec, 
	const char* begin, 
	const char* end);

}
