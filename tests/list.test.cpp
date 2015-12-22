#include <gtest/gtest.h>
#include <haste/list.hpp>
#include <haste/str.hpp>

TEST(list, basic) {
	using namespace haste;

	list<int> L;
	list<int> M = L;
	list<int> N = std::move(L);

	L = N;
	M = L;
	M = std::move(L);

	L = list<int>(0, 1, 2, 3, 4, 5, 6, 7);

	M = L;
	N = std::move(L);

	EXPECT_EQ(M, N);

	EXPECT_EQ(0, M[0]);
	EXPECT_EQ(1, M[1]);
	EXPECT_EQ(2, M[2]);
	EXPECT_EQ(3, M[3]);
	EXPECT_EQ(4, M[4]);
	EXPECT_EQ(7, M[7]);
}
