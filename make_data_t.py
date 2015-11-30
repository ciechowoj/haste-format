#!/usr/bin/python3

from itertools import *

KINDS = ['unorm', 'snorm', 'uint', 'sint', 'float']
PRECS = [8, 16, 32, 64]

def value(kind, prec, ndim):
	ikind = KINDS.index(kind)
	iprec = PRECS.index(prec)
	index = ikind * len(PRECS) + iprec

	return index << 16 | KINDS.index(kind) << 12 | iprec << 8 | (ndim - 1) << 10 | ((prec + 7) // 8 * ndim);

data_t_hpp = open("include/haste/data_t.hpp", "w+")
data_t_cpp = open("data_t.cpp", "w+")

data_t_hpp.write("#pragma once\n")
data_t_hpp.write("#include <cstddef>\n")
data_t_hpp.write("\n")
data_t_hpp.write("namespace haste {\n")
data_t_hpp.write("\n")
data_t_hpp.write("using std::size_t;\n")
data_t_hpp.write("\n")
data_t_hpp.write("enum class data_t {\n")

for kind in KINDS:
	for prec in PRECS:
		for d in range(1, 5):
			if kind != 'float' or prec != '8':
				v = value(kind, prec, d)
				data_t_hpp.write('\t{}{}x{} = 0x{:08x}u,\n'.format(kind, prec, d, v))

for kind in KINDS:
	for prec in PRECS:
		if kind != 'float' or prec != '8':
			v = value(kind, prec, 1) & 0xffff
			data_t_hpp.write('\t{}{} = 0x{:08x}u,\n'.format(kind, prec, v))		

data_t_hpp.write("};\n")
data_t_hpp.write("\n")

data_t_hpp.write("void datacpy(void* dst, const void* src, data_t dtype, data_t stype);\n")
data_t_hpp.write("\n")

data_t_hpp.write("inline size_t stride(data_t dtype) {\n")
data_t_hpp.write("\treturn size_t(dtype) & 0xffu;\n")
data_t_hpp.write("}\n")
data_t_hpp.write("\n")

ndim_func = """\
inline size_t ndim(data_t dtype) {
	return ((size_t(dtype) >> 10) & 0x3u) + 1;
}

"""

prec_func = """\
inline size_t prec(data_t dtype) {
	return 1u << (((size_t(dtype) >> 8) & 0x3u) + 3);
}

"""

subtype_func = """\
inline data_t subtype(data_t dtype) {
	return data_t((unsigned(dtype) & 0xf300u) | prec(dtype) / 8);
}

"""

data_t_hpp.write(ndim_func)
data_t_hpp.write(prec_func)
data_t_hpp.write(subtype_func)


data_t_hpp.write("data_t unorm8(size_t components);\n")

data_t_hpp.write("\n")
data_t_hpp.write("}\n")

data_t_cpp.write("#include <haste/data_t.hpp>\n")
data_t_cpp.write("#include <algorithm>\n")
data_t_cpp.write("#include <cstdint>\n")
data_t_cpp.write("#include <cstring>\n")
data_t_cpp.write("\n")
data_t_cpp.write("namespace haste {\n")
data_t_cpp.write("\n")
data_t_cpp.write("using namespace std;\n")
data_t_cpp.write("\n")

data_t_cpp.write("using float8_t = uint8_t;\n")
data_t_cpp.write("using float16_t = uint16_t;\n")
data_t_cpp.write("using float32_t = float;\n")
data_t_cpp.write("using float64_t = double;\n")
data_t_cpp.write("\n")
data_t_cpp.write("typedef void (*datacpy_t)(void*, const void*, size_t);\n")
data_t_cpp.write("\n")
data_t_cpp.write("inline size_t index(data_t dtype) {\n")
data_t_cpp.write("\treturn size_t(dtype) >> 16;\n")
data_t_cpp.write("}\n")
data_t_cpp.write("\n")


UNORM_MAX = {
	('unorm', 8) : 255,
	('unorm', 16) : 65535,
	('unorm', 32) : 2 ** 32 - 1,
	('unorm', 64) : 2 ** 64 - 1,
}

UNORM_MAX_INV = {
	('unorm', 8) : 1 / 255,
	('unorm', 16) : 1 / 65535,
	('unorm', 32) : 1 / (2 ** 32 - 1),
	('unorm', 64) : 1 / (2 ** 64 - 1),
}

def datacpy_name(dst, src):
	dstn = '{}{}'.format(dst[0], dst[1])
	srcn = '{}{}'.format(src[0], src[1])
	return "datacpy_{}_{}".format(dstn, srcn)

def conversion(dst, src):
	name = datacpy_name(dst, src)
	data_t_cpp.write("static void {}(void* dst, const void* src, size_t n) {{\n".format(name))		

	if dst == src:
		data_t_cpp.write("\t::memcpy(dst, src, {} * n);\n".format(dst[1] // 8))
	else:
		data_t_cpp.write("\tfor (size_t i = 0; i < n; ++i) {\n")
		
		if dst[0] == 'unorm':
			if src[0] == 'float':
				data_t_cpp.write("\t\t((uint{0}_t*)dst)[i] = uint{0}_t(((float{1}_t*)src)[i] * {2}u);\n".format(dst[1], src[1], UNORM_MAX[dst]))
		elif dst[0] == 'float':
			if src[0] == 'unorm':
				template = "\t\t((float{0}_t*)dst)[i] = float{0}_t(((uint{1}_t*)src)[i]) * {2};\n"
				k = ('{}' if dst[1] == 64 else '{}f').format(UNORM_MAX_INV[src])
				data_t_cpp.write(template.format(dst[1], src[1], k))
			elif src[0] == 'float':
				template = "\t\t((float{0}_t*)dst)[i] = float{0}_t(((float{1}_t*)src)[i]);\n"
				data_t_cpp.write(template.format(dst[1], src[1]))

		data_t_cpp.write("\t}\n")

	data_t_cpp.write("}\n\n")


for dst in product(KINDS, PRECS):
	for src in product(KINDS, PRECS):
		conversion(dst, src)

data_t_cpp.write("static datacpy_t datacpy_table[] = {\n")

for dst in product(KINDS, PRECS):
	for src in product(KINDS, PRECS):
		data_t_cpp.write("\t{},\n".format(datacpy_name(dst, src)))		

data_t_cpp.write("};\n")
data_t_cpp.write("\n")


data_t_cpp.write("void datacpy(void* dst, const void* src, data_t dtype, data_t stype) {\n")

SIZE = len(list(product(KINDS, PRECS)))

data_t_cpp.write("\tdatacpy_table[index(dtype) * {} + index(stype)](dst, src, min(ndim(dtype), ndim(stype)));\n".format(SIZE))

data_t_cpp.write("}\n")
data_t_cpp.write("\n")

data_t_cpp.write("data_t unorm8(size_t components) {\n")
data_t_cpp.write("\tswitch(components) {\n")
data_t_cpp.write("\t\tcase 1: return data_t::unorm8x1;\n")
data_t_cpp.write("\t\tcase 2: return data_t::unorm8x2;\n")
data_t_cpp.write("\t\tcase 3: return data_t::unorm8x3;\n")
data_t_cpp.write("\t\tcase 4: return data_t::unorm8x4;\n")
data_t_cpp.write("\t\tdefault: return data_t::unorm8x4;\n")
data_t_cpp.write("\t}\n")
data_t_cpp.write("}\n")


data_t_cpp.write("\n")
data_t_cpp.write("}\n")
