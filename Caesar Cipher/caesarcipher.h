#ifndef CAESARCIPHER_H_
#define CAESARCIPHER_H_

#include <string>

class CAESA {
 private:
  std::string plaintext;
  std::string ciphertext;
  int shift;

 public:
  CAESA();
  ~CAESA();

  std::string encrypt(const std::string &str, const int shift);
  std::string decrypt(const std::string &str, const int shift);
};

#endif