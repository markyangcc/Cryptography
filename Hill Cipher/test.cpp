#include <iostream>

#include "Eigen/Dense"

using namespace Eigen;
using namespace std;

int main() {
  int msg_row, msg_col;
  msg_row = 3, msg_col = 1;
  MatrixXd msg_matrix(msg_row, msg_col);
  msg_matrix << 0, 2, 19;
  // cout << "msg_matrix: " << endl << msg_matrix << endl;

  int key_row, key_col;
  key_row = 3, key_col = 3;
  MatrixXd key_matrix(key_row, key_col);
  key_matrix << 6, 24, 1, 13, 16, 10, 20, 17, 15;

  // Confirm it is reversible
  if (key_matrix.determinant() == 0) {
    cout << "The key matrix is not reversible" << endl;
    cout << "The determinant value is : " << key_matrix.determinant() << endl;
  }

  // encrypt
  // The rows of the product matrix are equal to the rows of the left matrix,
  // and the columns of the product matrix are equal to the columns of the
  // right matrix.
  int encrypted_row = msg_row;
  int encrypted_col = key_col;
  MatrixXd encrypted_matrix(msg_row, msg_col);
  // A matrix can be multiplied only if the number of columns of the left
  // matrix is equal to the number of rows of the right matrix.
  if (key_matrix.cols() == msg_matrix.rows()) {
    encrypted_matrix = key_matrix * msg_matrix;
  }
  cout << encrypted_matrix << endl;

  return 0;
}
