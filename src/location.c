#include "location.h"

#include <stdio.h>
#include <stdlib.h>

static int rand_in_range(int lower, int upper) {
  return (rand() % (upper - lower + 1)) + lower;
}

void populate_market(trade_good_t *market) {
  int i, rand_num;

  // FUEL = 0
  market[FUEL].buy_price = 10;
  market[FUEL].sell_price = 5;

  for (i = 1; i < NUM_TRADE_GOODS; i++) {
    rand_num = rand_in_range(25, 100);
    market[i].sell_price = rand_num;
    market[i].buy_price = 2 * market[i].sell_price;
  }
}

void simulate_market(trade_good_t *market) {
  int i, rand_num;

  for (i = 1; i < NUM_TRADE_GOODS; i++) {
    rand_num = rand_in_range(-10, 10);
    market[i].sell_price += rand_num;
    if (market[i].sell_price <= 0) {
      market[i].sell_price = rand_in_range(25, 100);
    }
    market[i].buy_price = 2 * market[i].sell_price;
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

void free_location(location_t *location) {
  free(location->name);
  free(location);
}

void print_map(location_t **locations) {
  int x, y, i, planet_found;

  for (y = 0; y < 10; y++) {
    for (x = 0; x < 10; x++) {
      planet_found = 0;
      for (i = 0; i < MAP_SIZE; ++i) {
        if (locations[i]->x == x && locations[i]->y == y) {
          putc('0' + i, stdout);
          planet_found = 1;
        }
      }
      if (planet_found == 0) {
        putc(' ', stdout);
      }
    }
    putc('\n', stdout);
  }

  for (i = 0; i < MAP_SIZE; ++i) {
    printf("%i: %s (%i, %i)\n", i + 1, locations[i]->name, locations[i]->x,
           locations[i]->y);
  }
}

void print_market(trade_good_t *market) {
  int i;

  printf("Market (Buy, Sell):\n");
  for (i = 0; i < NUM_TRADE_GOODS; i++) {
    printf("%i. %s (%i, %i)\n", i + 1, TRADE_GOOD_NAMES[i], market[i].buy_price,
           market[i].sell_price);
  }
}

int manhattan_distance(location_t *curr, location_t *dest) {
  return abs(curr->x - dest->x) + abs(curr->y - dest->y);
}
