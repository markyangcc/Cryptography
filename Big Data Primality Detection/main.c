#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "miracl.h"

#define ROUND 6

int Fermatjdu_prime(big obj);

int main(void) {
  FILE *fp;
  big obj;

  // mip: Miracl Instance Pointer
  // mirsys(num_of_digits, num_base) docs:5
  miracl *mip =
      mirsys(300000, 16);  //每次使用变量的位数(不能小于所求)，16表示数字进制

  // the 'printable' number base to be used for input and output(range[2,256]).
  // docs:7
  mip->IOBASE = 16;

  // all big variables need to be "mirvar"ed
  obj = mirvar(0);  //初始化变量obj，obj是输入的需要判断是否为素数的大数

  if ((fp = fopen("datatest.txt", "r+")) == NULL) {
    printf("Error, file open failed...\n");
    exit(EXIT_FAILURE);
  }  //判断文件是否能够正确打开

  //检测文件结束符
  while (!feof(fp)) {
    // int cinnum (flash x, FILE * filep)
    // x Big/flash number, filep File descriptor(stdin/opened file) docs:5
    cinnum(obj, fp);  // converts them（how many bytes digits) into big number x

    // Outputs a big/flash number to the screen or to a file, using as number
    // base the value currently assigned to docs:5
    cotnum(obj, stdout);

    if (Fermatjdu_prime(obj))
      printf("This number has a %6.4f%% probability of being a prime number.\n",
             100 * (1 - pow(0.5, ROUND)));
    else
      printf("This number is 100%% definitely a Composite number! \n");
  }

  fclose(fp);

  // Securely kills off a big/flash number by zeroising it, and freeing its
  // memory.
  mirkill(obj);

  // Cleans up after the current instance of MIRACL, and frees all internal
  // variables.
  mirexit();

  return 0;
}

int Fermatjdu_prime(big obj) {
  big radn, trans, mgcd, trans1, r, num1, num2, cons;

  int i, j;
  miracl *mip = mirsys(1500, 16);
  mip->IOBASE = 16;

  radn = mirvar(0);  //对函数中使用到的big型变量进行初始化
  trans = mirvar(0);
  mgcd = mirvar(0);
  trans1 = mirvar(0);
  r = mirvar(0);
  num1 = mirvar(1);
  num2 = mirvar(2);
  cons = mirvar(0);

  i = 0;
  j = 0;

  decr(obj, 2, trans);   // trans=obj-2
  decr(obj, 1, trans1);  // trans=obj-1
  srand((unsigned int)time(NULL));
  for (i = 0; i < ROUND; i++) {
    bigrand(obj, radn);     //生成所需要的随机数
    egcd(radn, obj, mgcd);  //计算obj和生成的随机数的最大公因数
    
    if (!mr_compare(
            mgcd,
            num1))  //判断obj和随机数是否互素，它们的最大公因数如果不是1的话，compare函数将会返回1，不满足条件
    {
      powmod(radn, trans1, obj,
             r);  //计算 ，如果r=1，则obj可能是素数，进入下一个if语句
      if (!mr_compare(r, num1))
        j++  // j是判断因子，如果一个数能够满足在当前的轮数下，满足上述的算法，则j能够计数；如果j不等于轮数，那么这个数就不是素数
            ;
    }
  }
  if (j == ROUND)
    return 1;
  else
    return 0;

  mirkill(obj);
  mirkill(radn);
  mirkill(trans);
  mirkill(trans1);
  mirkill(r);
  mirkill(mgcd);
}