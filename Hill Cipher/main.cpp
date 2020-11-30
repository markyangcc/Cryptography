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
  cout << "The eccrypted numbers:";
  for (auto i : encryptedvec) {
    cout << i << " ";
    i = i % 26;
    encryptedstr.push_back(char(i + 'a'));
  }
  cout << endl << "Encrypted text: ";
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

  string decryptedstr;
  for (auto i : decryptedvec) {
    decryptedstr.push_back(char(i + 'a'));
  }

  cout << "Encrypted text: " << decryptedstr << endl << endl;
}
