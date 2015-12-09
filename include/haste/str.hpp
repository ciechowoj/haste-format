#pragma once

namespace haste {

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
	str(const char*);
	~str();

	str& operator=(const str&);
	str& operator=(str&&);
	str& operator=(const char*);

	friend char* data(str& s);
	friend const char* data(const str& s);
	friend size_t nbytes(const str& s);
	friend void swap(str&, str&);
private:
	char _data[32];
};

str make_str(const char* begin, const char* end);
str make_str(const char* cstr);
str make_str(char c, size_t n);
str make_str();

void replace(str& s, size_t i, size_t n, const char* begin, const char* end);
void replace(str& s, size_t i, size_t n, const char* cstr);
void replace(str& s, size_t i, size_t n, const str& x);

}
