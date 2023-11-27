#ifndef DECK_H_DEFINED
#define DECK_H_DEFINED

#include "card.h"
#include <stdlib.h>
#include <time.h>

extern const int deckSize;

void initializeDeck(struct card deck[]);

void swapCards(struct card *a, struct card *b);

void shuffleDeck(struct card deck[]);

#endif