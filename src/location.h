#ifndef LOCATION_H
#define LOCATION_H

#define MAP_SIZE (8)

#include "items.h"

typedef struct location_t {
  char *name;
  int x, y;
  market_item_t market[ITEMS_SIZE];
} location_t;

location_t *new_location(char *name, int x, int y);

location_t **new_world_map();

void populate_market(market_item_t *market);

void simulate_market(market_item_t *market);

void print_market(location_t *location);

int manhattan_distance(location_t *curr, location_t *dest);

#endif /* LOCATION_H */
