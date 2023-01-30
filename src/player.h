#ifndef PLAYER_H
#define PLAYER_H

typedef enum item_t { WATER = 0, FOOD, FIREARMS, ROBOTS } item_t;

typedef struct player_t {
  char *name;
  int money;
  int inventory[4];
  int fuel_amount;
} player_t;

player_t *new_player();

#endif /* PLAYER_H */
