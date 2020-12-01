#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "include/miracl.h"

#define K 6  //安全系数

bool fermat_primality_test(big p);

int main() {
  FILE* fp;

  // mip: Miracl Instance Pointer
  // miracl* mirsys (int nd, mr_small nb)
  // Initialises the MIRACL system for the current program thread,
  //
  // nd The number of digits to use for each big/flash variable. If negative, it
  // is taken as indicating the
  // size of big/flash numbers in 8-bit bytes
  // nb The number base docs:5
  miracl* mip = mirsys(500, 10);  // This initialises the MIRACL system to
                                  // use 1500 decimal digits for each
                                  // big or flash number

  if ((fp = fopen("data.txt", "r+")) == NULL) {
    fprintf(stderr, "fopen() failed in file %s at line # %d", __FILE__,
            __LINE__);
    exit(EXIT_FAILURE);
  }

  big p = mirvar(0);

  while (!feof(fp)) {
    // int cinnum (flash x, FILE * filep)
    // x Big/flash number, filep File descriptor(stdin/opened file) docs:5
    cinnum(p, fp);  // converts *filep into big number x

    // int cotnum (flash x, FILE * filep)
    // Outputs a big/flash number to the screen or to a file, using as number
    // base the value currently assigned to docs:5
    mip->IOBASE = 10;  //设置为10进制输出
    cotnum(p, stdout);

    // Output
    if (fermat_primality_test(p) == true) {
      printf("\np有 %6.4lf%% 概率是素数\n", 100 * (1 - pow(0.5, K)));
    }
    if (fermat_primality_test(p) == false) {
      printf("\np是合数\n");
    }
  }
  fclose(fp);

  mirkill(p);

  return 0;
}

bool fermat_primality_test(big p) {
  big a = mirvar(0);          //随机选取的数
  big pminus1 = mirvar(0);    // p-1
  big pminus2 = mirvar(0);    // p-2
  big mgcd = mirvar(0);       //最大公因数
  big rval = mirvar(0);       //模幂运算返回值
  big constnum1 = mirvar(1);  //常数1
  big constnum2 = mirvar(2);  //常数2

  decr(p, 2, pminus2);  // pminus2 = p - 2;
  decr(p, 1, pminus1);  // pminus1 = p - 1;

  // void irand (mr_unsign32 seed)
  // Initialises internal random number system. Long integer types are used
  // internally to yield a generator with maximum period.
  irand((unsigned int)time(NULL));  //重新播种

  // void bigrand (big w, big x)
  // x A big random number in the range 0 <= x < w
  bigrand(pminus2, a);  //生成随机数a

  int j = 0;  //计数
  for (int i = 0; i < K; i++) {
    // int egcd (big x, big y, big z)
    // Calculates the Greatest Common Divisor of two big numbers.
    // z = gcd(x,y) docs:1
    egcd(a, p, mgcd);  //计算a与p的最大公因数
                       // 并赋值给mgcd（若互素，则最大公因数为1）

    // int compare* (big x, big y)
    // returns: +1 if x > y; 0 if x = y; -1 if x < y
    //判断p和随机数是否互素，若互素，则最大公因数mgcd为1
    if (mr_compare(mgcd, constnum1) == 0) {
      /* 随机选取整数b,2<=b<=n-2;
      计算rval≡b^(n-1)(mod n);
      如果r!=1,则n是合数;
      上述过程重复t次.

      费马素性检测
      如果p是素数， 1 ≤ a ≤ p − 1
      那么
      a^(p − 1) ≡ 1 ( mod p )
      如果我们想知道n是否是素数，我们在中间选取a，看看上面等式是否成立。
      如果对于数值a等式不成立，那么n是合数。
      如果有很多的a能够使等式成立，那么我们可以说n可能是素数，或者伪素数。
      */

      // void powmod (big x, big y, big n, big w)
      // w = xy (mod n)
      powmod(a, pminus1, p, rval);  //如果rval=1，则p可能是素数

      // j计数，有多少轮结果出来是素数
      if (mr_compare(rval, constnum1) == 0) {
        j++;
      }
    }
  }
  // 计算了K轮，每次结果都是素数 返回true,否则返回false
  if (j == K) {
    return true;
  } else {
    return false;
  }

  // void mirkill* (big x)
  // Securely kills off a big/flash number by zeroising it, and freeing its
  // memory.
  mirkill(a);
  mirkill(pminus2);
  mirkill(pminus1);
  mirkill(rval);
  mirkill(mgcd);
  mirkill(constnum1);
  mirkill(constnum2);
}