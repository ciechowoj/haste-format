#pragma once
#include <cstddef>

namespace haste {
namespace detail {

using std::size_t;

union str_t {
	struct heap_t {
		char* data;
		size_t size;
		size_t capacity;
		size_t padding;
	} heap;

	struct sso_t {
		char data[sizeof(heap_t) - 1];
		unsigned char size;
	} sso;
};

void init(str_t* x);
void init_copy(str_t* x, const str_t* s);
void init_move(str_t* x, str_t* s);

void clean(str_t* x);
void swap(str_t* x, str_t* y);

char* data(str_t* x);
const char* data(const str_t* x);

size_t nbytes(const str_t* x);
size_t capacity(const str_t* x);

void replace(str_t* x, size_t i, size_t n, const char* a, const char* b);
void substr(str_t* x, const str_t* s, size_t i, size_t n);
void substr(str_t* x, size_t i, size_t n);

}
}
