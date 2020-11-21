#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "miracl.h"
#include "mirdef.h"
#define K 6  //安全系数

int farmattest(big p);

int main() {
  FILE* fp;
  miracl* mip = mirsys(3000, 10);

  big p = mirvar(0);

  if ((fp = fopen("data.txt", "r+")) == NULL) {
    printf("Error, file open failed");
    exit(0);
  }

  while (!feof(fp)) {
    cinnum(p, fp);
    cotnum(p, stdout);
    if (farmattest(p) == 1) {
      printf("p is %6.4f%% prime\n", 100 * (1 - pow(0.5, K)));
    }
    if (farmattest(p) == 0) {
      printf("p is a composite\n");
    }
  }

  return 0;
}

int farmattest(big p) {
  int i = 0;
  int j = 0;

  big randnum = mirvar(0);  //生成一个随机数
  big pminus1 = mirvar(0);
  big pminus2 = mirvar(0);
  big mgcd = mirvar(0);       //最大公因数
  big rval = mirvar(0);       //模幂运算返回值
  big constnum1 = mirvar(1);  //
  big constnum2 = mirvar(2);

  decr(p, 2, pminus2);  // pminus2 = p - 2;
  decr(p, 1, pminus1);  // pminus1 = p - 1;

  srand((unsigned int)time(NULL));

  // void irand (mr_unsign32 seed)
  // Initialises internal random number system. Long integer types are used
  // internally to yield a generator with
  // maximum period.

  // void bigrand (big w, big x)
  // x A big random number in the range 0 <= x < w
  bigrand(pminus2, randnum);  //生成随机数a

  for (i = 0; i < K; i++) {
    // Calculates the Greatest Common Divisor of two big numbers.
    // z = gcd(x,y)
    egcd(randnum, p, mgcd);  //计算randnum与m的最大公因数
                             // 并赋值给mgcd（互素最大公因数为1）

    // compare returns: +1 if x > y; 0 if x = y; -1 if x < y
    //判断obj和随机数是否互素，它们的最大公因数如果不是1的话，compare函数将会返回1，不满足条件
    if (mr_compare(mgcd, constnum1) == 0) {
      // void powmod (big x, big y, big n, big w)
      // w = xy (mod n)

      /* 随机选取整数b,2<=b<=n-2;
      计算rval≡b^(n-1)(mod n);
      如果r!=1,则n是合数;
      上述过程重复t次.

      如果p是素数， 1 ≤ a ≤ p − 1
      那么
      a^(p − 1) ≡ 1 ( mod p )

      如果我们想知道n是否是素数，我们在中间选取a，看看上面等式是否成立。
      如果对于数值a等式不成立，那么n是合数。
      如果有很多的a能够使等式成立，那么我们可以说n可能是素数，或者伪素数。
      */

      powmod(randnum, pminus1, p, rval);  //如果r=1，则obj可能是素数

      // j是判断因子，如果一个数能够满足在当前的轮数下，满足上述的算法，则j能够计数；如果j不等于轮数，那么这个数就不是素数
      if (mr_compare(rval, constnum1) == 0) {
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
  mirkill(pminus2);
  mirkill(pminus1);
  mirkill(rval);
  mirkill(mgcd);
  mirkill(constnum1);
  mirkill(constnum2);
}