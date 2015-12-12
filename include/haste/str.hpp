#pragma once

namespace haste {

using ullong = unsigned long long;

class str;

void swap(str&, str&);

class str {
public:
	str();
	str(const str&);
	str(str&&);
	~str();

	str& operator=(const str&);
	str& operator=(str&&);
	
	friend void swap(str&, str&);

	char* data();
	const char* data() const;
	ullong nbytes() const;
private:
	char _data[sizeof(void*) * 4];
};

str make_str();
str make_str(const char* c_str);
str make_str(const char* begin, const char* end);

void replace(str& s, size_t i, size_t n, const char* begin, const char* end);
void replace(str& s, size_t i, size_t n, const char* cstr);
void replace(str& s, size_t i, size_t n, const str& x);

}
