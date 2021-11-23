#include "stdio.h"
void testfun() {
  double x = 2;
  long double y = static_cast<long double>(x);
  printf("%Lf\n", y);
}
