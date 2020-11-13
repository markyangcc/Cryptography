#include <algorithm>
#include <iostream>

using namespace std;

extern std::string rmstr_duplicates(std::string srcstr);
extern std::string rmstr_isspace(std::string srcstr);

string msgprogress(string s) {
  // remove space in string
  s = rmstr_isspace(s);

  char repchar = 'x';  // default fill character is 'x'

  char ch1;  // the first paired character
  char ch2;  // the second paired character

  for (int i = 0; i < (s.length() + 1) / 2; i++) {
    bool flag = false;
    for (int j = 0; j < s.length(); j = j + 2) {
      ch1 = s[j];
      ch2 = s[j + 1];

      if (ch1 == ch2 && ch1 == 'x') {
        repchar = 'q';
        // if the paired characters both are the special chararacter like 'x'
        // so change the fill character to 'q'
      }
      if (ch1 == ch2 && ch1 == 'q') {
        repchar = 'x';
      }
      if (ch1 == ch2) {
        s.insert(j + 1, &repchar);
        flag = true;
      }
      if (flag)
        break;  // use flag to jump out of two nested loop directly
                // if special character was inserted, break and loop the new
                // string
    }
  }

  // make all treated text characters can be paired (amount must be an even
  // number)
  if (s.length() % 2 != 0) {
    if (s[s.length()] == 'x')
      s += 'q';  // append 'q' to the last
    else
      s += 'x';  // else append 'x'
  }

  return s;
}
