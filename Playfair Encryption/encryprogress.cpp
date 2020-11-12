#include <array>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<int, int, int, int> encryprogress(pair<int, int> posch1,
                                        pair<int, int> posch2) {
  // rectangle
  if (posch1.first != posch2.first && posch1.second != posch2.second) {
    return make_tuple(posch1.first, posch2.second, posch1.first, posch2.second);
  }
  // on the same row
  else if (posch1.first == posch2.first && posch1.second != posch2.second) {
    return make_tuple(posch1.first, (posch1.second + 1) % 5, posch2.first,
                      (posch2.second + 1) % 5);

    // on the same col
  } else if (posch1.first != posch2.first && posch1.second == posch2.second) {
    return make_tuple((posch1.first + 1) % 5, posch1.second,
                      (posch2.first + 1) % 5, (posch2.second + 1) % 5);
  }
  // default return 0,0,0,0
  else {
    return make_tuple(0, 0, 0, 0);
  }
}

pair<int, int> locatelement(char c, array<array<char, 5>, 5>) {
  pair<int, int> location;

  location = make_pair(ch1, ch2);
}