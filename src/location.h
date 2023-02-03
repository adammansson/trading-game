#ifndef LOCATION_H
#define LOCATION_H

#define MAP_SIZE (7)

#include "items.h"

typedef struct location_t {
  char *name;
  int x, y;
  market_item_t market[ITEMS_SIZE];
} location_t;

void populate_market(market_item_t *market);

location_t *new_location(char *name, int x, int y);

location_t **new_world_map();

void simulate_market(market_item_t *market);

void print_market(market_item_t *market);

int manhattan_distance(location_t *curr, location_t *dest);

void free_location(location_t *location);

#endif /* LOCATION_H */
