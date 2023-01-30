#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct inventory_t {
  int water_amount;
  int food_amount;
  int fur_amount;
  int robot_amount;
} inventory_t;

inventory_t *new_inventory();

#endif /* INVENTORY_H */
