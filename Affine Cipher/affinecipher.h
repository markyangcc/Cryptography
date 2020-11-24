#ifndef AFFINECIPHER_H_
#define AFFINECIPHER_H_

#include <string>

class Affine {
 private:
  std::string plaintext;
  std::string ciphertext;
  int key;
  int shift;

 public:
  Affine();
  ~Affine();

  void set_plaintext(std::string str);
  void set_ciphertext(std::string str);
  void set_key(int val);
  void set_shift(int val);

  void encrypt();
  void decrypt();

  std::string &get_plaintext();
  std::string &get_ciphertext();
  int get_key();
  int get_shift();
};

#endif