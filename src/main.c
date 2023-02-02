#include "location.h"
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

void print_map(location_t **locations, int size) {
  int i;

  for (i = 0; i < size; ++i) {
    printf("%i: %s (%i, %i)\n", i, locations[i]->name, locations[i]->x,
           locations[i]->y);
  }
}

void goto_destination(input_buffer_t *input_buffer, player_t *player,
                      location_t **locations, int size) {
  int dest;

  print_map(locations, size);

  printf("Go to destination: ");
  read_input(input_buffer);

  dest = (int)strtol(input_buffer->buffer, (char **)NULL, 10);

  if (dest < 0 || dest > 6) {
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
  int fuel_amount, money;

  printf("Current fuel: %i litres.\nHow much fuel to buy: ", player->fuel);
  read_input(input_buffer);

  fuel_amount = (int)strtol(input_buffer->buffer, (char **)NULL, 10);
  if (0 > fuel_amount || fuel_amount > 100) {
    printf("Illegal amount '%s'.\n", input_buffer->buffer);
    return;
  }
  money = fuel_amount;

  if (money < player->money) {
    player->money -= money;
    player->fuel += fuel_amount;
    printf("Bought %i litres of fuel for %i$.\n", fuel_amount, money);
    return;
  }
  printf("Not enough money to buy this amount of fuel.\n");
}

void print_commands() {
  printf(
      "Commands:\n'.exit'\n'.status'\n'.map'\n'.market'\n'goto'\n'refuel'\n");
}

#define STR_EQUALS(str) strcmp(str, input_buffer->buffer) == 0

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
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}
