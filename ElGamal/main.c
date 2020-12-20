#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "include/miracl.h"
#define LENGTH 150  //安全素数 p 的位数

int main() {
  //-------------------------------------------------------------
  //验证所需文件是否存在
  FILE *fp;
  char fpname[255];
  printf("输入文件名称(包括路径名): ");  //明文文件的路径
  scanf("%s", fpname);
  if ((fp = fopen(fpname, "r")) == NULL) {
    fprintf(stderr, "Error,can't open file \"%s\"\n", fpname);
    exit(EXIT_FAILURE);
  }

  //-------------------------------------------------------------
  //密钥生成
  //公钥 (p,g,g^a)
  //私钥 a
  //
  miracl *mip = mirsys(1000, 10);  //初始化一个1000个10进制数的大数系统
  mip->IOBASE = 10;                //指定IO使用的是10进制

  big p = mirvar(0);        //随机大素数
  big g = mirvar(0);        //原根
  big pminus1 = mirvar(0);  // p-1
  big pminus2 = mirvar(0);  // p-2
  big q = mirvar(0);        //中间变量
  big a = mirvar(0);        //密钥
  big y = mirvar(0);        // g^a
  big C1 = mirvar(0), C2 = mirvar(0);
  big m = mirvar(0);          //读取的明文
  big m1 = mirvar(0);         //解密出的明文
  big k = mirvar(0);          //随机数
  big temp = mirvar(0);       //中间变量
  big constnum1 = mirvar(1);  //常量1

  irand((unsigned)time(NULL));  // 使用当前时间作为随机数种子

  // void bigdig (int n, int b, big x)
  // 生成一个给定长度的 b进制的大数并赋值给 x
  bigdig(LENGTH, 10, q);  //生成一个150位的10进制的随机数q

  // BOOL nxsafeprime (int type, int subset, big w, big p)
  // type: 素数的类型 q = (p − 1)/2 (type=0) or q = (p + 1)/2 (type=1)
  nxsafeprime(0, 0, q, p);  //生成下一个比q大的安全素数p

  decr(p, 1, pminus1);  //大数减法，生成pminus1 = p-1
  decr(p, 2, pminus2);  //大数减法，生成pminus2 = p-2

  // void copy* (flash x, flash y)
  // y = x
  copy(p, q);  // q = p, p为刚刚生成的随机安全素数

  // void decr (big x, int n, big z)
  // z = x − n
  decr(q, 1, q);  // q = q-1, 将q减一

  // int subdiv (big x, int n, big z)
  // z = x/n
  subdiv(q, 2, q);  //大数除法，q = (p-1)/2

  //==================================================================
  //选择随机大素数p的一个原根
  //
  //若g满足 g^2 mod p !=1 且 g^q mod p !=1，则说明g是一个原根
  while (true) {
    // void bigrand (big w, big x)
    //随机生成一个介于[0,w)之间的随机大数
    // 0 <= x < w
    bigrand(pminus1, g);  //随机生成一个特定范围的原根, g小于p-1

    // int compare* (big x, big y)
    // +1 if x > y; 0 if x = y; -1 if x < y
    if (mr_compare(g, constnum1) <= 0)  //保证生成的原根g是大于1的
      continue;

    big tmp1 = mirvar(0);
    big tmp2 = mirvar(0);

    // void powmod (big x, big y, big n, big w)
    // w = x^y (mod n)
    powmod(g, mirvar(2), p, tmp1);  // 构造 tmp1 = g^2 (mod p)
    powmod(g, q, p, tmp2);          // 构造 tmp2 = g^q (mod p)
    //如果 tmp1 不等于1，即 g 与2同余 如果 tmp2 不等于1 即 g与 q同余
    if (mr_compare(tmp1, constnum1) != 0 && mr_compare(tmp2, constnum1) != 0) {
      powmod(g, pminus1, p, temp);  // temp = g^(p-1) mod p
      if (mr_compare(temp, constnum1) == 0)
        break;  //如果temp =1 说明g是原根，跳出循环即可
    }
  }

  //==================================================================
  //选择一个随机数a作为私钥
  // 1 < a < p-1
  irand((unsigned)time(NULL));  // 随机数播种
  while (true) {
    bigrand(pminus1, a);               // 保证 a < p-1
    if (mr_compare(a, constnum1) > 0)  //保证 a > 1
      break;
  }

  //==================================================================
  //计算 g^a (mod p)
  powmod(g, a, p, y);  // y =g^a (mod p)

  printf("\n公钥（p, g, y(g^a)):\n");
  printf("p = \n");
  cotnum(p, stdout);
  printf("g = \n");
  cotnum(g, stdout);
  printf("y = \n");
  cotnum(y, stdout);
  printf("\n私钥a:\n");
  cotnum(a, stdout);

  //===============================================================
  // ElGamal加密
  // 1、随机选择k [1,p-2]
  // 2、计算 C1 = g^k (mod p)
  //    计算 C2 = m * ((g^a))^k (mod p)
  // 3、发送密文（C1,C2)
  //
  //随机生成一个数k，使得1<=k<=p-2,(k,p-1)=1
  irand((unsigned)time(NULL));  // 随机数种子
  while (true) {
    bigrand(pminus2, k);                // 保证 k<=p-2
    if (mr_compare(k, constnum1) >= 0)  //保证 k>=1
      break;
  }
  //计算C1 = g^k mod p
  powmod(g, k, p, C1);
  //计算C2 = m * y^k mod p  (y = g^a)
  cinnum(m, fp);
  printf("从文件中读入明文m：\n");
  cotnum(m, stdout);
  powmod2(m, constnum1, y, k, p, C2);
  printf("\n");
  printf("密文C = （C1，C2）:\n");
  printf("C1 = \n");
  cotnum(C1, stdout);
  printf("C2 = \n");
  cotnum(C2, stdout);

  //-------------------------------------------------------------
  // ElGamal 解密
  // 1、计算V = C1^a(mod p)
  // 2、计算m1 = C2 * V^-1 (mod p)

  //计算m1
  // void copy* (flash x, flash y)
  // y = x
  copy(C1, temp);  // temp = C1

  // int xgcd (big x, big y, big xd, big yd, big z)
  // z = gcd(x, y) = (x * xd) + (y * yd)
  // 常用举例（求逆）：xgcd(x, p, x, x, x,); // x = 1/x mod p (p is prime)
  xgcd(temp, p, temp, temp, temp);  // 代换后即temp是C1的逆，temp = 1/C1 mod p

  big V_r = mirvar(0);
  powmod(temp, a, p, V_r);  // V_r = （C^(-1)）^a mod p = V^(-1)

  powmod(C2, constnum1, p, C2);  // C2 = C2 mod p

  // void powmod2 (big x, big y, big a, big b, big n, big w)
  // w = xy ab (mod n)
  //计算两个模幂的乘积
  powmod2(C2, constnum1, V_r, constnum1, p, m1);  // m1 = C2 * V_r mod p
  printf("\n解密明文m1\n");
  cotnum(m1, stdout);

  //====================================
  //验证解密是否成功
  printf("\n读入明文m：\n");
  cotnum(m, stdout);
  if (mr_compare(m, m1) == 0) {
    printf("\n读入和解出明文相同，解密成功\n");
  } else
    printf("读入和解出明文不同，解密失败\n");

  mirexit();

  return 0;
}