#pragma once
#include <string>

namespace haste {

using std::string;
using std::size_t;

struct _format_param_base {
	enum class id {
		_null,
		_char,
		_bool,
		_int,
		_uint,
		_llong,
		_ullong,
		_double,
		_std_string,
		_c_string,
		_to_string,
	};

	id _id;
	union {
		char32_t _char;
		int _int;
		unsigned _uint;
		long long _llong;
		unsigned long long _ullong;
		double _double;
		struct {
			const void* _object;
			string (*_to_string)(const void*, int);
		};
	};
};

template <class T> struct _format_param : public _format_param_base {
	
};

template <> class _format_param<int> : public _format_param_base {
	_format_param(int x) { _int = x; _id = id::_int; }
};

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










