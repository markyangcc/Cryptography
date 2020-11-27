#include <iostream>
#include <vector>

constexpr unsigned ROWS{12};
constexpr unsigned COLS{28};

using matrix = std::vector<std::vector<int>>;

void print(const matrix& m);
matrix transpose(const matrix& m);
matrix multiply(const matrix& m1, const matrix& m2);

int main() {
  matrix src(ROWS, std::vector<int>(COLS, 2));

  std::cout << "src matrix:\n";
  print(src);

  std::cout << "rows of src: " << src.size()
            << "\ncols of src: " << src.at(0).size() << '\n';

  matrix src_trans(COLS, std::vector<int>(ROWS));

  src_trans = transpose(src);

  std::cout << "Transpose of src:\n";
  print(src_trans);

  // mul rows == src rows
  // mul columns == src_trans columns
  matrix mul(src.size(), std::vector<int>(src_trans.at(0).size()));

  mul = multiply(src, src_trans);
  std::cout << "\nProduct of src * src_trans:\n";
  print(mul);
}

void print(const matrix& m) {
  for (const auto& v : m) {
    for (const int i : v) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}

matrix transpose(const matrix& m) {
  matrix outtrans(m.at(0).size(), std::vector<int>(m.size()));
  for (std::size_t i = 0; i < m.size(); ++i) {
    for (std::size_t j = 0; j < m.at(0).size(); ++j) {
      outtrans.at(j).at(i) = m.at(i).at(j);
    }
  }
  return outtrans;
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