#include "../include/deck.h"

const int deckSize = 53;

void initializeDeck(struct card deck[]) {
    int suit;
    int rank;
    for (suit = 0; suit <= Spades; suit++) {
        for (rank = 2; rank <= Ace; rank++) {
            struct card newCard = {rank, suit};
            deck[suit * 13 + rank - 2] = newCard;
        }
    }
    struct card joker = {Joker, 4};
    deck[deckSize - 1] = joker;
}

void swapCards(struct card *a, struct card *b) {
    if (a == b) {
        return;
    }
    struct card temp = *a;
    *a = *b;
    *b = temp;
}

void shuffleDeck(struct card deck[]) {
    for (int i = deckSize - 1; i > 0; i--) {
        srand((unsigned)time(NULL)+i);
        swapCards(&deck[i], &deck[rand() % (i + 1)]);
    }
    return;
}