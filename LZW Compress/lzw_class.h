#ifndef LZW_H_
#define LZ_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Lzw {
 private:
  string str;

 public:
  vector<int> compress(string str);
  void decompress(vector<int> op);
};

#endif