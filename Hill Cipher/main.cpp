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
  cout << "How many cipher numbers: ";
  int num;
  cin >> num;
  cout << "Enter the cipher numbers to be decrypted: ";
  vector<int> ciphervec;

  for (int i = 0; i < num; i < ++i) {
    int input;
    cin >> input;
    ciphervec.push_back(input);
  }

  vector<double> decryptedvec = decrypt(ciphervec);

  string encryptedstr;
  for (auto i : decryptedvec) {
    encryptedstr.push_back(char(i + 'a'));
  }

  cout << "Encrypted text: " << encryptedstr << endl << endl;
}
