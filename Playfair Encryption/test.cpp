#include <algorithm>
#include <iostream>
#include <set>
#include <string>

std::string rmstr_duplicates(std::string str);

int main() {
  std::string str = "anchadbvhjxbzbh";

  str = rmstr_duplicates(str);

  std::cout << str << '\n';

  return 0;
}
