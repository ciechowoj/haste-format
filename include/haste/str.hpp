#pragma once

namespace haste {

using ullong = unsigned long long;

class str {
public:
	str();
	str(const char*);
	str(const str&);
	str(str&&);
	~str();

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

}
