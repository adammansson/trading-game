#ifndef PLAYER_H
#define PLAYER_H

#include "location.h"
#include "ship.h"

typedef struct player_t {
  char *name;
  int money;
  location_t *location;
  int inventory[NUM_TRADE_GOODS];
  ship_t *ship;
} player_t;

void populate_inventory(int *inventory);

void print_inventory(int *inventory);

player_t *new_player(location_t *starting_location, ship_t *starting_ship);

void print_player(player_t *player);

void free_player(player_t *player);

#endif /* PLAYER_H */
