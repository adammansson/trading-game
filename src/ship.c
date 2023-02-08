#include "ship.h"
#include <stdlib.h>
#include <string.h>

ship_t *new_ship(char *name, int max_storage, int max_fuel) {
  ship_t *ship;

  ship = malloc(sizeof(ship_t));
  ship->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(ship->name, name);
  ship->max_storage = max_storage;
  ship->max_fuel = max_fuel;

  return ship;
}

void free_ship(ship_t *ship) {
  free(ship->name);
  free(ship);
}
