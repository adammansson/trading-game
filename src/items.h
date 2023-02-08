#ifndef ITEMS_H
#define ITEMS_H

enum trade_goods { FUEL, WATER, FOOD, FIREARMS, ROBOTS, NUM_TRADE_GOODS };

extern const char *TRADE_GOOD_NAMES[NUM_TRADE_GOODS];

typedef struct trade_good_t {
  int buy_price;
  int sell_price;
} trade_good_t;

#endif /* ITEMS_H */
