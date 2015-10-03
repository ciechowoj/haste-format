#include <gtest/gtest.h>
#include <haste/_format.hpp>
#include <stdexcept> 

using namespace haste;

TEST(haste_format, _format_parse_name)
{
	size_t index = -1;
	vector<_format_index_t> indices;
	const char* begin, *end;

	#define EXPECT_NAME_PARSED(expected_index, expected_end, name) \
		index = -1; \
		indices.clear(); \
		begin = name; \
		end = begin + _strlen(begin); \
		ASSERT_EQ(expected_end, *_format_parse_name(index, indices, begin, end)); \
		EXPECT_EQ(expected_index, index);

	EXPECT_NAME_PARSED(-1, '\0', "");
	EXPECT_NAME_PARSED(0, '\0', "0");
	EXPECT_NAME_PARSED(1, '\0', "1");
	EXPECT_NAME_PARSED(2, '\0', "2");
	EXPECT_NAME_PARSED(9, '\0', "9");
	EXPECT_NAME_PARSED(10, '\0', "10");
	EXPECT_NAME_PARSED(42, '\0', "42");
	EXPECT_NAME_PARSED(1234321, '\0', "1234321");
	EXPECT_NAME_PARSED(-1, '-', "-");
	EXPECT_NAME_PARSED(123, ':', "123:");
	EXPECT_NAME_PARSED(123, '}', "123}");
	EXPECT_NAME_PARSED(7, '!', "7!");

	EXPECT_NAME_PARSED(0, '\0', "0[0]");
	ASSERT_EQ(1, indices.size());
	EXPECT_STREQ("0", string(indices[0].begin, indices[0].end).c_str());

	EXPECT_NAME_PARSED(0, '\0', "0[a]");
	ASSERT_EQ(1, indices.size());
	EXPECT_STREQ("a", string(indices[0].begin, indices[0].end).c_str());

	EXPECT_NAME_PARSED(0, '\0', "0[0][12]");
	ASSERT_EQ(2, indices.size());
	EXPECT_TRUE(indices[0].is_integer);
	EXPECT_STREQ("0", string(indices[0].begin, indices[0].end).c_str());
	EXPECT_TRUE(indices[1].is_integer);	
	EXPECT_STREQ("12", string(indices[1].begin, indices[1].end).c_str());

	EXPECT_NAME_PARSED(0, '\0', "0[0][12a]");
	ASSERT_EQ(2, indices.size());
	EXPECT_TRUE(indices[0].is_integer);
	EXPECT_STREQ("0", string(indices[0].begin, indices[0].end).c_str());
	EXPECT_FALSE(indices[1].is_integer);	
	EXPECT_STREQ("12a", string(indices[1].begin, indices[1].end).c_str());

	#undef EXPECT_NAME_PARSED

	#define EXPECT_NAME_THROWS(name) \
		index = -1; \
		begin = name; \
		end = begin + _strlen(begin); \
		EXPECT_THROW(_format_parse_name(index, indices, begin, end), std::invalid_argument);

	EXPECT_NAME_THROWS("7[");
	EXPECT_NAME_THROWS("7[123");
	EXPECT_NAME_THROWS("7[123!");
	EXPECT_NAME_THROWS("7[123][abba");
	EXPECT_NAME_THROWS("7[123][abba][");
	EXPECT_NAME_THROWS("7[123][]");

	#undef EXPECT_NAME_THROWS
}

TEST(haste_format, _format_parse_conv)
{
	char conv;
	vector<_format_index_t> indices;
	const char* begin, *end;

	#define EXPECT_CONV_PARSED(expected_conv, expected_end, name) \
		conv = 0; \
		begin = name; \
		end = begin + _strlen(begin); \
		ASSERT_EQ(expected_end, *_format_parse_conv(conv, begin, end)); \
		EXPECT_EQ(expected_conv, conv);

	EXPECT_CONV_PARSED('r', '\0', "!r");
	EXPECT_CONV_PARSED('s', '\0', "!s");
	EXPECT_CONV_PARSED('a', '\0', "!a");
	EXPECT_CONV_PARSED('a', 'a', "!aa");
	EXPECT_CONV_PARSED('a', ':', "!a:");

	#undef EXPECT_CONV_PARSED

	#define EXPECT_CONV_THROWS(name) \
		conv = 0; \
		begin = name; \
		end = begin + _strlen(begin); \
		EXPECT_THROW(_format_parse_conv(conv, begin, end), std::invalid_argument);

	EXPECT_CONV_THROWS("!");
	EXPECT_CONV_THROWS("!q");
	EXPECT_CONV_THROWS("!!");
	EXPECT_CONV_THROWS("!:");

	#undef EXPECT_CONV_THROWS
}

TEST(haste_format, _0) {
	EXPECT_EQ("", format(""));
	EXPECT_EQ("A", format("A"));

	EXPECT_EQ("{", format("{{"));
	EXPECT_EQ("}", format("}}"));
	EXPECT_EQ("{}", format("{{}}"));
}

TEST(haste_format, unmatched_braces)
{

	EXPECT_THROW(format("}"), std::invalid_argument);



}





