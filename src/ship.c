#include "ship.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void populate_storage(int *storage) {
  int i;

  for (i = 0; i < NUM_TRADE_GOODS; i++) {
    storage[i] = 0;
  }
}

void print_storage(int *storage) {
  int i;

  printf("Inventory:\n");
  for (i = 0; i < NUM_TRADE_GOODS; i++) {
    printf("%s %i\n", TRADE_GOOD_NAMES[i], storage[i]);
  }
}

ship_t *new_ship(char *name, int max_storage, int max_fuel) {
  ship_t *ship;

  ship = malloc(sizeof(ship_t));
  ship->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(ship->name, name);
  ship->max_storage = max_storage;
  populate_storage(ship->storage);
  ship->max_fuel = max_fuel;

  return ship;
}

void print_ship(ship_t *ship) {
  printf("Ship:\nName: %s\nMax storage: %i\nMax fuel %i\n", ship->name,
         ship->max_storage, ship->max_fuel);
  print_storage(ship->storage);
}

void free_ship(ship_t *ship) {
  free(ship->name);
  free(ship);
}
