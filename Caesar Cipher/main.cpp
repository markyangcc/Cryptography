#include <iostream>
// #include <string>

#include "caesarcipher.cpp"

int main() {
  Caesa caesa_cipher;

  std::cout << "Enter the plaintext: ";
  std::string str;
  std::cin >> str;
  caesa_cipher.set_plaintext(str);

  std::cout << "Enter shift number: ";
  int num;
  std::cin >> num;
  caesa_cipher.set_shift(num);

  std::cout << caesa_cipher.get_plaintext().size() << std::endl;

  caesa_cipher.encrypt();

  std::cout << caesa_cipher.get_plaintext() << std::endl
            << caesa_cipher.get_ciphertext() << std::endl
            << caesa_cipher.get_shift() << std::endl;

  return 0;
}