#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "dependfunc.h"

using namespace std;

array<array<char, 5>, 5> build_table(string key = "ballon") {
  array<array<char, 5>, 5> table = {0};

  cout << "Default key(ballon):" << key << endl;

  // make std key
  // TODO: try replace set to unordered_set to relize same funcrion, to
  // simpifily code
  string tarstr = rmstr_duplicates(key);
  tarstr = rmstr_isspace(tarstr);

  string alphastr = "abcdefghijklmnopqrstuvwxyz";

  set<char> alpha(begin(alphastr), end(alphastr));

  set<char> settarstr(begin(tarstr), end(tarstr));

  // clac symDifference set
  const set<char>& v1 = alpha;
  set<char> v2 = settarstr;

  // cout << "set_symmetric_difference" << endl;
  std::vector<char> symDifference;
  std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                                std::back_inserter(symDifference));

  set<char> lefalpha(begin(symDifference), end(symDifference));

  // check size() to check if function works successed
  // cout << "symDifference size: " << symDifference.size() << endl;

  //  vector<char> omitij = symDifference;
  //  // cout << "omitij size: " << omitij.size() << endl;

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
  const string& lefalphastr = tarlefstr;
  string keystr = tarstr + lefalphastr;

  cout << "Generated key: " << keystr << endl;

  std::vector<char> keystrvet(keystr.begin(), keystr.end());

  int cnt = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      table[i][j] = keystr[cnt++];
    }
  }
  cout << endl;

  return table;
}
