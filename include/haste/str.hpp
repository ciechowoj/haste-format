#pragma once

namespace haste {

using ullong = unsigned long long;
using size_t = ullong;

class str_view {
public:
	str_view();
	str_view(const char*);
	str_view(const char*, const char*);
	
	template <ullong N> str_view(const char (&that)[N]) 
		: str_view(that, that + N - 1) {
	}

	str_view(const str_view&);
	str_view(str_view&&);
private:
	char _data[sizeof(void*) * 3];
};

const char* begin(const str_view&);
const char* end(const str_view&);
size_t nbytes(const str_view&);
size_t nchars(const str_view&);

class str {
public:
	str();
	str(const char*);
	str(const str_view&);
	str(const str&);
	str(str&&);
	~str();

	operator str_view() const;

	str& operator=(const str&);
	str& operator=(str&&);

	const char* data() const;
	ullong nbytes() const;
	ullong nchars() const;
private:
	char _data[sizeof(void*) * 4];
};

void swap(str&, str&);

bool operator==(const str&, const str&);
bool operator!=(const str&, const str&);

str unsafe_init(size_t nbytes, size_t nchars);
void unsafe_resize(str&, size_t nbytes, size_t nchars);
char* unsafe_data(str&);

str _concat(const str_view* s, size_t n);

template <class... T> inline str concat(const T&... s) {
	str_view v[] = { str_view(s)... };
	return _concat(v, sizeof...(s));
}

}
