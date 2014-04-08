#ifndef HAND_H
#define HAND_H
#define MAX_HAND 5
#define MAX_PAIR 2
typedef enum { false, true } bool;
typedef enum { no_pair, one_pair, two_pair, full_house, three_kind, four_kind } num_pairs;
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
    bool (*is_no_pair) ();
    bool (*is_one_pair) ();
    bool (*is_two_pair) ();
    bool (*is_full_house) ();
    bool (*is_three_kind) ();
    bool (*is_four_kind) ();
    int (*high_card) ();
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

num_pairs find_pairs (Hand *);
bool is_no_pair (Hand *);
bool is_one_pair (Hand *);
bool is_two_pair (Hand *);
bool is_full_house (Hand *);
bool is_three_kind (Hand *);
bool is_four_kind (Hand *);
int high_card (Hand *);
#endif
