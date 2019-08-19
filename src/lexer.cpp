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

uint8_t LexerToken::get_type() const
{
  throw std::runtime_error("Must override get_type() by a class that inherits from LexerToken!");
}

StringToken* LexerToken::as_string_token()
{
  return nullptr;
}

const StringToken* LexerToken::as_string_token() const
{
  return nullptr;
}

LiteralToken* LexerToken::as_literal_token()
{
  return nullptr;
}

const LiteralToken* LexerToken::as_literal_token() const
{
  return nullptr;
}

NumberToken* LexerToken::as_number_token()
{
  return nullptr;
}

const NumberToken* LexerToken::as_number_token() const
{
  return nullptr;
}

NameToken* LexerToken::as_name_token()
{
  return nullptr;
}

const NameToken* LexerToken::as_name_token() const
{
  return nullptr;
}

PunctuationToken* LexerToken::as_punctuation_token()
{
  return nullptr;
}

const PunctuationToken* LexerToken::as_punctuation_token() const
{
  return nullptr;
}

StringToken::~StringToken()
{
  value_.clear();
}

uint8_t StringToken::get_type() const
{
  return LEXER_TOKEN_STRING;
}

StringToken* StringToken::as_string_token()
{
  return this;
}

const StringToken* StringToken::as_string_token() const
{
  return this;
}

void StringToken::set_value(std::string value)
{
  value_ = value;
}

std::string StringToken::get_value() const
{
  return value_;
}

uint8_t LiteralToken::get_type() const
{
  return LEXER_TOKEN_LITERAL;
}

LiteralToken* LiteralToken::as_literal_token()
{
  return this;
}

const LiteralToken* LiteralToken::as_literal_token() const
{
  return this;
}

uint8_t NumberToken::get_type() const
{
  return LEXER_TOKEN_NUMBER;
}

NumberToken* NumberToken::as_number_token()
{
  return this;
}

const NumberToken* NumberToken::as_number_token() const
{
  return this;
}

void NumberToken::set_is_negative(bool is_negative)
{
  is_negative_ = is_negative;
}

bool NumberToken::get_is_negative() const
{
  return is_negative_;
}

void NumberToken::set_is_floating_point(bool is_floating_point)
{
  is_floating_point_ = is_floating_point;
}

bool NumberToken::get_is_floating_point() const
{
  return is_floating_point_;
}

void NumberToken::clear()
{
  if (value_ != nullptr)
  {
    free(value_);
    value_ = nullptr;
  }

  is_negative_ = false;
  is_floating_point_ = false;
}

void NumberToken::size(size_t size)
{
  value_ = (uint8_t*)calloc(size, 1);
  if (value_ == nullptr)
  {
    throw std::runtime_error("Failed to resize NumberToken value, could not allocate enough memory!");
  }
}

void NumberToken::set_value(int8_t value)
{
  clear();
  size(sizeof(int8_t));
  memcpy(value_, &value, sizeof(int8_t));
  value_type_ = LEXER_INT_INT8;
  is_negative_ = true;
}

void NumberToken::set_value(uint8_t value)
{
  clear();
  size(sizeof(uint8_t));
  memcpy(value_, &value, sizeof(uint8_t));
  value_type_ = LEXER_INT_UINT8;
}

void NumberToken::set_value(int16_t value)
{
  clear();
  size(sizeof(int16_t));
  memcpy(value_, &value, sizeof(int16_t));
  value_type_ = LEXER_INT_INT16;
  is_negative_ = true;
}

void NumberToken::set_value(uint16_t value)
{
  clear();
  size(sizeof(uint16_t));
  memcpy(value_, &value, sizeof(uint16_t));
  value_type_ = LEXER_INT_UINT16;
}

void NumberToken::set_value(int32_t value)
{
  clear();
  size(sizeof(int32_t));
  memcpy(value_, &value, sizeof(int32_t));
  value_type_ = LEXER_INT_INT32;
  is_negative_ = true;
}

void NumberToken::set_value(uint32_t value)
{
  clear();
  size(sizeof(uint32_t));
  memcpy(value_, &value, sizeof(uint32_t));
  value_type_ = LEXER_INT_UINT32;
}

void NumberToken::set_value(int64_t value)
{
  clear();
  size(sizeof(int64_t));
  memcpy(value_, &value, sizeof(int64_t));
  value_type_ = LEXER_INT_INT64;
  is_negative_ = true;
}

void NumberToken::set_value(uint64_t value)
{
  clear();
  size(sizeof(uint64_t));
  memcpy(value_, &value, sizeof(uint64_t));
  value_type_ = LEXER_INT_UINT64;
}

void NumberToken::set_value(float value)
{
  clear();
  size(sizeof(float));
  memcpy(value_, &value, sizeof(float));
  value_type_ = LEXER_INT_FLOAT;
  is_negative_ = value < 0;
  is_floating_point_ = true;
}

void NumberToken::set_value(double value)
{
  clear();
  size(sizeof(double));
  memcpy(value_, &value, sizeof(double));
  value_type_ = LEXER_INT_DOUBLE;
  is_negative_ = value < 0;
  is_floating_point_ = true;
}

void NumberToken::set_compact_value(int64_t value)
{
  uint8_t type = get_int_type(value);
  switch (type)
  {
    case LEXER_INT_INT8:
      set_value((int8_t)value);
      break;
    case LEXER_INT_INT16:
      set_value((int16_t)value);
      break;
    case LEXER_INT_INT32:
      set_value((int32_t)value);
      break;
    case LEXER_INT_INT64:
      set_value((int64_t)value);
      break;
    default:
      break;
  }
}

void NumberToken::set_compact_value(uint64_t value)
{
  uint8_t type = get_uint_type(value);
  switch (type)
  {
    case LEXER_INT_UINT8:
      set_value((uint8_t)value);
      break;
    case LEXER_INT_UINT16:
      set_value((uint16_t)value);
      break;
    case LEXER_INT_UINT32:
      set_value((uint32_t)value);
      break;
    case LEXER_INT_UINT64:
      set_value((uint64_t)value);
      break;
    default:
      break;
  }
}

void NumberToken::set_compact_value(double value)
{
  uint8_t type = get_floating_point_type(value);
  switch (type)
  {
    case LEXER_INT_FLOAT:
      set_value((float)value);
      break;
    case LEXER_INT_DOUBLE:
      set_value((double)value);
      break;
    default:
      break;
  }
}

uint8_t* NumberToken::get_value() const
{
  return value_;
}

uint8_t NumberToken::get_value_type() const
{
  return value_type_;
}

int8_t NumberToken::get_int8() const
{
  int8_t value = 0;
  memcpy(&value, value_, sizeof(int8_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint8_t NumberToken::get_uint8() const
{
  uint8_t value = 0;
  memcpy(&value, value_, sizeof(uint8_t));
  return value;
}

int16_t NumberToken::get_int16() const
{
  int16_t value = 0;
  memcpy(&value, value_, sizeof(int16_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint16_t NumberToken::get_uint16() const
{
  uint16_t value = 0;
  memcpy(&value, value_, sizeof(uint16_t));
  return value;
}

int32_t NumberToken::get_int32() const
{
  int32_t value = 0;
  memcpy(&value, value_, sizeof(int32_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint32_t NumberToken::get_uint32() const
{
  uint32_t value = 0;
  memcpy(&value, value_, sizeof(uint32_t));
  return value;
}

int64_t NumberToken::get_int64() const
{
  int64_t value = 0;
  memcpy(&value, value_, sizeof(int64_t));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint64_t NumberToken::get_uint64() const
{
  uint64_t value = 0;
  memcpy(&value, value_, sizeof(uint64_t));
  return value;
}

float NumberToken::get_float() const
{
  float value = 0;
  memcpy(&value, value_, sizeof(float));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

double NumberToken::get_double() const
{
  double value = 0;
  memcpy(&value, value_, sizeof(double));
  if (is_negative_)
  {
    value = -value;
  }

  return value;
}

uint8_t NameToken::get_type() const
{
  return LEXER_TOKEN_NAME;
}

NameToken* NameToken::as_name_token()
{
  return this;
}

const NameToken* NameToken::as_name_token() const
{
  return this;
}

uint8_t PunctuationToken::get_type() const
{
  return LEXER_TOKEN_PUNCTUATION;
}

PunctuationToken* PunctuationToken::as_punctuation_token()
{
  return this;
}

const PunctuationToken* PunctuationToken::as_punctuation_token() const
{
  return this;
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

const NumberToken* Lexer::read_number()
{
  size_t offset = current_offset_;

  bool is_negative = false;
  bool is_floating_point = false;
  std::string number_str;

  // check to see if this is a negative number
  if (offset > 0)
  {
    int c = current_line_[offset - 1];
    if (c == '-')
    {
      is_negative = true;
      number_str += c;
    }
  }

  int c = current_line_[offset];

  do
  {
    number_str += c;
    if (c == '.')
    {
      is_floating_point = true;
    }

    offset++;
    c = current_line_[offset];
  } while (
          (c >= '0' && c <= '9') ||
          (c == '.' && current_line_[current_offset_ + 1] >= '0' &&
          (c == '.' && current_line_[current_offset_ + 1] <= '9')));

  NumberToken *token = new NumberToken(this, current_lineno_, current_offset_, offset);
  if (is_floating_point)
  {
    size_t sz;
    double value = std::stod(number_str, &sz);
    token->set_compact_value(value);
  }
  else
  {
    if (is_negative)
    {
      size_t sz;
      int64_t value = std::stoll(number_str, &sz, 0);
      token->set_compact_value(value);
    }
    else
    {
      size_t sz;
      uint64_t value = std::stoull(number_str, &sz, 0);
      token->set_compact_value(value);
    }
  }

  current_offset_ = offset;
  return token;
}

const StringToken* Lexer::read_string()
{
  size_t offset = current_offset_;
  offset++; // skip over the first quote

  int c = current_line_[offset];
  std::string str;

  while (c != '\"' && c != '\'')
  {
    str += c;
    offset++;
    c = current_line_[offset];
  }

  StringToken *token = new StringToken(this, current_lineno_, current_offset_, offset);
  token->set_value(str);

  current_offset_ = offset;
  return token;
}

const NameToken* Lexer::read_name()
{
  size_t offset = current_offset_;
  int c = current_line_[offset];
  std::string name;

  do
  {
    name += c;
    offset++;
    c = current_line_[offset];
  } while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');

  NameToken *token = new NameToken(this, current_lineno_, current_offset_, offset);
  token->set_value(name);

  current_offset_ = offset;
  return token;
}

const LexerToken* Lexer::read()
{
  while (true)
  {
    auto it = current_line_.begin() + current_offset_;
    if (it >= current_line_.end())
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
      int c = current_line_[current_offset_];
      if ((c >= '0' && c <= '9') ||
          (c == '.' && current_line_[current_offset_ + 1] >= '0' &&
          (c == '.' && current_line_[current_offset_ + 1] <= '9')))
      {
        return read_number();
      }
      else if (c == '\"' || c == '\'')
      {
        return read_string();
      }
      else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
      {
        return read_name();
      }

      current_offset_++;
    } while (it < current_line_.end());
  }

  return nullptr;
}
