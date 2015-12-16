#include <haste/str.hpp>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <utility>

namespace haste {

union str_t {
	struct heap_t {
		char* data;
		size_t nbytes;
		size_t nchars;
		size_t capacity;
	} heap;

	struct sso_t {
		char data[sizeof(heap_t) - 2];
		unsigned char nbytes;
		unsigned char nchars;

		#if defined __ORDER_LITTLE_ENDIAN__
		static const unsigned char flag = 1u << 7;
		#elif defined __ORDER_BIG_ENDIAN__
		static const unsigned char flag = 1u << 0;
		#else
		#error "Unsupported byte order."
		#endif
	} sso;

	void set_capacity(size_t capacity) {
		#if defined __ORDER_LITTLE_ENDIAN__
		heap.capacity = capacity | ~(~size_t(0) >> 1);
		#elif defined __ORDER_BIG_ENDIAN__
		heap.capacity = (capacity << 1) | 1u;
		#endif
	}

	size_t capacity() const {
		#if defined __ORDER_LITTLE_ENDIAN__
		return (heap.capacity << 1) >> 1;
		#elif defined __ORDER_BIG_ENDIAN__
		return heap.capacity >> 1;
		#endif
	}

	bool using_heap() const {
		return (sso.nchars & sso.flag) != 0;
	}

	void set_sso_nchars(size_t nchars) {
		#if defined __ORDER_LITTLE_ENDIAN__
		sso.nchars = nchars << 1;
		#elif defined __ORDER_BIG_ENDIAN__
		sso.nchars = nchars;
		#endif
	}

	size_t sso_nchars() const {
		#if defined __ORDER_LITTLE_ENDIAN__
		return sso.nchars >> 1;
		#elif defined __ORDER_BIG_ENDIAN__
		return sso.nchars;
		#endif
	}
};

static_assert(sizeof(str_t) == sizeof(str), "error");
static const ullong sso_max_size = sizeof(str_t) - 3;

str::str() {
	std::memset(this, 0, sizeof(str));
}

str::str(const char* that) {
	ullong size = std::strlen(that);
	auto* pthis = reinterpret_cast<str_t*>(this);

	if (sso_max_size < size) {
		pthis->heap.data = static_cast<char*>(std::malloc(size + 1));
		pthis->heap.nbytes = size;
		pthis->heap.nchars = size;
		pthis->set_capacity(size + 1);
		std::memcpy(pthis->heap.data, that, size + 1);
	}
	else {
		pthis->sso.nbytes = static_cast<unsigned char>(size);
		pthis->set_sso_nchars(size);
		std::memcpy(pthis->sso.data, that, size + 1);	
	}
}

str::str(const str& that) {
	auto* pthis = reinterpret_cast<str_t*>(this);
	const auto* pthat = reinterpret_cast<const str_t*>(&that);

	if (pthat->using_heap()) {
		pthis->heap.data = static_cast<char*>(std::malloc(pthat->heap.capacity));
		pthis->heap.nbytes = pthat->heap.nbytes;
		pthis->heap.nchars = pthat->heap.nchars;
		pthis->set_capacity(pthat->heap.capacity);
		std::memcpy(pthis->heap.data, pthat->heap.data, pthis->heap.nbytes + 1);
	}
	else {
		std::memcpy(pthis, pthat, sizeof(str));	
	}	
}

str::str(str&& that) {
	std::memcpy(this, &that, sizeof(str));
	std::memset(&that, 0, sizeof(str));
}

str::~str() {
	auto* pthis = reinterpret_cast<str_t*>(this);

	if (pthis->using_heap()) {
		std::free(pthis->heap.data);
	}

	std::memset(this, 0, sizeof(str));
}

str& str::operator=(const str& that) {
	str tmp = that;
	swap(*this, tmp);
	return *this;
}

str& str::operator=(str&& that) {
	str tmp = std::move(that);
	swap(*this, tmp);
	return *this;
}

char* str::data() {
	auto* pthis = reinterpret_cast<str_t*>(this);
	return pthis->using_heap() ? pthis->heap.data : pthis->sso.data;
}

const char* str::data() const {
	const auto* pthis = reinterpret_cast<const str_t*>(this);
	return pthis->using_heap() ? pthis->heap.data : pthis->sso.data;
}

ullong str::nbytes() const {
	const auto* pthis = reinterpret_cast<const str_t*>(this);
	return pthis->using_heap() ? pthis->heap.nbytes : pthis->sso.nbytes;
}

ullong str::nchars() const {
	const auto* pthis = reinterpret_cast<const str_t*>(this);
	return pthis->using_heap() ? pthis->heap.nchars : pthis->sso_nchars();
}

void swap(str& a, str& b) {
	char tmp[sizeof(str)];
	std::memcpy(tmp, &a, sizeof(str));
	std::memcpy(&a, &b, sizeof(str));
	std::memcpy(&b, tmp, sizeof(str));
}

bool operator==(const str& a, const str& b) {
	return a.nbytes() == b.nbytes() && std::memcmp(a.data(), b.data(), a.nbytes()) == 0;
}

bool operator!=(const str& a, const str& b) {
	return !(a == b);
}

}
