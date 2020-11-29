#include <iostream>
#include <vector>

#include "Eigen/Eigen"
using namespace std;
using namespace Eigen;

void foo(MatrixXf& m) {
  Matrix3f m2 = Matrix3f::Zero(3, 3);
  m2(0, 0) = 1;
  m = m2;
}

int main() {
  vector<int> m;
  m.push_back(1);
  m.push_back(1);

  cout << m.size() << endl;

  return 0;
}