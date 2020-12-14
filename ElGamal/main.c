#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "include/miracl.h"
#define MAX_D 150  //安全素数 p 的位数

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
  big p_1 = mirvar(0);  // p-1
  big p_2 = mirvar(0);  // p-2
  big q = mirvar(0);
  big g = mirvar(0);
  big x = mirvar(0);
  big y = mirvar(0);
  big y1 = mirvar(0), y2 = mirvar(0);
  big m = mirvar(0);   //明文
  big m1 = mirvar(0);  //解密出的明文
  big k = mirvar(0);
  big flag = mirvar(0);       //中间变量
  big constnum1 = mirvar(1);  //常量1

  irand((unsigned)time(NULL));  // 使用当前时间作为随机数种子
                                //随机生成一个安全素数p
  bigdig(MAX_D, 10, q);         //生成一个150位的随机数
  nxsafeprime(0, 0, q, p);      //生成一个比q大的安全素数p
  copy(p, q);
  decr(q, 1, q);
  subdiv(q, 2, q);  //生成q=(p-1)/2
  decr(p, 1, p_1);  //生成p_1=p-1
  decr(p, 2, p_2);  //生成p_2=p-2
  //寻找一个本原根
  // irand((unsigned)time(NULL)); // 使用当前时间作为随机数种子
  while (1) {
    bigrand(p_1, g);                    // g小于p-1
    if (mr_compare(g, constnum1) <= 0)  //保证g大于1
      continue;
    powmod(g, mirvar(2), p, flag);
    if (mr_compare(flag, constnum1) != 0) {
      powmod(g, q, p, flag);
      if (mr_compare(flag, constnum1) != 0) {
        multiply(q, mirvar(2), flag);
        powmod(g, flag, p, flag);
        if (mr_compare(flag, constnum1) == 0) break;
      }
    }
  }  // end

  //随机选择私钥x，1<x<p-2
  irand((unsigned)time(NULL));  // 使用当前时间作为随机数种子
  while (1) {
    bigrand(p_2, x);                   // x <p-2
    if (mr_compare(x, constnum1) > 0)  //保证x>1
      break;
  }  // end
  //计算y
  powmod(g, x, p, y);
  // end
  printf("\n-------公布公钥（p，g，y）--------\n");
  printf("p = \n");
  cotnum(p, stdout);
  printf("g = \n");
  cotnum(g, stdout);
  printf("y = \n");
  cotnum(y, stdout);
  printf("\n--------私钥----------------------\n");
  cotnum(x, stdout);

  //-------------------------------------------------------------
  //加密算法

  //随机生成k，使得1<=k<=p-2,(k,p-1)=1
  irand((unsigned)time(NULL));  // 随机数种子
  while (1) {
    bigrand(p_1, k);                   // k小于p-1
    if (mr_compare(k, constnum1) < 0)  //保证k>=1
      continue;
    egcd(k, p_1, flag);
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
  powmod(flag, x, p, y1);           //求(y1的逆)的x次方  mod p
  powmod(y2, constnum1, p, y2);     // y2 mod p
  powmod2(y1, constnum1, y2, constnum1, p, m1);
  printf("\n------------解密明文-----------------\n");
  cotnum(m1, stdout);
  if (mr_compare(m, m1) == 0) {
    printf("\n");
    printf("成功\n");
  } else
    printf("false\n");

  mirexit();

  return 0;
}