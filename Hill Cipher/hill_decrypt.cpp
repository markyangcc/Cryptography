#include <iostream>
#include <string>
#include <vector>

#include "Eigen/Eigen"

using namespace Eigen;
using namespace std;

vector<double> decrypt(vector<int> cipher_vec) {
  cout << "How many rows in the key matrix: ";
  int size;
  cin >> size;

  int key_row = size;
  int key_col = size;

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

  // TODO: Don't know how to get matrix's inverse
  MatrixXd invert_keymatrix(key_row, key_col);
  invert_keymatrix = key_matrix.inverse();
  cout << invert_keymatrix << endl;

  // map cipher_vec chars to ints
  vector<int> vec;
  // for (int i = 0; i < cipher_vec.size(); i++) {
  //   vec.push_back((cipher_vec[i] - 'a'));
  // }

  for (auto i : cipher_vec) vec.push_back(i);
  // vec.push_back(67);
  // vec.push_back(222);
  // vec.push_back(319);

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

  cout << "-------------" << endl;
  cout << "msg:" << endl << msg_matrix << endl;
  cout << "key:" << endl << key_matrix << endl;
  cout << "inv:" << endl << invert_keymatrix << endl;

  cout << "decy:" << endl << decrypted_matrix << endl;
  cout << "-------------" << endl;

  cout << "rows cols: " << decrypted_matrix.rows() << " "
       << decrypted_matrix.cols() << endl;

  vector<double> double_vec;

  for (int i = 0; i < decrypted_matrix.rows(); i++)
    for (int j = 0; j < decrypted_matrix.cols(); j++) {
      cout << "i, j" << i << " " << j << endl;
      double_vec.push_back(double(decrypted_matrix(i, j)));
    }

  cout << "Decry: " << decrypted_matrix(0, 0) << decrypted_matrix(1, 0)
       << decrypted_matrix(2, 0) << endl;

  cout << "Vec: " << endl;
  for (auto i : double_vec) {
    cout << i << endl;
  }

  return double_vec;
}