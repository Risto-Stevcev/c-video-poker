#include <stdlib.h>
#include "hand.h"
#include "card.h"

void
del_hand (Hand *self)
{
    int i;
    for (i = 0; i < MAX_HAND; i++)
        free(self->cards[i]);
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

void
get_ranks(int (*ranks)[], Card *(*cards)[]) 
{
    int i;
    for (i = 0; i < MAX_HAND; i++)
        (*ranks)[i] = (*cards)[i]->rank;

    qsort((*ranks), MAX_HAND, sizeof(int), intcmp);
}   

bool
is_straight (Hand *self)
{
    int ranks[MAX_HAND];
    get_ranks(&ranks, &self->cards);

    int i;
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
    get_ranks(&ranks, &self->cards);

    return self->is_straight(self) && self->is_flush(self)
        && ranks[0] == 10 && ranks[MAX_HAND-1] == 14;
}

num_pairs
find_pairs (Hand *self)
{
    int pairs[MAX_PAIR] = { 0, 0 };
    int ranks[MAX_HAND];
    get_ranks(&ranks, &self->cards);

    int i;
    int j = 0;
    for (i = 1; i < MAX_HAND; i++) {   
        if (ranks[i-1] == ranks[i])
            pairs[j]++;
        else if (j == 0 && pairs[j] != 0)
            j++;
    }

    if (pairs[0] == 1 && pairs[1] == 0)
        return one_pair;
    else if (pairs[0] == 1 && pairs[1] == 1)
        return two_pair;
    else if ((pairs[0] == 2 && pairs[1] == 1) || 
             (pairs[0] == 1 && pairs[1] == 2))
        return full_house;
    else if (pairs[0] == 2 && pairs[1] == 0)
        return three_kind;
    else if (pairs[0] == 3 && pairs[1] == 0)
        return four_kind;
    else
        return no_pair;
}

bool
is_one_pair (Hand *self)
{
    return find_pairs(self) == one_pair;
}

bool
is_no_pair (Hand *self)
{
    return find_pairs(self) == no_pair;
}

bool
is_two_pair (Hand *self)
{
    return find_pairs(self) == two_pair;
}

bool
is_full_house (Hand *self)
{
    return find_pairs(self) == full_house;
}

bool
is_three_kind (Hand *self)
{
    return find_pairs(self) == three_kind;
}

bool
is_four_kind (Hand *self)
{
    return find_pairs(self) == four_kind;
}

int
high_card (Hand *self)
{
    int ranks[MAX_HAND];
    get_ranks(&ranks, &self->cards);

    return ranks[MAX_HAND - 1];   
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
    hand->is_no_pair = is_no_pair;
    hand->is_one_pair = is_one_pair;
    hand->is_two_pair = is_two_pair;
    hand->is_full_house = is_full_house;
    hand->is_three_kind = is_three_kind;
    hand->is_four_kind = is_four_kind;
    hand->high_card = high_card;
    hand->del = del_hand;

    hand->cards[0] = NULL;
    hand->cards[1] = NULL;
    hand->cards[2] = NULL;
    hand->cards[3] = NULL;
    hand->cards[4] = NULL;
    return hand;
}
