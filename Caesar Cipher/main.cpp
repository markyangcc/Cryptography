#include <iostream>
// #include <string>

#include "caesarcipher.h"

int main() {
  Caesa caesa_cipher;

  std::cout << "Enter the plaintext: ";
  std::string str;
  std::cin >> str;
  caesa_cipher.set_plaintext(str);

  caesa_cipher.encrypt(caesa_cipher.get_ciphertext(), caesa_cipher.get_shift());


  return 0;
}