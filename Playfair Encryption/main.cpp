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
  tuple<int, int, int, int> loc, swapedloc;
  tuple<char, char> encryedchars;
  string encryedstr;
  //---------------------------------------------------
  for (int i = 0; i < groupedstr.length(); i = i + 2) {
    {
      ch1 = groupedstr[i];
      ch2 = groupedstr[i + 1];

      cout << i << ' ' << ch1 << ch2 << " ";

      loc = charmaploc(ch1, ch2, pftable);
      swapedloc = encryprogress(loc);
      encryedchars = locmapchar(swapedloc, pftable);

      //  cout << get<0>(encryedchars) << get<1>(encryedchars) << "   ";

      encryedstr = encryedstr + get<0>(encryedchars) + get<1>(encryedchars);
    }
  }

  cout << endl << "Encryed text: " << endl;
  cout << encryedstr << endl;

  return 0;
}
