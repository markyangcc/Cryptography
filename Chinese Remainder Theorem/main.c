#include <stdio.h>
#include <stdlib.h>

#include "include/miracl.h"

#define NUM 3  //从文本读入方程组个数，数据以分行存储

int main() {
  //中国剩余定理：x≡M1M1^1a1+M2M2^-1a2+……+MkMk^-1ak(modm)
  //其中m=m1m2m……mk,Mj=m/mj,MjMj^-1≡1(mod mj),j=1,2,……k
  int i, j;  //设定循环变量
  FILE *fp;
  int count = 0;
  big a[NUM], m[NUM], x[NUM], Mj[NUM],
      Mj1[NUM];  //设定大数数组，a存放同余号右边，m存放模值，x存放同余号左边，Mj与字面同义，Mj1存放Mj^-1
  big t0, t1, M, m1, X, y, W;

  miracl *mip = mirsys(1500, 10);  //初始化大数系统，1500个10进制数
  mip->IOBASE = 10;                //指定进制为10进制
  
  for (i = 0; i < NUM; i++)        //初始化数组
  {
    a[i] = mirvar(0);
    m[i] = mirvar(0);
    x[i] = mirvar(0);
    Mj[i] = mirvar(0);
    Mj1[i] = mirvar(0);
  }

  t0 = mirvar(0);  //初始化各变量
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
    if (count < NUM)  //从文件中读入a列并存入数组
    {
      cinstr(a[count], tmp);
      cotnum(a[count], stdout);
      count++;
    } else  //从文件中读入m列存入数组
    {
      cinstr(m[count - NUM], tmp);
      cotnum(m[count - NUM], stdout);
      count++;
    }
    if (count == 2 * NUM) break;
  }
  printf("结果为：");
  fclose(fp);

  for (i = 0; i < NUM; i++)  //判断m列是否两两互素
  {
    for (j = i + 1; j < NUM; j++) {
      egcd(m[i], m[j], t0);  // t0=存放公约数，若gcd(m[i],
                             // m[j])=1即m两两互素进行下一次判断，否则跳出
      if (mr_compare(t0, t1) == 0)
        continue;
      else {
        printf("不能直接应用中国剩余定理\n");
        exit(0);
      }
    }
  }

  for (i = 0; i < NUM; i++) {
    multiply(m[i], M, M);  //计算M=m1m2……mk
  }

  copy(M, W);  // W=M
  for (i = 0; i < 3; i++) {
    divide(M, m[i], Mj[i]);             //计算Mj
    xgcd(Mj[i], m[i], Mj1[i], m1, t1);  //计算Mj^1(mod mj)
    copy(W, M);                         // M=W，数值还原
  }

  for (i = 0; i < NUM; i++)  //计算xj及其累加结果X
  {
    multiply(Mj[i], Mj1[i], t0);
    multiply(t0, a[i], x[i]);
    add(x[i], X, X);
  }

  powmod(X, y, M, X);  // X mod M

  cotnum(X, stdout);
  mirexit();

  return 0;
}