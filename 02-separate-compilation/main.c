#include <stdio.h>
#include "simple_math.h"

int main(int argc, char *argv[]) {
  int sum = add(5, 2);
  int product = multiply(3, 7);

  printf("5 + 2: %d\n", sum);
  printf("3 * 7: %d\n", product);
  
  return 0;
}
