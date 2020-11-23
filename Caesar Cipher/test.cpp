#include <iostream>
#include <string>

using namespace std;

int main() {
  string str = "abc";

  cout << 'z' - 'a';
  string encryptedstr;

  for (int i = 0; i < str.size(); i++) {
    char lowerchar = tolower(str[i]);
    encryptedstr.push_back(static_cast<char>(
        ((static_cast<int>(lowerchar - 'a') + 26 - 3) % 26) + 'a'));
  }

  cout << "str:" << str << endl;
  cout << "encryptedstr:" << encryptedstr << endl;

  return 0;
}