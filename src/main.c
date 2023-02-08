#include "ship.h"
#define _POSIX_C_SOURCE 200809L

#include "player.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct input_buffer_t {
  char *buffer;
  size_t buffer_size;
  ssize_t input_size;
} input_buffer_t;

input_buffer_t *new_input_buffer() {
  input_buffer_t *input_buffer;

  input_buffer = malloc(sizeof(input_buffer_t));
  input_buffer->buffer = NULL;
  input_buffer->buffer_size = 0;
  input_buffer->input_size = 0;

  return input_buffer;
}

void close_input_buffer(input_buffer_t *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

void read_input(input_buffer_t *input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_size), stdin);
  if (bytes_read <= 0) {
    puts("Error reading input.");
    exit(EXIT_FAILURE);
  }

  input_buffer->input_size = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = '\0';
}

void goto_destination(input_buffer_t *input_buffer, player_t *player,
                      location_t **locations) {
  int dest;

  print_map(locations);

  printf("Go to destination: ");
  read_input(input_buffer);

  dest = (int)strtol(input_buffer->buffer, (char **)NULL, 10);

  if (dest < 1 || dest > MAP_SIZE) {
    printf("Illegal index '%s'.\n", input_buffer->buffer);
    return;
  }

  dest -= 1;

  if (locations[dest] == player->location) {
    printf("You can't travel to your current location.\n");
    return;
  }

  int fuel_needed = 5 * manhattan_distance(player->location, locations[dest]);

  if (fuel_needed > player->inventory[FUEL]) {
    printf("You don't have enough fuel for this journey, need at least %i "
           "litres, have %i.\n",
           fuel_needed, player->inventory[FUEL]);
    return;
  }
  player->inventory[FUEL] -= fuel_needed;

  simulate_market(player->location->market);
  player->location = locations[dest];
  simulate_market(player->location->market);

  printf("Arrived at %s.\n", locations[dest]->name);
}

void buy_items(input_buffer_t *input_buffer, player_t *player) {
  int item_to_buy, amount_to_buy, money_needed;

  print_inventory(player->inventory);

  print_market(player->location->market);

  printf("Which item to buy: ");
  read_input(input_buffer);

  item_to_buy = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  if (item_to_buy < 1 || item_to_buy > NUM_TRADE_GOODS) {
    printf("Illegal index '%s'.\n", input_buffer->buffer);
    return;
  }

  item_to_buy -= 1;

  printf("How many instances of %s to buy: ", TRADE_GOOD_NAMES[item_to_buy]);
  read_input(input_buffer);

  amount_to_buy = (int)strtol(input_buffer->buffer, (char **)NULL, 10);

  if (amount_to_buy < 1) {
    printf("You need to buy at least 1 item.\n");
    return;
  }

  money_needed =
      player->location->market[item_to_buy].buy_price * amount_to_buy;

  if (money_needed > player->money) {
    printf("Not enough money to buy these items, need at least %i$, have "
           "%i.\n",
           money_needed, player->money);
    return;
  }
  player->money -= money_needed;
  player->inventory[item_to_buy] += amount_to_buy;
  printf("Bought %i of %s for %i$.\n", amount_to_buy,
         TRADE_GOOD_NAMES[item_to_buy], money_needed);
}

void sell_items(input_buffer_t *input_buffer, player_t *player) {
  int item_to_sell, amount_to_sell, money_gained;

  print_market(player->location->market);

  print_inventory(player->inventory);

  printf("Which item to sell: ");
  read_input(input_buffer);

  item_to_sell = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  if (item_to_sell < 1 || item_to_sell > NUM_TRADE_GOODS) {
    printf("Illegal index '%s'.\n", input_buffer->buffer);
    return;
  }

  item_to_sell -= 1;

  printf("How many instances of %s to sell: ", TRADE_GOOD_NAMES[item_to_sell]);
  read_input(input_buffer);

  amount_to_sell = (int)strtol(input_buffer->buffer, (char **)NULL, 10);

  if (amount_to_sell < 1) {
    printf("You need to sell at least 1 item.\n");
    return;
  }

  if (amount_to_sell > player->inventory[item_to_sell]) {
    printf("Not enough items to sell, need %i$, have "
           "%i.\n",
           amount_to_sell, player->inventory[item_to_sell]);
    return;
  }

  money_gained =
      player->location->market[item_to_sell].sell_price * amount_to_sell;

  player->money += money_gained;
  player->inventory[item_to_sell] -= amount_to_sell;
  printf("Sold %i of %s for %i$.\n", amount_to_sell,
         TRADE_GOOD_NAMES[item_to_sell], money_gained);
}

void print_commands() {
  printf("Commands:\n'.exit'\n'.status'\n'.map'\n'.market'\n'goto'\n'buy'\n'"
         "sell'\n");
}

#define STR_EQUALS(str) strcmp(str, input_buffer->buffer) == 0

int main(void) {
  int i;
  input_buffer_t *input_buffer;
  player_t *player;
  location_t *world_map[MAP_SIZE];
  ship_t *ship_catalog[SHIPS_SIZE];

  srand(time(NULL));

  input_buffer = new_input_buffer();

  world_map[0] = new_location("Earth", 1, 1);
  world_map[1] = new_location("The moon", 2, 2);
  world_map[2] = new_location("Mars", 3, 4);
  world_map[3] = new_location("Venus", 5, 7);
  world_map[4] = new_location("Mercury", 8, 3);
  world_map[5] = new_location("Jupiter", 2, 9);
  world_map[6] = new_location("The sun", 9, 4);

  ship_catalog[0] = new_ship("Flea", 20, 30);

  player = new_player(world_map[0], ship_catalog[0]);

  while (1) {
    printf("> ");
    read_input(input_buffer);

    if (STR_EQUALS(".exit")) {
      exit(EXIT_SUCCESS);
    } else if (STR_EQUALS(".status")) {
      print_player(player);
      continue;
    } else if (STR_EQUALS(".map")) {
      print_map(world_map);
      continue;
    } else if (STR_EQUALS(".market")) {
      print_market(player->location->market);
      continue;
    } else if (STR_EQUALS(".commands")) {
      print_commands();
      continue;
    } else if (STR_EQUALS("goto")) {
      goto_destination(input_buffer, player, world_map);
      continue;
    } else if (STR_EQUALS("buy")) {
      buy_items(input_buffer, player);
      continue;
    } else if (STR_EQUALS("sell")) {
      sell_items(input_buffer, player);
      continue;
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }

  close_input_buffer(input_buffer);
  free_player(player);
  for (i = 0; i < MAP_SIZE; i++) {
    free_location(world_map[i]);
  }
}
