#include <iostream>
#include <vector>

using namespace std;
using matrix = std::vector<std::vector<int>>;

matrix multiply(const matrix& m1, const matrix& m2);

int main() {
  // plaintext
  matrix m1 = {{1}, {2}, {3}};
  // key
  matrix m2 = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};

  matrix result = multiply(m2, m1);

  // print martrix
  for (const auto& row : result) {
    for (const auto& s : row) std::cout << s << ' ';
    std::cout << std::endl;
  }

  return 0;
}

matrix multiply(const matrix& m1, const matrix& m2) {
  matrix result(m1.size(), std::vector<int>(m2.at(0).size()));

  for (std::size_t row = 0; row < result.size(); ++row) {
    for (std::size_t col = 0; col < result.at(0).size(); ++col) {
      for (std::size_t inner = 0; inner < m2.size(); ++inner) {
        result.at(row).at(col) += m1.at(row).at(inner) * m2.at(inner).at(col);
      }
    }
  }

  return result;
}