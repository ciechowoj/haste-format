#pragma once

namespace haste {

using ullong = unsigned long long;

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

void swap(str&, str&);

str cat(const char* s);
template <ullong N> str cat(const (char&)s[N]);
str cat(const str& s);
str cat(str&& s);

template <class H, class... T> inline str cat(const H& h, const T&... t) {
	return str();	
}

}
