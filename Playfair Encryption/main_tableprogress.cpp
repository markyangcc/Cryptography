#include "tableprogress.h"

int main() {
  array<array<char, 5>, 5> pftable;
  pftable = build_table();

  cout << "Main display:" << endl;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cout << pftable[i][j];
    }
    cout << endl;
  }

  // cout << endl << "Specify pos: " << pftable[2][1];

  return 0;
}