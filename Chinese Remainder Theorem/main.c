#include <stdio.h>
#include <stdlib.h>

#include "include/miracl.h"

int main() {
  //中国剩余定理：x ≡ m1*m1^-1*a1 + m2*m2^-1*a2 + …… + mk*mk^-1*ak (modm)
  //其中 M = m1m2m3……mk,Mi=M/mi,Mi*Mi^-1 ≡ 1(mod mi),i=1,2,……k
  // int i, j;  //设定循环变量e

  //---------------------------------------------------------------------------
  //从文本读入方程组个数，数据存储格式为分行存储
  int temp_num = 0;
  printf("输入方程组的个数：\n");
  scanf("%d", &temp_num);
  const int NUM = temp_num;

  FILE *fp;
  big a[NUM], m[NUM], x[NUM], Mi[NUM],
      Mi1[NUM];  //设定大数数组，a存放同余号右边，m存放模值，x存放同余号左边，Mi与字面同义，Mi1存放Mi^-1

  miracl *mip = mirsys(1500, 10);  //初始化大数系统，1500个10进制数
  mip->IOBASE = 10;                //指定进制为10进制

  for (int i = 0; i < NUM; i++)  //初始化大数数组为零
  {
    a[i] = mirvar(0);
    m[i] = mirvar(0);
    x[i] = mirvar(0);
    Mi[i] = mirvar(0);
    Mi1[i] = mirvar(0);
  }

  //初始化或声明用到的 big变量
  big constnum1 = mirvar(1);  //常量大数1
  big constnum0 = mirvar(0);  //常量大数0
  big M = mirvar(1);          //初始化mi的连乘变量M为1
  big X = mirvar(0);          //初始化方程组的解变量X为0
  big M_bak = mirvar(0);      //备份 连乘M 的值

  fp = fopen("data.txt", "r");
  char tmp[4000];
  int count = 0;
  while (1) {
    fscanf(fp, "%s", tmp);
    if (count < NUM)  //从文本文件中读取 NUM 行
    {
      cinstr(a[count], tmp);
      printf("\n成功读取大数并赋值给a[%d]:\n", count);
      cotnum(a[count], stdout);
      count++;
    } else  //从文件中读入m列存入数组
    {
      cinstr(m[count - NUM], tmp);
      printf("\n成功读取大数并赋值给m[%d]:\n", count - NUM);

      cotnum(m[count - NUM], stdout);
      count++;
    }
    if (count == 2 * NUM) break;
  }

  printf("\n方程组的解x为：\n");
  fclose(fp);

  //---------------------------------------------------------------------------
  //判断 mi 之间是否两两互素
  big gcd_num = mirvar(0);

  //结束条件的判断用到了同余定理的传递性：若a≡b(mod m)，b≡c(mod m)，则a≡c(mod m)
  for (int i = 0; i < NUM; i++) {
    for (int j = i + 1; j < NUM; j++) {
      // int egcd (big x, big y, big z)
      // z = gcd(x,y)
      // 计算两个大数的最大公约数，并讲结果赋值给 z
      egcd(m[i], m[j],
           gcd_num);  // gcd_num为最大公约数，若gcd(m[i], m[j])=1
                      // 说明二者互素，继续进行下一次判断，否则exit()
      if (mr_compare(gcd_num, constnum1) == 0)
        continue;
      else {
        printf("不能直接应用中国剩余定理\n");
        exit(EXIT_SUCCESS);
      }
    }
  }

  //---------------------------------------------------------------------------
  // 计算 mi 的乘积 M
  // void multiply (big x, big y, big z)
  // z = xy
  // 计算两个大数的乘积，赋值给 z
  for (int i = 0; i < NUM; i++) {
    multiply(m[i], M, M);  //计算 M = m1 * m2 * m3 *……* mk
  }

  //---------------------------------------------------------------------------
  //计算 M[i] 的模反,然后将模反结果存储到 Mi1[i]

  // void copy* (flash x, flash y)
  // 复制， y= x
  copy(M, M_bak);  // 备份 M 的值，M_bak = M
  for (int i = 0; i < NUM; i++) {
    // void divide (big x, big y, big z)
    // Divides one big number by another: z = x/y, x = x (mod y). The
    // quotient(商) only is returned if x and z are the same, the remainder(余)
    // only if y and z are the same.
    divide(M, m[i], Mi[i]);  //计算 Mi

    // int xgcd (big x, big y, big xd, big yd, big z)
    //计算两个大数的扩展最大公因数。 也可用于计算模反
    // z = gcd(x, y) = (x * xd) + (y * yd)
    //由裴蜀定理给出：给定二个整数a、b，必存在整数x、y使得ax + by = gcd(a,b)
    xgcd(Mi[i], m[i], Mi1[i], constnum0,
         constnum1);  //计算模反,Mi1[i] = Mi[i]^-1
    copy(M_bak, M);   // M = M_bak，每次循环前还原数据 M
  }

  //---------------------------------------------------------------------------
  //计算方程的通解形式 X
  // xi = Mi * Mi^-1 * ai
  // 解X = x1 + x2 + x3 + ... + xi
  for (int i = 0; i < NUM; i++)  //计算xj及其累加结果X
  {
    // void multiply (big x, big y, big z)
    // z = xy
    multiply(Mi[i], Mi1[i], gcd_num);
    multiply(gcd_num, a[i], x[i]);
    // void add (big x, big y, big z)
    // z = x + y
    add(x[i], X, X);
  }
  // void powmod (big x, big y, big n, big w)
  // w = xy (mod n)
  powmod(X, constnum1, M, X);  // X  = X *1 (mod M),即 X = X % M，计算 X % M
                               // 后赋值给 X y = 1

  cotnum(X, stdout);
  mirexit();

  return 0;
}