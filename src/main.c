#define _POSIX_C_SOURCE 200809L

#include "location.h"
#include "player.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_status(player_t *player) {
  printf("Name: %s\nMoney: %i$\nFuel: %i\nWater: %i\nFood: %i\n", player->name,
         player->money, player->fuel_amount, player->inventory[WATER],
         player->inventory[FOOD]);
}

void print_map(location_t *locations, int size) {
  int i;

  for (i = 0; i < size; ++i) {
    printf("%i: %s (%i, %i)\n", i, locations[i].name, locations[i].x,
           locations[i].y);
  }
}

typedef enum META_RESULT {
  META_SUCCESS,
  META_UNRECOGNIZED_COMMAND
} META_COMMAND_RESULT;

int main(void) {
  input_buffer_t *input_buffer;
  player_t *player;
  location_t world_map[2];
  int destination, fuel_amount, money;

  input_buffer = new_input_buffer();
  player = new_player();
  world_map[0] = (location_t){"Earth", 0, 0};
  world_map[1] = (location_t){"Moon", 1, 1};

  while (1) {
    printf("> ");
    read_input(input_buffer);

    if (strcmp(".exit", input_buffer->buffer) == 0) {
      exit(EXIT_SUCCESS);
    } else if (strcmp(".status", input_buffer->buffer) == 0) {
      print_status(player);
      continue;
    } else if (strcmp("goto", input_buffer->buffer) == 0) {
      print_map(world_map, 2);

      printf("Pick a destination: ");
      read_input(input_buffer);

      destination = atoi(input_buffer->buffer);
      if (0 > destination || destination > 1) {
        printf("Illegal destination '%s'.\n", input_buffer->buffer);
        continue;
      }
      printf("Traveling to %s.\n", world_map[destination].name);
      continue;
    } else if (strcmp("refuel", input_buffer->buffer) == 0) {
      printf("How much fuel to buy: ");
      read_input(input_buffer);

      fuel_amount = atoi(input_buffer->buffer);
      if (0 > fuel_amount || fuel_amount > 100) {
        printf("Illegal amount '%s'.\n", input_buffer->buffer);
        continue;
      }
      money = fuel_amount;

      if (money < player->money) {
        player->money -= money;
        player->fuel_amount += fuel_amount;
        printf("Bought %i litres of fuel for %i$.\n", fuel_amount, money);
      } else {
        printf("Not enough money to buy this amount of fuel.\n");
      }
      continue;
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}
