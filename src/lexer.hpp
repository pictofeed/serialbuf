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

#ifndef _LEXER_H
#define _LEXER_H

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cfloat>
#include <cctype>
#include <cfloat>

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

#include "utils.hpp"

typedef enum : uint8_t
{
  LEXER_TOKEN_STRING = 0,
  LEXER_TOKEN_LITERAL,
  LEXER_TOKEN_NUMBER,
  LEXER_TOKEN_NAME,
  LEXER_TOKEN_PUNCTUATION
} LexerTokenTypes;

typedef enum : uint8_t
{
  LEXER_INT_INT8 = 0,
  LEXER_INT_UINT8,

  LEXER_INT_INT16,
  LEXER_INT_UINT16,

  LEXER_INT_INT32,
  LEXER_INT_UINT32,

  LEXER_INT_INT64,
  LEXER_INT_UINT64,

  LEXER_INT_FLOAT,
  LEXER_INT_DOUBLE
} LexerIntegerTypes;

inline uint8_t get_int_type(int64_t value)
{
  if (value >= std::numeric_limits<int8_t>::min() && value <= std::numeric_limits<int8_t>::max())
  {
    return LEXER_INT_INT8;
  }
  else if (value >= std::numeric_limits<int16_t>::min() && value <= std::numeric_limits<int16_t>::max())
  {
    return LEXER_INT_INT16;
  }
  else if (value >= std::numeric_limits<int32_t>::min() && value <= std::numeric_limits<int32_t>::max())
  {
    return LEXER_INT_INT32;
  }
  else if (value >= std::numeric_limits<int64_t>::min() && value <= std::numeric_limits<int64_t>::max())
  {
    return LEXER_INT_INT64;
  }

  throw std::runtime_error("Failed to get signed integer type!");
}

inline uint8_t get_uint_type(uint64_t value)
{
  if (value <= std::numeric_limits<uint8_t>::max())
  {
    return LEXER_INT_UINT8;
  }
  else if (value <= std::numeric_limits<uint16_t>::max())
  {
    return LEXER_INT_UINT16;
  }
  else if (value <= std::numeric_limits<uint32_t>::max())
  {
    return LEXER_INT_UINT32;
  }
  else if (value <= std::numeric_limits<uint64_t>::max())
  {
    return LEXER_INT_UINT64;
  }

  throw std::runtime_error("Failed to get unsigned integer type!");
}

inline uint8_t get_floating_point_type(double value)
{
  if (value >= std::numeric_limits<float>::min() && value <= std::numeric_limits<float>::max())
  {
    return LEXER_INT_FLOAT;
  }
  else if (value >= std::numeric_limits<double>::min() && value <= std::numeric_limits<double>::max())
  {
    return LEXER_INT_DOUBLE;
  }

  throw std::runtime_error("Failed to get floating point integer type!");
}

class Lexer;

class StringToken;
class LiteralToken;
class NumberToken;
class NameToken;
class PunctuationToken;

class LexerToken
{
public:
  LexerToken(const Lexer *lexer, size_t lineno, size_t begin_pos, size_t end_pos);
  virtual ~LexerToken();

  const Lexer* get_lexer() const;

  size_t get_lineno();
  size_t get_begin_pos();
  size_t get_end_pos();

  virtual uint8_t get_type() const;

  virtual StringToken* as_string_token();
  virtual const StringToken* as_string_token() const;

  virtual LiteralToken* as_literal_token();
  virtual const LiteralToken* as_literal_token() const;

  virtual NumberToken* as_number_token();
  virtual const NumberToken* as_number_token() const;

  virtual NameToken* as_name_token();
  virtual const NameToken* as_name_token() const;

  virtual PunctuationToken* as_punctuation_token();
  virtual const PunctuationToken* as_punctuation_token() const;

protected:
  const Lexer *lexer_ = nullptr;
  size_t lineno_ = 0;
  size_t begin_pos_ = 0;
  size_t end_pos_ = 0;
};

class StringToken : public LexerToken
{
public:
  using LexerToken::LexerToken;
  virtual ~StringToken();

  virtual uint8_t get_type() const;

  StringToken* as_string_token();
  const StringToken* as_string_token() const;

  void set_value(std::string value);
  std::string get_value() const;

protected:
  std::string value_ = "";
};

class LiteralToken : public StringToken
{
public:
  using StringToken::StringToken;

  uint8_t get_type() const;

  LiteralToken* as_literal_token();
  const LiteralToken* as_literal_token() const;
};

class NumberToken : public LexerToken
{
public:
  using LexerToken::LexerToken;

  uint8_t get_type() const;

  NumberToken* as_number_token();
  const NumberToken* as_number_token() const;

  void set_is_negative(bool is_negative);
  bool get_is_negative() const;

  void set_is_floating_point(bool is_floating_point);
  bool get_is_floating_point() const;

  void clear();
  void size(size_t size);

  void set_value(int8_t value);
  void set_value(uint8_t value);

  void set_value(int16_t value);
  void set_value(uint16_t value);

  void set_value(int32_t value);
  void set_value(uint32_t value);

  void set_value(int64_t value);
  void set_value(uint64_t value);

  void set_value(float value);
  void set_value(double value);

  void set_compact_value(int64_t value);
  void set_compact_value(uint64_t value);

  void set_compact_value(double value);

  uint8_t* get_value() const;
  uint8_t get_value_type() const;

  int8_t get_int8() const;
  uint8_t get_uint8() const;

  int16_t get_int16() const;
  uint16_t get_uint16() const;

  int32_t get_int32() const;
  uint32_t get_uint32() const;

  int64_t get_int64() const;
  uint64_t get_uint64() const;

  float get_float() const;
  double get_double() const;

private:
  bool is_negative_ = false;
  bool is_floating_point_ = false;
  uint8_t *value_ = nullptr;
  uint8_t value_type_ = 0;
};

class NameToken : public StringToken
{
public:
  using StringToken::StringToken;

  uint8_t get_type() const;

  NameToken* as_name_token();
  const NameToken* as_name_token() const;
};

class PunctuationToken : public StringToken
{
public:
  using StringToken::StringToken;

  uint8_t get_type() const;

  PunctuationToken* as_punctuation_token();
  const PunctuationToken* as_punctuation_token() const;
};

class Lexer
{
public:
  Lexer(std::istringstream &stream);
  virtual ~Lexer();

  void set_current_line(std::string current_line);
  std::string get_current_line();

  void set_current_lineno(size_t current_lineno);
  size_t get_current_lineno();

  void set_current_offset(size_t current_offset);
  size_t get_current_offset();

  virtual const NumberToken* read_number();
  virtual const StringToken* read_string();
  virtual const NameToken* read_name();
  virtual const LexerToken* read();

protected:
  std::istringstream &stream_;
  std::string current_line_ = "";
  size_t current_lineno_ = 0;
  size_t current_offset_ = 0;
};

#endif // _LEXER_H
