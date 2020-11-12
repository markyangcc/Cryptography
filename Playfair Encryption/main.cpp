#include <iostream>

#include "msgprogress.h"
#include "tableprogress.h"

int main() {
  array<array<char, 5>, 5> pftable = {0};

  pftable = build_table();

  cout << "Enter the plaintext: ";
  string str = "helloworld";
  getline(cin, str);

  string groupedstr = msgprogress(str);
  cout << "The grouped str is: " << groupedstr << endl << endl;

  cout << "Table display:" << endl;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cout << pftable[i][j];
    }
    cout << endl;
  }

  return 0;
}