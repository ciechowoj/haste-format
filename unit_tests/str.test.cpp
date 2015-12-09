#include <gtest/gtest.h>
#include <haste/str.hpp>

using namespace haste;

TEST(str, basic1) {
	auto _0 = str();
	auto _1 = str(_0);
	auto _2 = str(std::move(_1));

	_1 = _0;
	_2 = std::move(_2);
	_0 = std::move(_2);

	ASSERT_EQ(0, nbytes(_0));
	ASSERT_EQ(0, nbytes(_1));
	ASSERT_EQ(0, nbytes(_2));

	ASSERT_STREQ("", data(_0));
	ASSERT_STREQ("", data(_1));
	ASSERT_STREQ("", data(_2));
}

TEST(str, basic2) {
	const char* _c12 = "Hello world!";
	const char* _c81 = "00000111112222233333444445555566666777778888899999AAAAABBBBBCCCCCDDDDDEEEEEFFFFF!";
	auto _0 = make_str();
	auto _12 = make_str(_c12);
	auto _81 = make_str(_c81);

	ASSERT_STREQ(_c12, data(_12));
	ASSERT_STREQ(_c81, data(_81));
}

