#include "inventory.h"
#include <stdlib.h>

inventory_t *new_inventory() {
  inventory_t *inventory;

  inventory = malloc(sizeof(inventory_t));
  inventory->water_amount = 0;
  inventory->food_amount = 0;
  inventory->fur_amount = 0;
  inventory->robot_amount = 0;

  return inventory;
}
