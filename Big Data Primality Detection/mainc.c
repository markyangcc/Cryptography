
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "miracl.h"
#include "mirdef.h"
#define K 6  //安全系数

int farmattest(big m);

int main() {
  FILE* fp;
  miracl* mip = mirsys(3000, 10);

  big m = mirvar(0);

  if ((fp = fopen("data.txt", "r+")) == NULL) {
    printf("Error, file open failed");
    exit(0);
  }

  while (!feof(fp)) {
    cinnum(m, fp);
    cotnum(m, stdout);
    if (farmattest(m) == 1) {
      printf("m is %6.4f%% prime\n", 100 * (1 - pow(0.5, K)));
    }
    if (farmattest(m) == 0) {
      printf("m is a composite\n");
    }
  }

  return 0;
}

int farmattest(big m) {
  int i = 0;
  int j = 0;

  big randnum;  //随机数
  big tran1;    // m-2
  big mgcd;     //最大公因数 g
  big tran2;    // m-1
  big r;
  big number1;  //数字1
  big number2;  //数字2

  randnum = mirvar(0);
  tran1 = mirvar(0);
  mgcd = mirvar(0);
  tran2 = mirvar(0);
  r = mirvar(0);
  number1 = mirvar(1);
  number2 = mirvar(2);

  decr(m, 2, tran1);  // tran1 = m - 2;
  decr(m, 1, tran2);  // tran2 = m - 1;

  srand((unsigned int)time(NULL));
  bigrand(tran1, randnum);  //生成随机数a

  for (i = 0; i < K; i++) {
    // Calculates the Greatest Common Divisor of two big numbers.
    // z = gcd(x,y)
    egcd(randnum, m, mgcd);  //计算randnum与m的最大公因数

    // compare returns: +1 if x > y; 0 if x = y; -1 if x < y
    if (!mr_compare(mgcd, number1)) {
      // void powmod (big x, big y, big n, big w)
      // w = xy (mod n)
      powmod(randnum, tran2, m, r);

      if (!mr_compare(r, number1)) {
        j++;
      }
    }
  }

  if (j == K) {
    return 1;
  } else {
    return 0;
  }

  mirkill(randnum);
  mirkill(tran1);
  mirkill(tran2);
  mirkill(r);
  mirkill(mgcd);
  mirkill(number1);
  mirkill(number2);
}