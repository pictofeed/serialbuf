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

#include "buffer.hpp"

TEST(BufferTests, write_uint8)
{
  Buffer *buffer = new Buffer();

  buffer->write_uint8(0);
  buffer->write_uint8(std::numeric_limits<uint8_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_uint8(), 0);
  ASSERT_EQ(buffer_iterator->read_uint8(), std::numeric_limits<uint8_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_int8)
{
  Buffer *buffer = new Buffer();

  buffer->write_int8(std::numeric_limits<int8_t>::min());
  buffer->write_int8(std::numeric_limits<int8_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_int8(), std::numeric_limits<int8_t>::min());
  ASSERT_EQ(buffer_iterator->read_int8(), std::numeric_limits<int8_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_uint16)
{
  Buffer *buffer = new Buffer();

  buffer->write_uint16(0);
  buffer->write_uint16(std::numeric_limits<uint16_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_uint16(), 0);
  ASSERT_EQ(buffer_iterator->read_uint16(), std::numeric_limits<uint16_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_int16)
{
  Buffer *buffer = new Buffer();

  buffer->write_int16(std::numeric_limits<int16_t>::min());
  buffer->write_int16(std::numeric_limits<int16_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_int16(), std::numeric_limits<int16_t>::min());
  ASSERT_EQ(buffer_iterator->read_int16(), std::numeric_limits<int16_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_uint32)
{
  Buffer *buffer = new Buffer();

  buffer->write_uint32(0);
  buffer->write_uint32(std::numeric_limits<uint32_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_uint32(), 0);
  ASSERT_EQ(buffer_iterator->read_uint32(), std::numeric_limits<uint32_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_int32)
{
  Buffer *buffer = new Buffer();

  buffer->write_int32(std::numeric_limits<int32_t>::min());
  buffer->write_int32(std::numeric_limits<int32_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_int32(), std::numeric_limits<int32_t>::min());
  ASSERT_EQ(buffer_iterator->read_int32(), std::numeric_limits<int32_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_uint64)
{
  Buffer *buffer = new Buffer();

  buffer->write_uint64(0);
  buffer->write_uint64(std::numeric_limits<uint64_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_uint64(), 0);
  ASSERT_EQ(buffer_iterator->read_uint64(), std::numeric_limits<uint64_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_int64)
{
  Buffer *buffer = new Buffer();

  buffer->write_int64(std::numeric_limits<int64_t>::min());
  buffer->write_int64(std::numeric_limits<int64_t>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_int64(), std::numeric_limits<int64_t>::min());
  ASSERT_EQ(buffer_iterator->read_int64(), std::numeric_limits<int64_t>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_float32)
{
  Buffer *buffer = new Buffer();

  buffer->write_float32(-std::numeric_limits<float>::max());
  buffer->write_float32(std::numeric_limits<float>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_float32(), -std::numeric_limits<float>::max());
  ASSERT_EQ(buffer_iterator->read_float32(), std::numeric_limits<float>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_float64)
{
  Buffer *buffer = new Buffer();

  buffer->write_float64(-std::numeric_limits<double>::max());
  buffer->write_float64(std::numeric_limits<double>::max());

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  ASSERT_EQ(buffer_iterator->read_float64(), -std::numeric_limits<double>::max());
  ASSERT_EQ(buffer_iterator->read_float64(), std::numeric_limits<double>::max());
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}

TEST(BufferTests, write_string)
{
  Buffer *buffer = new Buffer();

  std::string str = "A quick brown fox jumps over the lazy dog.";
  std::string str1 = "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG'S BACK 1234567890";
  buffer->write_string(str);
  buffer->write_string(str1);

  BufferIterator *buffer_iterator = new BufferIterator(buffer);
  EXPECT_TRUE(buffer_iterator->read_string().compare(str) == 0);
  EXPECT_TRUE(buffer_iterator->read_string().compare(str1) == 0);
  EXPECT_TRUE(buffer_iterator->get_remaining_size() == 0);

  delete buffer;
  delete buffer_iterator;
}
