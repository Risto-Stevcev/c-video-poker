#ifndef CARD_H
#define CARD_H
typedef enum { HEARTS, SPADES, DIAMONDS, CLUBS } card_suit;

typedef struct
card_t
{
    card_suit suit;
    int rank;

    void (*del) ();
} Card;

Card *initCard (card_suit, int);
void del_card (Card *);
#endif
