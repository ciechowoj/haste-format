#pragma once
#include <vector>
#include <haste/format.hpp>

namespace haste {

using std::vector;

static const int null_id = 0;
static const int bool_id = 1;
static const int char_id = 2;
static const int schar_id = 3;
static const int uchar_id = 4;
static const int char16_t_t = 5;
static const int char32_t_t = 6;
static const int wchar_t_t = 7;
static const int short_id = 8;
static const int ushort_id = 9;
static const int int_id = 10;
static const int uint_id = 11;
static const int long_id = 12;
static const int ulong_id = 13;
static const int llong_id = 14;
static const int ullong_id = 15;
static const int float_id = 16;
static const int double_id = 17;
static const int std_string_id = 18;
static const int c_string_id = 19;
static const int to_string_id = 20;

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
	bool dot : 1;

	_format_spec_t()
		: hash(false)
		, zero(false)
		, comma(false)
		, dot(false)
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
	int id,
	const char* begin, 
	const char* end);

}
