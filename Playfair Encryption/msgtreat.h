#include <algorithm>
#include <iostream>

#include "dependfunc.h"

using namespace std;

string msgprogress(string s) {
    s = rmstr_isspace(s);  // remove space in string

  char repchar = 'x';  // default fill character is 'x'

  char ch1;  // first paired character
  char ch2;  // second paired character

  for (int i = 0; i < (s.length() + 1) / 2; i++) {
    bool flag = false;
    for (int j = 0; j < s.length(); j = j + 2) {
      ch1 = s[j];
      ch2 = s[j + 1];

      if (ch1 == ch2 && ch1 == 'x') {
        repchar = 'q';
        // change fill character to 'q'
      }
      if (ch1 == ch2 && ch1 == 'q') {
        repchar = 'x';
      }
      if (ch1 == ch2) {
        s.insert(j + 1, &repchar);
        // cout << s << endl;
        flag = true;
      }
      if (flag) break;  // use flag to jump out of two nested loop directly
    }
  }

  // make all treated text characters can be paired
  if (s.length() % 2 != 0) {
    // cout << "Append an character to string last position" << endl;

    if (s[s.length()] == 'x')
      s += 'q';
    else
      s += 'x';  // then append 'x'
  }

  return s;
}
