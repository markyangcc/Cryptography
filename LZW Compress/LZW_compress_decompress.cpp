#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<int> compress(string str) {
  cout << "Compressing: " << endl;

  map<string, int> dict;

  // Init dictionary, ASCII have 256 characters(0-255)
  for (int i = 0; i <= 255; i++) {
    string ch;
    ch += char(i);
    dict[ch] = i;
  }

  string s, c;
  s += str[0];
  int code = 256;
  vector<int> compressed_code;

  cout << "String\tCompressed_code" << endl;
  for (int i = 0; i < str.length(); i++) {
    if (i != str.length() - 1) {
      c += str[i + 1];
    }
    if (dict.find(s + c) != dict.end()) {
      s += c;
    } else {
      cout << s << "\t" << dict[s] << "\t" << endl;
      compressed_code.push_back(dict[s]);
      dict[s + c] = code;
      code++;
      s = c;
    }
    c = "";
  }

  cout << s << "\t" << dict[s] << endl;
  compressed_code.push_back(dict[s]);

  return compressed_code;
}

void decompress(vector<int> encodings) {
  cout << endl << "Decompressing" << endl;
  map<int, string> dict;
  for (int i = 0; i <= 255; i++) {
    string ch;
    ch += char(i);
    dict[i] = ch;
  }

  int src = encodings[0], n;
  string s = dict[src];
  string c;
  c += s[0];
  cout << s;
  int count = 256;

  for (int i = 0; i < encodings.size() - 1; i++) {
    n = encodings[i + 1];
    if (dict.find(n) == dict.end()) {
      s = dict[src];
      s += c;
    } else {
      s = dict[n];
    }
    cout << s;
    c = "";
    c += s[0];
    dict[count] = dict[src] + c;
    count++;
    src = n;
  }
}

int main() {
  string s = "ABABBABCABABBA";
  vector<int> compressed_encodings = compress(s);
  cout << endl << "Compressed codes are: ";
  for (int i = 0; i < compressed_encodings.size(); i++) {
    cout << compressed_encodings[i] << " ";
  }
  cout << endl;

  decompress(compressed_encodings);
  cout << endl;
}
