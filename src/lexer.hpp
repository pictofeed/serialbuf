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
#include <cctype>

#include <iostream>
#include <string>
#include <sstream>

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

  virtual uint8_t get_type();

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

  virtual uint8_t get_type();

  StringToken* as_string_token();
  const StringToken* as_string_token() const;

  void set_value(std::string value);
  std::string get_value();

protected:
  std::string value_ = "";
};

class LiteralToken : public StringToken
{
public:
  using StringToken::StringToken;

  uint8_t get_type();

  LiteralToken* as_literal_token();
  const LiteralToken* as_literal_token() const;
};

class NumberToken : public LexerToken
{
public:
  using LexerToken::LexerToken;

  uint8_t get_type();

  NumberToken* as_number_token();
  const NumberToken* as_number_token() const;

  void set_is_negative(bool is_negative);
  bool get_is_negative();

  void set_is_floating_point(bool is_floating_point);
  bool get_is_floating_point();

  void set_value(uint64_t value);
  uint64_t get_value();

  uint8_t get_integer_type();

  int8_t get_int8();
  uint8_t get_uint8();

  int16_t get_int16();
  uint16_t get_uint16();

  int32_t get_int32();
  uint32_t get_uint32();

  int64_t get_int64();
  uint64_t get_uint64();

  float get_float();
  double get_double();

protected:
  bool is_negative_ = false;
  bool is_floating_point_ = false;
  uint64_t value_ = 0;
};

class NameToken : public StringToken
{
public:
  using StringToken::StringToken;

  uint8_t get_type();

  NameToken* as_name_token();
  const NameToken* as_name_token() const;
};

class PunctuationToken : public StringToken
{
public:
  using StringToken::StringToken;

  uint8_t get_type();

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

  const LexerToken* read();

protected:
  std::istringstream &stream_;
  std::string current_line_ = "";
  size_t current_lineno_ = 0;
  size_t current_offset_ = 0;
};

#endif // _LEXER_H
