#include <gtest/gtest.h>
#include <haste/image.hpp>
#include <stdexcept> 

using namespace haste;

TEST(image, constructors) {
	image X;
	image Y(X);
	image Z(std::move(Y));

	Z = X;
	Z = Z;
	Z = Y;
}

TEST(image, dtype) {
	auto image = make_image(1, 1, data_t::unorm8x4);
	ASSERT_EQ(data_t::unorm8x4, image.dtype());
}

TEST(image, at11) {
	auto image = make_image(1, 1, data_t::unorm8x4);

	set_at(image, 0, 0, vec4(0.f, 1.f, 0.f, 1.f));

	ASSERT_EQ(0xff00ff00u, *((unsigned*)image.data()));

	EXPECT_EQ(0.0, at(image, 0, 0).x);
	EXPECT_EQ(1.0, at(image, 0, 0).y);
	EXPECT_EQ(0.0, at(image, 0, 0).z);
	EXPECT_EQ(1.0, at(image, 0, 0).w);

	set_at(image, 0, 0, vec4(0.f, 0.25f, 0.5f, 0.75f));

	EXPECT_EQ(0.0, at(image, 0, 0).x);
	EXPECT_GE(0.1, abs(0.25 - at(image, 0, 0).y));
	EXPECT_GE(0.1, abs(0.5 - at(image, 0, 0).z));
	EXPECT_GE(0.1, abs(0.75 - at(image, 0, 0).w));
}

TEST(image, at11_b) {
	auto image = make_image(1, 1, data_t::unorm8x3);

	set_at(image, 0, 0, vec4(0.f, 0.25f, 0.5f, 0.75f));

	EXPECT_EQ(0.0, at(image, 0, 0).x);
	EXPECT_GE(0.1, abs(0.25 - at(image, 0, 0).y));
	EXPECT_GE(0.1, abs(0.5 - at(image, 0, 0).z));
	EXPECT_EQ(0.0, at(image, 0, 0).w);
}

TEST(image, at22) {
	auto image = make_image(2, 2, data_t::unorm8x4);

	set_at(image, 0, 0, vec4(1.f, 0.f, 0.f, 0.f));
	set_at(image, 1, 0, vec4(1.f, 1.f, 0.f, 0.f));
	set_at(image, 0, 1, vec4(1.f, 0.f, 1.f, 0.f));
	set_at(image, 1, 1, vec4(1.f, 0.f, 0.f, 1.f));

	EXPECT_EQ(dvec4(1.f, 0.f, 0.f, 0.f), at(image, 0, 0));
	EXPECT_EQ(dvec4(1.f, 1.f, 0.f, 0.f), at(image, 1, 0));
	EXPECT_EQ(dvec4(1.f, 0.f, 1.f, 0.f), at(image, 0, 1));
	EXPECT_EQ(dvec4(1.f, 0.f, 0.f, 1.f), at(image, 1, 1));
}

TEST(image, width) {
	auto image = make_image(17, 42, data_t::unorm8x4);

	EXPECT_EQ(17, image.width());
	EXPECT_EQ(42, image.height());
}

TEST(image, convert) {
	auto image = make_image(2, 2, data_t::float32x4);

	set_at(image, 0, 0, vec4(1.f, 0.f, 0.f, 0.f));
	set_at(image, 1, 0, vec4(1.f, 1.f, 0.f, 0.f));
	set_at(image, 0, 1, vec4(1.f, 0.f, 1.f, 0.f));
	set_at(image, 1, 1, vec4(1.f, 0.f, 0.f, 1.f));

	auto image_conv = conv_image(image, data_t::unorm8x4);

	EXPECT_EQ(dvec4(1.f, 0.f, 0.f, 0.f), at(image_conv, 0, 0));
	EXPECT_EQ(dvec4(1.f, 1.f, 0.f, 0.f), at(image_conv, 1, 0));
	EXPECT_EQ(dvec4(1.f, 0.f, 1.f, 0.f), at(image_conv, 0, 1));
	EXPECT_EQ(dvec4(1.f, 0.f, 0.f, 1.f), at(image_conv, 1, 1));
}

TEST(image, make_image_1) {
	auto image = make_image(2, 2, data_t::float32x2, 3.0);

	EXPECT_EQ(dvec4(3.f, 3.f, 0.f, 0.f), at(image, 0, 0));
	EXPECT_EQ(dvec4(3.f, 3.f, 0.f, 0.f), at(image, 1, 0));
	EXPECT_EQ(dvec4(3.f, 3.f, 0.f, 0.f), at(image, 0, 1));
	EXPECT_EQ(dvec4(3.f, 3.f, 0.f, 0.f), at(image, 1, 1));	
}

TEST(image, mul) {
	auto image = make_image(2, 2, data_t::float32x3);

	set_at(image, 0, 0, vec4(1.f, 0.f, 0.f, 0.f));
	set_at(image, 1, 0, vec4(1.f, 1.f, 0.f, 0.f));
	set_at(image, 0, 1, vec4(1.f, 0.f, 1.f, 0.f));
	set_at(image, 1, 1, vec4(1.f, 0.f, 0.f, 1.f));

	mul(image, dvec4(3.f));

	EXPECT_EQ(dvec4(3.f, 0.f, 0.f, 0.f), at(image, 0, 0));
	EXPECT_EQ(dvec4(3.f, 3.f, 0.f, 0.f), at(image, 1, 0));
	EXPECT_EQ(dvec4(3.f, 0.f, 3.f, 0.f), at(image, 0, 1));
	EXPECT_EQ(dvec4(3.f, 0.f, 0.f, 0.f), at(image, 1, 1));	
}

TEST(image, ndim) {
	ASSERT_EQ(1, ndim(data_t::unorm8));
	ASSERT_EQ(1, ndim(data_t::unorm8x1));
	ASSERT_EQ(2, ndim(data_t::unorm8x2));
	ASSERT_EQ(3, ndim(data_t::unorm8x3));
	ASSERT_EQ(4, ndim(data_t::unorm8x4));
}

TEST(image, prec) {
	ASSERT_EQ(8, prec(data_t::unorm8));
	ASSERT_EQ(16, prec(data_t::unorm16x1));
	ASSERT_EQ(8, prec(data_t::unorm8x2));
	ASSERT_EQ(32, prec(data_t::unorm32x3));
	ASSERT_EQ(64, prec(data_t::unorm64x4));
}

TEST(image, subtype) {
	ASSERT_EQ(data_t::unorm8, subtype(data_t::unorm8x2));
	ASSERT_EQ(data_t::snorm16, subtype(data_t::snorm16x4));
	ASSERT_EQ(data_t::uint32, subtype(data_t::uint32x2));
	ASSERT_EQ(data_t::sint64, subtype(data_t::sint64x1));
	ASSERT_EQ(data_t::float32, subtype(data_t::float32x2));
	ASSERT_EQ(data_t::float8, subtype(data_t::float8x3));
}






