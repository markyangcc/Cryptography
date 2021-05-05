#include <cstdio>
#include <stdio.h>

typedef unsigned char uint8_t;

inline uint8_t add(uint8_t a, uint8_t b, uint8_t p) { return (a + b) % p; }
inline uint8_t subtract(uint8_t a, uint8_t b, uint8_t p) { return (a - b) % p; }
inline uint8_t multiply(uint8_t a, uint8_t b, uint8_t p) { return (a * b) % p; }
inline uint8_t divide(uint8_t a, uint8_t b, uint8_t p) { return (a / b) % p; }

int main() {
  uint8_t p = 8;
  uint8_t a = 39;
  uint8_t b = 16;

  uint8_t ret;

  printf("a,b,p: \t\t%02d,%02d,%02d\n", a, b, p);

  ret = add(a, b, p);
  printf("add:\t\t%02X\n", ret);

  ret = subtract(a, b, p);
  printf("subtract:\t%02X\n", ret);

  ret = multiply(a, b, p);
  printf("multiply:\t%02X\n", ret);

  ret = divide(a, b, p);
  printf("divide:\t\t%02X", ret);

  return 0;
}
