#include "market.h"
#include "item.h"
#include <stdlib.h>

int rand_in_range(int lower, int upper) {
  int r;

  r = rand();

  return (r % (upper - lower + 1)) + lower;
}

int *new_market() {
  int i, *market;

  market = malloc(ITEMS_SIZE * sizeof(int));
  for (i = 0; i < ITEMS_SIZE; i++) {
    market[i] = rand_in_range(0, 100);
  }

  return market;
}
