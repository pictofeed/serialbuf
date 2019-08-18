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

#include <limits>

#include "lexer.hpp"

LexerToken::LexerToken(const Lexer *lexer, size_t lineno, size_t begin_pos, size_t end_pos)
  : lexer_(lexer), lineno_(lineno), begin_pos_(begin_pos), end_pos_(end_pos)
{

}

LexerToken::~LexerToken()
{

}

const Lexer* LexerToken::get_lexer() const
{
  return lexer_;
}

size_t LexerToken::get_lineno()
{
  return lineno_;
}

size_t LexerToken::get_begin_pos()
{
  return begin_pos_;
}

size_t LexerToken::get_end_pos()
{
  return end_pos_;
}

uint8_t LexerToken::get_type()
{
  throw std::runtime_error("Must override get_type() by a class that inherits from LexerToken!");
}

StringToken::~StringToken()
{
  value_.clear();
}

uint8_t StringToken::get_type()
{
  return LEXER_TOKEN_STRING;
}

void StringToken::set_value(std::string value)
{
  value_ = value;
}

std::string StringToken::get_value()
{
  return value_;
}

uint8_t LiteralToken::get_type()
{
  return LEXER_TOKEN_LITERAL;
}

uint8_t NumberToken::get_type()
{
  return LEXER_TOKEN_NUMBER;
}

void NumberToken::set_is_negative(bool is_negative)
{
  is_negative_ = is_negative;
}

bool NumberToken::get_is_negative()
{
  return is_negative_;
}

void NumberToken::set_is_floating_point(bool is_floating_point)
{
  is_floating_point_ = is_floating_point;
}

bool NumberToken::get_is_floating_point()
{
  return is_floating_point_;
}

void NumberToken::set_value(uint64_t value)
{
  value_ = value;
}

uint64_t NumberToken::get_value()
{
  return value_;
}

uint8_t NumberToken::get_integer_type()
{
  if (is_floating_point_)
  {
    double value = 0;
    memcpy(&value, &value_, sizeof(double));
    if (is_negative_)
    {
      value = -value;
    }

    if (value >= std::numeric_limits<float>::min() && value <= std::numeric_limits<float>::max())
    {
      return LEXER_INT_FLOAT;
    }
    else if (value >= std::numeric_limits<double>::min() && value <= std::numeric_limits<double>::max())
    {
      return LEXER_INT_DOUBLE;
    }
  }
  else if (is_negative_)
  {
    int64_t value = -value_;
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
  }
  else
  {
    if (value_ <= std::numeric_limits<uint8_t>::max())
    {
      return LEXER_INT_UINT8;
    }
    else if (value_ <= std::numeric_limits<uint16_t>::max())
    {
      return LEXER_INT_UINT16;
    }
    else if (value_ <= std::numeric_limits<uint32_t>::max())
    {
      return LEXER_INT_UINT32;
    }
    else if (value_ <= std::numeric_limits<uint64_t>::max())
    {
      return LEXER_INT_UINT64;
    }
  }

  throw std::runtime_error("Failed to get integer type for an invalid value!");
}

int8_t NumberToken::get_int8()
{
  int8_t value = 0;
  memcpy(&value, &value_, sizeof(int8_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint8_t NumberToken::get_uint8()
{
  uint8_t value = 0;
  memcpy(&value, &value_, sizeof(uint8_t));
  return value;
}

int16_t NumberToken::get_int16()
{
  int16_t value = 0;
  memcpy(&value, &value_, sizeof(int16_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint16_t NumberToken::get_uint16()
{
  uint16_t value = 0;
  memcpy(&value, &value_, sizeof(uint16_t));
  return value;
}

int32_t NumberToken::get_int32()
{
  int32_t value = 0;
  memcpy(&value, &value_, sizeof(int32_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint32_t NumberToken::get_uint32()
{
  uint32_t value = 0;
  memcpy(&value, &value_, sizeof(uint32_t));
  return value;
}

int64_t NumberToken::get_int64()
{
  int64_t value = 0;
  memcpy(&value, &value_, sizeof(int64_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint64_t NumberToken::get_uint64()
{
  uint64_t value = 0;
  memcpy(&value, &value_, sizeof(uint64_t));
  return value;
}

float NumberToken::get_float()
{
  float value = 0;
  memcpy(&value, &value_, sizeof(float));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

double NumberToken::get_double()
{
  double value = 0;
  memcpy(&value, &value_, sizeof(double));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint8_t NameToken::get_type()
{
  return LEXER_TOKEN_NAME;
}

uint8_t PunctuationToken::get_type()
{
  return LEXER_TOKEN_PUNCTUATION;
}

Lexer::Lexer(std::istringstream &stream)
  : stream_(stream), current_line_(""), current_lineno_(0), current_offset_(0)
{

}

Lexer::~Lexer()
{
  stream_.clear();
}

void Lexer::set_current_line(std::string current_line)
{
  current_line_ = current_line;
}

std::string Lexer::get_current_line()
{
  return current_line_;
}

void Lexer::set_current_lineno(size_t current_lineno)
{
  current_lineno_ = current_lineno;
}

size_t Lexer::get_current_lineno()
{
  return current_lineno_;
}

void Lexer::set_current_offset(size_t current_offset)
{
  current_offset_ = current_offset;
}

size_t Lexer::get_current_offset()
{
  return current_offset_;
}

const LexerToken* Lexer::read()
{
  auto it = current_line_.begin() + current_offset_;
  if (it == current_line_.end())
  {
    current_line_.clear();
    if (!std::getline(stream_, current_line_))
    {
      return nullptr;
    }

    current_lineno_++;
    current_offset_ = 0;
  }

  do
  {
    it = current_line_.begin() + current_offset_;
    current_offset_++;
  } while (it != current_line_.end());

  return nullptr;
}
