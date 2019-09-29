#include <system.h>
#include <stdio.h>
#include "sys/alt_timestamp.h"

unsigned modk(unsigned x, unsigned k) {
  return (x & ((1 << k) - 1));
}

unsigned divk(unsigned x, unsigned k) {
  return (x >> k);
}

unsigned modulo(unsigned x) {
  unsigned r, q, k, a, m, z;
  m = 0xB3; // 179
  k = 8;
  a = (1 << k) - m;
  r = modk(x, k);
  q = divk(x, k);
  do {
    do {
      r = r + modk(q * a, k);
      q = divk(q * a, k);
    } while (q != 0);
    q = divk(r, k);
    r = modk(r, k);
  } while (q != 0);
  if (r >= m)
    z = r - m;
  else
    z = r;
  return z;
}

int main() {
  volatile unsigned a;
  unsigned i;
  unsigned ticks[10];
  
  alt_timestamp_start();
  
  printf("Timer Frequency %u\n", (alt_u32) alt_timestamp_freq());
  
  printf("Empty call ticks: ");
  for (i=0; i<9; i++) {
    ticks[i] = alt_timestamp();
    ticks[i] = alt_timestamp() - ticks[i];
    printf("%5d ", ticks[i]);
  }
  printf("\n");

  printf("Modulo call ticks: ");
  for (i=0; i<9; i++) {
    ticks[i] = alt_timestamp();
    a = modulo(0x00c0ffee);
    ticks[i] = alt_timestamp() - ticks[i];
    printf("%5d ", ticks[i]);
  }
  printf("\n");

  return 0;
}
