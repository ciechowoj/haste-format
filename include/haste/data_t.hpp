#pragma once
#include <cstddef>

namespace haste {

using std::size_t;

enum class data_t {
	unorm8x1 = 0x00000001u,
	unorm8x2 = 0x00000402u,
	unorm8x3 = 0x00000803u,
	unorm8x4 = 0x00000c04u,
	unorm16x1 = 0x00010102u,
	unorm16x2 = 0x00010504u,
	unorm16x3 = 0x00010906u,
	unorm16x4 = 0x00010d08u,
	unorm32x1 = 0x00020204u,
	unorm32x2 = 0x00020608u,
	unorm32x3 = 0x00020a0cu,
	unorm32x4 = 0x00020e10u,
	unorm64x1 = 0x00030308u,
	unorm64x2 = 0x00030710u,
	unorm64x3 = 0x00030b18u,
	unorm64x4 = 0x00030f20u,
	snorm8x1 = 0x00041001u,
	snorm8x2 = 0x00041402u,
	snorm8x3 = 0x00041803u,
	snorm8x4 = 0x00041c04u,
	snorm16x1 = 0x00051102u,
	snorm16x2 = 0x00051504u,
	snorm16x3 = 0x00051906u,
	snorm16x4 = 0x00051d08u,
	snorm32x1 = 0x00061204u,
	snorm32x2 = 0x00061608u,
	snorm32x3 = 0x00061a0cu,
	snorm32x4 = 0x00061e10u,
	snorm64x1 = 0x00071308u,
	snorm64x2 = 0x00071710u,
	snorm64x3 = 0x00071b18u,
	snorm64x4 = 0x00071f20u,
	uint8x1 = 0x00082001u,
	uint8x2 = 0x00082402u,
	uint8x3 = 0x00082803u,
	uint8x4 = 0x00082c04u,
	uint16x1 = 0x00092102u,
	uint16x2 = 0x00092504u,
	uint16x3 = 0x00092906u,
	uint16x4 = 0x00092d08u,
	uint32x1 = 0x000a2204u,
	uint32x2 = 0x000a2608u,
	uint32x3 = 0x000a2a0cu,
	uint32x4 = 0x000a2e10u,
	uint64x1 = 0x000b2308u,
	uint64x2 = 0x000b2710u,
	uint64x3 = 0x000b2b18u,
	uint64x4 = 0x000b2f20u,
	sint8x1 = 0x000c3001u,
	sint8x2 = 0x000c3402u,
	sint8x3 = 0x000c3803u,
	sint8x4 = 0x000c3c04u,
	sint16x1 = 0x000d3102u,
	sint16x2 = 0x000d3504u,
	sint16x3 = 0x000d3906u,
	sint16x4 = 0x000d3d08u,
	sint32x1 = 0x000e3204u,
	sint32x2 = 0x000e3608u,
	sint32x3 = 0x000e3a0cu,
	sint32x4 = 0x000e3e10u,
	sint64x1 = 0x000f3308u,
	sint64x2 = 0x000f3710u,
	sint64x3 = 0x000f3b18u,
	sint64x4 = 0x000f3f20u,
	float8x1 = 0x00104001u,
	float8x2 = 0x00104402u,
	float8x3 = 0x00104803u,
	float8x4 = 0x00104c04u,
	float16x1 = 0x00114102u,
	float16x2 = 0x00114504u,
	float16x3 = 0x00114906u,
	float16x4 = 0x00114d08u,
	float32x1 = 0x00124204u,
	float32x2 = 0x00124608u,
	float32x3 = 0x00124a0cu,
	float32x4 = 0x00124e10u,
	float64x1 = 0x00134308u,
	float64x2 = 0x00134710u,
	float64x3 = 0x00134b18u,
	float64x4 = 0x00134f20u,
	unorm8 = 0x00000001u,
	unorm16 = 0x00000102u,
	unorm32 = 0x00000204u,
	unorm64 = 0x00000308u,
	snorm8 = 0x00001001u,
	snorm16 = 0x00001102u,
	snorm32 = 0x00001204u,
	snorm64 = 0x00001308u,
	uint8 = 0x00002001u,
	uint16 = 0x00002102u,
	uint32 = 0x00002204u,
	uint64 = 0x00002308u,
	sint8 = 0x00003001u,
	sint16 = 0x00003102u,
	sint32 = 0x00003204u,
	sint64 = 0x00003308u,
	float8 = 0x00004001u,
	float16 = 0x00004102u,
	float32 = 0x00004204u,
	float64 = 0x00004308u,
};

void datacpy(void* dst, const void* src, data_t dtype, data_t stype);

inline size_t stride(data_t dtype) {
	return size_t(dtype) & 0xffu;
}

inline size_t ndim(data_t dtype) {
	return ((size_t(dtype) >> 10) & 0x3u) + 1;
}

inline size_t prec(data_t dtype) {
	return 1u << (((size_t(dtype) >> 8) & 0x3u) + 3);
}

inline data_t subtype(data_t dtype) {
	return data_t((unsigned(dtype) & 0xf300u) | prec(dtype) / 8);
}

data_t unorm8(size_t components);

}
