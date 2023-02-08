#include "player.h"
#include "location.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populate_inventory(int *inventory) {
  int i;

  for (i = 0; i < NUM_TRADE_GOODS; i++) {
    inventory[i] = 0;
  }
}

void print_inventory(int *inventory) {
  int i;

  printf("Inventory:\n");
  for (i = 0; i < NUM_TRADE_GOODS; i++) {
    printf("%s %i\n", TRADE_GOOD_NAMES[i], inventory[i]);
  }
}

player_t *new_player(location_t *starting_location, ship_t *starting_ship) {
  player_t *player;

  player = malloc(sizeof(player_t));
  player->name = malloc(sizeof(char) * (strlen("Arthur Dent") + 1));
  strcpy(player->name, "Arthur Dent");
  player->money = 1000;
  player->location = starting_location;
  player->ship = starting_ship;
  populate_inventory(player->inventory);

  return player;
}

void print_player(player_t *player) {
  printf("Name: %s\nMoney: %i$\nCurrent location: %s (%i, %i)\nShip: %s\nFuel: "
         "%i litres\n",
         player->name, player->money, player->location->name,
         player->location->x, player->location->y, player->ship->name,
         player->inventory[FUEL]);
}

void free_player(player_t *player) {
  free(player->name);
  free(player);
}
