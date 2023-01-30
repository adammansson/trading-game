#include "player.h"
#include "inventory.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

player_t *new_player() {
  player_t *player;

  player = malloc(sizeof(player_t));
  player->name = "Arthur Dent";
  player->money = 1000;
  memset(player->inventory, 0, 4 * sizeof(int));
  player->fuel_amount = 0;

  return player;
}
