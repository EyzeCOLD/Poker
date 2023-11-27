#include "../include/gameloop.h"

int printCard(struct card a, int shorter) {
    int sum = 0;
    if (getRank(a) == Joker) {
        return printf("%s", getRankStr(a, shorter));
    }
    if (shorter) {
        return printf("%c%s", getSuitChar(a), getRankStr(a, shorter));
    } else {
        return printf("%s of %s", getRankStr(a, shorter), getSuitStr(a));
    }
    return -1;
}

// Deals initial hand of 5 cards
void dealHand(struct card d[], struct card *h[]) {
    for (int i = 0; i < 5; i++) {
        h[i] = &d[i];
    }
}

// Keep held cards, discard the rest, draw that many cards
void lootHand(struct card d[], struct card *h[], char held[]) {
    int deckDepth = 5;
    for (int i = 0; i < 5; i++) {
        if (held[i] != 'h') {
            h[i] = &d[deckDepth++];
        }
    }
}

void printHand(struct card *h[], char held[]) {
    for (int i = 0; i < 5; i++) {
        printf("[%d.] -- [[", i + 1);
        if (held[i] == 'h') {
            printf("HOLD");
        } else {
            printf("    ");
        }
        printf("]] -- [");
        printCard(*h[i], 0);
        printf("]\n");
    }
}

void holdOrUndo(char *cardInHand) {
    if (*cardInHand == 'h') {
        *cardInHand = ' ';
    } else {
        *cardInHand = 'h';
    }
}

void swapCardsInHand(struct card *a, struct card *b) {
    struct card temp = *a;
    *a = *b;
    *b = temp;
}

void sortHand(struct card *h[]) {
    for (int i = 1; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            if (getRank(*h[j]) > getRank(*h[j+1])) {
                swapCardsInHand(h[j], h[j+1]);
            }
        }
    }
}

int evaluateHand(struct card *h[]) {
    sortHand(h);
    int flushness = 0;
    int straightness = 0;
    int ranks[15];
    for (int i = 0; i < 15; i++) {
        ranks[i] = 0;
    }

    // add up how much of each rank appears in the hand
    for (int i = 0; i < 5; i++) {
        ranks[getRank(*h[i])]++;
    }

    // figure out the rank with most and the rank with the second most occurences in hand
    // if current rank has more occurences than the recorded mostOf, save the RANK as mostOf
    // and save previous mostOf as 
    int mostOf = 0;
    int secondMostOf = 0;
    for (int i = 2; i < 15; i++) {
        if (ranks[i] > ranks[mostOf]) {
            if (ranks[mostOf] > ranks[secondMostOf]) {
                secondMostOf = mostOf;
            }
            mostOf = i;
        } else if (ranks[i] > ranks[secondMostOf]) {
            secondMostOf = i;
        }
    }

    // figure out the straightness and the flushness of the hand
    for (int i = 0; i < 4; i++) {
        if (getSuit(*h[i]) == getSuit(*h[i+1])) {
            flushness++;
        }
        if (getRank(*h[i]) + 1 == getRank(*h[i+1])) {
            straightness++;
        }
    }
    
    // ??? Joker effects ???
    if (ranks[Joker] > 0) {
        ranks[mostOf] += ranks[Joker];
        flushness++;

        // Joker effects for straights
        int gapsOfOneRanks = 0;
        int gapsOfTwoRanks = 0;
        int gap = 0;
        for (int i = 1; i < 4; i++) {
            gap = getRank(*h[i+1]) - getRank(*h[i]);
            if (gap == 1) {
                gapsOfOneRanks++;
            } else if (gap == 2) {
                gapsOfTwoRanks++;
            }
        }
        if (gapsOfOneRanks + gapsOfTwoRanks == 3 && gapsOfTwoRanks <= 1) {
            straightness = 4;
        } 
    }

    if (ranks[mostOf] == 5) {
        return Fives;
    }

    if (straightness == 4 && flushness == 4) {
        return StraightFlush;
    }

    if (ranks[mostOf] == 4) {
        return Fours;
    }

    if (ranks[mostOf] == 3 && ranks[secondMostOf] == 2) {
        return FullHouse;
    }

    if (flushness == 4) {
        return Flush;
    }

    if (straightness == 4) {
        return Straight;
    }

    if (ranks[mostOf] == 3) {
        return Threes;
    }

    if (ranks[mostOf] == 2 && ranks[secondMostOf] == 2) {
        return TwoPairs;
    }

    if (ranks[mostOf] == 2) {
        return Pair;
    }

    return Nothing;
}

int playAHand(struct card d[], struct card *h[]) {
    char input;
    char hold[5];

    shuffleDeck(d);
    dealHand(d, h);
    // reset held cards
    for (int i = 0; i < 5; i++) {
        hold[i] = ' ';
    }

    while (1) {
        printf("\n");
        printHand(h, hold);

        printf("\n1, 2, 3, 4, 5 - hold or undo\nd - move to draw a new card for each card not held\n");
            
        scanf(" %c", &input);

        switch (input) {
            case '1':
                holdOrUndo(&hold[0]);
                break;
            case '2':
                holdOrUndo(&hold[1]);
                break;
            case '3':
                holdOrUndo(&hold[2]);
                break;
            case '4':
                holdOrUndo(&hold[3]);
                break;
            case '5':
                holdOrUndo(&hold[4]);
                break;
            default:
                break;
        }

        if (input == 'd') {
            lootHand(d, h, hold);
            printHand(h, hold);
            return evaluateHand(h);
        }
    }
}

void gameloop() {
    struct card deck[53];
    initializeDeck(deck);
    struct card *hand[5];

    printf("WELCOME TO POKER\n\n");

    char input;
    int money = 100;
    int bet = 2;

    while (money > 0) {
        if (bet > money) {
            bet = money;
        }
        printf("Money: $%d.00\n", money);
        printf("Bet: $%d.00\n", bet);
        printf("d - deal\n");
        printf("b - change bet\n");
        printf("q - quit\n");

        scanf(" %c", &input);

        if (input == 'q') {
            printf("\nThanks for playing!\n");
            return;
        }

        if (input == 'b') {
            printf("\nChange bet (min. $1.00 - $%d.00 max.)\n", money);
            scanf(" %d", &bet);
            if (bet > money) {
                bet = money;
            } else if (bet < 1) {
                bet = 1;
            }
        }

        if (input == 'd') {
            money -= bet;
            int multiplier = 0;
            switch (playAHand(deck, hand)) {
                case Nothing:
                    multiplier = 0;
                    printf("\nYou got nothing.\n");
                    break;
                case Pair:
                    multiplier = 1;
                    printf("\nA pair.\n");
                    break;
                case TwoPairs:
                    multiplier = 2;
                    printf("\nTwo pairs.\n");
                    break;
                case Threes:
                    multiplier = 2;
                    printf("\nThree of a kind.\n");
                    break;
                case Straight:
                    multiplier = 3;
                    printf("\nA straight!.\n");
                    break;
                case Flush:
                    multiplier = 4;
                    printf("\nA flush!\n");
                    break;
                case FullHouse:
                    multiplier = 8;
                    printf("\nFull house!!\n");
                    break;
                case Fours:
                    multiplier = 15;
                    printf("\nFOUR OF A KIND!\n");
                    break;
                case StraightFlush:
                    multiplier = 30;
                    printf("\nS t r a i g h t\nF l u s h\n");
                    break;
                case Fives:
                    multiplier = 50;
                    printf("\nF I V E  O F\nA  K I N D\n");
                    break;
                default:
                    break;
            }
            if (multiplier == 1) {
                printf("\nYou got your bet back.\n");
                money += bet;
            }
            if (multiplier > 1) {
                printf("\nYou won $%d.00!\n\n", bet * multiplier);
                money += bet * multiplier;
            }
        }
    }
    printf("\nYou've gambled all your money away. You sell your house without telling your wife to cover your debts. ");
    printf("One morning you decided to end it all. She wad gotten up early and made you eggs. Over easy, just like you liked them. ");
    printf("You left without eating, while Sammy was still asleep. She said \"I love you\" with a smile, you could only reply with a sullen \"Thanks...\". ");
    printf("She was still completely oblivious that her and poor little Sammy were already technically homeless. Soon they'd be without a husband and a father. ");
    printf("The cold muzzle of the shotgun got stuck on your tongue like a last cruel jest from the universe. Or was it just the inevitability of it all? ");
    printf("Well, it's not going to matter. Goodbye.");
    printf("\nG A M E  O V E R\n");
    return;
}

void handEvaluationTest() {
    struct card deck[53];
    initializeDeck(deck);
    struct card *hand[5];
    char held[] = {' ', ' ', ' ', ' ', ' '};

    hand[0] = &deck[9 - 2 + Spades * 13];
    hand[1] = &deck[10 - 2 + Diamonds * 13];
    hand[2] = &deck[52];
    hand[3] = &deck[Jack - 2 + Hearts * 13];
    hand[4] = &deck[Queen - 2 + Clubs * 13];

    printHand(hand, held);

    printf("%d", evaluateHand(hand));
}