#include <haste/str.hpp>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <utility>

namespace haste {

using std::memset;
using std::memcpy;
using std::strlen;

struct _str_t {
	size_t capacity;
	size_t size;
	char* data;
};

inline _str_t* _str(str* s) {
	return reinterpret_cast<_str_t*>(s);
}

inline const _str_t* _str(const str* s) {
	return reinterpret_cast<const _str_t*>(s);
}

inline bool _sso(const str* s) {
	const char* _data = reinterpret_cast<const char*>(s);
	
	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return (_data[0] & 1) == 0;
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return (_data[0] & (1 << 7)) == 0;
	#else
	#error "Unsupported byte order."
	#endif
}

inline size_t _capacity(const str* s) {
	const _str_t* _str = reinterpret_cast<const _str_t*>(s);

	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	return _str -> capacity >> 1;
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	return _str -> capacity << 1 >> 1;
	#else
	#error "Unsupported byte order."
	#endif	
}

inline void _set_capacity(str* s, size_t capacity) {
	_str_t* _str = reinterpret_cast<_str_t*>(s);

	#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	_str -> capacity = (capacity << 1) | 1;
	#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	_str -> capacity = capacity | ~(~size_t(0) << 1 >> 1);
	#else
	#error "Unsupported byte order."
	#endif	
}

str::str() {
	::memset(this, 0, sizeof(str));
}

str::str(const str& that) {
	if (_sso(&that)) {
		::memcpy(this, &that, sizeof(str));
	}
	else {
		_str_t* _this = _str(this);
		const _str_t* _that = _str(&that);
		_this -> size = _that -> size;
		_this -> capacity = _that -> capacity;
		_this -> data = reinterpret_cast<char*>(::malloc(_this -> capacity));
		::memcpy(_this -> data, _that -> data, _this -> size + 1);
	}
}

str::str(str&& that) {
	::memcpy(this, &that, sizeof(str));
	::memset(&that, 0, sizeof(str));
}

str::~str() {
	if (!_sso) {
		::free(_str(this) -> data);
	}
}

void swap(str& a, str& b) {
	char tmp[sizeof(str)];
	::memcpy(tmp, &a, sizeof(str));
	::memcpy(&a, &b, sizeof(str));
	::memcpy(&b, tmp, sizeof(str));
}

str& str::operator=(const str& that) {
	str tmp(that);
	swap(*this, tmp);
	return *this;
}

str& str::operator=(str&& that) {
	swap(*this, that);
	return *this;	
}

char* data(str& s) {
	if (_sso(&s)) {
		return s._data + 1;
	}
	else {
		return _str(&s) -> data;
	}
}

const char* data(const str& s) {
	if (_sso(&s)) {
		return s._data + 1;
	}
	else {
		return _str(&s) -> data;
	}
}

size_t nbytes(const str& s) {
	if (_sso(&s)) {
		return static_cast<size_t>(s._data[0]);
	}
	else {
		return _str(&s) -> size;
	}
}

str make_str() {
	return str();
}

str make_str(const char* c_str) {
	return make_str(c_str, c_str + ::strlen(c_str));
}

str make_str(const char* begin, const char* end) {
	return make_str();
}

}
