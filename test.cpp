/**
 * Tests for base64_utils
 */

#include <iostream>
#include <string>
#include "base64_utils.hpp"

using namespace std;

int
main(int argc, char **argv)
{
  string str("The brown fox jumped over the fence but got stuck and died!!!");
  basic_string<unsigned char> decoded_str(
      reinterpret_cast<const unsigned char *>(str.c_str()), str.length());
  string encoded_str(
      "VGhlIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgZmVuY2UgYnV0IGdvdCBzdHVjayBhbmQgZGllZCEhIQ==");

  string encode_result = base64::encode(decoded_str);
  if (encode_result.compare(encoded_str) != 0) {
    cout << "Encoding failed" << endl;
    cout << "'" << encode_result << "' != '";
  } else {
    cout << "Encoding passed" << endl;
    cout << "'" << encode_result << "' == '";
  }
  cout << encoded_str << "'" << endl;

  basic_string<unsigned char> decode_result = base64::decode(encoded_str);
  if (decode_result == decoded_str) {
    cout << "Decoding passed" << endl;
    cout << "'" << reinterpret_cast<const char *>(decode_result.c_str()) <<
        "' == '";
  } else {
    cout << "Decoding failed" << endl;
    cout << "'" << reinterpret_cast<const char *>(decode_result.c_str()) <<
        "' != '";
  }
  cout << reinterpret_cast<const char *>(decoded_str.c_str()) << "'" << endl;

  return 0;
}
