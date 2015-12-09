#include <haste/str.hpp>

namespace haste {

struct _str_t {
	char* data;
	size_t size;
	size_t capacity;
};

inline _str_t* _str(str* s) {
	return reinterpret_cast<_str_t*>(&s);
}

inline const _str_t* _str(const str* s) {
	return reinterpret_cast<const _str_t*>(&s);
}

str::str() {
	
}




char* str::data(str& s)
{
	return *reinterpret_cast<char**>(this);
}

const char8_t* data(const str& s)
{
	return 
}

size_t nbytes(const str& s)
{
	return 
}

void swap(str&, str&)
{
	return 
}


}
