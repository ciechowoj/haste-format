#include <haste/format.hpp>
#include <cstring>

namespace haste {

string _format(const _format_params_desc& desc)
{
	return string(desc.format_begin, desc.format_end);
}

size_t _strlen(const char* _string)
{
	return std::strlen(_string);
}

}
