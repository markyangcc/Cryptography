#include <iostream>
#include <tuple>

using namespace std;
tuple<int, int, int> tu();
int main() {
  tuple<char, char, char> tumain;

  tumain = make_tuple('a', 'b', 'c');

  // cout << get<2>(tumain);

  string s = "helloworld";

  cout << s.length() << endl;

  s = s + get<0>(tumain) + get<1>(tumain);

  cout << s;

  return 0;
}

tuple<int, int, int> tu() {
  tuple<int, int, int> temp;

  temp = make_tuple(0, 0, 1);

  return temp;
}