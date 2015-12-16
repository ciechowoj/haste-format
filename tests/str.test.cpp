#include <gtest/gtest.h>
#include <haste/_str.hpp>
#include <haste/str.hpp>

using namespace haste;
using namespace haste::detail;

TEST(str_t, init)
{
	char zeros[sizeof(str_t)];
	::memset(&zeros, 0, sizeof(str_t));

	str_t a;
	init(&a);

	ASSERT_TRUE(::memcmp(&a, zeros, sizeof(str_t)) == 0);
	ASSERT_STREQ("", data(&a));
	ASSERT_EQ(0, nbytes(&a));
	ASSERT_EQ(sizeof(str_t) - 2, capacity(&a));
}

TEST(str_t, init_copy)
{
	char zeros[sizeof(str_t)];
	::memset(&zeros, 0, sizeof(str_t));

	str_t a, b;
	init(&a);
	init_copy(&b, &a);

	ASSERT_TRUE(::memcmp(&b, zeros, sizeof(str_t)) == 0);
	ASSERT_STREQ("", data(&b));
	ASSERT_EQ(0, nbytes(&b));
	ASSERT_EQ(sizeof(str_t) - 2, capacity(&b));
}

TEST(str_t, init_move)
{
	char zeros[sizeof(str_t)];
	::memset(&zeros, 0, sizeof(str_t));

	str_t a, b;
	init(&a);
	init_move(&b, &a);

	ASSERT_TRUE(::memcmp(&b, zeros, sizeof(str_t)) == 0);
	ASSERT_STREQ("", data(&b));
	ASSERT_EQ(0, nbytes(&b));
	ASSERT_EQ(sizeof(str_t) - 2, capacity(&b));
}

TEST(str, basic) {
	ASSERT_STREQ("", str().data());
	ASSERT_EQ(0, str(str()).nbytes());
	ASSERT_EQ(0, str(std::move(str())).nbytes());

	str a, b;

	a = b;
	ASSERT_EQ(0, a.nbytes());
	a = std::move(b);
	ASSERT_EQ(0, a.nbytes());
}
 





