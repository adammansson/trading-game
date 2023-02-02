#include "items.h"
#define _POSIX_C_SOURCE 200809L

#include "location.h"
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

void print_map(location_t **locations, int size) {
  int i;

  for (i = 0; i < size; ++i) {
    printf("%i: %s (%i, %i)\n", i, locations[i]->name, locations[i]->x,
           locations[i]->y);
  }
}

void print_commands() {
  printf(
      "Commands:\n'.exit'\n'.status'\n'.map'\n'.market'\n'goto'\n'refuel'\n");
}

#define STR_EQUALS(str) strcmp(str, input_buffer->buffer) == 0

void goto_destination(input_buffer_t *input_buffer, player_t *player,
                      location_t **locations, int size) {
  int dest;

  print_map(locations, size);

  printf("Go to destination: ");
  read_input(input_buffer);

  dest = (int)strtol(input_buffer->buffer, (char **)NULL, 10);

  if (dest < 0 || dest > MAP_SIZE - 1) {
    printf("Illegal index '%s'.\n", input_buffer->buffer);
    return;
  }

  if (locations[dest] == player->location) {
    printf("You can't travel to your current location.\n");
    return;
  }

  int fuel_needed = 5 * manhattan_distance(player->location, locations[dest]);

  if (fuel_needed > player->fuel) {
    printf("You don't have enough fuel for this journey, need at least %i "
           "litres, have %i.\n",
           fuel_needed, player->fuel);
    return;
  }
  player->fuel -= fuel_needed;

  simulate_market(player->location->market);
  player->location = locations[dest];
  simulate_market(player->location->market);

  printf("Arrived at %s.\n", locations[dest]->name);
}

void refuel_ship(input_buffer_t *input_buffer, player_t *player) {
  int fuel_amount, money_needed;

  printf("Current fuel: %i litres.\nHow much fuel to buy: ", player->fuel);
  read_input(input_buffer);

  fuel_amount = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  if (fuel_amount < 0 || fuel_amount > 100) {
    printf("Illegal amount '%s'.\n", input_buffer->buffer);
    return;
  }
  money_needed = 5 * fuel_amount;

  if (money_needed > player->money) {
    printf(
        "Not enough money to buy this amount of fuel, need at least %i$, have "
        "%i.\n",
        money_needed, player->money);
    return;
  }
  player->money -= money_needed;
  player->fuel += fuel_amount;
  printf("Bought %i litres of fuel for %i$.\n", fuel_amount, money_needed);
}

void buy_items(input_buffer_t *input_buffer, player_t *player) {
  int i, item_to_buy, amount_to_buy, money_needed;

  printf("Buying:\n");
  print_inventory(player);
  printf("\nMarket:\n");
  for (i = 0; i < ITEMS_SIZE; i++) {
    printf("%i %s %i$\n", i, ITEM_NAMES[i],
           player->location->market[i].buy_price);
  }
  printf("Which item to buy: ");
  read_input(input_buffer);

  item_to_buy = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  if (item_to_buy < 0 || item_to_buy > ITEMS_SIZE - 1) {
    printf("Illegal index '%s'.\n", input_buffer->buffer);
    return;
  }

  printf("How many instances to buy: ");
  read_input(input_buffer);

  amount_to_buy = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  money_needed =
      player->location->market[item_to_buy].buy_price * amount_to_buy;
  if (money_needed > player->money) {
    printf("Not enough money to buy these items, need at least %i$, have "
           "%i.\n",
           money_needed, player->money);
    return;
  }
  player->money -= money_needed;
  player->inventory[item_to_buy].amount += amount_to_buy;
  printf("Bought %i of %s for %i$.\n", amount_to_buy, ITEM_NAMES[item_to_buy],
         money_needed);
}

void sell_items(input_buffer_t *input_buffer, player_t *player) {
  int i, item_to_sell, amount_to_sell, money_gained;

  printf("Selling:\n");

  for (i = 0; i < ITEMS_SIZE; i++) {
    printf("%i %s %i\n", i, ITEM_NAMES[i], player->inventory[i].amount);
  }

  printf("\nMarket:\n");
  for (i = 0; i < ITEMS_SIZE; i++) {
    printf("%s %i$\n", ITEM_NAMES[i], player->location->market[i].sell_price);
  }
  printf("Which item to sell: ");
  read_input(input_buffer);

  item_to_sell = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  if (item_to_sell < 0 || item_to_sell > ITEMS_SIZE - 1) {
    printf("Illegal index '%s'.\n", input_buffer->buffer);
    return;
  }

  printf("How many instances to sell: ");
  read_input(input_buffer);

  amount_to_sell = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  if (amount_to_sell > player->inventory[item_to_sell].amount) {
    printf("Not enough items to sell, need %i$, have "
           "%i.\n",
           amount_to_sell, player->inventory[item_to_sell].amount);
    return;
  }

  money_gained =
      player->location->market[item_to_sell].sell_price * amount_to_sell;

  player->money += money_gained;
  player->inventory[item_to_sell].amount -= amount_to_sell;
  printf("Sold %i of %s for %i$.\n", amount_to_sell, ITEM_NAMES[item_to_sell],
         money_gained);
}

int main(void) {
  input_buffer_t *input_buffer;
  player_t *player;
  location_t **world_map;

  srand(time(NULL));

  input_buffer = new_input_buffer();
  world_map = new_world_map();
  player = new_player(world_map[0]);

  while (1) {
    printf("> ");
    read_input(input_buffer);

    if (STR_EQUALS(".exit")) {
      exit(EXIT_SUCCESS);
    } else if (STR_EQUALS(".status")) {
      print_player(player);
      continue;
    } else if (STR_EQUALS(".map")) {
      print_map(world_map, MAP_SIZE);
      continue;
    } else if (STR_EQUALS(".market")) {
      print_market(player->location);
      continue;
    } else if (STR_EQUALS(".commands")) {
      print_commands();
      continue;
    } else if (STR_EQUALS("goto")) {
      goto_destination(input_buffer, player, world_map, 7);
      continue;
    } else if (STR_EQUALS("refuel")) {
      refuel_ship(input_buffer, player);
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
}
