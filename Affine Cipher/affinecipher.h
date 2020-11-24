#ifndef AFFINECIPHER_H_
#define AFFINECIPHER_H_


#include <string>

class Caesa {
 private:
  std::string plaintext;
  std::string ciphertext;
  int shift;

 public:
  Caesa();
  ~Caesa();

  void set_plaintext(std::string str);
  void set_ciphertext(std::string str);
  void set_shift(int val);

  void encrypt();
  void decrypt();

  std::string &get_plaintext();
  std::string &get_ciphertext();
  int get_shift();
};

#endif