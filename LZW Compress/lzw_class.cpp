
#include "lzw_class.h"

vector<int> compress(string str) {
  cout << "Compressing: " << endl;

  map<string, int> table;

  for (int i = 0; i <= 255; i++) {
    string ch;
    ch += char(i);
    table[ch] = i;
  }

  string s, c;
  s += str[0];
  int code = 256;
  vector<int> compressed_code;

  cout << "String\tOutput_Code\tAddition" << endl;
  for (int i = 0; i < str.length(); i++) {
    if (i != str.length() - 1) {
      c += str[i + 1];
    }
    if (table.find(s + c) != table.end()) {
      s += c;
    } else {
      cout << s << "\t" << table[s] << "\t\t" << s + c << "\t" << code << endl;
      compressed_code.push_back(table[s]);
      table[s + c] = code;
      code++;
      s = c;
    }
    c = "";
  }

  cout << s << "\t" << table[s] << endl;
  compressed_code.push_back(table[s]);
  return compressed_code;
}

void decompress(vector<int> op) {
  cout << endl << "Decompressing" << endl;
  map<int, string> table;
  for (int i = 0; i <= 255; i++) {
    string ch;
    ch += char(i);
    table[i] = ch;
  }

  int old = op[0], n;
  string s = table[old];
  string c;
  c += s[0];
  cout << s;
  int count = 256;

  for (int i = 0; i < op.size() - 1; i++) {
    n = op[i + 1];
    if (table.find(n) == table.end()) {
      s = table[old];
      s += c;
    } else {
      s = table[n];
    }
    cout << s;
    c = "";
    c += s[0];
    table[count] = table[old] + c;
    count++;
    old = n;
  }
}