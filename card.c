#include <stdlib.h>
#include "card.h"


void
del_card (Card *card)
{
    free(card);
}

Card *
initCard (card_suit suit, int rank)
{
    Card *card = (Card *) malloc(sizeof(Card));
    card->del = del_card;

    card->suit = suit;
    card->rank = rank;
    return card;
}
