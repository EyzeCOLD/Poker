#include "../include/card.h"

int getSuit(struct card a) {
    return a.suit;
}

int getRank(struct card a) {
    return a.rank;
}

void setSuit(struct card a, int suit) {
    a.suit = suit;
}

void setRank(struct card a, int rank) {
    a.rank = rank;
}

char getSuitChar(struct card a) {
    switch (getSuit(a)) {
        case Clubs:
            return 'C';
        case Diamonds:
            return 'D';
        case Hearts:
            return 'S';
        case Spades:
            return 'H';
        default:
            return '\0';
    }
}

char *getSuitStr(struct card a) {
    switch (getSuit(a)) {
        case Clubs:
            return "CLUBS";
        case Diamonds:
            return "DIAMONDS";
        case Hearts:
            return "HEARTS";
        case Spades:
            return "SPADES";
        default:
            return "JOKERSUIT";
    }
}

char *getRankStr(struct card a, int shorter) {
    switch (getRank(a)) {
        case 0:
            if (shorter) {
                return "*";
            }
            return "JOKER";
        case 2:
            return "2";
        case 3:
            return "3";
        case 4:
            return "4";
        case 5:
            return "5";
        case 6:
            return "6";
        case 7:
            return "7";
        case 8:
            return "8";
        case 9:
            return "9";
        case 10:
            return "10";
        case Jack:
            if (shorter) {
                return "J";
            }
            return "JACK";
        case Queen:
            if (shorter) {
                return "Q";
            }
            return "QUEEN";
        case King:
            if (shorter) {
                return "K";
            }
            return "KING";
        case Ace:
                if (shorter) {
                return "A";
            }
            return "ACE";
        default:
            return "ERROR";
    }
}