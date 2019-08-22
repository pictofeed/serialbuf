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

#include "buffer.hpp"

Buffer::Buffer(const uint8_t *data, size_t size, size_t offset) : size_(size), offset_(offset)
{
  if (size > 0)
  {
    if (data != nullptr)
    {
      set_data(data, size);
    }
    else
    {
      pad(size);
    }
  }
}

Buffer::Buffer(const uint8_t *data, size_t size) : Buffer(data, size, 0)
{

}

Buffer::Buffer() : Buffer(nullptr, 0, 0)
{

}

Buffer::~Buffer()
{
  clear();
}

void Buffer::clear()
{
  if (data_ != nullptr)
  {
    free(data_);
    data_ = nullptr;
  }

  size_ = 0;
  offset_ = 0;
}

void Buffer::set_data(const uint8_t *data, size_t size)
{
  assert(data != nullptr);
  assert(size > 0);

  // clear our current data
  clear();

  // copy the new data
  data_ = (uint8_t*)calloc(size, 1);
  if (!data_)
  {
    throw std::runtime_error(StringFormatter() << "Failed to set buffer data with size: " << size);
  }

  memcpy(data_, data, size);
  size_ = size;
}

const uint8_t* Buffer::get_data() const
{
  return data_;
}

void Buffer::set_size(size_t size)
{
  size_ = size;
}

size_t Buffer::get_size() const
{
  return size_;
}

void Buffer::set_offset(size_t offset)
{
  offset_ = offset;
}

size_t Buffer::get_offset() const
{
  return offset_;
}

void Buffer::copy(Buffer *other_buffer)
{
  assert(other_buffer != nullptr);

  // prepare the other buffer for copying
  other_buffer->clear();
  other_buffer->resize(size_);

  // copy our contents to the other buffer
  other_buffer->set_data(data_, size_);
  other_buffer->set_offset(offset_);
}

bool Buffer::compare(const Buffer *other_buffer) const
{
  assert(other_buffer != nullptr);
  return (
    memcmp(data_, other_buffer->get_data(), size_) == 0 &&
    size_ == other_buffer->get_size() &&
    offset_ == other_buffer->get_offset());
}

void Buffer::resize(size_t size)
{
  assert(size > 0);
  size_t current_size = size_ - offset_;
  if (current_size >= size)
  {
    return;
  }

  data_ = (uint8_t*)realloc(data_, size_ + size);
  if (data_ == nullptr)
  {
    throw std::runtime_error(StringFormatter() << "Failed to resize buffer data with size: " << size);
  }

  memset(data_ + offset_, 0, size);
  size_ += size;
}

void Buffer::write(const uint8_t *data, size_t size)
{
  assert(data != nullptr);
  assert(size > 0);

  resize(size);
  memcpy(data_ + offset_, data, size);
  offset_ += size;
}

void Buffer::pad(size_t size)
{
  assert(size > 0);
  uint8_t *data = (uint8_t*)calloc(size, 1);
  if (data == nullptr)
  {
    throw std::runtime_error(StringFormatter() << "Failed to pad bytes with size: " << size);
  }

  write(data, size);
  free(data);
}

void Buffer::write_uint8(uint8_t value)
{
  resize(1);
  *(uint8_t*)(data_ + offset_) = value;
  offset_ += 1;
}

void Buffer::write_int8(int8_t value)
{
  resize(1);
  *(int8_t*)(data_ + offset_) = value;
  offset_ += 1;
}

void Buffer::write_uint16(uint16_t value)
{
  resize(2);
  *(uint16_t*)(data_ + offset_) = value;
  offset_ += 2;
}

void Buffer::write_int16(int16_t value)
{
  resize(2);
  *(int16_t*)(data_ + offset_) = value;
  offset_ += 2;
}

void Buffer::write_uint32(uint32_t value)
{
  resize(4);
  *(uint32_t*)(data_ + offset_) = value;
  offset_ += 4;
}

void Buffer::write_int32(int32_t value)
{
  resize(4);
  *(int32_t*)(data_ + offset_) = value;
  offset_ += 4;
}

void Buffer::write_uint64(uint64_t value)
{
  resize(8);
  *(uint64_t*)(data_ + offset_) = value;
  offset_ += 8;
}

void Buffer::write_int64(int64_t value)
{
  resize(8);
  *(int64_t*)(data_ + offset_) = value;
  offset_ += 8;
}

void Buffer::write_float32(float value)
{
  uint32_t v = 0;
  memcpy(&v, &value, 4);
  write_uint32(v);
}

void Buffer::write_float64(double value)
{
  uint64_t v = 0;
  memcpy(&v, &value, 8);
  write_uint64(v);
}

void Buffer::write_string8(const char *string, uint8_t size)
{
  write_uint8(size);
  write((const uint8_t*)string, size);
}

void Buffer::write_string8(std::string str)
{
  write_string8(str.c_str(), str.size());
}

void Buffer::write_string16(const char *string, uint16_t size)
{
  write_uint16(size);
  write((const uint8_t*)string, size);
}
void Buffer::write_string16(std::string str)
{
  write_string16(str.c_str(), str.size());
}

void Buffer::write_string32(const char *string, uint32_t size)
{
  write_uint32(size);
  write((const uint8_t*)string, size);
}

void Buffer::write_string32(std::string str)
{
  write_string32(str.c_str(), str.size());
}

void Buffer::write_string64(const char *string, uint64_t size)
{
  write_uint64(size);
  write((const uint8_t*)string, size);
}

void Buffer::write_string64(std::string str)
{
  write_string64(str.c_str(), str.size());
}

void Buffer::write_string(const char *string, size_t size)
{
  assert(size > 0);
  if (size <= std::numeric_limits<uint8_t>::max())
  {
    write_uint8(BufferStringTypes::STRING8);
    write_string8(string, size);
  }
  else if (size <= std::numeric_limits<uint16_t>::max())
  {
    write_uint8(BufferStringTypes::STRING16);
    write_string16(string, size);
  }
  else if (size <= std::numeric_limits<uint32_t>::max())
  {
    write_uint8(BufferStringTypes::STRING32);
    write_string32(string, size);
  }
  else if (size <= std::numeric_limits<uint64_t>::max())
  {
    write_uint8(BufferStringTypes::STRING64);
    write_string64(string, size);
  }
  else
  {
    throw std::runtime_error(StringFormatter() << "Cannot write string with invalid size: " << size);
  }
}

void Buffer::write_string(std::string str)
{
  write_string(str.c_str(), str.size());
}

void Buffer::write_padded_string(const char *string, size_t size, size_t padded_size)
{
  assert(size > 0);
  assert(padded_size > 0);
  if (size > padded_size)
  {
    throw std::runtime_error(StringFormatter() << "Cannot write padded string, string size: " << size << " exceeds padded size: " << padded_size);
  }

  // write the data
  write((const uint8_t*)string, size);

  // pad the remaining size left in the array
  size_t remaining_padding_size = padded_size - size;
  if (remaining_padding_size > 0)
  {
    pad(remaining_padding_size);
  }
}

void Buffer::write_padded_string(std::string str, size_t padded_size)
{
  write_padded_string(str.c_str(), str.size(), padded_size);
}

BufferIterator::BufferIterator(const Buffer *buffer, size_t offset)
  : buffer_(buffer), offset_(offset)
{

}

BufferIterator::BufferIterator(const Buffer *buffer)
  : BufferIterator(buffer, 0)
{

}

BufferIterator::BufferIterator() : BufferIterator(nullptr, 0)
{

}

BufferIterator::~BufferIterator()
{
  clear();
}

void BufferIterator::clear()
{
  buffer_ = nullptr;
  offset_ = 0;
}

void BufferIterator::set_buffer(const Buffer *buffer)
{
  buffer_ = buffer;
}

const Buffer* BufferIterator::get_buffer() const
{
  return buffer_;
}

void BufferIterator::set_offset(size_t offset)
{
  offset_ = offset;
}

size_t BufferIterator::get_offset() const
{
  return offset_;
}

void BufferIterator::copy(BufferIterator *other_buffer_iterator)
{
  assert(other_buffer_iterator != nullptr);

  // prepare the buffer iterator for copying
  other_buffer_iterator->clear();

  // copy our contents to the other buffer iterator
  other_buffer_iterator->set_buffer(buffer_);
  other_buffer_iterator->set_offset(offset_);
}

bool BufferIterator::compare(const BufferIterator *other_buffer_iterator) const
{
  assert(other_buffer_iterator != nullptr);

  const Buffer *buffer = buffer_;
  const Buffer *other_buffer = other_buffer_iterator->get_buffer();

  // handle comparison of a null buffer
  if (buffer == nullptr || other_buffer == nullptr)
  {
    return buffer == nullptr && other_buffer == nullptr;
  }

  return (
    buffer->compare(other_buffer) &&
    offset_ == other_buffer_iterator->get_offset());
}

size_t BufferIterator::get_remaining_size() const
{
  return buffer_->get_size() - offset_;
}

const uint8_t* BufferIterator::get_remaining_data() const
{
  return buffer_->get_data() + offset_;
}

uint8_t* BufferIterator::read(size_t size)
{
  assert(size > 0);
  size_t remaining_size = get_remaining_size();
  if (remaining_size < size)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read data from BufferIterator, not enough bytes remain: " << size << " bytes left: " << remaining_size);
  }

  uint8_t *data = (uint8_t*)calloc(size, 1);
  if (data == nullptr)
  {
    throw std::runtime_error(StringFormatter() << "Failed to read data from BufferIterator with size: " << size);
  }

  const uint8_t *remaining_data = get_remaining_data();
  memcpy(data, remaining_data, size);
  offset_ += size;
  return data;
}

void BufferIterator::skip_read(size_t size)
{
  assert(size > 0);
  size_t remaining_size = get_remaining_size();
  if (remaining_size < size)
  {
    throw std::runtime_error(StringFormatter() << "Cannot skip read for BufferIterator, not enough bytes remain: " << size << " bytes left: " << remaining_size);
  }

  offset_ += size;
}

uint8_t BufferIterator::read_uint8()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 1)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read uint8 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 1;
  return (uint8_t)data[offset];
}

int8_t BufferIterator::read_int8()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 1)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read int8 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 1;
  return (int8_t)data[offset];
}

uint16_t BufferIterator::read_uint16()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 2)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read uint16 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 2;
  uint16_t value = (uint16_t)data[offset + 1] << 8 |
                   (uint16_t)data[offset + 0] << 0;

  return value;
}

int16_t BufferIterator::read_int16()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 2)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read int16 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 2;
  int16_t value = (int16_t)data[offset + 1] << 8 |
                  (int16_t)data[offset + 0] << 0;

  return value;
}

uint32_t BufferIterator::read_uint32()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 4)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read uint32 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 4;
  uint32_t value = (uint32_t)data[offset + 3] << 24 |
                   (uint32_t)data[offset + 2] << 16 |
                   (uint32_t)data[offset + 1] <<  8 |
                   (uint32_t)data[offset + 0] <<  0;

  return value;
}

int32_t BufferIterator::read_int32()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 4)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read int32 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 4;
  int32_t value = (int32_t)data[offset + 3] << 24 |
                  (int32_t)data[offset + 2] << 16 |
                  (int32_t)data[offset + 1] <<  8 |
                  (int32_t)data[offset + 0] <<  0;

  return value;
}

uint64_t BufferIterator::read_uint64()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 8)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read uint64 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 8;
  uint64_t value = (uint64_t)data[offset + 7] << 56 |
                   (uint64_t)data[offset + 6] << 48 |
                   (uint64_t)data[offset + 5] << 40 |
                   (uint64_t)data[offset + 4] << 32 |
                   (uint64_t)data[offset + 3] << 24 |
                   (uint64_t)data[offset + 2] << 16 |
                   (uint64_t)data[offset + 1] <<  8 |
                   (uint64_t)data[offset + 0] <<  0;

  return value;
}

int64_t BufferIterator::read_int64()
{
  size_t remaining_size = get_remaining_size();
  if (remaining_size < 8)
  {
    throw std::runtime_error(StringFormatter() << "Cannot read int64 from BufferIterator, not enough bytes remain!");
  }

  const uint8_t *data = buffer_->get_data();
  assert(data != nullptr);

  size_t offset = offset_;
  offset_ += 8;
  int64_t value = (int64_t)data[offset + 7] << 56 |
                  (int64_t)data[offset + 6] << 48 |
                  (int64_t)data[offset + 5] << 40 |
                  (int64_t)data[offset + 4] << 32 |
                  (int64_t)data[offset + 3] << 24 |
                  (int64_t)data[offset + 2] << 16 |
                  (int64_t)data[offset + 1] <<  8 |
                  (int64_t)data[offset + 0] <<  0;

  return value;
}

float BufferIterator::read_float32()
{
  uint32_t value = read_uint32();
  float v = 0.0f;
  memcpy(&v, &value, 4);
  return v;
}

double BufferIterator::read_float64()
{
  uint64_t value = read_uint64();
  double v = 0.0f;
  memcpy(&v, &value, 8);
  return v;
}

std::string BufferIterator::read_string8()
{
  uint8_t size = read_uint8();
  uint8_t *data = read(size);
  std::string str((char*)data, size);
  free(data);
  return str;
}

std::string BufferIterator::read_string16()
{
  uint16_t size = read_uint16();
  uint8_t *data = read(size);
  std::string str((char*)data, size);
  free(data);
  return str;
}

std::string BufferIterator::read_string32()
{
  uint32_t size = read_uint32();
  uint8_t *data = read(size);
  std::string str((char*)data, size);
  free(data);
  return str;
}

std::string BufferIterator::read_string64()
{
  uint64_t size = read_uint64();
  uint8_t *data = read(size);
  std::string str((char*)data, size);
  free(data);
  return str;
}

std::string BufferIterator::read_string()
{
  uint8_t string_type = read_uint8();
  switch (string_type)
  {
    case BufferStringTypes::STRING8:
      return read_string8();
    case BufferStringTypes::STRING16:
      return read_string16();
    case BufferStringTypes::STRING32:
      return read_string32();
    case BufferStringTypes::STRING64:
      return read_string64();
    default:
      throw std::runtime_error(StringFormatter() << "Failed to read string of unknown type: " << string_type);
  }
}

std::string BufferIterator::read_padded_string(size_t padded_size)
{
  assert(padded_size > 0);
  uint8_t *data = read(padded_size);
  std::string str((char*)data, padded_size);
  free(data);
  return str;
}
