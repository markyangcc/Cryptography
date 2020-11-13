#include <iostream>

#include "encrytext.h"
#include "maketable.h"
#include "msgtreat.h"

int main() {
  array<array<char, 5>, 5> pftable{};

  pftable = build_table();

  cout << "Enter the plaintext: default helloworld" << endl;
  string str = "hellworld";
  // getline(cin, str);

  string groupedstr = msgprogress(str);
  cout << "The grouped str is: " << groupedstr << endl << endl;

  cout << "Table display:" << endl;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cout << pftable[i][j];
    }
    cout << endl;
  }

  string aftertext = encrytext(groupedstr, pftable);

  cout << aftertext << endl;

  return 0;
}
