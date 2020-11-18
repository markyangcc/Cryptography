#include "lzw_class.cpp"

// vector<int> compress(string str);
// void decompress(vector<int> op);

int main() {
  string s = "ABABBABCABABBA";
  vector<int> output_code = compress(s);
  cout << "Output Codes are: ";
  for (int i = 0; i < output_code.size(); i++) {
    cout << output_code[i] << " ";
  }
  cout << endl;
  decompress(output_code);
}
