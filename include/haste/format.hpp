#pragma once
#include <string>

namespace haste {

using std::nullptr_t;
using std::string;
using std::size_t;

namespace _format_detail {

struct B {
	int id;
	union {
		char32_t _char;
		int _int;
		unsigned _uint;
		long long _llong;
		unsigned long long _ullong;
		double _double;
		const char* _string;
		struct {
			const void* _object;
			string (*_to_string)(const void*, int);
		};
	};
};

template <class T> struct F : public B { };
template <> struct F<nullptr_t> : public B { F(nullptr_t) { id = 0; } };
template <> struct F<bool> : public B { F(bool x) { _int = int(x); id = 1; } };
template <> struct F<char> : public B { F(char x) { _char = x; id = 2; } };
template <> struct F<signed char> : public B { F(signed char x) { _char = x; id = 3; } };
template <> struct F<unsigned char> : public B { F(unsigned char x) { _char = x; id = 4; } };
template <> struct F<char16_t> : public B { F(char16_t x) { _char = x; id = 5; } };
template <> struct F<char32_t> : public B { F(char32_t x) { _char = x; id = 6; } };
template <> struct F<wchar_t> : public B { F(wchar_t x) { _char = x; id = 7; } };
template <> struct F<short> : public B { F(short x) { _int = x; id = 8; } };
template <> struct F<unsigned short> : public B { F(unsigned short x) { _uint = x; id = 9; } };
template <> struct F<int> : public B { F(int x) { _int = x; id = 10; } };
template <> struct F<unsigned int> : public B { F(unsigned int x) { _uint = x; id = 11; } };
template <> struct F<long> : public B { F(long x) { _llong = x; id = 12; } };
template <> struct F<unsigned long> : public B { F(unsigned long x) { _ullong = x; id = 13; } };
template <> struct F<long long> : public B { F(long long x) { _llong = x; id = 14; } };
template <> struct F<unsigned long long> : public B { F(unsigned long long x) { _ullong = x; id = 15; } };
template <> struct F<float> : public B { F(float x) { _double = x; id = 16; } };
template <> struct F<double> : public B { F(double x) { _double = x; id = 17; } };
template <> struct F<string> : public B { F(string x) { _string = x.c_str(); id = 18; } };
template <> struct F<const char*> : public B { F(const char* x) { _string = x; id = 19; } };
template <size_t N> struct F<char[N]> : public B { F(const char* x) { _string = x; id = 19; } };

}

typedef _format_detail::B _format_param_base;
template <typename T> using _format_param = _format_detail::F<T>;

struct _format_params_desc {
	const char* format_begin;
	const char* format_end;
	const _format_param_base* params_begin;
	const _format_param_base* params_end;
};

string _format(const _format_params_desc& desc);
size_t _strlen(const char* _string);

template <class... Params> string format(const char* format_string, const Params&... params) {
	_format_param_base params_array[sizeof...(Params) + 1] = { 
		_format_param<Params>(params)... , _format_param_base() 
	};

	_format_params_desc desc;
	desc.format_begin = format_string;
	desc.format_end = format_string + _strlen(format_string);
	desc.params_begin = params_array;
	desc.params_end = params_array + sizeof...(Params);

	return _format(desc);
}

}
