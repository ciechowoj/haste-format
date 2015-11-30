#pragma once
#include <utility>
#include <string>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

#include <haste/array.hpp>

namespace haste {

using namespace glm;

using std::string;

class image;

const dvec4 at(const image& self, size_t x, size_t y);
void set_at(image& self, size_t x, size_t y, const dvec4& value);

class image {
public:
	using ubyte = array::ubyte;

	image();
	image(size_t x, size_t y, data_t dtype);
	image(const image&);
	image(image&&);
	~image();

	image(const array& that);
	image(array&& that);

	image& operator=(const image&);
	image& operator=(image&&);

	ubyte* data();
	const ubyte* data() const;
	ubyte* data(size_t x, size_t y);
	const ubyte* data(size_t x, size_t y) const;

	size_t ndim() const;
	size_t nbytes() const;
	size_t shape(size_t i) const;
	size_t stride(size_t i) const;
	data_t dtype() const;
	size_t width() const;
	size_t height() const;
private:
	ubyte* _data(size_t x, size_t y);
	const ubyte* _data(size_t x, size_t y) const;
	
	array _array;
	
	friend const dvec4 at(const image& self, size_t x, size_t y);
	friend void set_at(image& self, size_t x, size_t y, const dvec4& value);
};

image load_jpg(const string& path);
image load_png(const string& path);
image load_exr(const string& path);
void save_png(const image& image, const string& path);
image make_image(size_t width, size_t height, data_t dtype);
image make_image(size_t width, size_t height, data_t dtype, double value);
image conv_image(const image& src, data_t dtype);

void mul(image& out, dvec4 a);
void mad(image& out, const image& a, dvec4 b);
void clamp(image& out, double a, double b);

}
