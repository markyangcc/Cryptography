#include <iostream>
#include <string>
#include <vector>

#include "Eigen/Eigen"

using namespace Eigen;
using namespace std;

string encrypt(string str) {
  // map char to int
  vector<int> vec;
  for (int i = 0; i < str.size(); i++) {
    vec.push_back((str[i] - 'a'));
  }

  int msg_row, msg_col;
  msg_row = str.size(), msg_col = 1;
  MatrixXd msg_matrix(msg_row, msg_col);

  for (int i = 0; i < msg_matrix.rows(); i++)
    for (int j = 0; j < msg_matrix.cols(); j++) {
      msg_matrix(i, j) = vec[i * msg_col + j];
    }

  // cout << "msg_matrix: " << endl << msg_matrix << endl;

  int key_col = msg_row;
  int key_row = key_col;
  // the key_matrix must invertible， otherwise it cannot be decrypted
  MatrixXd key_matrix(key_row, key_col);

  // cout << key_row << " " << key_col << endl;
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

  // encrypt
  // The rows of the product matrix are equal to the rows of the left matrix,
  // and the columns of the product matrix are equal to the columns of the
  // right matrix.
  int encrypted_row = msg_row;
  int encrypted_col = key_col;
  MatrixXd encrypted_matrix(encrypted_row, encrypted_col);
  // A matrix can be multiplied only if the number of columns of the left
  // matrix is equal to the number of rows of the right matrix.
  if (key_matrix.cols() == msg_matrix.rows()) {
    encrypted_matrix = key_matrix * msg_matrix;
  }
  // cout << "-------------" << endl;
  // cout << "msg:" << endl << msg_matrix << endl;
  // cout << "key:" << endl << key_matrix << endl;
  // cout << "ency:" << endl << encrypted_matrix << endl;
  // cout << "-------------" << endl;

  // cout << encrypted_matrix.rows() << " " << encrypted_matrix.cols() << endl;

  vector<int> int_vec;

  for (int i = 0; i < encrypted_matrix.rows(); i++)
    for (int j = 0; j < encrypted_matrix.cols(); j++) {
      int_vec.push_back(encrypted_matrix(i, j));
    }

  string ret_str;
  for (auto i : int_vec) {
    i = i % 26;
    ret_str.push_back(char(i + 'a'));
  }

  return ret_str;
}
