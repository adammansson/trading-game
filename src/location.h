#ifndef LOCATION_H
#define LOCATION_H

#define MAP_SIZE (7)

#include "items.h"

typedef struct location_t {
  char *name;
  int x, y;
  trade_good_t market[NUM_TRADE_GOODS];
} location_t;

void populate_market(trade_good_t *market);

void simulate_market(trade_good_t *market);

location_t *new_location(char *name, int x, int y);

void free_location(location_t *location);

void print_map(location_t **locations);

void print_market(trade_good_t *market);

int manhattan_distance(location_t *curr, location_t *dest);

#endif /* LOCATION_H */
