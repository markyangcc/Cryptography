//
//                      Description
//
// encrypt： f(a)=(a+N) mod 26
// decrypt： f(a)=(a+(26-N)) mod 26
// a: character  N: shift(most of time it's 3)
// ---------------------------------------------------
#include "caesarcipher.h"

#include <iostream>

Caesa::Caesa() = default;

Caesa::~Caesa() = default;

void Caesa::set_plaintext(std::string str) { plaintext = str; }
void Caesa::set_ciphertext(std::string str) { ciphertext = str; }
void Caesa::set_shift(int val) { shift = val; }

std::string &Caesa::get_plaintext() { return plaintext; }
std::string &Caesa::get_ciphertext() { return ciphertext; }
int Caesa::get_shift() { return shift; }

void Caesa::encrypt() {
  for (int i = 0; i < plaintext.size(); i++) {
    char lowerchar = tolower(plaintext[i]);

    ciphertext.push_back(static_cast<char>(
        ((static_cast<int>(lowerchar - 'a') + shift) % 26) + 'a'));
  }
}
void Caesa::decrypt() {
  for (int i = 0; i < ciphertext.size(); i++) {
    char lowerchar = tolower(ciphertext[i]);

    plaintext.push_back(static_cast<char>(
        ((static_cast<int>(lowerchar - 'a') + (26 - shift)) % 26) + 'a'));
  }
}
