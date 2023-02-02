#include "player.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

player_t *new_player(location_t *starting_location) {
  player_t *player;

  player = malloc(sizeof(player_t));
  player->name = "Arthur Dent";
  player->money = 1000;
  player->location = starting_location;
  memset(player->inventory, 0, ITEMS_SIZE * sizeof(item_t));
  player->fuel = 0;

  return player;
}

void print_inventory(player_t *player) {
  printf("Inventory:\nWater: "
         "%i\nFood: %i\nFirearms: %i\nRobots: %i\n",
         player->inventory[WATER].amount, player->inventory[FOOD].amount,
         player->inventory[FIREARMS].amount, player->inventory[ROBOTS].amount);
}

void print_player(player_t *player) {
  printf("Name: %s\nMoney: %i$\nCurrent location: %s (%i, %i)\nFuel: "
         "%i\n\n",
         player->name, player->money, player->location->name,
         player->location->x, player->location->y, player->fuel);
  print_inventory(player);
}
