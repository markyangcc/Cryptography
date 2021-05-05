#include <cstdio>
#include <stdio.h>
#include <vector>

typedef unsigned char uint8_t;
uint8_t sbox[16][16];

//初始化 sbox[i][j] <- {ij}
void initialize();

//找到非零最高位并返回
uint8_t msb(unsigned short num);

//一个字节的多项式除法,返回商(a/b)
uint8_t divide(unsigned short a, uint8_t b, uint8_t &r);

// GF(2^8)乘法,返回 a * b
uint8_t multiply(uint8_t a, uint8_t b);

//扩展欧几里得算法求b在GF(2^8)的乘法逆元
uint8_t inverse(uint8_t b);

//映射
uint8_t map(uint8_t a);

int main() {
  std::vector<unsigned char> sboxvec;
  initialize();
  uint8_t i, j;
  for (i = 0; i <= 0xF; i++) {
    for (j = 0; j <= 0xF; j++) {
      sbox[i][j] = map(sbox[i][j]);
      sboxvec.push_back(sbox[i][j]);
    }
  }

  for (int i = 0; i < sboxvec.size(); i++) {
    if (i % 16 == 0)
      printf("\n");
    printf("%02X ", sboxvec[i]);
  }

  return 0;
}

void initialize() {
  uint8_t i, j;
  for (i = 0; i <= 0xF; i++) {
    for (j = 0; j <= 0xF; j++) {
      sbox[i][j] = inverse((i << 4) + j);
    }
  }
}

uint8_t msb(unsigned short num) {
  uint8_t i;
  for (i = 0; i <= 8; i++) {
    if (!(num >> (i + 1))) {
      return i;
    }
  }
  return i;
}

// a/b
uint8_t divide(unsigned short a, uint8_t b, uint8_t &r) {
  uint8_t a_msb = msb(a);
  uint8_t b_msb = msb(b);
  if (a < b) {
    r = a;
    return 0;
  }
  uint8_t bit = a_msb - b_msb;
  unsigned short temp = b;
  temp = temp << bit;
  a = a ^ temp;
  return (1 << bit) | divide(a, b, r);
}

uint8_t multiply(uint8_t a, uint8_t b) {
  uint8_t p = 0;

  for (int i = 0; i < 8; ++i) {
    if (a & 0x01) {
      p ^= b;
    }
    int flag = (b & 0x80);
    b <<= 1;
    if (flag) {
      b ^= 0x1B; /* P(x) = x^8 + x^4 + x^3 + x + 1 */
    }
    a >>= 1;
  }

  return p;
}

uint8_t inverse(uint8_t b) {
  if (b == 0)
    return 0;

  short r0 = 0x11B;
  uint8_t r1 = b, r2, q;
  uint8_t w0 = 0, w1 = 1, w2;
  q = divide(r0, r1, r2);
  w2 = w0 ^ multiply(q, w1); // w2 = -q
  while (1) {
    if (r2 == 0)
      break;
    r0 = r1;
    r1 = r2;
    q = divide(r0, r1, r2);
    w0 = w1;
    w1 = w2;
    w2 = w0 ^ multiply(q, w1);
  }
  return w1;
}

uint8_t map(uint8_t a) {
  uint8_t c = 0x63;
  uint8_t res = 0x0;
  uint8_t temp = 0x0;
  uint8_t i;
  for (i = 0; i < 8; i++) {
    temp = temp ^ ((a >> i) & 0x1) ^
           ((a >> ((i + 4) % 8)) & 0x1); //优先级>> 高于 &
    temp = temp ^ ((a >> ((i + 5) % 8)) & 0x1) ^ ((a >> ((i + 6) % 8)) & 0x1);
    temp = temp ^ ((a >> ((i + 7) % 8)) & 0x1) ^ ((c >> i) & 0x1);
    res = res | (temp << i);
    temp = 0x0;
  }
  return res;
}
