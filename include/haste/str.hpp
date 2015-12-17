#pragma once

namespace haste {

using ullong = unsigned long long;

class str_ref {
public:
	str_ref();
	str_ref(const char*);
	str_ref(const char*, const char*);
	
	template <ullong N> str_ref(const char (&that)[N]) {
		_data[0] = that;
		_data[1] = that + N;
	}

private:
	const char* _data[2];
};

const char* begin(const str_ref&);
const char* end(const str_ref&);

class str {
public:
	str();
	str(const char*);
	str(const str_ref&);
	str(const str&);
	str(str&&);
	~str();

	operator str_ref() const;

	str& operator=(const str&);
	str& operator=(str&&);

	char* data();
	const char* data() const;
	ullong nbytes() const;
	ullong nchars() const;
private:
	char _data[sizeof(void*) * 4];
};

void swap(str&, str&);

bool operator==(const str&, const str&);
bool operator!=(const str&, const str&);

str _concat(const str_ref* s, ullong n);

template <class... T> inline str concat(const T&... s) {
	str_ref v[] = { str_ref(s)... };
	return _concat(v, sizeof...(s));
}

}
