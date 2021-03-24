//
//                      Description
//
// Encryption function： E(x)=(ax+b) mod m
// Decryption function: D(x)=a^-1(x-b)mod m
// modulus m is the size of the alphabet and a and b are the keys of the cipher.
// The value a must be chosen such that a and m are coprime.
//
// The Caesar cipher is an Affine cipher with a = 1,
// since the encrypting function simply reduces to a linear shift. ----wikipedia
// -------------------------------------------------------------------------------

#include "affinecipher.h"

#include <algorithm>
#include <iostream>

Affine::Affine() = default;

Affine::~Affine() = default;

void Affine::set_plaintext(std::string str) { plaintext = str; }
void Affine::set_ciphertext(std::string str) { ciphertext = str; }
void Affine::set_key(int val) { key = val; }
void Affine::set_shift(int val) { shift = val; }

std::string &Affine::get_plaintext() { return plaintext; }
std::string &Affine::get_ciphertext() { return ciphertext; }
int Affine::get_key() { return key; }
int Affine::get_shift() { return shift; }

void Affine::encrypt()
{
  // Only when key is reciprocal to 26 is a modulo-reversible, in other words,
  // the affine cipher is reversible (can be both encrypted and decrypted).
  if (std::__gcd(key, 26) == 1)
  {
    for (int i = 0; i < plaintext.size(); i++)
    {
      char lowerchar = tolower(plaintext[i]);
      ciphertext.push_back(static_cast<char>(
          ((key * (static_cast<int>(lowerchar - 'a')) + shift) % 26) + 'a'));
    }
  }
}
void Affine::decrypt()
{
  int coprimeval;
  for (int i = 0; i < 26; i++)
  {
    if (((i * key) % 26) == 1)
      coprimeval = i;
  }

  // The greatest common divisor（gcd） is equal to 1, then prove that the two
  // numbers are relatively prime
  if (std::__gcd(key, 26) == 1)
  {
    for (int i = 0; i < ciphertext.size(); i++)
    {
      char lowerchar = tolower(ciphertext[i]);
      // If the result of multiplying a, b by 26 modulo is 1, then b is the
      // modulo-inverse of a
      // a--key, b ---mod_val
      int mod_val =
          (coprimeval * ((static_cast<int>(lowerchar - 'a')) - shift)) % 26;
      // make c++ % operator result be positive, when one num is negative and
      // the other is positive, to meet the demand
      if (mod_val < 0)
        mod_val += 26;

      plaintext.push_back(static_cast<char>(mod_val + 'a'));
    }
  }
}
