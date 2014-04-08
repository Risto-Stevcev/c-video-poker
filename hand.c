#include <stdlib.h>
#include "hand.h"
#include "card.h"

void
del_hand (Hand *self)
{
    int i;
    for (i = 0; i < MAX_HAND; i++)
    {
        free(self->cards[i]);
    }
    free(self);
}

void
add_card (Hand *self, Card *card)
{
    int i;
    for (i = 0; i < MAX_HAND; i++) { 
        if (self->cards[i] == NULL) {
            self->cards[i] = card;
            break;
        }
    }
}

void
remove_card (Hand *self, Card *card)
{
    int i;
    for (i = 0; i < MAX_HAND; i++) { 
        if (self->cards[i] == card) {
            free(self->cards[i]);
            self->cards[i] = NULL;
            break;
        }
    }
}

bool
is_flush (Hand *self)
{
    card_suit suit = self->cards[0]->suit;
    int i;
    for (i = 0; i < MAX_HAND; i++) { 
        if (self->cards[i]->suit != suit)
            return false;
    }
    return true;
}

int intcmp(const void *aa, const void *bb)
{
    const int *a = aa, *b = bb;
    return (*a < *b) ? -1 : (*a > *b);
}

bool
is_straight (Hand *self)
{
    int ranks[MAX_HAND];

    int i;
    for (i = 0; i < MAX_HAND; i++)
        ranks[i] = self->cards[i]->rank;

    qsort(ranks, MAX_HAND, sizeof(int), intcmp);

    for (i = 1; i < MAX_HAND; i++) { 
        if (ranks[i-1] + 1 != ranks[i])
            return false;
    }
    return true;
}

bool
is_straight_flush (Hand *self)
{
    return self->is_straight(self) && self->is_flush(self);
}

bool
is_royal_flush (Hand *self)
{
    int ranks[MAX_HAND];

    int i;
    for (i = 0; i < MAX_HAND; i++)
        ranks[i] = self->cards[i]->rank;

    qsort(ranks, MAX_HAND, sizeof(int), intcmp);

    return self->is_straight(self) && self->is_flush(self)
        && ranks[0] == 10 && ranks[MAX_HAND-1] == 14;
}

Hand *
initHand ()
{
    Hand *hand = (Hand *) malloc(sizeof(Hand));
    hand->add_card = add_card;
    hand->remove_card = remove_card;
    hand->is_flush = is_flush;
    hand->is_straight = is_straight;
    hand->is_straight_flush = is_straight_flush;
    hand->is_royal_flush = is_royal_flush;
    hand->del = del_hand;

    hand->cards[0] = NULL;
    hand->cards[1] = NULL;
    hand->cards[2] = NULL;
    hand->cards[3] = NULL;
    hand->cards[4] = NULL;
    return hand;
}
