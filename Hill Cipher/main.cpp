#include <iostream>
#include <string>
#include <vector>

#include "Eigen/Eigen"
#include "hill_decrypt.cpp"
#include "hill_encrypt.cpp"

using namespace Eigen;
using namespace std;

int main() {
  // get message
  cout << "Enter message to be encrypted: ";
  string plaintext;
  cin >> plaintext;

  vector<int> encryptedvec = encrypt(plaintext);

  string encryptedstr;
  for (auto i : encryptedvec) {
    i = i % 26;
    encryptedstr.push_back(char(i + 'a'));
  }
  cout << "Encrypted text: ";
  cout << encryptedstr << endl << endl;
  cout << "--------------------------------------" << endl;

  cout << "Enter the cipher numbers to be decrypted: ";
  vector<int> ciphervec;
  int temp;
  cin >> temp;
  while (temp != '\n') {
    ciphervec.push_back(temp);
    cin >> temp;
  }
  // vector<double> decryptedvec;
  vector<double> decryptedvec = decrypt(ciphervec);

  // cout << "Decrypted text: " << decrypted_text << endl;
}
