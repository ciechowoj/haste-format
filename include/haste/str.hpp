#pragma once
#include <cstddef>

namespace haste {

using std::size_t;

class str;

char* data(str&);
const char* data(const str&);
size_t nbytes(const str&);

void swap(str&, str&);

class str {
public:
	str();
	str(const str&);
	str(str&&);
	~str();

	friend void swap(str&, str&);
	str& operator=(const str&);
	str& operator=(str&&);

	friend char* data(str& s);
	friend const char* data(const str& s);
	friend size_t nbytes(const str& s);
private:
	char _data[32];
};

str make_str();
str make_str(const char* c_str);
str make_str(const char* begin, const char* end);

void replace(str& s, size_t i, size_t n, const char* begin, const char* end);
void replace(str& s, size_t i, size_t n, const char* cstr);
void replace(str& s, size_t i, size_t n, const str& x);

}
