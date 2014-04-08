#ifndef HAND_H
#define HAND_H
#define MAX_HAND 5
typedef enum { false, true } bool;
typedef struct card_t Card;

typedef struct
hand_t
{
    Card *cards[MAX_HAND];

    void (*add_card) ();
    void (*remove_card) ();
    bool (*is_flush) ();
    bool (*is_straight) ();
    bool (*is_straight_flush) ();
    bool (*is_royal_flush) ();
    void (*del) ();
} Hand;

Hand *initHand ();
void del_hand (Hand *);

void add_card (Hand *, Card *);
void remove_card (Hand *, Card *);
bool is_flush (Hand *);
bool is_straight (Hand *);
bool is_straight_flush (Hand *);
bool is_royal_flush (Hand *);
#endif
