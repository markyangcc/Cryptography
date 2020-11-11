#include <iostream>
#include <string>

#include "msgprogress.h"

using namespace std;

int main() {
  cout << "Enter the plaintext: ";
  string str = "helloworld";
  getline(cin, str);

  cout << "-------" << str[str.length()-1] << endl;
  string groupedstr;

  groupedstr = msgprogress(str);

  cout << groupedstr;

  return 0;
}
