#ifndef ITEMS_H
#define ITEMS_H

#define ITEMS_SIZE (4)

enum item_index { WATER = 0, FOOD, FIREARMS, ROBOTS };

// char *ITEM_NAMES[] = {"Water", "Food", "Firearms", "Robots"};

typedef struct inventory_item_t {
  char *name;
  int amount;
  int purchase_price;
} inventory_item_t;

typedef struct market_item_t {
  char *name;
  int buy_price;
  int sell_price;
} market_item_t;

#endif /* ITEMS_H */
