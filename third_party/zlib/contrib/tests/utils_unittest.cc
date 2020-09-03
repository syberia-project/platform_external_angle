// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the Chromium source repository LICENSE file.

#include "infcover.h"

#include <cstddef>
#include <vector>

#include "compression_utils_portable.h"
#include "gtest.h"
#include "zlib.h"

void TestPayloads(size_t input_size, zlib_internal::WrapperType type) {
  std::vector<unsigned char> input;
  input.reserve(input_size);
  for (size_t i = 1; i <= input_size; ++i)
    input.push_back(i & 0xff);

  // If it is big enough for GZIP, will work for other wrappers.
  std::vector<unsigned char> compressed(
      zlib_internal::GzipExpectedCompressedSize(input.size()));
  std::vector<unsigned char> decompressed(input.size());

  // Libcores's java/util/zip/Deflater default settings: ZLIB,
  // DEFAULT_COMPRESSION and DEFAULT_STRATEGY.
  unsigned long compressed_size = static_cast<unsigned long>(compressed.size());
  int result = zlib_internal::CompressHelper(
      type, compressed.data(), &compressed_size, input.data(), input.size(),
      Z_DEFAULT_COMPRESSION, nullptr, nullptr);
  ASSERT_EQ(result, Z_OK);

  unsigned long decompressed_size =
      static_cast<unsigned long>(decompressed.size());
  result = zlib_internal::UncompressHelper(type, decompressed.data(),
                                           &decompressed_size,
                                           compressed.data(), compressed_size);
  ASSERT_EQ(result, Z_OK);
  EXPECT_EQ(input, decompressed);
}

TEST(ZlibTest, ZlibWrapper) {
  // Minimal ZLIB wrapped short stream size is about 8 bytes.
  for (size_t i = 1; i < 1024; ++i)
    TestPayloads(i, zlib_internal::WrapperType::ZLIB);
}

TEST(ZlibTest, GzipWrapper) {
  // GZIP should be 12 bytes bigger than ZLIB wrapper.
  for (size_t i = 1; i < 1024; ++i)
    TestPayloads(i, zlib_internal::WrapperType::GZIP);
}

TEST(ZlibTest, RawWrapper) {
  // RAW has no wrapper (V8 Blobs is a known user), size
  // should be payload_size + 2 for short payloads.
  for (size_t i = 1; i < 1024; ++i)
    TestPayloads(i, zlib_internal::WrapperType::ZRAW);
}

TEST(ZlibTest, InflateCover) {
  cover_support();
  cover_wrap();
  cover_back();
  cover_inflate();
  // TODO(cavalcantii): enable this last test.
  // cover_trees();
  cover_fast();
}

TEST(ZlibTest, DeflateStored) {
  const int no_compression = 0;
  const zlib_internal::WrapperType type = zlib_internal::WrapperType::GZIP;
  std::vector<unsigned char> input(1 << 10, 42);
  std::vector<unsigned char> compressed(
      zlib_internal::GzipExpectedCompressedSize(input.size()));
  std::vector<unsigned char> decompressed(input.size());
  unsigned long compressed_size = static_cast<unsigned long>(compressed.size());
  int result = zlib_internal::CompressHelper(
      type, compressed.data(), &compressed_size, input.data(), input.size(),
      no_compression, nullptr, nullptr);
  ASSERT_EQ(result, Z_OK);

  unsigned long decompressed_size =
      static_cast<unsigned long>(decompressed.size());
  result = zlib_internal::UncompressHelper(type, decompressed.data(),
                                           &decompressed_size,
                                           compressed.data(), compressed_size);
  ASSERT_EQ(result, Z_OK);
  EXPECT_EQ(input, decompressed);
}

TEST(ZlibTest, StreamingInflate) {
  uint8_t comp_buf[4096], decomp_buf[4096];
  z_stream comp_strm, decomp_strm;
  int ret;

  std::vector<uint8_t> src;
  for (size_t i = 0; i < 1000; i++) {
    for (size_t j = 0; j < 40; j++) {
      src.push_back(j);
    }
  }

  // Deflate src into comp_buf.
  comp_strm.zalloc = Z_NULL;
  comp_strm.zfree = Z_NULL;
  comp_strm.opaque = Z_NULL;
  ret = deflateInit(&comp_strm, Z_BEST_COMPRESSION);
  ASSERT_EQ(ret, Z_OK);
  comp_strm.next_out = comp_buf;
  comp_strm.avail_out = sizeof(comp_buf);
  comp_strm.next_in = src.data();
  comp_strm.avail_in = src.size();
  ret = deflate(&comp_strm, Z_FINISH);
  ASSERT_EQ(ret, Z_STREAM_END);
  size_t comp_sz = sizeof(comp_buf) - comp_strm.avail_out;

  // Inflate comp_buf one 4096-byte buffer at a time.
  decomp_strm.zalloc = Z_NULL;
  decomp_strm.zfree = Z_NULL;
  decomp_strm.opaque = Z_NULL;
  ret = inflateInit(&decomp_strm);
  ASSERT_EQ(ret, Z_OK);
  decomp_strm.next_in = comp_buf;
  decomp_strm.avail_in = comp_sz;

  while (decomp_strm.avail_in > 0) {
    decomp_strm.next_out = decomp_buf;
    decomp_strm.avail_out = sizeof(decomp_buf);
    ret = inflate(&decomp_strm, Z_FINISH);
    ASSERT_TRUE(ret == Z_OK || ret == Z_STREAM_END || ret == Z_BUF_ERROR);

    // Verify the output bytes.
    size_t num_out = sizeof(decomp_buf) - decomp_strm.avail_out;
    for (size_t i = 0; i < num_out; i++) {
      EXPECT_EQ(decomp_buf[i], src[decomp_strm.total_out - num_out + i]);
    }
  }

  // Cleanup memory (i.e. makes ASAN bot happy).
  ret = deflateEnd(&comp_strm);
  EXPECT_EQ(ret, Z_OK);
  ret = inflateEnd(&decomp_strm);
  EXPECT_EQ(ret, Z_OK);
}
