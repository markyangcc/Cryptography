#include <stdio.h>
#include <stdlib.h>

#include "include/miracl.h"

#define NUM 3  //从文本读入方程组个数，数据以分行存储

FILE *fp;

int flag = 0;

int main() {
  int i, j;

  big a[NUM], m[NUM], x[NUM], mj[NUM], mjr[NUM];
  big t0, t1, M, m1, X, y, W;  //这里mj[] 为 Mj
                               // mjr[] 为 M^-1 j
                               // M 为 m[] 的连乘

  miracl *mip = mirsys(1500, 10);  //初始化大数系统，1500个10进制数
  mip->IOBASE = 10;                //指定进制为10进制

  for (i = 0; i < NUM; i++) {
    a[i] = mirvar(0);
    m[i] = mirvar(0);
    x[i] = mirvar(0);
    mj[i] = mirvar(0);
    mjr[i] = mirvar(0);
  }
  
  t0 = mirvar(0);
  t1 = mirvar(1);
  M = mirvar(1);
  m1 = mirvar(0);
  X = mirvar(0);
  y = mirvar(1);
  W = mirvar(0);

  fp = fopen("data.txt", "r");
  char tmp[4000];

  while (1) {
    fscanf(fp, "%s", tmp);
    if (flag < NUM) {
      cinstr(a[flag], tmp);
      cotnum(a[flag], stdout);
      flag++;
    } else {
      cinstr(m[flag - NUM], tmp);
      cotnum(m[flag - NUM], stdout);
      flag++;
    }
    if (flag == 2 * NUM) break;
  }
  printf("\n");
  fclose(fp);

  for (i = 0; i < NUM; i++)  //判断mi是否两两互素
  {
    for (j = i + 1; j < NUM; j++) {
      egcd(m[i], m[j], t0);
      if (mr_compare(t0, t1))
        continue;
      else {
        printf("不能直接应用中国剩余定理\n");
        exit(0);
      }
    }
  }

  for (i = 0; i < NUM; i++) {
    multiply(m[i], M, M);  //计算M=m1 x m2 x ... x mn
  }

  copy(M, W);
  for (i = 0; i < 2; i++) {
    divide(
        M, m[i],
        mj[i]);  //计算mj = Mj ???运算一次后M的值就清0了！！！释放空间了？？？
    xgcd(mj[i], m[i], mjr[i], m1, t1);  //计算mjr = M1~j
    copy(W, M);
  }

  for (i = 0; i < NUM; i++)  //计算xj
  {
    multiply(mj[i], mjr[i], t0);
    multiply(t0, a[i], x[i]);
  }

  for (i = 0; i < NUM; i++)  //计算xj和
  {
    add(x[i], X, X);
  }

  powmod(X, y, M, X);  // X mod M

  cotnum(X, stdout);
  mirexit();

  return 0;
}