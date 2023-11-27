#ifndef GAMELOOP_H_DEFINED
#define GAMELOOP_H_DEFINED

#include <stdio.h>
#include "deck.h"
#include "card.h"

enum Hands {
    Nothing,
    Pair,
    TwoPairs,
    Threes,
    Straight,
    Flush,
    FullHouse,
    Fours,
    StraightFlush,
    Fives
};;

int printCard(struct card a, int shorter);

void dealHand(struct card d[], struct card *h[]);

void lootHand(struct card d[], struct card *h[], char held[]);

void printHand(struct card *h[], char held[]);

void holdOrUndo(char *cardInHand);

void swapCardsInHand(struct card *a, struct card *b);

void sortHand(struct card *h[]);

int evaluateHand(struct card *h[]);

int playAHand(struct card d[], struct card *h[]);

void gameloop();

void handEvaluationTest();

#endif