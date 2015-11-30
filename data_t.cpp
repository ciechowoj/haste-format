#include <haste/data_t.hpp>
#include <algorithm>
#include <cstdint>
#include <cstring>

namespace haste {

using namespace std;

using float8_t = uint8_t;
using float16_t = uint16_t;
using float32_t = float;
using float64_t = double;

typedef void (*datacpy_t)(void*, const void*, size_t);

inline size_t index(data_t dtype) {
	return size_t(dtype) >> 16;
}

static void datacpy_unorm8_unorm8(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 1 * n);
}

static void datacpy_unorm8_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm8_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint8_t*)dst)[i] = uint8_t(((float8_t*)src)[i] * 255u);
	}
}

static void datacpy_unorm8_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint8_t*)dst)[i] = uint8_t(((float16_t*)src)[i] * 255u);
	}
}

static void datacpy_unorm8_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint8_t*)dst)[i] = uint8_t(((float32_t*)src)[i] * 255u);
	}
}

static void datacpy_unorm8_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint8_t*)dst)[i] = uint8_t(((float64_t*)src)[i] * 255u);
	}
}

static void datacpy_unorm16_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_unorm16(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 2 * n);
}

static void datacpy_unorm16_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm16_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint16_t*)dst)[i] = uint16_t(((float8_t*)src)[i] * 65535u);
	}
}

static void datacpy_unorm16_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint16_t*)dst)[i] = uint16_t(((float16_t*)src)[i] * 65535u);
	}
}

static void datacpy_unorm16_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint16_t*)dst)[i] = uint16_t(((float32_t*)src)[i] * 65535u);
	}
}

static void datacpy_unorm16_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint16_t*)dst)[i] = uint16_t(((float64_t*)src)[i] * 65535u);
	}
}

static void datacpy_unorm32_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_unorm32(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 4 * n);
}

static void datacpy_unorm32_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm32_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint32_t*)dst)[i] = uint32_t(((float8_t*)src)[i] * 4294967295u);
	}
}

static void datacpy_unorm32_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint32_t*)dst)[i] = uint32_t(((float16_t*)src)[i] * 4294967295u);
	}
}

static void datacpy_unorm32_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint32_t*)dst)[i] = uint32_t(((float32_t*)src)[i] * 4294967295u);
	}
}

static void datacpy_unorm32_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint32_t*)dst)[i] = uint32_t(((float64_t*)src)[i] * 4294967295u);
	}
}

static void datacpy_unorm64_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_unorm64(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 8 * n);
}

static void datacpy_unorm64_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_unorm64_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint64_t*)dst)[i] = uint64_t(((float8_t*)src)[i] * 18446744073709551615u);
	}
}

static void datacpy_unorm64_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint64_t*)dst)[i] = uint64_t(((float16_t*)src)[i] * 18446744073709551615u);
	}
}

static void datacpy_unorm64_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint64_t*)dst)[i] = uint64_t(((float32_t*)src)[i] * 18446744073709551615u);
	}
}

static void datacpy_unorm64_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((uint64_t*)dst)[i] = uint64_t(((float64_t*)src)[i] * 18446744073709551615u);
	}
}

static void datacpy_snorm8_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_snorm8(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 1 * n);
}

static void datacpy_snorm8_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm8_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_snorm16(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 2 * n);
}

static void datacpy_snorm16_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm16_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_snorm32(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 4 * n);
}

static void datacpy_snorm32_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm32_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_snorm64(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 8 * n);
}

static void datacpy_snorm64_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_snorm64_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_uint8(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 1 * n);
}

static void datacpy_uint8_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint8_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_uint16(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 2 * n);
}

static void datacpy_uint16_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint16_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_uint32(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 4 * n);
}

static void datacpy_uint32_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint32_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_uint64(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 8 * n);
}

static void datacpy_uint64_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_uint64_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_sint8(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 1 * n);
}

static void datacpy_sint8_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint8_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_sint16(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 2 * n);
}

static void datacpy_sint16_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint16_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_sint32(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 4 * n);
}

static void datacpy_sint32_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint32_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_sint64(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 8 * n);
}

static void datacpy_sint64_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_sint64_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float8_t*)dst)[i] = float8_t(((uint8_t*)src)[i]) * 0.00392156862745098f;
	}
}

static void datacpy_float8_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float8_t*)dst)[i] = float8_t(((uint16_t*)src)[i]) * 1.5259021896696422e-05f;
	}
}

static void datacpy_float8_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float8_t*)dst)[i] = float8_t(((uint32_t*)src)[i]) * 2.3283064370807974e-10f;
	}
}

static void datacpy_float8_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float8_t*)dst)[i] = float8_t(((uint64_t*)src)[i]) * 5.421010862427522e-20f;
	}
}

static void datacpy_float8_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float8_float8(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 1 * n);
}

static void datacpy_float8_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float8_t*)dst)[i] = float8_t(((float16_t*)src)[i]);
	}
}

static void datacpy_float8_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float8_t*)dst)[i] = float8_t(((float32_t*)src)[i]);
	}
}

static void datacpy_float8_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float8_t*)dst)[i] = float8_t(((float64_t*)src)[i]);
	}
}

static void datacpy_float16_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float16_t*)dst)[i] = float16_t(((uint8_t*)src)[i]) * 0.00392156862745098f;
	}
}

static void datacpy_float16_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float16_t*)dst)[i] = float16_t(((uint16_t*)src)[i]) * 1.5259021896696422e-05f;
	}
}

static void datacpy_float16_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float16_t*)dst)[i] = float16_t(((uint32_t*)src)[i]) * 2.3283064370807974e-10f;
	}
}

static void datacpy_float16_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float16_t*)dst)[i] = float16_t(((uint64_t*)src)[i]) * 5.421010862427522e-20f;
	}
}

static void datacpy_float16_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float16_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float16_t*)dst)[i] = float16_t(((float8_t*)src)[i]);
	}
}

static void datacpy_float16_float16(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 2 * n);
}

static void datacpy_float16_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float16_t*)dst)[i] = float16_t(((float32_t*)src)[i]);
	}
}

static void datacpy_float16_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float16_t*)dst)[i] = float16_t(((float64_t*)src)[i]);
	}
}

static void datacpy_float32_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float32_t*)dst)[i] = float32_t(((uint8_t*)src)[i]) * 0.00392156862745098f;
	}
}

static void datacpy_float32_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float32_t*)dst)[i] = float32_t(((uint16_t*)src)[i]) * 1.5259021896696422e-05f;
	}
}

static void datacpy_float32_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float32_t*)dst)[i] = float32_t(((uint32_t*)src)[i]) * 2.3283064370807974e-10f;
	}
}

static void datacpy_float32_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float32_t*)dst)[i] = float32_t(((uint64_t*)src)[i]) * 5.421010862427522e-20f;
	}
}

static void datacpy_float32_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float32_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float32_t*)dst)[i] = float32_t(((float8_t*)src)[i]);
	}
}

static void datacpy_float32_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float32_t*)dst)[i] = float32_t(((float16_t*)src)[i]);
	}
}

static void datacpy_float32_float32(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 4 * n);
}

static void datacpy_float32_float64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float32_t*)dst)[i] = float32_t(((float64_t*)src)[i]);
	}
}

static void datacpy_float64_unorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float64_t*)dst)[i] = float64_t(((uint8_t*)src)[i]) * 0.00392156862745098;
	}
}

static void datacpy_float64_unorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float64_t*)dst)[i] = float64_t(((uint16_t*)src)[i]) * 1.5259021896696422e-05;
	}
}

static void datacpy_float64_unorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float64_t*)dst)[i] = float64_t(((uint32_t*)src)[i]) * 2.3283064370807974e-10;
	}
}

static void datacpy_float64_unorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float64_t*)dst)[i] = float64_t(((uint64_t*)src)[i]) * 5.421010862427522e-20;
	}
}

static void datacpy_float64_snorm8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_snorm16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_snorm32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_snorm64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_uint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_uint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_uint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_uint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_sint8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_sint16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_sint32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_sint64(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
	}
}

static void datacpy_float64_float8(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float64_t*)dst)[i] = float64_t(((float8_t*)src)[i]);
	}
}

static void datacpy_float64_float16(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float64_t*)dst)[i] = float64_t(((float16_t*)src)[i]);
	}
}

static void datacpy_float64_float32(void* dst, const void* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		((float64_t*)dst)[i] = float64_t(((float32_t*)src)[i]);
	}
}

static void datacpy_float64_float64(void* dst, const void* src, size_t n) {
	::memcpy(dst, src, 8 * n);
}

static datacpy_t datacpy_table[] = {
	datacpy_unorm8_unorm8,
	datacpy_unorm8_unorm16,
	datacpy_unorm8_unorm32,
	datacpy_unorm8_unorm64,
	datacpy_unorm8_snorm8,
	datacpy_unorm8_snorm16,
	datacpy_unorm8_snorm32,
	datacpy_unorm8_snorm64,
	datacpy_unorm8_uint8,
	datacpy_unorm8_uint16,
	datacpy_unorm8_uint32,
	datacpy_unorm8_uint64,
	datacpy_unorm8_sint8,
	datacpy_unorm8_sint16,
	datacpy_unorm8_sint32,
	datacpy_unorm8_sint64,
	datacpy_unorm8_float8,
	datacpy_unorm8_float16,
	datacpy_unorm8_float32,
	datacpy_unorm8_float64,
	datacpy_unorm16_unorm8,
	datacpy_unorm16_unorm16,
	datacpy_unorm16_unorm32,
	datacpy_unorm16_unorm64,
	datacpy_unorm16_snorm8,
	datacpy_unorm16_snorm16,
	datacpy_unorm16_snorm32,
	datacpy_unorm16_snorm64,
	datacpy_unorm16_uint8,
	datacpy_unorm16_uint16,
	datacpy_unorm16_uint32,
	datacpy_unorm16_uint64,
	datacpy_unorm16_sint8,
	datacpy_unorm16_sint16,
	datacpy_unorm16_sint32,
	datacpy_unorm16_sint64,
	datacpy_unorm16_float8,
	datacpy_unorm16_float16,
	datacpy_unorm16_float32,
	datacpy_unorm16_float64,
	datacpy_unorm32_unorm8,
	datacpy_unorm32_unorm16,
	datacpy_unorm32_unorm32,
	datacpy_unorm32_unorm64,
	datacpy_unorm32_snorm8,
	datacpy_unorm32_snorm16,
	datacpy_unorm32_snorm32,
	datacpy_unorm32_snorm64,
	datacpy_unorm32_uint8,
	datacpy_unorm32_uint16,
	datacpy_unorm32_uint32,
	datacpy_unorm32_uint64,
	datacpy_unorm32_sint8,
	datacpy_unorm32_sint16,
	datacpy_unorm32_sint32,
	datacpy_unorm32_sint64,
	datacpy_unorm32_float8,
	datacpy_unorm32_float16,
	datacpy_unorm32_float32,
	datacpy_unorm32_float64,
	datacpy_unorm64_unorm8,
	datacpy_unorm64_unorm16,
	datacpy_unorm64_unorm32,
	datacpy_unorm64_unorm64,
	datacpy_unorm64_snorm8,
	datacpy_unorm64_snorm16,
	datacpy_unorm64_snorm32,
	datacpy_unorm64_snorm64,
	datacpy_unorm64_uint8,
	datacpy_unorm64_uint16,
	datacpy_unorm64_uint32,
	datacpy_unorm64_uint64,
	datacpy_unorm64_sint8,
	datacpy_unorm64_sint16,
	datacpy_unorm64_sint32,
	datacpy_unorm64_sint64,
	datacpy_unorm64_float8,
	datacpy_unorm64_float16,
	datacpy_unorm64_float32,
	datacpy_unorm64_float64,
	datacpy_snorm8_unorm8,
	datacpy_snorm8_unorm16,
	datacpy_snorm8_unorm32,
	datacpy_snorm8_unorm64,
	datacpy_snorm8_snorm8,
	datacpy_snorm8_snorm16,
	datacpy_snorm8_snorm32,
	datacpy_snorm8_snorm64,
	datacpy_snorm8_uint8,
	datacpy_snorm8_uint16,
	datacpy_snorm8_uint32,
	datacpy_snorm8_uint64,
	datacpy_snorm8_sint8,
	datacpy_snorm8_sint16,
	datacpy_snorm8_sint32,
	datacpy_snorm8_sint64,
	datacpy_snorm8_float8,
	datacpy_snorm8_float16,
	datacpy_snorm8_float32,
	datacpy_snorm8_float64,
	datacpy_snorm16_unorm8,
	datacpy_snorm16_unorm16,
	datacpy_snorm16_unorm32,
	datacpy_snorm16_unorm64,
	datacpy_snorm16_snorm8,
	datacpy_snorm16_snorm16,
	datacpy_snorm16_snorm32,
	datacpy_snorm16_snorm64,
	datacpy_snorm16_uint8,
	datacpy_snorm16_uint16,
	datacpy_snorm16_uint32,
	datacpy_snorm16_uint64,
	datacpy_snorm16_sint8,
	datacpy_snorm16_sint16,
	datacpy_snorm16_sint32,
	datacpy_snorm16_sint64,
	datacpy_snorm16_float8,
	datacpy_snorm16_float16,
	datacpy_snorm16_float32,
	datacpy_snorm16_float64,
	datacpy_snorm32_unorm8,
	datacpy_snorm32_unorm16,
	datacpy_snorm32_unorm32,
	datacpy_snorm32_unorm64,
	datacpy_snorm32_snorm8,
	datacpy_snorm32_snorm16,
	datacpy_snorm32_snorm32,
	datacpy_snorm32_snorm64,
	datacpy_snorm32_uint8,
	datacpy_snorm32_uint16,
	datacpy_snorm32_uint32,
	datacpy_snorm32_uint64,
	datacpy_snorm32_sint8,
	datacpy_snorm32_sint16,
	datacpy_snorm32_sint32,
	datacpy_snorm32_sint64,
	datacpy_snorm32_float8,
	datacpy_snorm32_float16,
	datacpy_snorm32_float32,
	datacpy_snorm32_float64,
	datacpy_snorm64_unorm8,
	datacpy_snorm64_unorm16,
	datacpy_snorm64_unorm32,
	datacpy_snorm64_unorm64,
	datacpy_snorm64_snorm8,
	datacpy_snorm64_snorm16,
	datacpy_snorm64_snorm32,
	datacpy_snorm64_snorm64,
	datacpy_snorm64_uint8,
	datacpy_snorm64_uint16,
	datacpy_snorm64_uint32,
	datacpy_snorm64_uint64,
	datacpy_snorm64_sint8,
	datacpy_snorm64_sint16,
	datacpy_snorm64_sint32,
	datacpy_snorm64_sint64,
	datacpy_snorm64_float8,
	datacpy_snorm64_float16,
	datacpy_snorm64_float32,
	datacpy_snorm64_float64,
	datacpy_uint8_unorm8,
	datacpy_uint8_unorm16,
	datacpy_uint8_unorm32,
	datacpy_uint8_unorm64,
	datacpy_uint8_snorm8,
	datacpy_uint8_snorm16,
	datacpy_uint8_snorm32,
	datacpy_uint8_snorm64,
	datacpy_uint8_uint8,
	datacpy_uint8_uint16,
	datacpy_uint8_uint32,
	datacpy_uint8_uint64,
	datacpy_uint8_sint8,
	datacpy_uint8_sint16,
	datacpy_uint8_sint32,
	datacpy_uint8_sint64,
	datacpy_uint8_float8,
	datacpy_uint8_float16,
	datacpy_uint8_float32,
	datacpy_uint8_float64,
	datacpy_uint16_unorm8,
	datacpy_uint16_unorm16,
	datacpy_uint16_unorm32,
	datacpy_uint16_unorm64,
	datacpy_uint16_snorm8,
	datacpy_uint16_snorm16,
	datacpy_uint16_snorm32,
	datacpy_uint16_snorm64,
	datacpy_uint16_uint8,
	datacpy_uint16_uint16,
	datacpy_uint16_uint32,
	datacpy_uint16_uint64,
	datacpy_uint16_sint8,
	datacpy_uint16_sint16,
	datacpy_uint16_sint32,
	datacpy_uint16_sint64,
	datacpy_uint16_float8,
	datacpy_uint16_float16,
	datacpy_uint16_float32,
	datacpy_uint16_float64,
	datacpy_uint32_unorm8,
	datacpy_uint32_unorm16,
	datacpy_uint32_unorm32,
	datacpy_uint32_unorm64,
	datacpy_uint32_snorm8,
	datacpy_uint32_snorm16,
	datacpy_uint32_snorm32,
	datacpy_uint32_snorm64,
	datacpy_uint32_uint8,
	datacpy_uint32_uint16,
	datacpy_uint32_uint32,
	datacpy_uint32_uint64,
	datacpy_uint32_sint8,
	datacpy_uint32_sint16,
	datacpy_uint32_sint32,
	datacpy_uint32_sint64,
	datacpy_uint32_float8,
	datacpy_uint32_float16,
	datacpy_uint32_float32,
	datacpy_uint32_float64,
	datacpy_uint64_unorm8,
	datacpy_uint64_unorm16,
	datacpy_uint64_unorm32,
	datacpy_uint64_unorm64,
	datacpy_uint64_snorm8,
	datacpy_uint64_snorm16,
	datacpy_uint64_snorm32,
	datacpy_uint64_snorm64,
	datacpy_uint64_uint8,
	datacpy_uint64_uint16,
	datacpy_uint64_uint32,
	datacpy_uint64_uint64,
	datacpy_uint64_sint8,
	datacpy_uint64_sint16,
	datacpy_uint64_sint32,
	datacpy_uint64_sint64,
	datacpy_uint64_float8,
	datacpy_uint64_float16,
	datacpy_uint64_float32,
	datacpy_uint64_float64,
	datacpy_sint8_unorm8,
	datacpy_sint8_unorm16,
	datacpy_sint8_unorm32,
	datacpy_sint8_unorm64,
	datacpy_sint8_snorm8,
	datacpy_sint8_snorm16,
	datacpy_sint8_snorm32,
	datacpy_sint8_snorm64,
	datacpy_sint8_uint8,
	datacpy_sint8_uint16,
	datacpy_sint8_uint32,
	datacpy_sint8_uint64,
	datacpy_sint8_sint8,
	datacpy_sint8_sint16,
	datacpy_sint8_sint32,
	datacpy_sint8_sint64,
	datacpy_sint8_float8,
	datacpy_sint8_float16,
	datacpy_sint8_float32,
	datacpy_sint8_float64,
	datacpy_sint16_unorm8,
	datacpy_sint16_unorm16,
	datacpy_sint16_unorm32,
	datacpy_sint16_unorm64,
	datacpy_sint16_snorm8,
	datacpy_sint16_snorm16,
	datacpy_sint16_snorm32,
	datacpy_sint16_snorm64,
	datacpy_sint16_uint8,
	datacpy_sint16_uint16,
	datacpy_sint16_uint32,
	datacpy_sint16_uint64,
	datacpy_sint16_sint8,
	datacpy_sint16_sint16,
	datacpy_sint16_sint32,
	datacpy_sint16_sint64,
	datacpy_sint16_float8,
	datacpy_sint16_float16,
	datacpy_sint16_float32,
	datacpy_sint16_float64,
	datacpy_sint32_unorm8,
	datacpy_sint32_unorm16,
	datacpy_sint32_unorm32,
	datacpy_sint32_unorm64,
	datacpy_sint32_snorm8,
	datacpy_sint32_snorm16,
	datacpy_sint32_snorm32,
	datacpy_sint32_snorm64,
	datacpy_sint32_uint8,
	datacpy_sint32_uint16,
	datacpy_sint32_uint32,
	datacpy_sint32_uint64,
	datacpy_sint32_sint8,
	datacpy_sint32_sint16,
	datacpy_sint32_sint32,
	datacpy_sint32_sint64,
	datacpy_sint32_float8,
	datacpy_sint32_float16,
	datacpy_sint32_float32,
	datacpy_sint32_float64,
	datacpy_sint64_unorm8,
	datacpy_sint64_unorm16,
	datacpy_sint64_unorm32,
	datacpy_sint64_unorm64,
	datacpy_sint64_snorm8,
	datacpy_sint64_snorm16,
	datacpy_sint64_snorm32,
	datacpy_sint64_snorm64,
	datacpy_sint64_uint8,
	datacpy_sint64_uint16,
	datacpy_sint64_uint32,
	datacpy_sint64_uint64,
	datacpy_sint64_sint8,
	datacpy_sint64_sint16,
	datacpy_sint64_sint32,
	datacpy_sint64_sint64,
	datacpy_sint64_float8,
	datacpy_sint64_float16,
	datacpy_sint64_float32,
	datacpy_sint64_float64,
	datacpy_float8_unorm8,
	datacpy_float8_unorm16,
	datacpy_float8_unorm32,
	datacpy_float8_unorm64,
	datacpy_float8_snorm8,
	datacpy_float8_snorm16,
	datacpy_float8_snorm32,
	datacpy_float8_snorm64,
	datacpy_float8_uint8,
	datacpy_float8_uint16,
	datacpy_float8_uint32,
	datacpy_float8_uint64,
	datacpy_float8_sint8,
	datacpy_float8_sint16,
	datacpy_float8_sint32,
	datacpy_float8_sint64,
	datacpy_float8_float8,
	datacpy_float8_float16,
	datacpy_float8_float32,
	datacpy_float8_float64,
	datacpy_float16_unorm8,
	datacpy_float16_unorm16,
	datacpy_float16_unorm32,
	datacpy_float16_unorm64,
	datacpy_float16_snorm8,
	datacpy_float16_snorm16,
	datacpy_float16_snorm32,
	datacpy_float16_snorm64,
	datacpy_float16_uint8,
	datacpy_float16_uint16,
	datacpy_float16_uint32,
	datacpy_float16_uint64,
	datacpy_float16_sint8,
	datacpy_float16_sint16,
	datacpy_float16_sint32,
	datacpy_float16_sint64,
	datacpy_float16_float8,
	datacpy_float16_float16,
	datacpy_float16_float32,
	datacpy_float16_float64,
	datacpy_float32_unorm8,
	datacpy_float32_unorm16,
	datacpy_float32_unorm32,
	datacpy_float32_unorm64,
	datacpy_float32_snorm8,
	datacpy_float32_snorm16,
	datacpy_float32_snorm32,
	datacpy_float32_snorm64,
	datacpy_float32_uint8,
	datacpy_float32_uint16,
	datacpy_float32_uint32,
	datacpy_float32_uint64,
	datacpy_float32_sint8,
	datacpy_float32_sint16,
	datacpy_float32_sint32,
	datacpy_float32_sint64,
	datacpy_float32_float8,
	datacpy_float32_float16,
	datacpy_float32_float32,
	datacpy_float32_float64,
	datacpy_float64_unorm8,
	datacpy_float64_unorm16,
	datacpy_float64_unorm32,
	datacpy_float64_unorm64,
	datacpy_float64_snorm8,
	datacpy_float64_snorm16,
	datacpy_float64_snorm32,
	datacpy_float64_snorm64,
	datacpy_float64_uint8,
	datacpy_float64_uint16,
	datacpy_float64_uint32,
	datacpy_float64_uint64,
	datacpy_float64_sint8,
	datacpy_float64_sint16,
	datacpy_float64_sint32,
	datacpy_float64_sint64,
	datacpy_float64_float8,
	datacpy_float64_float16,
	datacpy_float64_float32,
	datacpy_float64_float64,
};

void datacpy(void* dst, const void* src, data_t dtype, data_t stype) {
	datacpy_table[index(dtype) * 20 + index(stype)](dst, src, min(ndim(dtype), ndim(stype)));
}

data_t unorm8(size_t components) {
	switch(components) {
		case 1: return data_t::unorm8x1;
		case 2: return data_t::unorm8x2;
		case 3: return data_t::unorm8x3;
		case 4: return data_t::unorm8x4;
		default: return data_t::unorm8x4;
	}
}

}
