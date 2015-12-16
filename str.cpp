#include <haste/_str.hpp>
#include <haste/str.hpp>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <utility>

namespace haste {
namespace detail {

static_assert(sizeof(str_t::sso_t) == sizeof(str_t), "Sizes must match.");

static const unsigned char sso_mask = 1u << 7;

inline bool sso(const str_t* x) {
	return (x->sso.size && sso_mask) == 0;
}

void init(str_t* x) {
	std::memset(x, 0, sizeof(str_t));
}

void init_copy(str_t* x, const str_t* s) {
	if (sso(s)) {
		std::memcpy(x, s, sizeof(str_t));
	}
	else {
		x->heap.data = static_cast<char*>(::malloc(s->heap.capacity));
		x->heap.size = s->heap.size;
		x->heap.capacity = s->heap.capacity;
		std::memcpy(x->heap.data, s->heap.data, s->heap.size + 1);
	}
}

void init_move(str_t* x, str_t* s)
{
	std::memcpy(x, s, sizeof(str_t));
	std::memset(s, 0, sizeof(str_t));
}

void assign_copy(str_t* x, const str_t* s) {
	if (x != s) {
		clean(x);
		init_copy(x, s);
	}
}

void assign_move(str_t* x, str_t* s) {
	if (x != s) {
		clean(x);
		init_move(x, s);
	}
}

void clean(str_t* x) {
	if (!sso(x)) {
		::free(x->heap.data);
	}
}

void swap(str_t* x, str_t* y) {
	char t[sizeof(str_t)];
	std::memcpy(t, y, sizeof(str_t));
	std::memcpy(y, x, sizeof(str_t));
	std::memcpy(x, t, sizeof(str_t));
}

char* data(str_t* x) {
	if (sso(x)) {
		return x->sso.data;
	}
	else {
		return x->heap.data;
	}
}

const char* data(const str_t* x) {
	if (sso(x)) {
		return x->sso.data;
	}
	else {
		return x->heap.data;
	}
}

size_t nbytes(const str_t* x) {
	if (sso(x)) {
		return x->sso.size;
	}
	else {
		return x->heap.size;
	}
}

size_t capacity(const str_t* x) {
	if (sso(x)) {
		return sizeof(x->sso.data) - 1;
	}
	else {
		return x->heap.capacity;
	}	
}

}

using namespace detail;

static_assert(sizeof(str_t) == sizeof(str), "Sizes must match.");

inline str_t* cast(str* x) {
	return reinterpret_cast<str_t*>(x);
}

inline const str_t* cast(const str* x) {
	return reinterpret_cast<const str_t*>(x);
}

str::str() {
	init(cast(this));
}

str::str(const str& that) {
	init_copy(cast(this), cast(&that));
}

str::str(str&& that) {
	init_move(cast(this), cast(&that));
}

str::~str() {
	clean(cast(this));
}

str& str::operator=(const str& that) {
	assign_copy(cast(this), cast(&that));
	return *this;
}

str& str::operator=(str&& that) {
	assign_move(cast(this), cast(&that));
	return *this;
}

void swap(str& x, str& y) {
	swap(cast(&x), cast(&y));
}

char* str::data() {
	return haste::detail::data(cast(this));
}

const char* str::data() const {
	return haste::detail::data(cast(this));
}

ullong str::nbytes() const {
	return haste::detail::nbytes(cast(this));
}

}
