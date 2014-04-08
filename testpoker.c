#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "card.h"
#include "hand.h"


/* * * * * * * * * * * *
 * Suite 1 - Test Card *
 * * * * * * * * * * * */
Card *temp_card = NULL;

int 
setup_suite1(void)
{
    temp_card = initCard(SPADES, 7);
    if (temp_card != NULL) {
        return 0;
    }
    else {
        return -1;
    }
}

int
teardown_suite1(void)
{
    temp_card->del(temp_card);
    temp_card = NULL;
    return 0;
}

void
test_init_values_suite1(void)
{
    CU_ASSERT(temp_card->suit == SPADES);
    CU_ASSERT(temp_card->rank == 7);
}


/* * * * * * * * * * * *
 * Suite 2 - Test Hand *
 * * * * * * * * * * * */
Hand *temp_hand = NULL;

int 
setup_suite2(void)
{
    temp_hand = initHand();
    if (temp_hand != NULL) {
        return 0;
    }
    else {
        return -1;
    }
}

int
teardown_suite2(void)
{
    temp_hand->del(temp_hand);
    temp_hand = NULL;
    return 0;
}

void
test_init_values_suite2(void)
{
    CU_ASSERT(temp_hand->cards[0] == NULL);
    CU_ASSERT(temp_hand->cards[1] == NULL);
    CU_ASSERT(temp_hand->cards[2] == NULL);
    CU_ASSERT(temp_hand->cards[3] == NULL);
    CU_ASSERT(temp_hand->cards[4] == NULL);
}

void
test_add_card_suite2(void)
{
    CU_ASSERT(temp_hand->cards[0] == NULL);

    Card *added_card = initCard(HEARTS, 2);
    temp_hand->add_card(temp_hand, added_card);

    CU_ASSERT(temp_hand->cards[0] != NULL);
    CU_ASSERT(temp_hand->cards[0]->suit == HEARTS);
    CU_ASSERT(temp_hand->cards[0]->rank == 2);
}

void
test_remove_card_suite2(void)
{
    CU_ASSERT(temp_hand->cards[0] != NULL);
    CU_ASSERT(temp_hand->cards[0]->suit == HEARTS);
    CU_ASSERT(temp_hand->cards[0]->rank == 2);

    temp_hand->remove_card(temp_hand, temp_hand->cards[0]);

    CU_ASSERT(temp_hand->cards[0] == NULL);
}


/* * * * * * * * * * * * * * * *
 * Suite 3 - Test Hand (Flush) *
 * * * * * * * * * * * * * * * */
Hand *temp_hand2 = NULL;

int 
setup_suite3(void)
{
    temp_hand2 = initHand();
    if (temp_hand2 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 4);
    Card *card2 = initCard(DIAMONDS, 5);
    Card *card3 = initCard(DIAMONDS, 7);
    Card *card4 = initCard(DIAMONDS, 12);
    Card *card5 = initCard(DIAMONDS, 10);

    temp_hand2->add_card(temp_hand2, card1);
    temp_hand2->add_card(temp_hand2, card2);
    temp_hand2->add_card(temp_hand2, card3);
    temp_hand2->add_card(temp_hand2, card4);
    temp_hand2->add_card(temp_hand2, card5);

    return 0;
}

int
teardown_suite3(void)
{
    temp_hand2->del(temp_hand2);
    temp_hand2 = NULL;
    return 0;
}

void
test_init_values_suite3(void)
{
    CU_ASSERT(temp_hand2->cards[0] != NULL && temp_hand2->cards[0]->suit == DIAMONDS
                                           && temp_hand2->cards[0]->rank == 4);
    CU_ASSERT(temp_hand2->cards[1] != NULL && temp_hand2->cards[1]->suit == DIAMONDS
                                           && temp_hand2->cards[1]->rank == 5);
    CU_ASSERT(temp_hand2->cards[2] != NULL && temp_hand2->cards[2]->suit == DIAMONDS
                                           && temp_hand2->cards[2]->rank == 7);
    CU_ASSERT(temp_hand2->cards[3] != NULL && temp_hand2->cards[3]->suit == DIAMONDS
                                           && temp_hand2->cards[3]->rank == 12);
    CU_ASSERT(temp_hand2->cards[4] != NULL && temp_hand2->cards[4]->suit == DIAMONDS
                                           && temp_hand2->cards[4]->rank == 10);
}

void
test_is_flush_suite3(void)
{
    CU_ASSERT(temp_hand2->is_flush(temp_hand2));
}

void
test_is_not_flush_suite3(void)
{
    Card *not_in_suit = initCard(CLUBS, 4);
    CU_ASSERT(not_in_suit != NULL && not_in_suit->suit == CLUBS
                                  && not_in_suit->rank == 4);

    temp_hand2->remove_card(temp_hand2, temp_hand2->cards[0]);
    temp_hand2->add_card(temp_hand2, not_in_suit);
    CU_ASSERT(temp_hand2->cards[0] != NULL && temp_hand2->cards[0]->suit == CLUBS
                                           && temp_hand2->cards[0]->rank == 4);

    CU_ASSERT(temp_hand2->is_flush(temp_hand2) == false); 
}


/* * * * * * * * * * * * * * * * * *
 * Suite 4 - Test Hand (Straight)  *
 * * * * * * * * * * * * * * * * * */
Hand *temp_hand3 = NULL;

int 
setup_suite4(void)
{
    temp_hand3 = initHand();
    if (temp_hand3 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 4);
    Card *card2 = initCard(HEARTS, 5);
    Card *card3 = initCard(SPADES, 3);
    Card *card4 = initCard(CLUBS, 2);
    Card *card5 = initCard(CLUBS, 6);

    temp_hand3->add_card(temp_hand3, card1);
    temp_hand3->add_card(temp_hand3, card2);
    temp_hand3->add_card(temp_hand3, card3);
    temp_hand3->add_card(temp_hand3, card4);
    temp_hand3->add_card(temp_hand3, card5);

    return 0;
}

int
teardown_suite4(void)
{
    temp_hand3->del(temp_hand3);
    temp_hand3 = NULL;
    return 0;
}

void
test_init_values_suite4(void)
{
    CU_ASSERT(temp_hand3->cards[0] != NULL && temp_hand3->cards[0]->suit == DIAMONDS
                                           && temp_hand3->cards[0]->rank == 4);
    CU_ASSERT(temp_hand3->cards[1] != NULL && temp_hand3->cards[1]->suit == HEARTS
                                           && temp_hand3->cards[1]->rank == 5);
    CU_ASSERT(temp_hand3->cards[2] != NULL && temp_hand3->cards[2]->suit == SPADES
                                           && temp_hand3->cards[2]->rank == 3);
    CU_ASSERT(temp_hand3->cards[3] != NULL && temp_hand3->cards[3]->suit == CLUBS
                                           && temp_hand3->cards[3]->rank == 2);
    CU_ASSERT(temp_hand3->cards[4] != NULL && temp_hand3->cards[4]->suit == CLUBS
                                           && temp_hand3->cards[4]->rank == 6);
}

void
test_is_straight_suite4(void)
{
    CU_ASSERT(temp_hand3->is_straight(temp_hand3));
}

void
test_is_not_straight_suite4(void)
{
    Card *not_in_sequential_rank = initCard(SPADES, 12);
    CU_ASSERT(not_in_sequential_rank != NULL && not_in_sequential_rank->suit == SPADES
                                             && not_in_sequential_rank->rank == 12);

    temp_hand3->remove_card(temp_hand3, temp_hand3->cards[0]);
    temp_hand3->add_card(temp_hand3, not_in_sequential_rank);
    CU_ASSERT(temp_hand3->cards[0] != NULL && temp_hand3->cards[0]->suit == SPADES
                                           && temp_hand3->cards[0]->rank == 12);

    CU_ASSERT(temp_hand3->is_straight(temp_hand3) == false); 
}


/* * * * * * * * * * * * * * * * * * * * *
 * Suite 5 - Test Hand (Straight-Flush)  *
 * * * * * * * * * * * * * * * * * * * * */
Hand *temp_hand4 = NULL;

int 
setup_suite5(void)
{
    temp_hand4 = initHand();
    if (temp_hand4 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 12);
    Card *card2 = initCard(DIAMONDS, 10);
    Card *card3 = initCard(DIAMONDS, 11);
    Card *card4 = initCard(DIAMONDS, 9);
    Card *card5 = initCard(DIAMONDS, 8);

    temp_hand4->add_card(temp_hand4, card1);
    temp_hand4->add_card(temp_hand4, card2);
    temp_hand4->add_card(temp_hand4, card3);
    temp_hand4->add_card(temp_hand4, card4);
    temp_hand4->add_card(temp_hand4, card5);

    return 0;
}

int
teardown_suite5(void)
{
    temp_hand4->del(temp_hand4);
    temp_hand4 = NULL;
    return 0;
}

void
test_init_values_suite5(void)
{
    CU_ASSERT(temp_hand4->cards[0] != NULL && temp_hand4->cards[0]->suit == DIAMONDS 
                                           && temp_hand4->cards[0]->rank == 12);
    CU_ASSERT(temp_hand4->cards[1] != NULL && temp_hand4->cards[1]->suit == DIAMONDS
                                           && temp_hand4->cards[1]->rank == 10);
    CU_ASSERT(temp_hand4->cards[2] != NULL && temp_hand4->cards[2]->suit == DIAMONDS
                                           && temp_hand4->cards[2]->rank == 11);
    CU_ASSERT(temp_hand4->cards[3] != NULL && temp_hand4->cards[3]->suit == DIAMONDS
                                           && temp_hand4->cards[3]->rank == 9);
    CU_ASSERT(temp_hand4->cards[4] != NULL && temp_hand4->cards[4]->suit == DIAMONDS
                                           && temp_hand4->cards[4]->rank == 8);
}

void
test_is_straight_flush_suite5(void)
{
    CU_ASSERT(temp_hand4->is_straight_flush(temp_hand4));
}

void
test_is_not_straight_flush_suite5(void)
{
    Card *not_in_sequential_rank = initCard(DIAMONDS, 3);
    CU_ASSERT(not_in_sequential_rank != NULL && not_in_sequential_rank->suit == DIAMONDS
                                             && not_in_sequential_rank->rank == 3);

    temp_hand4->remove_card(temp_hand4, temp_hand4->cards[0]);
    temp_hand4->add_card(temp_hand4, not_in_sequential_rank);
    CU_ASSERT(temp_hand4->cards[0] != NULL && temp_hand4->cards[0]->suit == DIAMONDS
                                           && temp_hand4->cards[0]->rank == 3);

    CU_ASSERT(temp_hand4->is_straight_flush(temp_hand4) == false); 

    Card *not_in_suit = initCard(SPADES, 12);
    CU_ASSERT(not_in_suit != NULL && not_in_suit->suit == SPADES
                                  && not_in_suit->rank == 12);

    temp_hand4->remove_card(temp_hand4, temp_hand4->cards[0]);
    temp_hand4->add_card(temp_hand4, not_in_suit);
    CU_ASSERT(temp_hand4->cards[0] != NULL && temp_hand4->cards[0]->suit == SPADES
                                           && temp_hand4->cards[0]->rank == 12);

    CU_ASSERT(temp_hand4->is_straight_flush(temp_hand4) == false); 
}


/* * * * * * * * * * * * * * * * * * *
 * Suite 6 - Test Hand (Royal-Flush) *
 * * * * * * * * * * * * * * * * * * */
Hand *temp_hand5 = NULL;

int 
setup_suite6(void)
{
    temp_hand5 = initHand();
    if (temp_hand5 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 12);
    Card *card2 = initCard(DIAMONDS, 10);
    Card *card3 = initCard(DIAMONDS, 11);
    Card *card4 = initCard(DIAMONDS, 13);
    Card *card5 = initCard(DIAMONDS, 14);

    temp_hand5->add_card(temp_hand5, card1);
    temp_hand5->add_card(temp_hand5, card2);
    temp_hand5->add_card(temp_hand5, card3);
    temp_hand5->add_card(temp_hand5, card4);
    temp_hand5->add_card(temp_hand5, card5);

    return 0;
}

int
teardown_suite6(void)
{
    temp_hand5->del(temp_hand5);
    temp_hand5 = NULL;
    return 0;
}

void
test_init_values_suite6(void)
{
    CU_ASSERT(temp_hand5->cards[0] != NULL && temp_hand5->cards[0]->suit == DIAMONDS 
                                           && temp_hand5->cards[0]->rank == 12);
    CU_ASSERT(temp_hand5->cards[1] != NULL && temp_hand5->cards[1]->suit == DIAMONDS
                                           && temp_hand5->cards[1]->rank == 10);
    CU_ASSERT(temp_hand5->cards[2] != NULL && temp_hand5->cards[2]->suit == DIAMONDS
                                           && temp_hand5->cards[2]->rank == 11);
    CU_ASSERT(temp_hand5->cards[3] != NULL && temp_hand5->cards[3]->suit == DIAMONDS
                                           && temp_hand5->cards[3]->rank == 13);
    CU_ASSERT(temp_hand5->cards[4] != NULL && temp_hand5->cards[4]->suit == DIAMONDS
                                           && temp_hand5->cards[4]->rank == 14);
}

void
test_is_royal_flush_suite6(void)
{
    CU_ASSERT(temp_hand5->is_royal_flush(temp_hand5));
}

void
test_is_not_royal_flush_suite6(void)
{
    Card *not_in_royal_rank = initCard(DIAMONDS, 9);
    CU_ASSERT(not_in_royal_rank != NULL && not_in_royal_rank->suit == DIAMONDS
                                        && not_in_royal_rank->rank == 9);

    temp_hand5->remove_card(temp_hand5, temp_hand5->cards[4]);
    temp_hand5->add_card(temp_hand5, not_in_royal_rank);
    CU_ASSERT(temp_hand5->cards[4] != NULL && temp_hand5->cards[4]->suit == DIAMONDS
                                           && temp_hand5->cards[4]->rank == 9);

    CU_ASSERT(temp_hand5->is_straight_flush(temp_hand5) == true); 
    CU_ASSERT(temp_hand5->is_royal_flush(temp_hand5) == false); 

    Card *not_in_suit = initCard(SPADES, 14);
    CU_ASSERT(not_in_suit != NULL && not_in_suit->suit == SPADES
                                  && not_in_suit->rank == 14);

    temp_hand5->remove_card(temp_hand5, temp_hand5->cards[4]);
    temp_hand5->add_card(temp_hand5, not_in_suit);
    CU_ASSERT(temp_hand5->cards[4] != NULL && temp_hand5->cards[4]->suit == SPADES
                                           && temp_hand5->cards[4]->rank == 14);

    CU_ASSERT(temp_hand5->is_royal_flush(temp_hand5) == false); 
}


/* * * * * * * * * * * * * * * * * *
 * Suite 7 - Test Hand (One Pair)  *
 * * * * * * * * * * * * * * * * * */
Hand *temp_hand6 = NULL;

int 
setup_suite7(void)
{
    temp_hand6 = initHand();
    if (temp_hand6 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 4);
    Card *card2 = initCard(HEARTS, 5);
    Card *card3 = initCard(SPADES, 3);
    Card *card4 = initCard(CLUBS, 7);
    Card *card5 = initCard(CLUBS, 3);

    temp_hand6->add_card(temp_hand6, card1);
    temp_hand6->add_card(temp_hand6, card2);
    temp_hand6->add_card(temp_hand6, card3);
    temp_hand6->add_card(temp_hand6, card4);
    temp_hand6->add_card(temp_hand6, card5);

    return 0;
}

int
teardown_suite7(void)
{
    temp_hand6->del(temp_hand6);
    temp_hand6 = NULL;
    return 0;
}

void
test_init_values_suite7(void)
{
    CU_ASSERT(temp_hand6->cards[0] != NULL && temp_hand6->cards[0]->suit == DIAMONDS
                                           && temp_hand6->cards[0]->rank == 4);
    CU_ASSERT(temp_hand6->cards[1] != NULL && temp_hand6->cards[1]->suit == HEARTS
                                           && temp_hand6->cards[1]->rank == 5);
    CU_ASSERT(temp_hand6->cards[2] != NULL && temp_hand6->cards[2]->suit == SPADES
                                           && temp_hand6->cards[2]->rank == 3);
    CU_ASSERT(temp_hand6->cards[3] != NULL && temp_hand6->cards[3]->suit == CLUBS
                                           && temp_hand6->cards[3]->rank == 7);
    CU_ASSERT(temp_hand6->cards[4] != NULL && temp_hand6->cards[4]->suit == CLUBS
                                           && temp_hand6->cards[4]->rank == 3);
}

void
test_is_one_pair_suite7(void)
{
    CU_ASSERT(temp_hand6->is_one_pair(temp_hand6));
}

void
test_is_not_one_pair_suite7(void)
{
    Card *unique_rank = initCard(SPADES, 12);
    CU_ASSERT(unique_rank != NULL && unique_rank->suit == SPADES
                                  && unique_rank->rank == 12);

    temp_hand6->remove_card(temp_hand6, temp_hand6->cards[2]);
    temp_hand6->add_card(temp_hand6, unique_rank);
    CU_ASSERT(temp_hand6->cards[2] != NULL && temp_hand6->cards[2]->suit == SPADES
                                           && temp_hand6->cards[2]->rank == 12);

    CU_ASSERT(temp_hand6->is_one_pair(temp_hand6) == false); 
    CU_ASSERT(temp_hand6->is_no_pair(temp_hand6)); 
}


/* * * * * * * * * * * * * * * * * *
 * Suite 8 - Test Hand (Two Pair)  *
 * * * * * * * * * * * * * * * * * */
Hand *temp_hand7 = NULL;

int 
setup_suite8(void)
{
    temp_hand7 = initHand();
    if (temp_hand7 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 7);
    Card *card2 = initCard(HEARTS, 5);
    Card *card3 = initCard(SPADES, 3);
    Card *card4 = initCard(CLUBS, 7);
    Card *card5 = initCard(CLUBS, 3);

    temp_hand7->add_card(temp_hand7, card1);
    temp_hand7->add_card(temp_hand7, card2);
    temp_hand7->add_card(temp_hand7, card3);
    temp_hand7->add_card(temp_hand7, card4);
    temp_hand7->add_card(temp_hand7, card5);

    return 0;
}

int
teardown_suite8(void)
{
    temp_hand7->del(temp_hand7);
    temp_hand7 = NULL;
    return 0;
}

void
test_init_values_suite8(void)
{
    CU_ASSERT(temp_hand7->cards[0] != NULL && temp_hand7->cards[0]->suit == DIAMONDS
                                           && temp_hand7->cards[0]->rank == 7);
    CU_ASSERT(temp_hand7->cards[1] != NULL && temp_hand7->cards[1]->suit == HEARTS
                                           && temp_hand7->cards[1]->rank == 5);
    CU_ASSERT(temp_hand7->cards[2] != NULL && temp_hand7->cards[2]->suit == SPADES
                                           && temp_hand7->cards[2]->rank == 3);
    CU_ASSERT(temp_hand7->cards[3] != NULL && temp_hand7->cards[3]->suit == CLUBS
                                           && temp_hand7->cards[3]->rank == 7);
    CU_ASSERT(temp_hand7->cards[4] != NULL && temp_hand7->cards[4]->suit == CLUBS
                                           && temp_hand7->cards[4]->rank == 3);
}

void
test_is_two_pair_suite8(void)
{
    CU_ASSERT(temp_hand7->is_two_pair(temp_hand7));
}

void
test_is_not_two_pair_suite8(void)
{
    Card *unique_rank = initCard(SPADES, 12);
    CU_ASSERT(unique_rank != NULL && unique_rank->suit == SPADES
                                  && unique_rank->rank == 12);

    temp_hand7->remove_card(temp_hand7, temp_hand7->cards[2]);
    temp_hand7->add_card(temp_hand7, unique_rank);
    CU_ASSERT(temp_hand7->cards[2] != NULL && temp_hand7->cards[2]->suit == SPADES
                                           && temp_hand7->cards[2]->rank == 12);

    CU_ASSERT(temp_hand7->is_two_pair(temp_hand7) == false); 
    CU_ASSERT(temp_hand7->is_one_pair(temp_hand7)); 
}


/* * * * * * * * * * * * * * * * * * *
 * Suite 9 - Test Hand (Full House)  *
 * * * * * * * * * * * * * * * * * * */
Hand *temp_hand8 = NULL;

int 
setup_suite9(void)
{
    temp_hand8 = initHand();
    if (temp_hand8 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 7);
    Card *card2 = initCard(HEARTS, 7);
    Card *card3 = initCard(SPADES, 3);
    Card *card4 = initCard(CLUBS, 7);
    Card *card5 = initCard(CLUBS, 3);

    temp_hand8->add_card(temp_hand8, card1);
    temp_hand8->add_card(temp_hand8, card2);
    temp_hand8->add_card(temp_hand8, card3);
    temp_hand8->add_card(temp_hand8, card4);
    temp_hand8->add_card(temp_hand8, card5);

    return 0;
}

int
teardown_suite9(void)
{
    temp_hand8->del(temp_hand8);
    temp_hand8 = NULL;
    return 0;
}

void
test_init_values_suite9(void)
{
    CU_ASSERT(temp_hand8->cards[0] != NULL && temp_hand8->cards[0]->suit == DIAMONDS
                                           && temp_hand8->cards[0]->rank == 7);
    CU_ASSERT(temp_hand8->cards[1] != NULL && temp_hand8->cards[1]->suit == HEARTS
                                           && temp_hand8->cards[1]->rank == 7);
    CU_ASSERT(temp_hand8->cards[2] != NULL && temp_hand8->cards[2]->suit == SPADES
                                           && temp_hand8->cards[2]->rank == 3);
    CU_ASSERT(temp_hand8->cards[3] != NULL && temp_hand8->cards[3]->suit == CLUBS
                                           && temp_hand8->cards[3]->rank == 7);
    CU_ASSERT(temp_hand8->cards[4] != NULL && temp_hand8->cards[4]->suit == CLUBS
                                           && temp_hand8->cards[4]->rank == 3);
}

void
test_is_full_house_suite9(void)
{
    CU_ASSERT(temp_hand8->is_full_house(temp_hand8));
}

void
test_is_not_full_house_suite9(void)
{
    Card *unique_rank = initCard(SPADES, 12);
    CU_ASSERT(unique_rank != NULL && unique_rank->suit == SPADES
                                  && unique_rank->rank == 12);

    temp_hand8->remove_card(temp_hand8, temp_hand8->cards[1]);
    temp_hand8->add_card(temp_hand8, unique_rank);
    CU_ASSERT(temp_hand8->cards[1] != NULL && temp_hand8->cards[1]->suit == SPADES
                                           && temp_hand8->cards[1]->rank == 12);

    CU_ASSERT(temp_hand8->is_full_house(temp_hand8) == false); 
    CU_ASSERT(temp_hand8->is_two_pair(temp_hand8)); 
}


/* * * * * * * * * * * * * * * * * * * * * *
 * Suite 10 - Test Hand (Three-of-a-Kind)  *
 * * * * * * * * * * * * * * * * * * * * * */
Hand *temp_hand9 = NULL;

int 
setup_suite10(void)
{
    temp_hand9 = initHand();
    if (temp_hand9 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 4);
    Card *card2 = initCard(HEARTS, 3);
    Card *card3 = initCard(SPADES, 3);
    Card *card4 = initCard(CLUBS, 7);
    Card *card5 = initCard(CLUBS, 3);

    temp_hand9->add_card(temp_hand9, card1);
    temp_hand9->add_card(temp_hand9, card2);
    temp_hand9->add_card(temp_hand9, card3);
    temp_hand9->add_card(temp_hand9, card4);
    temp_hand9->add_card(temp_hand9, card5);

    return 0;
}

int
teardown_suite10(void)
{
    temp_hand9->del(temp_hand9);
    temp_hand9 = NULL;
    return 0;
}

void
test_init_values_suite10(void)
{
    CU_ASSERT(temp_hand9->cards[0] != NULL && temp_hand9->cards[0]->suit == DIAMONDS
                                           && temp_hand9->cards[0]->rank == 4);
    CU_ASSERT(temp_hand9->cards[1] != NULL && temp_hand9->cards[1]->suit == HEARTS
                                           && temp_hand9->cards[1]->rank == 3);
    CU_ASSERT(temp_hand9->cards[2] != NULL && temp_hand9->cards[2]->suit == SPADES
                                           && temp_hand9->cards[2]->rank == 3);
    CU_ASSERT(temp_hand9->cards[3] != NULL && temp_hand9->cards[3]->suit == CLUBS
                                           && temp_hand9->cards[3]->rank == 7);
    CU_ASSERT(temp_hand9->cards[4] != NULL && temp_hand9->cards[4]->suit == CLUBS
                                           && temp_hand9->cards[4]->rank == 3);
}

void
test_is_three_kind_suite10(void)
{
    CU_ASSERT(temp_hand9->is_three_kind(temp_hand9));
}

void
test_is_not_three_kind_suite10(void)
{
    Card *unique_rank = initCard(SPADES, 12);
    CU_ASSERT(unique_rank != NULL && unique_rank->suit == SPADES
                                  && unique_rank->rank == 12);

    temp_hand9->remove_card(temp_hand9, temp_hand9->cards[2]);
    temp_hand9->add_card(temp_hand9, unique_rank);
    CU_ASSERT(temp_hand9->cards[2] != NULL && temp_hand9->cards[2]->suit == SPADES
                                           && temp_hand9->cards[2]->rank == 12);

    CU_ASSERT(temp_hand9->is_three_kind(temp_hand9) == false); 
    CU_ASSERT(temp_hand9->is_one_pair(temp_hand9)); 
}


/* * * * * * * * * * * * * * * * * * * * *
 * Suite 11 - Test Hand (Four-of-a-Kind) *
 * * * * * * * * * * * * * * * * * * * * */
Hand *temp_hand10 = NULL;

int 
setup_suite11(void)
{
    temp_hand10 = initHand();
    if (temp_hand10 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 3);
    Card *card2 = initCard(HEARTS, 3);
    Card *card3 = initCard(SPADES, 3);
    Card *card4 = initCard(CLUBS, 7);
    Card *card5 = initCard(CLUBS, 3);

    temp_hand10->add_card(temp_hand10, card1);
    temp_hand10->add_card(temp_hand10, card2);
    temp_hand10->add_card(temp_hand10, card3);
    temp_hand10->add_card(temp_hand10, card4);
    temp_hand10->add_card(temp_hand10, card5);

    return 0;
}

int
teardown_suite11(void)
{
    temp_hand10->del(temp_hand10);
    temp_hand10 = NULL;
    return 0;
}

void
test_init_values_suite11(void)
{
    CU_ASSERT(temp_hand10->cards[0] != NULL && temp_hand10->cards[0]->suit == DIAMONDS
                                           && temp_hand10->cards[0]->rank == 3);
    CU_ASSERT(temp_hand10->cards[1] != NULL && temp_hand10->cards[1]->suit == HEARTS
                                           && temp_hand10->cards[1]->rank == 3);
    CU_ASSERT(temp_hand10->cards[2] != NULL && temp_hand10->cards[2]->suit == SPADES
                                           && temp_hand10->cards[2]->rank == 3);
    CU_ASSERT(temp_hand10->cards[3] != NULL && temp_hand10->cards[3]->suit == CLUBS
                                           && temp_hand10->cards[3]->rank == 7);
    CU_ASSERT(temp_hand10->cards[4] != NULL && temp_hand10->cards[4]->suit == CLUBS
                                           && temp_hand10->cards[4]->rank == 3);
}

void
test_is_four_kind_suite11(void)
{
    CU_ASSERT(temp_hand10->is_four_kind(temp_hand10));
}

void
test_is_not_four_kind_suite11(void)
{
    Card *unique_rank = initCard(SPADES, 12);
    CU_ASSERT(unique_rank != NULL && unique_rank->suit == SPADES
                                  && unique_rank->rank == 12);

    temp_hand10->remove_card(temp_hand10, temp_hand10->cards[2]);
    temp_hand10->add_card(temp_hand10, unique_rank);
    CU_ASSERT(temp_hand10->cards[2] != NULL && temp_hand10->cards[2]->suit == SPADES
                                           && temp_hand10->cards[2]->rank == 12);

    CU_ASSERT(temp_hand10->is_four_kind(temp_hand10) == false); 
    CU_ASSERT(temp_hand10->is_three_kind(temp_hand10)); 
}


/* * * * * * * * * * * * * * * * * * * * *
 * Suite 12 - Test Hand (High card) *
 * * * * * * * * * * * * * * * * * * * * */
Hand *temp_hand11 = NULL;

int 
setup_suite12(void)
{
    temp_hand11 = initHand();
    if (temp_hand11 == NULL)
        return -1;

    Card *card1 = initCard(DIAMONDS, 11);
    Card *card2 = initCard(HEARTS, 4);
    Card *card3 = initCard(SPADES, 13);
    Card *card4 = initCard(CLUBS, 7);
    Card *card5 = initCard(CLUBS, 3);

    temp_hand11->add_card(temp_hand11, card1);
    temp_hand11->add_card(temp_hand11, card2);
    temp_hand11->add_card(temp_hand11, card3);
    temp_hand11->add_card(temp_hand11, card4);
    temp_hand11->add_card(temp_hand11, card5);

    return 0;
}

int
teardown_suite12(void)
{
    temp_hand11->del(temp_hand11);
    temp_hand11 = NULL;
    return 0;
}

void
test_init_values_suite12(void)
{
    CU_ASSERT(temp_hand11->cards[0] != NULL && temp_hand11->cards[0]->suit == DIAMONDS
                                           && temp_hand11->cards[0]->rank == 11);
    CU_ASSERT(temp_hand11->cards[1] != NULL && temp_hand11->cards[1]->suit == HEARTS
                                           && temp_hand11->cards[1]->rank == 4);
    CU_ASSERT(temp_hand11->cards[2] != NULL && temp_hand11->cards[2]->suit == SPADES
                                           && temp_hand11->cards[2]->rank == 13);
    CU_ASSERT(temp_hand11->cards[3] != NULL && temp_hand11->cards[3]->suit == CLUBS
                                           && temp_hand11->cards[3]->rank == 7);
    CU_ASSERT(temp_hand11->cards[4] != NULL && temp_hand11->cards[4]->suit == CLUBS
                                           && temp_hand11->cards[4]->rank == 3);
}

void
test_high_card_suite12(void)
{
    CU_ASSERT(temp_hand11->high_card(temp_hand11) == 13);
}


/* * * * * * * *
 * Run C-unit  *
 * * * * * * * */
int main()
{
   CU_pSuite pSuite1 = NULL;
   CU_pSuite pSuite2 = NULL;
   CU_pSuite pSuite3 = NULL;
   CU_pSuite pSuite4 = NULL;
   CU_pSuite pSuite5 = NULL;
   CU_pSuite pSuite6 = NULL;
   CU_pSuite pSuite7 = NULL;
   CU_pSuite pSuite8 = NULL;
   CU_pSuite pSuite9 = NULL;
   CU_pSuite pSuite10 = NULL;
   CU_pSuite pSuite11 = NULL;
   CU_pSuite pSuite12 = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add suites to the registry */
   pSuite1 = CU_add_suite("Test Card", setup_suite1, teardown_suite1);
   pSuite2 = CU_add_suite("Test Hand", setup_suite2, teardown_suite2);
   pSuite3 = CU_add_suite("Test Hand (Flush)", setup_suite3, teardown_suite3);
   pSuite4 = CU_add_suite("Test Hand (Straight)", setup_suite4, teardown_suite4);
   pSuite5 = CU_add_suite("Test Hand (Straight-Flush)", setup_suite5, teardown_suite5);
   pSuite6 = CU_add_suite("Test Hand (Royal-Flush)", setup_suite6, teardown_suite6);
   pSuite7 = CU_add_suite("Test Hand (One-Pair)", setup_suite7, teardown_suite7);
   pSuite8 = CU_add_suite("Test Hand (Two-Pair)", setup_suite8, teardown_suite8);
   pSuite9 = CU_add_suite("Test Hand (Full-House)", setup_suite9, teardown_suite9);
   pSuite10 = CU_add_suite("Test Hand (Three-of-a-Kind)", setup_suite10, teardown_suite10);
   pSuite11 = CU_add_suite("Test Hand (Four-of-a-Kind)", setup_suite11, teardown_suite11);
   pSuite12 = CU_add_suite("Test Hand (High card)", setup_suite12, teardown_suite12);

   if (  pSuite1  == NULL || pSuite2  == NULL || pSuite3  == NULL 
      || pSuite4  == NULL || pSuite5  == NULL || pSuite6  == NULL  
      || pSuite7  == NULL || pSuite8  == NULL || pSuite9  == NULL 
      || pSuite10 == NULL || pSuite11 == NULL || pSuite12 == NULL  ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if (  (NULL == CU_add_test(pSuite1, "test card initialization", test_init_values_suite1))

      || (NULL == CU_add_test(pSuite2, "test hand initialization", test_init_values_suite2))
      || (NULL == CU_add_test(pSuite2, "test adding a card to the hand", test_add_card_suite2))
      || (NULL == CU_add_test(pSuite2, "test removing a card from the hand", test_remove_card_suite2))
      
      || (NULL == CU_add_test(pSuite3, "test hand (flush) initialization", test_init_values_suite3))
      || (NULL == CU_add_test(pSuite3, "test hand is a flush", test_is_flush_suite3))
      || (NULL == CU_add_test(pSuite3, "test hand is not a flush", test_is_not_flush_suite3))
      
      || (NULL == CU_add_test(pSuite4, "test hand (straight) initialization", test_init_values_suite4))
      || (NULL == CU_add_test(pSuite4, "test hand is a straight", test_is_straight_suite4))
      || (NULL == CU_add_test(pSuite4, "test hand is not a straight", test_is_not_straight_suite4))

      || (NULL == CU_add_test(pSuite5, "test hand (straight-flush) initialization", test_init_values_suite5))
      || (NULL == CU_add_test(pSuite5, "test hand is a straight-flush", test_is_straight_flush_suite5))
      || (NULL == CU_add_test(pSuite5, "test hand is not a straight-flush", test_is_not_straight_flush_suite5))

      || (NULL == CU_add_test(pSuite6, "test hand (royal-flush) initialization", test_init_values_suite6))
      || (NULL == CU_add_test(pSuite6, "test hand is a royal-flush", test_is_royal_flush_suite6))
      || (NULL == CU_add_test(pSuite6, "test hand is not a royal-flush", test_is_not_royal_flush_suite6))

      || (NULL == CU_add_test(pSuite7, "test hand (one-pair) initialization", test_init_values_suite7))
      || (NULL == CU_add_test(pSuite7, "test hand is a one-pair", test_is_one_pair_suite7))
      || (NULL == CU_add_test(pSuite7, "test hand is not a one-pair", test_is_not_one_pair_suite7))

      || (NULL == CU_add_test(pSuite8, "test hand (two-pair) initialization", test_init_values_suite8))
      || (NULL == CU_add_test(pSuite8, "test hand is a two-pair", test_is_two_pair_suite8))
      || (NULL == CU_add_test(pSuite8, "test hand is not a two-pair", test_is_not_two_pair_suite8))

      || (NULL == CU_add_test(pSuite9, "test hand (full-house) initialization", test_init_values_suite9))
      || (NULL == CU_add_test(pSuite9, "test hand is a full-house", test_is_full_house_suite9))
      || (NULL == CU_add_test(pSuite9, "test hand is not a full-house", test_is_not_full_house_suite9))

      || (NULL == CU_add_test(pSuite10, "test hand (three-of-a-kind) initialization", test_init_values_suite10))
      || (NULL == CU_add_test(pSuite10, "test hand is a three-of-a-kind", test_is_three_kind_suite10))
      || (NULL == CU_add_test(pSuite10, "test hand is not a three-of-a-kind", test_is_not_three_kind_suite10))

      || (NULL == CU_add_test(pSuite11, "test hand (four-of-a-kind) initialization", test_init_values_suite11))
      || (NULL == CU_add_test(pSuite11, "test hand is a four-of-a-kind", test_is_four_kind_suite11))
      || (NULL == CU_add_test(pSuite11, "test hand is not a four-of-a-kind", test_is_not_four_kind_suite11))

      || (NULL == CU_add_test(pSuite12, "test hand (high card) initialization", test_init_values_suite12))
      || (NULL == CU_add_test(pSuite12, "test hand high card", test_high_card_suite12))  )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}
