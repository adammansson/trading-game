#ifndef LOCATION_H
#define LOCATION_H

#include "market.h"

#define MAP_SIZE (8)

typedef struct location_t {
  char *name;
  int x, y;
  int *market;
} location_t;

location_t *new_location(char *name, int x, int y);

location_t **new_world_map();

#endif /* LOCATION_H */
