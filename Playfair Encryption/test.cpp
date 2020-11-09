#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
std::string rmstr_isspace(std::string str);

int main() {
  std::string str("Hello World");

  string s = rmstr_isspace(str);

  char s1;
  char s2;

  int i = 0;

  for (auto i : s) {
    s1 = tolower(s[i]);
    s2 = tolower(s[i + 1]);

    if (s1 == s2) {
      s.insert(i, "x");
        }

    i = i + 2;
    cout << s1 << s2 << endl;
  }

  return 0;
}
std::string rmstr_isspace(std::string srcstr) {
  std::string str = srcstr;

  str.erase(std::remove_if(str.begin(), str.end(),
                           [](unsigned char x) { return std::isspace(x); }),
            str.end());

  return str;
}
