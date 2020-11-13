#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

extern std::string rmstr_duplicates(std::string srcstr);
extern std::string rmstr_isspace(std::string srcstr);

using namespace std;

array<array<char, 5>, 5> build_table(const string& key = "ballon") {
  cout << "Entered key: " << key << endl;

  // TODO: try replace set to unordered_set to relize same funcrion, to
  // simpifily code

  // remove duplicates and spaces in user-input string
  string tarstr = rmstr_duplicates(key);
  tarstr = rmstr_isspace(tarstr);

  string alphastr = "abcdefghijklmnopqrstuvwxyz";

  // convert string to set to minus
  set<char> alpha(begin(alphastr), end(alphastr));
  set<char> settarstr(begin(tarstr), end(tarstr));

  // find out symDifference set
  std::vector<char> symDifference;
  std::set_symmetric_difference(alpha.begin(), alpha.end(), settarstr.begin(),
                                settarstr.end(),
                                std::back_inserter(symDifference));

  // Rename symDifference set
  set<char> lefalpha(begin(symDifference), end(symDifference));

  // std::find() Returns an iterator to the first element in the range
  // [first,last) that compares equal to val. If no such element is found, the
  // function returns last.
  //!= end() means find, ==end() means not found

  // handle i/j problems
  if (settarstr.find('i') != settarstr.end() &&
      settarstr.find('j') != settarstr.end()) {
    cout << endl << "Found i and j in target str" << endl;
    settarstr.erase('j');
  } else if (settarstr.find('i') != settarstr.end() &&
             settarstr.find('j') == settarstr.end()) {
    cout << endl << "Found i, but not dound j in target str" << endl;

    lefalpha.erase('j');

  } else if (settarstr.find('j') != settarstr.end() &&
             settarstr.find('i') == settarstr.end()) {
    cout << endl << "Found j, but not dound i in target str" << endl;

    // In this situation i is equal to j， Determine whether to use i or j
    // according to the actual meaning of the word
    lefalpha.erase('i');

  } else {
    cout << endl << "Not found i or j in target str" << endl;
    lefalpha.erase('j');
  }

  // contcatenates two different parts and then convert to string
  std::vector<char> tarlefstrvet(lefalpha.begin(), lefalpha.end());
  std::string tarlefstr(tarlefstrvet.begin(), tarlefstrvet.end());
  const string& lefalphastr = tarlefstr;
  string keystr = tarstr + lefalphastr;

  cout << "Generated table in oneline: " << keystr << endl;

  // assign to 5*5 playfair table
  array<array<char, 5>, 5> table = {0};
  int cnt = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      table[i][j] = keystr[cnt++];
    }
  }

  return table;
}
