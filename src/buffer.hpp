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

#ifndef _BUFFER_H
#define _BUFFER_H

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <iostream>
#include <string>

#include "utils.hpp"

typedef enum : uint8_t
{
  STRING8 = 0,
  STRING16,
  STRING32,
  STRING64
} BufferStringTypes;

class Buffer
{
public:
  Buffer(const uint8_t *data, size_t size, size_t offset);
  Buffer(const uint8_t *data, size_t size);
  Buffer();
  virtual ~Buffer();

  void clear();

  void set_data(const uint8_t *data, size_t size);
  const uint8_t* get_data() const;

  void set_size(size_t size);
  size_t get_size() const;

  void set_offset(size_t offset);
  size_t get_offset() const;

  bool compare(const Buffer *other_buffer) const;
  void copy(Buffer *other_buffer);

  void resize(size_t size);
  void write(const uint8_t *data, size_t size);
  void pad(size_t size);

  void write_uint8(uint8_t value);
  void write_int8(int8_t value);

  void write_uint16(uint16_t value);
  void write_int16(int16_t value);

  void write_uint32(uint32_t value);
  void write_int32(int32_t value);

  void write_uint64(uint64_t value);
  void write_int64(int64_t value);

  void write_float32(float value);
  void write_float64(double value);

  void write_string8(const char *string, uint8_t size);
  void write_string8(std::string str);

  void write_string16(const char *string, uint16_t size);
  void write_string16(std::string str);

  void write_string32(const char *string, uint32_t size);
  void write_string32(std::string str);

  void write_string64(const char *string, uint64_t size);
  void write_string64(std::string str);

  void write_string(const char *string, size_t size);
  void write_string(std::string str);

  void write_padded_string(const char *string, size_t size, size_t padded_size);
  void write_padded_string(std::string str, size_t padded_size);

protected:
  uint8_t *data_ = nullptr;
  size_t size_ = 0;
  size_t offset_ = 0;
};

class BufferIterator
{
public:
  BufferIterator(const Buffer *buffer, size_t offset);
  BufferIterator(const Buffer *buffer);
  BufferIterator();
  virtual ~BufferIterator();

  void clear();

  void set_buffer(const Buffer *buffer);
  const Buffer* get_buffer() const;

  void set_offset(size_t offset);
  size_t get_offset() const;

  void copy(BufferIterator *other_buffer_iterator);
  bool compare(const BufferIterator *other_buffer_iterator) const;

  size_t get_remaining_size();
  const uint8_t* get_remaining_data();

  uint8_t* read(size_t size);
  void skip_read(size_t size);

  uint8_t read_uint8();
  int8_t read_int8();

  uint16_t read_uint16();
  int16_t read_int16();

  uint32_t read_uint32();
  int32_t read_int32();

  uint64_t read_uint64();
  int64_t read_int64();

  float read_float32();
  double read_float64();

  std::string read_string8();
  std::string read_string16();
  std::string read_string32();
  std::string read_string64();

  std::string read_string();

  std::string read_padded_string(size_t padded_size);

protected:
  const Buffer *buffer_ = nullptr;
  size_t offset_ = 0;
};

#endif // _BUFFER_H
