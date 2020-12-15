#include <math.h>
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
  miracl *mip = mirsys(1000, 10);  //初始化一个1000个10进制数的大数系统
  mip->IOBASE = 10;                //指定IO使用的是10进制

  big p = mirvar(0);
  big g = mirvar(0);
  big pminus1 = mirvar(0);  // p-1
  big pminus2 = mirvar(0);  // p-2
  big q = mirvar(0);
  big a = mirvar(0);  //密钥
  big y = mirvar(0);
  big y1 = mirvar(0), y2 = mirvar(0);
  big m = mirvar(0);   //明文
  big m1 = mirvar(0);  //解密出的明文
  big k = mirvar(0);
  big flag = mirvar(0);       //中间变量
  big constnum1 = mirvar(1);  //常量1

  irand((unsigned)time(NULL));  // 使用当前时间作为随机数种子
                                //随机生成一个安全素数p

  // void bigdig (int n, int b, big x)
  // 生成一个给定长度的 b进制的大数并赋值给 x
  bigdig(LENGTH, 10, q);  //生成一个150位的10进制的随机数q

  // BOOL nxsafeprime (int type, int subset, big w, big p)
  // type: 素数的类型 q = (p − 1)/2 (type=0) or q = (p + 1)/2 (type=1)
  nxsafeprime(0, 0, q, p);  //生成下一个比q大的安全素数p

  // void copy* (flash x, flash y)
  // y = x
  copy(p, q);  // q = p, p为刚刚生成的随机安全素数

  // void decr (big x, int n, big z)
  // z = x − n
  decr(q, 1, q);  // q = q-1, 将q减一

  // int subdiv (big x, int n, big z)
  // z = x/n
  subdiv(q, 2, q);  //大数除法，q = (p-1)/2

  decr(p, 1, pminus1);  //大数减法，生成pminus1 = p-1
  decr(p, 2, pminus2);  //大数减法，生成pminus2 = p-2

  //==================================================================
  //查找一个原根
  //若g满足 g^2 mod p !=1 且 g^q mod p !=1，则说明g是一个原根
  while (1) {
    // void bigrand (big w, big x)
    //随机生成一个介于[0,w)之间的随机大数
    // 0 <= x < w
    bigrand(pminus1, g);  //随机生成一个特定范围的原根, g小于p-1

    // int compare* (big x, big y)
    // +1 if x > y; 0 if x = y; -1 if x < y
    if (mr_compare(g, constnum1) <= 0)  //保证生成的原根g是大于1的
      continue;  //如果生成的g等于或者小于1都继续循环生成

    // void powmod (big x, big y, big n, big w)
    // w = x^y (mod n)
    powmod(g, mirvar(2), p, flag);  // 构造flag = g^2 (mod p)
    //如果flag不等于1，即g与2同余
    if (mr_compare(flag, constnum1) != 0) {
      powmod(g, q, p, flag);  // 构造flag = g^q (mod p)
      //如果flag不等于1,即 g与2同余且与q同余，此时说明g是原根
      if (mr_compare(flag, constnum1) != 0) {
        // void multiply (big x, big y, big z)
        // z = xy
        multiply(q, mirvar(2), flag);  // flag = q*2
        powmod(g, flag, p, flag);      // flag = g^flag (mod p)，

        //如果flag =1 退出循环，即 g^2q (mod p) = 1 时退出循环
        if (mr_compare(flag, constnum1) == 0) break;
      }
    }
  }

  //==================================================================
  //随机选择私钥 a
  // 1 < a < p-2
  irand((unsigned)time(NULL));  // 随机数播种
  while (1) {
    bigrand(pminus2, a);               // a < p-2
    if (mr_compare(a, constnum1) > 0)  //保证 a > 1
      break;
  }

  //==================================================================
  //计算 g^a (mod p)
  powmod(g, a, p, y);  // y =g^a (mod p)

  printf("\n-------公布公钥（p，g，y）--------\n");
  printf("p = \n");
  cotnum(p, stdout);
  printf("g = \n");
  cotnum(g, stdout);
  printf("y = \n");
  cotnum(y, stdout);
  printf("\n--------私钥----------------------\n");
  cotnum(a, stdout);

  //-------------------------------------------------------------
  //加密算法

  //随机生成k，使得1<=k<=p-2,(k,p-1)=1
  irand((unsigned)time(NULL));  // 随机数种子
  while (1) {
    bigrand(pminus1, k);               // k小于p-1
    if (mr_compare(k, constnum1) < 0)  //保证k>=1
      continue;
    egcd(k, pminus1, flag);
    if (mr_compare(flag, constnum1) == 0) break;
  }  // end
  //计算y1=g^k mod p
  powmod(g, k, p, y1);
  //计算y2=my^k mod p
  cinnum(m, fp);
  powmod2(m, constnum1, y, k, p, y2);
  printf("\n");
  printf("------------密文（y1，y2）-----------\n");
  printf("y1 = \n");
  cotnum(y1, stdout);
  printf("y2 = \n");
  cotnum(y2, stdout);

  //-------------------------------------------------------------
  //解密算法

  //计算m1
  copy(y1, flag);
  xgcd(flag, p, flag, flag, flag);  //求y1的逆放到flag里面
  powmod(flag, a, p, y1);           //求(y1的逆)的x次方  mod p
  powmod(y2, constnum1, p, y2);     // y2 mod p
  powmod2(y1, constnum1, y2, constnum1, p, m1);
  printf("\n------------解密明文-----------------\n");
  cotnum(m1, stdout);
  if (mr_compare(m, m1) == 0) {
    printf("\n");
    printf("解密成功\n");
  } else
    printf("解密失败\n");

  mirexit();

  return 0;
}