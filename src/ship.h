#ifndef SHIP_H
#define SHIP_H

#include "items.h"

#define SHIPS_SIZE (1)

typedef struct ship_t {
  char *name;
  int storage[NUM_TRADE_GOODS];
  int max_fuel;
  int max_storage;
} ship_t;

void populate_storage(int *storage);

void print_storage(int *storage);

ship_t *new_ship(char *name, int max_storage, int max_fuel);

void print_ship(ship_t *ship);

void free_ship(ship_t *ship);

#endif /* SHIP_H */
