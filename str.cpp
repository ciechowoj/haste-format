#include <haste/str.hpp>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cstdio>

namespace haste {

struct str_view_t {
	const char* data;
	size_t nbytes;
	size_t nchars;
};

str_view::str_view() {
	std::memset(this, 0, sizeof(str_view_t));
}

str_view::str_view(const char* that) {
	auto pthis = reinterpret_cast<str_view_t*>(this);
	pthis->data = that;
	pthis->nbytes = std::strlen(that);
	pthis->nchars = pthis->nbytes;
}

str_view::str_view(const char* begin, const char* end) {
	auto* pthis = reinterpret_cast<str_view_t*>(this);
	pthis->data = begin;
	pthis->nbytes = end - begin;
	pthis->nchars = pthis->nbytes;
}

const char* begin(const str_view& _this) {
	return reinterpret_cast<const str_view_t*>(&_this)->data;
}

const char* end(const str_view& _this) {
	const auto* pthis = reinterpret_cast<const str_view_t*>(&_this);
	return pthis->data + pthis->nbytes;
}

size_t nbytes(const str_view& _this) {
	return reinterpret_cast<const str_view_t*>(&_this)->nbytes;
}

size_t nchars(const str_view& _this) {
	return reinterpret_cast<const str_view_t*>(&_this)->nchars;
}

union str_t {
	struct heap_t {
		char* data;
		size_t nbytes;
		size_t nchars;
	private:
		size_t capacity;

		friend str_t;
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
		pthis->set_capacity(size);
		std::memcpy(pthis->heap.data, that, size + 1);
	}
	else {
		pthis->sso.nbytes = static_cast<unsigned char>(size);
		pthis->set_sso_nchars(size);
		std::memcpy(pthis->sso.data, that, size + 1);	
	}
}

str::str(const str_view& that) {
	ullong size = end(that) - begin(that);
	auto* pthis = reinterpret_cast<str_t*>(this);

	if (sso_max_size < size) {
		pthis->heap.data = static_cast<char*>(std::malloc(size + 1));
		pthis->heap.nbytes = size;
		pthis->heap.nchars = size;
		pthis->set_capacity(size);
		std::memcpy(pthis->heap.data, begin(that), size);
		pthis->heap.data[size] = 0;
	}
	else {
		pthis->sso.nbytes = static_cast<unsigned char>(size);
		pthis->set_sso_nchars(size);
		std::memcpy(pthis->sso.data, begin(that), size);
		pthis->sso.data[size] = 0;
	}

}

str::str(const str& that) {
	auto* pthis = reinterpret_cast<str_t*>(this);
	const auto* pthat = reinterpret_cast<const str_t*>(&that);

	if (pthat->using_heap()) {
		pthis->heap.data = static_cast<char*>(std::malloc(pthat->capacity() + 1));
		pthis->heap.nbytes = pthat->heap.nbytes;
		pthis->heap.nchars = pthat->heap.nchars;
		pthis->set_capacity(pthat->capacity());
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

str::operator str_view() const {
	const char* data = this -> data();
	return str_view(data, data + nbytes());
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

str unsafe_init(size_t nbytes, size_t nchars) {
	str_t result;
	
	if (sso_max_size < nbytes) {
		result.heap.data = static_cast<char*>(std::malloc(nbytes + 1));
		result.heap.nbytes = nbytes;
		result.heap.nchars = nchars;
		result.set_capacity(nbytes);
	}
	else {
		result.sso.nbytes = static_cast<unsigned char>(nbytes);
		result.set_sso_nchars(nchars);	
	}

	return reinterpret_cast<str&&>(result);
}

void unsafe_resize(str& _this, size_t nbytes, size_t nchars) {
	auto* pthis = reinterpret_cast<str_t*>(&_this);

	if (pthis->using_heap()) {
		size_t capacity = pthis->capacity();

		if (capacity < nbytes || nbytes < capacity * 3 / 2) {
			std::free(pthis->heap.data);
		}
		else {
			pthis->heap.nbytes = nbytes;
			pthis->heap.nchars = nchars;
			return;
		}
	}
	
	if (sso_max_size < nbytes) {
		pthis->heap.data = static_cast<char*>(std::malloc(nbytes + 1));
		pthis->heap.nbytes = nbytes;
		pthis->heap.nchars = nchars;
		pthis->set_capacity(nbytes);
	}
	else {
		pthis->sso.nbytes = static_cast<unsigned char>(nbytes);
		pthis->set_sso_nchars(nchars);	
	}	
}

char* unsafe_data(str& _this) {
	auto* pthis = reinterpret_cast<str_t*>(&_this);
	return pthis->using_heap() ? pthis->heap.data : pthis->sso.data;
}

str _concat(const str_view* s, size_t n) {
	size_t total_nbytes = 0;
	size_t total_nchars = 0;

	for (size_t i = 0; i < n; ++i) {
		total_nbytes += nbytes(s[i]);
		total_nchars += nchars(s[i]);
	}

	str result = std::move(unsafe_init(total_nbytes, total_nchars));
	char *ptr = unsafe_data(result);

	for (size_t i = 0; i < n; ++i) {
		std::memcpy(ptr, begin(s[i]), nbytes(s[i]));
		ptr += nbytes(s[i]);
	}

	*ptr = 0;

	return result;
}

}
