#include <iostream>
#include <string>
#include <vector>

#include "Eigen/Eigen"
#include "hill_encrypt.cpp"

using namespace Eigen;
using namespace std;

int main() {
  // get message
  cout << "Enter message to be encrypted: ";
  string plaintext;
  cin >> plaintext;

  string encryptedstr = encrypt(plaintext);

  cout << "Encrypted text: " << encryptedstr << endl << endl;

  cout << "--------------------------------------" << endl;

  cout << "Enter the ciphertext to be decrypted: ";
  string ciphertext;
  cin >> ciphertext;

  string decryptedstr ;

}
