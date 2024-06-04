#ifndef OPPORTUNITY_CARD_H
#define OPPORTUNITY_CARD_H

#include "main.h"

void add_trash_card_deck (struct Node * & deck, int & size, int card);

void opportunity_card_graphics(struct player & Player);

void opportunity_card_logic(struct player & Player);
void use_opportunity_card(struct player & Player, struct monster & Monster);

#endif
