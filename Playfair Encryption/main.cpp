#include <iostream>

#include "encryprogress.h"
#include "msgprogress.h"
#include "tableprogress.h"

int main() {
  array<array<char, 5>, 5> pftable = {0};

  pftable = build_table();

  cout << "Enter the plaintext: default helloworld" << endl;
  string str = "helloworld";
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

  char ch1, ch2;
  tuple<int, int, int, int> loctu, encryedtu;
  tuple<char, char> encrytu;
  //---------------------------------------------------
  for (int i = 0; i < (str.length() + 1) / 2; i++) {
    bool flag = false;
    for (int j = 0; j < str.length(); j = j + 2) {
      ch1 = str[j];
      ch2 = str[j + 1];

      loctu = charmaploc(ch1, ch2, pftable);
      encryedtu = encryprogress(loctu);
      locmapchar(loctu, pftable);

      if (flag == true)
        break;  // use flag to jump out of two nested loop directly
    }
  }

  return 0;
}