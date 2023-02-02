#include "location.h"
#include <stdlib.h>

location_t *new_location(char *name, int x, int y) {
  location_t *location;

  location = malloc(sizeof(location_t));
  location->name = name;
  location->x = x;
  location->y = y;
  location->market = new_market();

  return location;
}

location_t **new_world_map() {
  location_t **map;

  map = malloc(MAP_SIZE * sizeof(location_t));
  // map[0] = (location_t){"Earth", 0, 0};
  // map[1] = (location_t){"The moon", 1, 0};
  // map[2] = (location_t){"Mars", 3, 1};
  // map[3] = (location_t){"Venus", 5, 1};
  // map[4] = (location_t){"Mercury", 1, 1};
  // map[5] = (location_t){"Jupiter", 1, 1};
  // map[6] = (location_t){"The sun", 1, 1};
  map[0] = new_location("Earth", 0, 0);
  map[1] = new_location("The moon", 1, 0);
  map[2] = new_location("Mars", 3, 1);
  map[3] = new_location("Venus", 5, 1);
  map[4] = new_location("Mercury", 1, 1);
  map[5] = new_location("Jupiter", 1, 1);
  map[6] = new_location("The sun", 1, 1);
  return map;
}
