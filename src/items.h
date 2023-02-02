#ifndef ITEMS_H
#define ITEMS_H

#define ITEMS_SIZE (4)

typedef enum item_names_t { WATER = 0, FOOD, FIREARMS, ROBOTS } item_names_t;

typedef struct inventory_item_t {
  int amount;
  int purchase_price;
} item_t;

typedef struct market_item_t {
  int buy_price;
  int sell_price;
} market_item_t;

#endif /* ITEMS_H */
