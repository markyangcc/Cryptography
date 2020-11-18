#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

vector<int> compress(string str);

int main() {
  string s = "ABABBABCABABBA";

  vector<int> compressed_code = compress(s);
  cout << endl << "Compressed encodings are: ";
  for (int i = 0; i < compressed_code.size(); i++) {
    cout << compressed_code[i] << " ";
  }
  cout << endl << endl;

  cout << "Compression Rate: "
       << (double)compressed_code.size() / (double)s.size() << endl;

  return 0;
}
// compress function
vector<int> compress(string str) {
  cout << "Compressing: " << endl;

  map<string, int> dict;

  // find all unique characters in str
  set<char> unique_chars;
  for (auto i : str) {
    unique_chars.insert(i);
  }

  // add all unique characters into dictionary
  int cnt = 1;
  for (auto i : unique_chars) {
    string st(1, i);
    dict.insert(make_pair(st, cnt));
    cnt++;
  }

  string s, c;
  s += str[0];
  // store compressed encodings
  vector<int> compressed_encodings;

  cout << "String\tEncodings" << endl;
  for (int i = 0; i < str.length(); i++) {
    if (i != str.length() - 1) {
      c += str[i + 1];
    }
    if (dict.find(s + c) != dict.end()) {
      s += c;
    } else {
      cout << s << "\t" << dict[s] << endl;
      compressed_encodings.push_back(dict[s]);
      dict[s + c] = cnt;
      cnt++;
      s = c;
    }
    c = "";
  }

  cout << s << "\t" << dict[s] << endl;
  compressed_encodings.push_back(dict[s]);

  return compressed_encodings;
}
