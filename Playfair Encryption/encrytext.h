#include <array>
#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<int, int, int, int> swapcharsloc(tuple<int, int, int, int> loc);
tuple<int, int, int, int> charmaploc(char ch1, char ch2,
                                     array<array<char, 5>, 5> table);
tuple<char, char> locmapchar(tuple<int, int, int, int> loc,
                             array<array<char, 5>, 5> table);

// string groupedstr is copied everytime, so make it a reference
string encrytext(const string &groupedstr, array<array<char, 5>, 5> pftable) {
  char ch1, ch2;
  tuple<char, char> encryedchars;
  string encryedstr;
  //---------------------------------------------------
  for (int i = 0; i < groupedstr.length(); i = i + 2) {
    {
      ch1 = groupedstr[i];
      ch2 = groupedstr[i + 1];

      auto loc = charmaploc(ch1, ch2, pftable);
      auto swapedloc = swapcharsloc(loc);

      encryedchars = locmapchar(swapedloc, pftable);

      // contcatenates encryed characters into string

      encryedstr += get<0>(encryedchars);
      encryedstr += get<1>(encryedchars);
    }
  }

  return encryedstr;
}

tuple<int, int, int, int> swapcharsloc(tuple<int, int, int, int> loc) {
  // rectangle shape
  if (get<0>(loc) != get<2>(loc) && get<1>(loc) != get<3>(loc)) {
    return make_tuple(get<0>(loc), get<3>(loc), get<2>(loc), get<1>(loc));
  }
  // on the same row
  else if (get<0>(loc) == get<2>(loc) && get<1>(loc) != get<3>(loc)) {
    return make_tuple(get<0>(loc), (get<1>(loc) + 1) % 5, get<2>(loc),
                      (get<3>(loc) + 1) % 5);
    // on the same col
  } else if (get<0>(loc) != get<2>(loc) && get<1>(loc) == get<3>(loc)) {
    return make_tuple((get<0>(loc) + 1) % 5, get<1>(loc), (get<2>(loc) + 1) % 5,
                      get<3>(loc));
  } else {
    return make_tuple(0, 0, 0, 0);
  }
}

tuple<int, int, int, int> charmaploc(char ch1, char ch2,
                                     array<array<char, 5>, 5> table) {
  tuple<int, int, int, int> locations;

  for (int i = 0; i < 5; i++)  // hard encoding
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