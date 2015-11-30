#include <haste/image.hpp>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <png.h>
#include <jpeglib.h>

namespace haste {

using namespace std;
using namespace glm;

image::image() { }

image::image(size_t width, size_t height, data_t dtype) 
	: image() {
	size_t shape[] = { height, width };
	_array = array::empty(2, shape, dtype);
}

image::image(const image& that) 
	: _array(that._array) {
}

image::image(image&& that) 
	: _array(std::move(that._array)) {
}

image::~image() {
}

image::image(const array& that) 
	: _array(that) {
}

image::image(array&& that)
	: _array(std::move(that)) {
}

image& image::operator=(const image& that) {
	_array = that._array;
	return *this;
}

image& image::operator=(image&& that) {
	_array = std::move(that._array);
	return *this;
}

image::ubyte* image::data() {
	return _array.data();
}

const image::ubyte* image::data() const {
	return _array.data();
}

image::ubyte* image::data(size_t x, size_t y) {
	return _data(x, y);
}

const image::ubyte* image::data(size_t x, size_t y) const {
	return _data(x, y);
}

size_t image::ndim() const {
	return _array.ndim();
}

size_t image::nbytes() const {
	return _array.nbytes();
}

size_t image::shape(size_t i) const {
	return _array.shape(i);
}

size_t image::stride(size_t i) const {
	return _array.stride(i);
}

data_t image::dtype() const {
	return _array.dtype();	
}

size_t image::width() const {
	return shape(ndim() - 1);
}

size_t image::height() const {
	return shape(ndim() - 2);
}

const dvec4 at(const image& self, size_t x, size_t y) {
	dvec4 result;
	datacpy((image::ubyte*)&result, self._data(x, y), data_t::float64x4, self._array.dtype());
	return result;
}

void set_at(image& self, size_t x, size_t y, const dvec4& value) {
	datacpy(self._data(x, y), (const image::ubyte*)&value, self._array.dtype(), data_t::float64x4);
}

image::ubyte* image::_data(size_t x, size_t y) {
	const auto yoffset = _array.stride(_array.ndim() - 2) * y;
	const auto xoffset =  haste::stride(_array.dtype()) * x;
	return _array.data() + yoffset + xoffset;
}

const image::ubyte* image::_data(size_t x, size_t y) const {
 	const auto yoffset = _array.stride(_array.ndim() - 2) * y;
	const auto xoffset =  haste::stride(_array.dtype()) * x;
	return _array.data() + yoffset + xoffset;
}

image load_jpg(const string& path) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);

	FILE* file = fopen(path.c_str(), "rb");

	if (!file) {
		// ERRORS
	}

	jpeg_stdio_src(&cinfo, file);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);

	size_t shape[] = { cinfo.output_height, cinfo.output_width };

	auto result = array::empty(2, shape, unorm8(cinfo.output_components));
	auto stride = result.stride(-2);

	for (JDIMENSION i = 0; i < cinfo.output_height; ++i) {
		array::ubyte* scanline = result.data() + i * stride;
		jpeg_read_scanlines(&cinfo, &scanline, 1);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(file);

	return std::move(result);
}


image load_png(const string& path) {
	static const size_t bytes_to_check = 8;

	FILE *file = fopen(path.c_str(), "rb");	

	if (!file) {
		throw std::runtime_error("Cannot open '" + path + "'.");
	}

	png_byte buffer[bytes_to_check];

	if (fread(buffer, 1, bytes_to_check, file) != bytes_to_check) {
		fclose(file);
		throw std::runtime_error("Cannot read '" + path + "'.");
	}

	if (png_sig_cmp(buffer, 0, bytes_to_check) != 0)
	{
		fclose(file);
		throw std::runtime_error("'" + path + "' is not a png.");
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	if (png_ptr == nullptr) {
		fclose(file);
		throw std::runtime_error("Cannot create png_struct (" + path + ").");
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);

	if (info_ptr == nullptr) {
		png_destroy_read_struct(&png_ptr, nullptr, nullptr);
		fclose(file);
		throw std::runtime_error("Cannot create png_info (" + path + ").");
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		fclose(file);
		throw std::runtime_error("libpng error (" + path + ").");
	}

	png_init_io(png_ptr, file);
	png_set_sig_bytes(png_ptr, bytes_to_check);
	
	png_read_info(png_ptr, info_ptr);

	int width = png_get_image_width(png_ptr, info_ptr);
	int height = png_get_image_height(png_ptr, info_ptr);
	int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	int color_type = png_get_color_type(png_ptr, info_ptr);

	if (color_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}

	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_gray_1_2_4_to_8(png_ptr);
	}

	if (bit_depth == 16) {
		png_set_strip_16(png_ptr);
	}

	if (color_type & PNG_COLOR_MASK_ALPHA) {
		png_set_strip_alpha(png_ptr);
	}

	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
		png_set_gray_to_rgb(png_ptr);
	}
			
	double gamma = 1.0;
	
	if (png_get_gAMA(png_ptr, info_ptr, &gamma)) {
		png_set_gamma(png_ptr, 1.0, gamma);
	}
	else {
		png_set_gamma(png_ptr, 1.0, 1.0);
	}	

	auto result = make_image(width, height, data_t::unorm8x3);
	auto stride = result.stride(0);

	png_bytep* row_pointers = static_cast<png_bytep*>(::malloc(height * sizeof(png_bytep)));

	for (int i = 0; i < height; ++i) {
		row_pointers[i] = static_cast<png_bytep>(result.data()) + stride * i;
	}

	png_read_image(png_ptr, row_pointers);

	::free(row_pointers);
	
	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	fclose(file);

	return result;
}

void save_png(const image& image, const string& path) {
	FILE* file = fopen(path.c_str(), "wb");

	if (!file) {
		throw std::runtime_error("Cannot open '" + path + "'.");
	}

	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

	if (png_ptr == nullptr) {
		fclose(file);
		throw std::runtime_error("Cannot create png_struct (" + path + ").");
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);

	if (info_ptr == nullptr) {
		png_destroy_write_struct(&png_ptr, nullptr);
		fclose(file);
		throw std::runtime_error("Cannot create png_info (" + path + ").");
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(file);
		throw std::runtime_error("libpng error (" + path + ").");
	}

	png_init_io(png_ptr, file);

	int color_type = 0;

	switch (image.stride(1)) {
		case 1: color_type = PNG_COLOR_TYPE_GRAY; break;
		case 2: color_type = PNG_COLOR_TYPE_GRAY_ALPHA; break;
		case 3: color_type = PNG_COLOR_TYPE_RGB; break;
		case 4: color_type = PNG_COLOR_TYPE_RGB_ALPHA; break;
	}

	png_set_IHDR(
		png_ptr, 
		info_ptr, 
		image.width(), 
		image.height(), 
		8, 
		color_type,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);

	png_set_gAMA(
		png_ptr, 
		info_ptr, 
		1.0);

	const png_byte** row_pointers = static_cast<const png_byte**>(::malloc(image.height() * sizeof(png_bytep)));
	const size_t stride = image.stride(0);

	for (size_t y = 0; y < image.height(); ++y) {
		row_pointers[y] = reinterpret_cast<const png_byte*>(image.data()) + y * stride;
	}

	png_set_rows(png_ptr, info_ptr, const_cast<png_bytepp>(row_pointers));

	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_SWAP_ENDIAN, nullptr);

	::free(row_pointers);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(file);
}

image make_image(size_t width, size_t height, data_t dtype) {
	return image(width, height, dtype);
}

image make_image(size_t width, size_t height, data_t dtype, double value) {
	image result = make_image(width, height, dtype);

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			set_at(result, x, y, dvec4(value));
		}
	}

	return result;
}

void mul(image& out, dvec4 a) {
	size_t width = out.width();
	size_t height = out.height();

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			set_at(out, x, y, at(out, x, y) * a);
		}
	}
}

void mad(image& out, const image& a, dvec4 b) {
	size_t width = out.width();
	size_t height = out.height();

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			set_at(out, x, y, at(out, x, y) * (dvec4(1.0) + b));
		}
	}	
}

void clamp(image& out, double a, double b) {
	size_t width = out.width();
	size_t height = out.height();

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			set_at(out, x, y, clamp(at(out, x, y), a, b));
		}
	}
}

image conv_image(const image& src, data_t dtype) {
	const size_t width = src.width();
	const size_t height = src.height();

	image result = make_image(width, height, dtype);

	for (size_t y = 0; y < height; ++y) {
		for (size_t x = 0; x < width; ++x) {
			set_at(result, x, y, at(src, x, y));
		}
	}

	return result;
}

}

#include <ImfOutputFile.h>
#include <ImfInputFile.h>
#include <ImfChannelList.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>

namespace haste {

using namespace Imf;

image load_exr(const string& path) {
	InputFile file(path.c_str());

	Imath::Box2i window = file.header().dataWindow();

	int width = window.max.x - window.min.x + 1;
	int height = window.max.y - window.min.y + 1;

	image result = make_image(width, height, data_t::float32x3);

	size_t pixel = stride(result.dtype());
	size_t stride = result.stride(0);
	char* data = (char*)result.data();

	auto R = Slice(Imf::FLOAT, data + sizeof(float) * 0, pixel, stride);
	auto G = Slice(Imf::FLOAT, data + sizeof(float) * 1, pixel, stride);
	auto B = Slice(Imf::FLOAT, data + sizeof(float) * 2, pixel, stride);

	FrameBuffer framebuffer;
	framebuffer.insert("R", R);
	framebuffer.insert("G", G);
	framebuffer.insert("B", B);

	file.setFrameBuffer(framebuffer);
	file.readPixels(window.min.y, window.max.y);

	return result;
}


/*void save_image_exr(const image3xF32& image, const string& path) {
	image3xF32 temp = image;
	int width = image.width();
	int height = image.height();
	char* data = static_cast<char*>(temp.data());

	Header header (width, height);
	header.channels().insert ("R", Channel (Imf::FLOAT));
	header.channels().insert ("G", Channel (Imf::FLOAT));
	header.channels().insert ("B", Channel (Imf::FLOAT));

	OutputFile file (path.c_str(), header);

	FrameBuffer framebuffer;

	auto R = Slice(Imf::FLOAT, data + sizeof(float) * 0, sizeof(vec3), image.wstride());
	auto G = Slice(Imf::FLOAT, data + sizeof(float) * 1, sizeof(vec3), image.wstride());
	auto B = Slice(Imf::FLOAT, data + sizeof(float) * 2, sizeof(vec3), image.wstride());

	framebuffer.insert("R", R);
	framebuffer.insert("G", G);
	framebuffer.insert("B", B);

	file.setFrameBuffer(framebuffer);
	file.writePixels(height);
}*/
/*
void save_image(const image3xF32& image, const string& path) {
	const vec3 gamma = 1.f / vec3(2.2f, 2.2f, 2.2f);

	image3xU8 result(image.width(), image.height());

	for (int y = 0; y < image.height(); ++y) {
		for (int x = 0; x < image.width(); ++x) {
			result.at(x, y) = u8vec3(glm::pow(image.at(x, y), gamma) * 255.f);
		}
	}

	save_image(result, path);
}
*/
}
