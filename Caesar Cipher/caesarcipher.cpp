//
//                      Description
//
// encrypt： f(a)=(a+N) mod 26
// decrypt： f(a)=(a+(26-N)) mod 26
// a: character  N: shift(most of time it's 3)
// ---------------------------------------------------

#include "caesarcipher.h"

CAESA::CAESA() = default;

CAESA::~CAESA() = default;

std::string CAESA::encrypt(const std::string &str, const int shift) {
  std::string encryptedstr;

  for (int i = 0; i < str.size(); i++) {
    char lowerchar = tolower(str[i]);

    encryptedstr.push_back(static_cast<char>(
        ((static_cast<int>(lowerchar - 'a') + shift) % 26) + 'a'));
  }

  return encryptedstr;
}
std::string CAESA::decrypt(const std::string &str, const int shift) {
  std::string decryptedstr;

  for (int i = 0; i < str.size(); i++) {
    char lowerchar = tolower(str[i]);

    decryptedstr.push_back(static_cast<char>(
        ((static_cast<int>(lowerchar - 'a') + (26 - shift)) % 26) + 'a'));
  }

  return decryptedstr;
}