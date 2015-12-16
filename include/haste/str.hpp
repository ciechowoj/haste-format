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

 
}
