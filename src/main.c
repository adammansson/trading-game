#define _POSIX_C_SOURCE 200809L

#include "item.h"
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

void goto_destination(input_buffer_t *input_buffer, player_t *player,
                      location_t **locations, int size) {
  int destination;

  print_map(locations, size);

  printf("Go to destination: ");
  read_input(input_buffer);

  destination = atoi(input_buffer->buffer);
  if (destination < 0 || destination > 6) {
    printf("Illegal destination '%s'.\n", input_buffer->buffer);
    return;
  }
  player->location = locations[destination];
  printf("Traveling to %s.\n", locations[destination]->name);
}

void refuel_ship(input_buffer_t *input_buffer, player_t *player) {
  int fuel_amount, money;

  printf("How much fuel to buy: ");
  read_input(input_buffer);

  fuel_amount = atoi(input_buffer->buffer);
  if (0 > fuel_amount || fuel_amount > 100) {
    printf("Illegal amount '%s'.\n", input_buffer->buffer);
    return;
  }
  money = fuel_amount;

  if (money < player->money) {
    player->money -= money;
    player->fuel_amount += fuel_amount;
    printf("Bought %i litres of fuel for %i$.\n", fuel_amount, money);
  } else {
    printf("Not enough money to buy this amount of fuel.\n");
  }
}

void print_market(player_t *player) {
  int *market;

  market = player->location->market;
  printf("Water: %i\nFood: %i\nFirearms: %i\nRobots: %i\n", market[WATER],
         market[FOOD], market[FIREARMS], market[ROBOTS]);
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

    if (strcmp(".exit", input_buffer->buffer) == 0) {
      exit(EXIT_SUCCESS);
    } else if (strcmp(".status", input_buffer->buffer) == 0) {
      print_player(player);
      continue;
    } else if (strcmp(".map", input_buffer->buffer) == 0) {
      print_map(world_map, 7);
      continue;
    } else if (strcmp("goto", input_buffer->buffer) == 0) {
      goto_destination(input_buffer, player, world_map, 7);
      continue;
    } else if (strcmp("refuel", input_buffer->buffer) == 0) {
      refuel_ship(input_buffer, player);
      continue;
    } else if (strcmp("market", input_buffer->buffer) == 0) {
      print_market(player);
      continue;
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}
