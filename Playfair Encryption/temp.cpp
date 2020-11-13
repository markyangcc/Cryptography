// #include <iostream>
// #include <tuple>

// using namespace std;
// tuple<int, int, int> &tu();
// int main() {
//   // tuple<char, char, char> tumain;

//   auto (value1, value2, value3) = tu();

//   // cout << get<2>(tumain);

//   // string s = "helloworld";

//   // cout << s.length() << endl;

//   cout << "Tuple:";
//   cout << get<0>(tumain) << get<1>(tumain);

//   // cout << s;

//   return 0;
// }

// tuple<int, int, int> &tu() {
//   tuple<int, int, int> temp;

//   temp = make_tuple(0, 0, 1);

//   return temp;
// }

#include <iostream>
#include <tuple>
using namespace std;

auto foo() {
  return make_tuple(0, 1, 2);  // Return the local structure
}

int main() {
  auto t = foo();  // structured binding declaration
  cout << get<0>(t) << endl;
}
