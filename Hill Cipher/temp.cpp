#include <iostream>

#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

void foo(MatrixXf& m) {
  Matrix3f m2 = Matrix3f::Zero(3, 3);
  m2(0, 0) = 1;
  m = m2;
}

int main() {
  /* 定义，定义时默认没有初始化，必须自己初始化 */
  MatrixXf m1(3, 4);  //动态矩阵，建立3行4列。
  MatrixXf m2(4, 3);  // 4行3列，依此类推。
  MatrixXf m3(3, 3);
  Vector3f v1;  //若是静态数组，则不用指定行或者列
  /* 初始化 */
  m1 = MatrixXf::Zero(3, 4);  //用0矩阵初始化,要指定行列数
  m2 = MatrixXf::Zero(4, 3);
  m3 = MatrixXf::Identity(3, 3);  //用单位矩阵初始化
  v1 = Vector3f::Zero();  //同理，若是静态的，不用指定行列数

  m1 << 1, 0, 0, 1,  //也可以以这种方式初始化
      1, 5, 0, 1, 0, 0, 9, 1;
  m2 << 1, 0, 0, 0, 4, 0, 0, 0, 7, 1, 1, 1;

  /* 元素的访问 */
  v1[1] = 1;
  m3(2, 2) = 7;
  cout << "v1:\n" << v1 << endl;
  cout << "m3:\n" << m3 << endl;
  /* 复制操作 */
  VectorXf v2 = v1;  //复制后，行数与列数和右边的v1相等,matrix也是一样,
                     //也可以通过这种方式重置动态数组的行数与列数
  cout << "v2:\n" << v2 << endl;

  /* 矩阵操作，可以实现 + - * /
  操作，同样可以实现连续操作(但是维数必须符合情况),
  如m1,m2,m3维数相同,则可以m1 = m2 + m3 + m1; */
  m3 = m1 * m2;
  v2 += v1;
  cout << "m3:\n" << m3 << endl;
  cout << "v2:\n" << v2 << endl;
  // m3 = m3.transpose();  这句出现错误，估计不能给自己赋值
  cout << "m3转置:\n" << m3.transpose() << endl;
  cout << "m3行列式:\n" << m3.determinant() << endl;
  m3 = m3.inverse();
  cout << "m3求逆:\n" << m3 << endl;

  return 0;
}