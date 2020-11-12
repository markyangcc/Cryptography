#include <iostream>
#include <utility>

const size_t N = 3;

std::pair<size_t, size_t> find_position(const int (&a)[N][N], int value) {
  size_t row = 0;
  size_t col = 0;

  for (; row < N; row++) {
    col = 0;
    while (col < N && a[row][col] != value) col++;
    if (col != N) break;
  }

  return {row, col};
}

int main() {
  int a[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  int value = 9;

  auto position = find_position(a, value);

  if (position.first != N) {
    std::cout << "Row = " << position.first << ", Column = " << position.second
              << std::endl;
  }

  return 0;
}