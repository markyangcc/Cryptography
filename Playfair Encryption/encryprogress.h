#ifndef ENCRY_H_
#define ENCRY_H

#include <array>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

// ugly code......
tuple<int, int, int, int> encryprogress(tuple<int, int, int, int> loc) {
  // rectangle

  tuple<int, int, int, int> location;

  cout << "Not swaped location:";
  cout << get<0>(loc) << get<1>(loc) << get<2>(loc) << get<3>(loc) << endl;

  if (get<0>(loc) != get<2>(loc) && get<1>(loc) != get<3>(loc)) {
    location = make_tuple(get<0>(loc), get<3>(loc), get<2>(loc), get<1>(loc));
    return location;
  }
  // on the same row
  else if (get<0>(loc) == get<2>(loc) && get<1>(loc) != get<3>(loc)) {
    location = make_tuple(get<0>(loc), (get<1>(loc) + 1) % 5, get<2>(loc),
                          (get<3>(loc) + 1) % 5);
    return location;

    // on the same col
  } else if (get<0>(loc) != get<2>(loc) && get<1>(loc) == get<3>(loc)) {
    location = make_tuple((get<0>(loc) + 1) % 5, get<1>(loc),
                          (get<2>(loc) + 1) % 5, get<3>(loc));

    return location;
  }
  // default return 0,0,0,0
  else {
    location = make_tuple(0, 0, 0, 0);
    return location;
  }
}

tuple<int, int, int, int> charmaploc(char ch1, char ch2,
                                     array<array<char, 5>, 5> table) {
  tuple<int, int, int, int> locations;

  for (int i = 0; i < 5; i++)  // hard coding
    for (int j = 0; j < 5; j++) {
      if (table[i][j] == ch1) {
        get<0>(locations) = i;
        get<1>(locations) = j;
      }
      if (table[i][j] == ch2) {
        get<2>(locations) = i;
        get<3>(locations) = j;
      }
    }

  return locations;
}

tuple<char, char> locmapchar(tuple<int, int, int, int> loc,
                             array<array<char, 5>, 5> table) {
  return make_tuple(table[get<0>(loc)][get<1>(loc)],
                    table[get<2>(loc)][get<3>(loc)]);
}

#endif