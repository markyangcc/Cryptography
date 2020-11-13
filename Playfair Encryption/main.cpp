#include <iostream>

#include "encryprogress.h"
#include "msgprogress.h"
#include "tableprogress.h"

int main() {
  array<array<char, 5>, 5> pftable = {0};

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

  char ch1, ch2;
  tuple<char, char> encryedchars;
  string encryedstr;
  //---------------------------------------------------
  for (int i = 0; i < groupedstr.length(); i = i + 2) {
    {
      ch1 = groupedstr[i];
      ch2 = groupedstr[i + 1];

      cout << i << ' ' << ch1 << ch2 << " ";

      auto loc = charmaploc(ch1, ch2, pftable);
      auto swapedloc = encryprogress(loc);

      cout << "Swaped location:";
      cout << get<0>(swapedloc) << get<1>(swapedloc) << get<2>(swapedloc)
           << get<3>(swapedloc) << endl;

      encryedchars = locmapchar(swapedloc, pftable);

      encryedstr = encryedstr + get<0>(encryedchars) + get<1>(encryedchars);
    }
  }

  cout << endl << "Encryed text: " << endl;
  cout << encryedstr << endl;

  return 0;
}
