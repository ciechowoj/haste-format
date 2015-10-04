#include <gtest/gtest.h>
#include <haste/_format.hpp>
#include <stdexcept> 

using namespace haste;

TEST(haste_format, _format_parse_name)
{
	int index = -1;
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

TEST(haste_format, _format_parse_spec_SINGLE)
{
	_format_spec_t spec;
	const char* begin, *end;

	#define EXPECT_SPEC_PARSED(expected_end, name) \
		spec = _format_spec_t(); \
		begin = name; \
		end = begin + _strlen(begin); \
		ASSERT_EQ(expected_end, *_format_parse_spec(spec, 17, begin, end)); \

	EXPECT_SPEC_PARSED('\0', "");
	EXPECT_EQ(string(), spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":");
	EXPECT_EQ(string(), spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);
	
	EXPECT_SPEC_PARSED('\0', ":a=");
	EXPECT_EQ("a", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ('=', spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('{', ":{=");
	EXPECT_SPEC_PARSED('s', ":xs}="); 
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ('x', spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":x<");
	EXPECT_EQ("x", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ('<', spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":x=");
	EXPECT_EQ("x", spec.fill);
	EXPECT_EQ('=', spec.align);

	EXPECT_SPEC_PARSED('\0', ":-");
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ('-', spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":#");
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_TRUE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":0");
	EXPECT_EQ("0", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ('=', spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_TRUE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":x<0");
	EXPECT_EQ("x", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ('<', spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_TRUE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":<0");
	EXPECT_EQ("0", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ('<', spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_TRUE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":1");
	EXPECT_EQ(" ", spec.fill);
	EXPECT_EQ(1, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":42");
	EXPECT_EQ(" ", spec.fill);
	EXPECT_EQ(42, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":,");
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_TRUE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":.123");
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(123, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('%', ":%%");
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ('%', spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	EXPECT_SPEC_PARSED('\0', ":<");
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ('<', spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	#undef EXPECT_SPEC_PARSED

	#define EXPECT_SPEC_THROWS(name) \
		spec = _format_spec_t(); \
		begin = name; \
		end = begin + _strlen(begin); \
		EXPECT_THROW(_format_parse_spec(spec, 17, begin, end), std::invalid_argument);

	EXPECT_SPEC_THROWS(":.");
	EXPECT_SPEC_THROWS(":.%%");

	#undef EXPECT_SPEC_THROWS
}

TEST(haste_format, _format_parse_spec_MISMATCH) {
	_format_spec_t spec;
	const char* begin, *end;

	#define EXPECT_SPEC_THROWS(id, name) \
		spec = _format_spec_t(); \
		begin = name; \
		end = begin + _strlen(begin); \
		EXPECT_THROW(_format_parse_spec(spec, id, begin, end), std::invalid_argument);

	EXPECT_SPEC_THROWS(null_id, ":,");
	EXPECT_SPEC_THROWS(std_string_id, ":#");

	#undef EXPECT_SPEC_THROWS	
}

TEST(haste_format, _format_parse_spec_MULTIPLE)
{
	_format_spec_t spec;
	const char* begin, *end;

	#define EXPECT_SPEC_PARSED(expected_end, name) \
		spec = _format_spec_t(); \
		begin = name; \
		end = begin + _strlen(begin); \
		ASSERT_EQ(expected_end, *_format_parse_spec(spec, 17, begin, end));

	EXPECT_SPEC_PARSED('\0', ":w=-#0123,.34X");
	EXPECT_EQ("w", spec.fill);
	EXPECT_EQ(123, spec.width);
	EXPECT_EQ(34, spec.precision);
	EXPECT_EQ('=', spec.align);
	EXPECT_EQ('-', spec.sign);
	EXPECT_EQ('X', spec.type);
	EXPECT_TRUE(spec.hash);
	EXPECT_TRUE(spec.zero);
	EXPECT_TRUE(spec.comma);
	
	EXPECT_SPEC_PARSED('\0', ":");
	EXPECT_EQ("", spec.fill);
	EXPECT_EQ(0, spec.width);
	EXPECT_EQ(0, spec.precision);
	EXPECT_EQ(0, spec.align);
	EXPECT_EQ(0, spec.sign);
	EXPECT_EQ(0, spec.type);
	EXPECT_FALSE(spec.hash);
	EXPECT_FALSE(spec.zero);
	EXPECT_FALSE(spec.comma);

	#undef EXPECT_SPEC_PARSED
}

TEST(format, escape_sequences) {
	EXPECT_EQ("", format(""));
	EXPECT_EQ("A", format("A"));

	EXPECT_EQ("{", format("{{"));
	EXPECT_EQ("}", format("}}"));
	EXPECT_EQ("{}", format("{{}}"));
}

TEST(format, unmatched_braces)
{
	EXPECT_THROW(format("}"), std::invalid_argument);
	EXPECT_THROW(format("{"), std::invalid_argument);
}

TEST(format, automatic_numbering) 
{
	EXPECT_THROW(format("{}{0}", 0, 1), std::invalid_argument);
	EXPECT_THROW(format("{0}{}", 0, 1), std::invalid_argument);
}

TEST(format, not_indexable) {
	EXPECT_THROW(format("{0[0]}", 0), std::invalid_argument);
	EXPECT_THROW(format("{0[0]}", '\0'), std::invalid_argument);
	EXPECT_THROW(format("{0[0]}", "string"), std::invalid_argument);
}

TEST(format, specifier_unsupported_for_type) {
	EXPECT_THROW(format("{0:#}", nullptr), std::invalid_argument);	
	EXPECT_THROW(format("{0:,}", string()), std::invalid_argument);
	EXPECT_THROW(format("{0:+0}", "sudo"), std::invalid_argument);
	EXPECT_THROW(format("{0: .123}", string()), std::invalid_argument);
}

TEST(format, specifier_supported_for_type) {
	EXPECT_NO_THROW(format("{0:#}", 0));	
	EXPECT_NO_THROW(format("{0:,}", 0.0));
	EXPECT_NO_THROW(format("{0:+0}", 80ull));
	EXPECT_NO_THROW(format("{0:.123}", 42.0f));
}

TEST(format, eq_allowed_for_numeric_only) {
	EXPECT_THROW(format("{0:==}", string()), std::invalid_argument);
	EXPECT_THROW(format("{0:=}", string()), std::invalid_argument);
}

TEST(format, format_nullptr) {
	EXPECT_EQ("nullptr", format("{}", nullptr));
	EXPECT_EQ("nullptr   ", format("{:10}", nullptr));
	EXPECT_EQ("nullptr   ", format("{:<10}", nullptr));
	EXPECT_EQ("   nullptr", format("{:>10}", nullptr));
	EXPECT_EQ(" nullptr  ", format("{:^10}", nullptr));

	EXPECT_EQ("nullptr<<<", format("{:<<10}", nullptr));
	EXPECT_EQ("<<<nullptr", format("{:<>10}", nullptr));
	EXPECT_EQ(">nullptr>>", format("{:>^10}", nullptr));

	EXPECT_EQ("nullptr000", format("{:<010}", nullptr));
	EXPECT_EQ("000nullptr", format("{:>010}", nullptr));
	EXPECT_EQ("0nullptr00", format("{:^010}", nullptr));

	EXPECT_EQ("null      ", format("{:<10.4}", nullptr));
	EXPECT_EQ("      null", format("{:>10.4}", nullptr));
	EXPECT_EQ("   null   ", format("{:^10.4}", nullptr));

	EXPECT_EQ("          ", format("{:<10.0}", nullptr));
	EXPECT_EQ("          ", format("{:>10.0}", nullptr));
	EXPECT_EQ("          ", format("{:^10.0}", nullptr));

	EXPECT_EQ("nullp", format("{:<5.5}", nullptr));
	EXPECT_EQ("nullp", format("{:>5.5}", nullptr));
	EXPECT_EQ("nullp", format("{:^5.5}", nullptr));
}





