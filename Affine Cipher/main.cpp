#include <iostream>

#include "affinecipher.h"

int main() {
  Caesa caesa_cipher_en;

  // Encrypt begin
  //----------------------------------------------------------------------
  std::cout << "Enter the plaintext: ";
  std::string str;
  std::cin >> str;
  caesa_cipher_en.set_plaintext(str);

  std::cout << "Enter shift number: ";
  int num;
  std::cin >> num;
  caesa_cipher_en.set_shift(num);

  caesa_cipher_en.encrypt();

  std::cout << std::endl
            << "Plaintext: " << caesa_cipher_en.get_plaintext() << std::endl
            << "Shift: " << caesa_cipher_en.get_shift() << std::endl
            << "Ciphertext: " << caesa_cipher_en.get_ciphertext() << std::endl;

  std::cout << "Encrypt end..." << std::endl << std::endl;
  //----------------------------------------------------------------------
  //  Encrypt end

  // Dectypt begin
  //----------------------------------------------------------------------
  Caesa caesa_cipher_de;

  std::cout << "Enter the ciphertext: ";
  std::cin >> str;
  caesa_cipher_de.set_ciphertext(str);

  std::cout << "Enter shift number: ";
  std::cin >> num;
  caesa_cipher_de.set_shift(num);

  caesa_cipher_de.decrypt();

  std::cout << std::endl
            << "Ciphertext: " << caesa_cipher_de.get_ciphertext() << std::endl
            << "Shift: " << caesa_cipher_de.get_shift() << std::endl
            << "Plaintext: " << caesa_cipher_de.get_plaintext() << std::endl;

  std::cout << "Decrypt end..." << std::endl << std::endl;

  //----------------------------------------------------------------------
  // Dectypt end

  return 0;
}