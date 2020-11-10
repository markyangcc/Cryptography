#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1;
  s1 = "helloxxxxld";

  char repchar = 'x';  // default fill character is 'x'

  char ch1;
  char ch2;

  for (int i = 0; i < (s1.length() + 1) / 2; i++) {
    bool flag = false;
    for (int j = 0; j < s1.length(); j = j + 2) {
      ch1 = s1[j];
      ch2 = s1[j + 1];

      if (ch1 == ch2 && ch1 == 'x') {
        repchar = 'q';
        // change fill character to 'q'
      }
      if (ch1 == ch2 && ch1 == 'q') {
        repchar = 'x';
      }
      if (ch1 == ch2) {
        s1.insert(j + 1, &repchar);
        cout << s1 << endl;
        flag = true;
      }
      if (flag == true)
        break;  // use flag to jump out of two nested loop directly
    }
  }
  cout << s1 << endl;

  return 0;
}