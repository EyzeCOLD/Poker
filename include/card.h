#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

enum Suit {
    Clubs, Diamonds, Hearts, Spades
};

enum Rank {
    Joker, Jack = 11, Queen, King, Ace 
};

struct card
{
    int rank;
    int suit;
};

int getSuit(struct card a);

int getRank(struct card a);

void setSuit(struct card a, int suit);

void setRank(struct card a, int rank);

char getSuitChar(struct card a);

char *getSuitStr(struct card a);

char *getRankStr(struct card a, int shoter);

#endif