#include <iostream>
#define N 4
using namespace std;
void findCoFactor(int mat[N][N], int mat2[N][N], int p, int q, int n) {
  int i = 0, j = 0;
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (row != p && col != q) {
        mat2[i][j++] = mat[row][col];
        if (j == n - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}
int getDeterminant(int mat[N][N], int n) {
  int determinant = 0;
  if (n == 1) return mat[0][0];
  int temp[N][N];
  int sign = 1;
  for (int f = 0; f < n; f++) {
    findCoFactor(mat, temp, 0, f, n);
    determinant += sign * mat[0][f] * getDeterminant(temp, n - 1);
    sign = -sign;
  }
  return determinant;
}
bool isMatrixInvertible(int mat[N][N], int n) {
  if (getDeterminant(mat, N) != 0)
    return true;
  else
    return false;
}
int main() {
  int matrix[N][N] = {{1, 0, 2, -1}, {3, 0, 0, 5}, {2, 1, 4, -3}, {1, 0, 5, 0}};
  if (isMatrixInvertible(matrix, N))
    cout << "The matrix is invetible";
  else
    cout << "The matrix is not invetible";
}