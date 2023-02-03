#ifndef PLAYER_H
#define PLAYER_H

#include "location.h"

typedef struct player_t {
  char *name;
  int money;
  location_t *location;
  inventory_item_t inventory[ITEMS_SIZE];
  int fuel;
} player_t;

void populate_inventory(inventory_item_t *inventory);

player_t *new_player(location_t *starting_location);

void print_player(player_t *player);

void free_player(player_t *player);

#endif /* PLAYER_H */
