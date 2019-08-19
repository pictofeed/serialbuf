// Copyright (c) 2019, Pictofeed, LLC.
//
// This file is part of SerialBuf.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// You should have received a copy of the MIT License
// along with SerialBuf. If not, see <https://opensource.org/licenses/MIT>.

#include <cassert>
#include <cstdlib>
#include <cstdint>

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

#include <gtest/gtest.h>

#include "lexer.hpp"

TEST(LexerTests, parse_string_token_single_quote)
{
  std::istringstream stream("\'Hello World!\'");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_STRING);

  const StringToken *string_token = token->as_string_token();
  EXPECT_TRUE(string_token != nullptr);
  EXPECT_TRUE(string_token->get_value().compare("Hello World!") == 0);

  delete token;
}

TEST(LexerTests, parse_string_token_double_quote)
{
  std::istringstream stream("\"Hello World!\"");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_STRING);

  const StringToken *string_token = token->as_string_token();
  EXPECT_TRUE(string_token != nullptr);
  EXPECT_TRUE(string_token->get_value().compare("Hello World!") == 0);

  delete token;
}

TEST(LexerTests, parse_token_name)
{
  std::istringstream stream("some_random_token_name");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NAME);

  const NameToken *name_token = token->as_name_token();
  EXPECT_TRUE(name_token != nullptr);
  EXPECT_TRUE(name_token->get_value().compare("some_random_token_name") == 0);

  delete token;
}

TEST(LexerTests, parse_number_token_int8)
{
  std::istringstream stream("-128");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_INT8);
  EXPECT_TRUE(num_token->get_is_negative() == true);

  int8_t value = std::numeric_limits<int8_t>::min();
  ASSERT_EQ(num_token->get_int8(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_uint8)
{
  std::istringstream stream("255");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_UINT8);
  EXPECT_TRUE(num_token->get_is_negative() == false);

  int8_t value = std::numeric_limits<uint8_t>::max();
  ASSERT_EQ(num_token->get_int8(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_int16)
{
  std::istringstream stream("-32768");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_INT16);
  EXPECT_TRUE(num_token->get_is_negative() == true);

  int16_t value = std::numeric_limits<int16_t>::min();
  ASSERT_EQ(num_token->get_int16(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_uint16)
{
  std::istringstream stream("65535");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_UINT16);
  EXPECT_TRUE(num_token->get_is_negative() == false);

  uint16_t value = std::numeric_limits<uint16_t>::max();
  ASSERT_EQ(num_token->get_uint16(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_int32)
{
  std::istringstream stream("-2147483648");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_INT32);
  EXPECT_TRUE(num_token->get_is_negative() == true);

  int32_t value = std::numeric_limits<int32_t>::min();
  ASSERT_EQ(num_token->get_int32(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_uint32)
{
  std::istringstream stream("4294967295");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_UINT32);
  EXPECT_TRUE(num_token->get_is_negative() == false);

  uint32_t value = std::numeric_limits<uint32_t>::max();
  ASSERT_EQ(num_token->get_uint32(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_int64)
{
  std::istringstream stream("-9223372036854775808");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_INT64);
  EXPECT_TRUE(num_token->get_is_negative() == true);

  int64_t value = std::numeric_limits<int64_t>::min();
  ASSERT_EQ(num_token->get_int64(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_uint64)
{
  std::istringstream stream("18446744073709551615");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_UINT64);
  EXPECT_TRUE(num_token->get_is_negative() == false);

  uint64_t value = std::numeric_limits<uint64_t>::max();
  ASSERT_EQ(num_token->get_uint64(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_float)
{
  std::istringstream stream("340282346638528859811704183484516925440.000000");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  ASSERT_EQ(token->get_type(), LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  ASSERT_EQ(num_token->get_value_type(), LEXER_INT_FLOAT);
  EXPECT_TRUE(num_token->get_is_negative() == false);

  float value = 340282346638528859811704183484516925440.000000;
  ASSERT_EQ(num_token->get_float(), value);

  delete token;
}

TEST(LexerTests, parse_number_token_double)
{
  std::istringstream stream("179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000");
  Lexer lexer(stream);

  const LexerToken *token = lexer.read();
  EXPECT_TRUE(token != nullptr);
  EXPECT_TRUE(token->get_type() == LEXER_TOKEN_NUMBER);

  const NumberToken *num_token = token->as_number_token();
  EXPECT_TRUE(num_token != nullptr);
  EXPECT_TRUE(num_token->get_is_negative() == false);

  double value = 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000;
  ASSERT_EQ(num_token->get_double(), value);

  delete token;
}
