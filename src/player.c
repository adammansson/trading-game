#include "player.h"
#include "location.h"
#include "ship.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

player_t *new_player(location_t *starting_location, ship_t *starting_ship) {
  player_t *player;

  player = malloc(sizeof(player_t));
  player->name = malloc(sizeof(char) * (strlen("Arthur Dent") + 1));
  strcpy(player->name, "Arthur Dent");
  player->money = 1000;
  player->location = starting_location;
  player->ship = starting_ship;

  return player;
}

void print_player(player_t *player) {
  printf("Player:\nName: %s\nMoney: %i$\nCurrent location: %s (%i, %i)\n",
         player->name, player->money, player->location->name,
         player->location->x, player->location->y);
  print_ship(player->ship);
}

void free_player(player_t *player) {
  free(player->name);
  free(player);
}
