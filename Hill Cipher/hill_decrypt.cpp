#include <iostream>
#include <string>
#include <vector>

#include "Eigen/Eigen"

using namespace Eigen;
using namespace std;

vector<double> decrypt(vector<int> cipher_vec) {
 
  int key_row = cipher_vec.size();
  int key_col = cipher_vec.size();

  MatrixXd key_matrix(key_row, key_col);

  cout << "Enter the key matrix(" << key_row << "*" << key_col
       << "), each row a new line: " << endl;

  int num;
  for (int i = 0; i < key_matrix.rows(); i++)
    for (int j = 0; j < key_matrix.cols(); j++) {
      cin >> num;
      key_matrix(i, j) = num;
    }

  cout << "key_matrix: " << endl << key_matrix << endl;

  // Confirm it is invertible (if not  invertible, can not decrypt)
  if (key_matrix.determinant() == 0) {
    cout << "The key matrix is not invertible" << endl;
    cout << "The determinant value is : " << key_matrix.determinant() << endl;
  }

  MatrixXd invert_keymatrix(key_row, key_col);
  invert_keymatrix = key_matrix.inverse();

  // map cipher_vec chars to ints
  vector<int> vec;

  for (auto i : cipher_vec) vec.push_back(i);

  int msg_row, msg_col;
  msg_row = cipher_vec.size(), msg_col = 1;
  MatrixXd msg_matrix(msg_row, msg_col);

  for (int i = 0; i < msg_matrix.rows(); i++)
    for (int j = 0; j < msg_matrix.cols(); j++) {
      msg_matrix(i, j) = vec[i * msg_col + j];
    }

  int decrypted_row = msg_row;
  int decrypted_col = key_col;
  MatrixXd decrypted_matrix(decrypted_row, decrypted_col);
  // A matrix can be multiplied only if the number of columns of the left
  // matrix is equal to the number of rows of the right matrix.
  if (invert_keymatrix.cols() == msg_matrix.rows()) {
    decrypted_matrix = invert_keymatrix * msg_matrix;
  }

  vector<double> double_vec;

  for (int i = 0; i < decrypted_matrix.rows(); i++)
    for (int j = 0; j < decrypted_matrix.cols(); j++) {
      double_vec.push_back(double(decrypted_matrix(i, j)));
    }

  return double_vec;
}