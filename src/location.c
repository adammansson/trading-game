#include "location.h"

#include <stdio.h>
#include <stdlib.h>

#define BUY_PRICE(name) market[name].buy_price
#define SELL_PRICE(name) market[name].sell_price

static int rand_in_range(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

void populate_market(market_item_t *market) {
  int i, rand_num;
  char *item_names[] = {"Water", "Food", "Firearms", "Robots"};

  for (i = 0; i < ITEMS_SIZE; i++) {
    rand_num = rand_in_range(0, 100);
    market[i].name = item_names[i];
    BUY_PRICE(i) = 2 * rand_num;
    SELL_PRICE(i) = rand_num;
  }
}

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

  map[0] = new_location("Earth", 1, 1);
  map[1] = new_location("The moon", 2, 2);
  map[2] = new_location("Mars", 3, 4);
  map[3] = new_location("Venus", 5, 7);
  map[4] = new_location("Mercury", 8, 3);
  map[5] = new_location("Jupiter", 2, 9);
  map[6] = new_location("The sun", 9, 4);

  return map;
}

void simulate_market(market_item_t *market) {
  int i, rand_num;

  for (i = 0; i < ITEMS_SIZE; i++) {
    rand_num = rand_in_range(-10, 10);
    market[i].buy_price += 2 * rand_num;
    market[i].sell_price += rand_num;
  }
}

void print_market(market_item_t *market) {
  int i;

  printf("Market (Buy, Sell):\n");
  for (i = 0; i < ITEMS_SIZE; i++) {
    printf("%s (%i, %i)\n", market[i].name, BUY_PRICE(i), SELL_PRICE(i));
  }
}

int manhattan_distance(location_t *curr, location_t *dest) {
  return abs(curr->x - dest->x) + abs(curr->y - dest->y);
}

void free_location(location_t *location) {
  free(location->name);
  free(location);
}
