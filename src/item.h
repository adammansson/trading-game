#ifndef ITEM_H
#define ITEM_H

#define ITEMS_SIZE (4)

typedef enum item_names_t { WATER = 0, FOOD, FIREARMS, ROBOTS } item_names_t;

typedef struct item_t {
  int amount;
  int purchase_price;
} item_t;

#endif /* ITEM_H */
