#include "location.h"

#include <stdio.h>
#include <stdlib.h>

location_t *new_location(char *name, int x, int y) {
  location_t *location;

  location = malloc(sizeof(location_t));
  location->name = name;
  location->x = x;
  location->y = y;
  populate_market(location->market);

  return location;
}

location_t **new_world_map() {
  location_t **map;

  map = calloc(MAP_SIZE * sizeof(location_t), sizeof(location_t));
  map[0] = new_location("Earth", 0, 0);
  map[1] = new_location("The moon", 1, 0);
  map[2] = new_location("Mars", 3, 1);
  map[3] = new_location("Venus", 5, 7);
  map[4] = new_location("Mercury", 8, 3);
  map[5] = new_location("Jupiter", 2, 9);
  map[6] = new_location("The sun", 11, 4);
  return map;
}

static int rand_in_range(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

void populate_market(market_item_t *market) {
  int i, rand_num;

  for (i = 0; i < ITEMS_SIZE; i++) {
    rand_num = rand_in_range(0, 100);
    market[i].buy_price = rand_num;
    market[i].sell_price = 2 * rand_num;
  }
}

void simulate_market(market_item_t *market) {
  int i, rand_num;

  for (i = 0; i < ITEMS_SIZE; i++) {
    rand_num = rand_in_range(-10, 10);
    market[i].buy_price += rand_num;
    market[i].sell_price += 2 * rand_num;
  }
}

#define BUYP(name) market[name].buy_price
#define SELLP(name) market[name].sell_price

void print_market(location_t *location) {
  market_item_t *market;

  market = location->market;
  printf("Market:\nBuy Sell\nWater: %i$ %i$\nFood: %i$ %i$\nFirearms: "
         "%i$ %i$\nRobots: %i$ %i$\n",
         BUYP(WATER), SELLP(WATER), BUYP(WATER), SELLP(WATER), BUYP(FIREARMS),
         SELLP(FIREARMS), BUYP(ROBOTS), SELLP(ROBOTS));
}

int manhattan_distance(location_t *curr, location_t *dest) {
  return abs(curr->x - dest->x) + abs(curr->y - dest->y);
}
