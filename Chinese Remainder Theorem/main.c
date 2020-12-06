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

  miracl *mip = mirsys(1500, 10);  //初始化大数系统，1500个10进制数
  mip->IOBASE = 10;                //指定进制为10进制

  for (i = 0; i < NUM; i++)  //初始化大数数组为零
  {
    a[i] = mirvar(0);
    m[i] = mirvar(0);
    x[i] = mirvar(0);
    Mj[i] = mirvar(0);
    Mj1[i] = mirvar(0);
  }

  big num_gcd = mirvar(0);    //初始化用到的 big变量
  big constnum1 = mirvar(1);  //常量大数1
  big M = mirvar(1);
  big m1 = mirvar(0);
  big X = mirvar(0);
  big y = mirvar(1);
  big W = mirvar(0);

  fp = fopen("data.txt", "r");
  char tmp[4000];
  while (1) {
    fscanf(fp, "%s", tmp);
    if (count < NUM)  //从文本文件中读取 NUM 行
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
      egcd(m[i], m[j], num_gcd);  // num_gcd=存放公约数，若gcd(m[i],
                                  // m[j])=1即m两两互素进行下一次判断，否则跳出
      if (mr_compare(num_gcd, constnum1) == 0)
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
    divide(M, m[i], Mj[i]);                    //计算Mj
    xgcd(Mj[i], m[i], Mj1[i], m1, constnum1);  //计算Mj^1(mod mj)
    copy(W, M);                                // M=W，数值还原
  }

  for (i = 0; i < NUM; i++)  //计算xj及其累加结果X
  {
    multiply(Mj[i], Mj1[i], num_gcd);
    multiply(num_gcd, a[i], x[i]);
    add(x[i], X, X);
  }

  powmod(X, y, M, X);  // X mod M

  cotnum(X, stdout);
  mirexit();

  return 0;
}