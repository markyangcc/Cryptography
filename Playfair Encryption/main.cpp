#include <iostream>

#include "encrytext.h"
#include "maketable.h"
#include "msgtreat.h"

int main() {
  array<array<char, 5>, 5> pftable{};

  // get user input
  cout << "Enter the key: ";
  string key;
  getline(cin, key);

  pftable = build_table(key);

  cout << "Enter the plaintext(default \"hello world\"): " << endl;
  string str = "hello world";
  getline(cin, str);
  string treatedstr = msgprogress(str);

  cout << "The treated string: " << treatedstr << endl << endl;

  cout << "Table display:" << endl;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cout << pftable[i][j];
    }
    cout << endl;
  }

  string aftertext = encrytext(treatedstr, pftable);

  cout << aftertext << endl;

  return 0;
}
