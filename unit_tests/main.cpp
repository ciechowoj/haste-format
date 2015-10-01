#include <gtest/gtest.h>
#include <haste/format.hpp>

using namespace haste;

TEST(haste_format, _0) {
	EXPECT_EQ("", format(""));
	EXPECT_EQ("A", format("A"));

	EXPECT_EQ("{", format("{{"));
	EXPECT_EQ("}", format("}}"));
	EXPECT_EQ("{}}", format("{{}}"));
}





