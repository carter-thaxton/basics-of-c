#include <stdio.h>
#include "data.h"

int main(int argc, char *argv[]) {
  inc_counter();

  printf("counter: %d\ntitle: %s\n", counter, title);

  return 0;
}
