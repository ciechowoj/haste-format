#include <gtest/gtest.h>
#include <haste/str.hpp>

using namespace haste;

TEST(string, base) {
	str x;
	str y = "";
	str z = "x";
	str w = "xy";

	str a = x;
	str b = y;
	str c = z;
	str d = w;

	x = d;
	y = c;
	z = b;
	w = a;

	ASSERT_EQ("xy", x);
	ASSERT_EQ("x", y);
	ASSERT_EQ("", z);
	ASSERT_EQ("", w);	
}

TEST(string, sso_threshold)
{
	str x;

	const char T27[] = "012345678901234567890123456";
	const char T28[] = "0123456789012345678901234567";
	const char T29[] = "01234567890123456789012345678";
	const char T30[] = "012345678901234567890123456789";
	const char T31[] = "0123456789012345678901234567891";
	const char T32[] = "01234567890123456789012345678912";
	const char T33[] = "012345678901234567890123456789123";
	const char T34[] = "0123456789012345678901234567891234";
	const char T35[] = "01234567890123456789012345678912345";
	const char T36[] = "012345678901234567890123456789123456";
	const char T37[] = "0123456789012345678901234567891234567";
	const char T38[] = "01234567890123456789012345678912345678";

	ASSERT_GE(sizeof(str), sizeof(T27) + 4);
	ASSERT_LE(sizeof(str), sizeof(T38));

	ASSERT_EQ(sizeof(T27) - 1, str(T27).nbytes());
	ASSERT_EQ(sizeof(T28) - 1, str(T28).nbytes());
	ASSERT_EQ(sizeof(T29) - 1, str(T29).nbytes());
	ASSERT_EQ(sizeof(T30) - 1, str(T30).nbytes());
	ASSERT_EQ(sizeof(T31) - 1, str(T31).nbytes());
	ASSERT_EQ(sizeof(T32) - 1, str(T32).nbytes());
	ASSERT_EQ(sizeof(T33) - 1, str(T33).nbytes());
	ASSERT_EQ(sizeof(T34) - 1, str(T34).nbytes());
	ASSERT_EQ(sizeof(T35) - 1, str(T35).nbytes());
	ASSERT_EQ(sizeof(T36) - 1, str(T36).nbytes());
	ASSERT_EQ(sizeof(T37) - 1, str(T37).nbytes());
	ASSERT_EQ(sizeof(T38) - 1, str(T38).nbytes());

	x = T27; ASSERT_EQ(T27, x); ASSERT_EQ(sizeof(T27) - 1, x.nbytes()); ASSERT_EQ(sizeof(T27) - 1, x.nchars());
	x = T28; ASSERT_EQ(T28, x); ASSERT_EQ(sizeof(T28) - 1, x.nbytes()); ASSERT_EQ(sizeof(T28) - 1, x.nchars());
	x = T29; ASSERT_EQ(T29, x); ASSERT_EQ(sizeof(T29) - 1, x.nbytes()); ASSERT_EQ(sizeof(T29) - 1, x.nchars());
	x = T30; ASSERT_EQ(T30, x); ASSERT_EQ(sizeof(T30) - 1, x.nbytes()); ASSERT_EQ(sizeof(T30) - 1, x.nchars());
	x = T31; ASSERT_EQ(T31, x); ASSERT_EQ(sizeof(T31) - 1, x.nbytes()); ASSERT_EQ(sizeof(T31) - 1, x.nchars());
	x = T32; ASSERT_EQ(T32, x); ASSERT_EQ(sizeof(T32) - 1, x.nbytes()); ASSERT_EQ(sizeof(T32) - 1, x.nchars());
	x = T33; ASSERT_EQ(T33, x); ASSERT_EQ(sizeof(T33) - 1, x.nbytes()); ASSERT_EQ(sizeof(T33) - 1, x.nchars());
	x = T34; ASSERT_EQ(T34, x); ASSERT_EQ(sizeof(T34) - 1, x.nbytes()); ASSERT_EQ(sizeof(T34) - 1, x.nchars());
	x = T35; ASSERT_EQ(T35, x); ASSERT_EQ(sizeof(T35) - 1, x.nbytes()); ASSERT_EQ(sizeof(T35) - 1, x.nchars());
	x = T36; ASSERT_EQ(T36, x); ASSERT_EQ(sizeof(T36) - 1, x.nbytes()); ASSERT_EQ(sizeof(T36) - 1, x.nchars());
	x = T37; ASSERT_EQ(T37, x); ASSERT_EQ(sizeof(T37) - 1, x.nbytes()); ASSERT_EQ(sizeof(T37) - 1, x.nchars());
	x = T38; ASSERT_EQ(T38, x); ASSERT_EQ(sizeof(T38) - 1, x.nbytes()); ASSERT_EQ(sizeof(T38) - 1, x.nchars());
}

TEST(string, concat) {
	EXPECT_EQ("", concat(""));
	EXPECT_EQ("0", concat("0"));
	EXPECT_EQ("012", concat("012"));
	EXPECT_EQ("0123", concat("0123"));
	EXPECT_EQ("0123456789012345678901234567890123456789", 
			  concat("0123456789012345678901234567890123456789"));

	str x = "x";
	const char* y = "y";
	const char z[] = "z";

	EXPECT_EQ("xyz", concat(x, y, z));
}





 
