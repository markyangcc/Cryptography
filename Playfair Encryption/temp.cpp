#include <iostream>
#include <tuple>

using namespace std;
tuple<int, int, int> tu();
int main() {
  tuple<int, int, int> tumain;

  tumain = make_tuple(1, 2, 3);

  cout << get<2>(tumain);

  return 0;
}

tuple<int, int, int> tu() {
  tuple<int, int, int> temp;

  temp = make_tuple(0, 0, 1);

  return temp;
}