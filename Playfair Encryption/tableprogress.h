#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "somefunc.h"

using namespace std;

std::string rmstr_duplicates(std::string str);
std::string rmstr_isspace(std::string str);

array<array<char, 5>, 5> build_table();

array<array<char, 5>, 5> build_table() {
  array<array<char, 5>, 5> table = {0};

  // get user input
  // cout << "Enter the key: ";
  // string key;
  // getline(cin, key);

  cout << "Default key: Playfair example" << endl;
  string key = "Playfair example";

  // make std key
  // TODO: try replace set to unordered_set to relize same funcrion, to
  // simpifily code
  string tarstr = rmstr_duplicates(key);
  tarstr = rmstr_isspace(tarstr);

  // cout << tarstr << endl;
  // cout << tarstr.length() << endl;

  // add key to table
  // int pos = 0;
  // int continue_i = 0, continue_j = 0;  // Calc Next start position to fill
  // table for (int i = 0; i < 5; i++) {
  //   for (int j = 0; j < 5; j++) {
  //     if (pos <= tarstr.length()) {
  //       table[i][j] = tarstr[pos++];
  //       // cout << "Pos: " << pos;
  //       continue_j = (pos - 1) % 5;
  //       continue_i = (pos - continue_j) / 5;
  //       // cout <<endl<< "Pos: " << pos;
  //     }
  //   }
  // }

  // cout << continue_i << "  " << continue_j << endl;

  // cout << "tarstr: " << tarstr << endl;
  //------------------------------------------------------

  string alphastr = "abcdefghijklmnopqrstuvwxyz";

  set<char> alpha(begin(alphastr), end(alphastr));

  set<char> settarstr(begin(tarstr), end(tarstr));

  // clac symDifference set
  set<char> v1 = alpha;
  set<char> v2 = settarstr;

  // cout << "set_symmetric_difference" << endl;
  std::vector<char> symDifference;
  std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                                std::back_inserter(symDifference));

  set<char> lefalpha(begin(symDifference), end(symDifference));

  // check size() to check if function works successed
  // cout << "symDifference size: " << symDifference.size() << endl;

  vector<char> omitij = symDifference;
  // cout << "omitij size: " << omitij.size() << endl;

  // std::find() Returns an iterator to the first element in the range
  // [first,last) that compares equal to val. If no such element is found, the
  // function returns last.
  //!= end() means find, ==end() means not found

  // handle i/j problems
  if (settarstr.find('i') != settarstr.end() &&
      settarstr.find('j') != settarstr.end()) {
    cout << "Found i and j in target str" << endl;
    settarstr.erase('j');
  } else if (settarstr.find('i') != settarstr.end() &&
             settarstr.find('j') == settarstr.end()) {
    cout << "Found i, but not dound j in target str" << endl;

    lefalpha.erase('j');

  } else if (settarstr.find('j') != settarstr.end() &&
             settarstr.find('i') == settarstr.end()) {
    cout << "Found j, but not dound i in target str" << endl;

    // TODO: replace j to i in tarstr
    // tarstr.replace('j', 'i'); and find()
    //  tarstr.find()
    lefalpha.erase('i');

  } else {
    cout << "Not found i or j in target str" << endl;
    lefalpha.erase('j');
  }

  std::vector<char> tarlefstrvet(lefalpha.begin(), lefalpha.end());
  std::string tarlefstr(tarlefstrvet.begin(), tarlefstrvet.end());
  string lefalphastr = tarlefstr;
  string keystr = tarstr + lefalphastr;

  cout << "---------------------------------------" << keystr << endl;

  std::vector<char> keystrvet(keystr.begin(), keystr.end());

  int cnt = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      table[i][j] = keystr[cnt++];
    }
  }
  cout << endl;

  // add left alpha chars to table
  // pos = 0;
  // std::vector<char> tarlefstr(lefalpha.begin(), lefalpha.end());
  // // cout << "Pos: " << pos << endl;
  // for (int i = continue_i; i < 5; i++) {
  //   for (int j = continue_j; j < 5; j++) {
  //     if (pos < lefalpha.size()) {
  //       table[i][j] = tarlefstr[pos++];
  //     }
  //   }
  // }

  // cout << "----------------------------------------" << endl;
  // cout << "Alpha: ";
  // for (auto i : alpha) cout << i;

  // cout << endl;
  // cout << "Settarstr: ";
  // for (auto i : settarstr) cout << i;

  // cout << endl;
  // cout << "symDifference: ";
  // for (auto i : symDifference) std::cout << i;
  // cout << endl;

  // cout << "left alpha: ";
  // for (auto i : lefalpha) std::cout << i;
  // cout << endl;

  // cout << "----------------------------------------" << endl;

  // cout << alpha.length() << endl;

  // display table
  // for (int i = 0; i < 5; i++) {
  //   for (int j = 0; j < 5; j++) {
  //     cout << table[i][j];
  //   }
  //   cout << endl;
  // }

  return table;
}

// //---------------------------------------------------------------
// std::string rmstr_duplicates(std::string srcstr) {
//   std::string str = srcstr;

//   std::set<char> chars;

//   str.erase(std::remove_if(str.begin(), str.end(),
//                            [&chars](char i) {
//                              // If encountered character, remove this one.
//                              if (chars.count(i)) {
//                                return true;
//                              }

//                              // Otherwise, mark this character encountered
//                              and
//                              // don't remove.
//                              chars.insert(i);
//                              return false;
//                            }),
//             str.end());

//   str.erase(std::remove_if(str.begin(), str.end(),
//                            [](unsigned char x) { return std::isspace(x); }),
//             str.end());

//   // test print statement
//   //   std::cout << str << '\n';
//   //   std::cout << srcstr << '\n';

//   return str;
// }

// std::string rmstr_isspace(std::string srcstr) {
//   std::string str = srcstr;

//   str.erase(std::remove_if(str.begin(), str.end(),
//                            [](unsigned char x) { return std::isspace(x); }),
//             str.end());

//   return str;
// }