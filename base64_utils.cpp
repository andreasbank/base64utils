/**
 *
 * base64_utils.cpp: A C++ (11) base64 encoder/decoder.
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

#include <stdexcept>
#include <string>

#include "base64_utils.hpp"

using namespace std;

const string base64::chars(
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=");

string
base64::encode(const basic_string<unsigned char>& input) {
  return encode(input.c_str(), input.length());
}

string
base64::encode(const unsigned char *input, size_t input_size) {
  /**
   * Theory behind the encoding:
   *
   * encode64('Bank') -> 'QmFuaw=='
   *
   * chars/bytes  |    B    |    a    |    n    |    k    |
   * base64 bits  |010000|10 0110|0001 01|101110|011010|11 0000|00000|00000|
   * base64 codes |  16  |  38   |   5   |  46  |  26  |  48   |     |     |
   * translated   |   Q  |   m   |   F   |   u  |   a  |   w   |  =  |  =  |
   *
   * and append '=' as many times it takes to reach [output length] % 4 = 0,
   * also making sure that two '=' chars are added at the end after all the
   * calculations.
   */

  /* Size of the output is at most 137% of the original size */
  string output;
  int translated;
  for (size_t i = 0; i < input_size; i += 3) {
      translated = (input[i] & 0xFC) >> 2;
      output += chars[translated];
      translated = (input[i] & 0x03) << 4;
      if ((i + 1) < input_size) {
          translated |= (input[i + 1] & 0xF0) >> 4;
          output += chars[translated];
          translated = (input[i + 1] & 0x0F) << 2;
          if (i + 2 < input_size)  {
              translated |= (input[i + 2] & 0xC0) >> 6;
              output += chars[translated];
              translated = input[i + 2] & 0x3F;
              output += chars[translated];
          } else  {
              output += chars[translated];
              output += "=";
          }
      } else      {
        output += chars[translated];
        output += "==";
      }
  }

  return output;
}

basic_string<unsigned char>
base64::decode(const string& input)
{
  if (input.length() % 4 != 0)    {
    /* Input data is not padded correctly or not a base64-ecnoded string */
    throw invalid_argument("Invalid base64 encoded string");
  }

  basic_string<unsigned char> output(((input.length() * 3) / 4) -
      (input.find_first_of('=') != string::npos ?
      (input.length() - input.find_first_of('=')) : 0), '\0');
  int output_pos = 0;
  int translated[4];
  for (unsigned int i = 0; i < input.length(); i += 4) {
    translated[0] = chars.find_first_of(input[i]);
    translated[1] = chars.find_first_of(input[i + 1]);
    translated[2] = chars.find_first_of(input[i + 2]);
    translated[3] = chars.find_first_of(input[i + 3]);

    output[output_pos++] =
        static_cast<char>(((translated[0] << 2) | (translated[1] >> 4)));
    if (translated[2] < 64) {
      output[output_pos++] =
          static_cast<char>(((translated[1] << 4) | (translated[2] >> 2)));
      if (translated[3] < 64)  {
        output[output_pos++] =
            static_cast<char>(((translated[2] << 6) | translated[3]));
      }
    }
  }

  return output;
}


