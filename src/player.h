#ifndef PLAYER_H
#define PLAYER_H

#include "item.h"
#include "location.h"

typedef struct player_t {
  char *name;
  int money;
  location_t *location;
  item_t inventory[4];
  int fuel_amount;
} player_t;

player_t *new_player(location_t *starting_location);

void print_player(player_t *player);

#endif /* PLAYER_H */
