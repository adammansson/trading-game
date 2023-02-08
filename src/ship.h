#ifndef SHIP_H
#define SHIP_H

#define SHIPS_SIZE (1)

typedef struct ship_t {
  char *name;
  int max_storage;
  int max_fuel;
} ship_t;

ship_t *new_ship(char *name, int max_storage, int max_fuel);

void free_ship(ship_t *ship);

#endif /* SHIP_H */
