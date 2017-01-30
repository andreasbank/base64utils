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
  string decoded_str("The brown fox jumped over the fence but got stuck and died!!!");
  string encoded_str("VGhlIGJyb3duIGZveCBqdW1wZWQgb3ZlciB0aGUgZmVuY2UgYnV0IGdvdCBzdHVjayBhbmQgZGllZCEhIQ==");

  string result = base64::encode(decoded_str);
  if (result.compare(encoded_str) != 0) {
    cout << "Encoding failed" << endl;
    cout << "'" << result << "' != '" << encoded_str << "'" << endl;
  } else {
    cout << "Encoding passed" << endl;
  }

  result = base64::decode(encoded_str);
  if (result.compare(decoded_str) != 0) {
    cout << "Decoding failed" << endl;
    cout << "'" << result << "' != '" << decoded_str << "'" << endl;
  } else {
    cout << "Decoding passed" << endl;
  }

  return 0;
}
