#include "tableprogress.h"

int main() {
  array<array<char, 5>, 5> pftable = build_table();

  cout << "Main display:";

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cout << pftable[i][j];
    }
    cout << endl;
  }

  return 0;
}