#pragma once
/**
 *
 * base64_utils.hpp: Header file for the C++ (11) base64 encoder/decoder.
 *
 * Author: Andreas Bank, andreas.mikael.bank@gmail.com
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#include <string>

class base64
{
  static const std::string chars;
public:

  /**
   * Encode a binary string as base64.
   *
   * @param str The binary string to encode.
   *
   * @return A base64 encoded string.
   */
  static std::string encode(const std::basic_string<unsigned char>& input);

  /**
   * Encode a binary string as base64.
   *
   * @param str The binary string to encode.
   *
   * @return A base64 encoded string.
   */
  static std::string encode(const unsigned char *str, size_t input_size);

  /**
   * Decode a base64 string.
   *
   * @param str The string to decode.
   *
   * @return A decoded string.
   */
  static std::basic_string<unsigned char> decode(const std::string& str);
};
