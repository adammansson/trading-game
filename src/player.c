#include "player.h"
#include "location.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populate_inventory(inventory_item_t *inventory) {
  int i;
  char *item_names[] = {"Water", "Food", "Firearms", "Robots"};

  for (i = 0; i < ITEMS_SIZE; i++) {
    inventory[i].name = item_names[i];
    inventory[i].amount = 0;
    inventory[i].purchase_price = 0;
  }
}

player_t *new_player(location_t *starting_location) {
  player_t *player;

  player = malloc(sizeof(player_t));
  player->name = "Arthur Dent";
  player->money = 1000;
  player->location = starting_location;
  populate_inventory(player->inventory);
  player->fuel = 0;

  return player;
}

void print_player(player_t *player) {
  printf("Name: %s\nMoney: %i$\nCurrent location: %s (%i, %i)\nFuel: "
         "%i litres\n",
         player->name, player->money, player->location->name,
         player->location->x, player->location->y, player->fuel);
}

void free_player(player_t *player) {
  free(player->name);
  free(player);
}
