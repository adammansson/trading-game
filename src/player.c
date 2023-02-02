#include "player.h"
#include "inventory.h"
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
  memset(player->inventory, 0, 4 * sizeof(item_t));
  player->fuel_amount = 0;

  return player;
}

void print_player(player_t *player) {
  printf(
      "Name: %s\nMoney: %i$\nCurrent location: %s (%i, %i)\nFuel: %i\nWater: "
      "%i\nFood: %i\n",
      player->name, player->money, player->location->name, player->location->x,
      player->location->y, player->fuel_amount, player->inventory[WATER].amount,
      player->inventory[FOOD].amount);
}
