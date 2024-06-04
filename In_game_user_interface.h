#ifndef IN_GAME_USER_INTERFACE_H
#define IN_GAME_USER_INTERFACE_H

#include <string>

#include "User_Interface.h"
#include "check_index.h"
#include "index_calculator.h"
#include "main.h"

using namespace std;

void caculate_monster_anger_level(struct monster & current_mon, int & old_health, int & new_health);
int calculate_monster_strength(struct monster & current_mon);
void calculate_health(int & health, int & defense, int & damage);

void display_graphics( struct player Player);
void map_graphics( struct player Player , int display_index);

void fight_graphics( struct player Player);
void after_fighting_graphics(struct player & Player);

void store_main_menu_graphics (struct player Player);

void buy_potion_graphics(int money);
void buy_magic_graphics ( struct player Player);

void display_logic(struct player Player); // load from the grand menu
void map_logic(struct player Player); // load from the grand menu

void fight_logic(struct player & Player);

void store_logic(struct player & Player);
void store_amount_logic(struct player & Player, int & amount, int price);

void fight_magic_gra();
void fight_potion_gra(struct player Player);
void fight_potion_log(struct player & Player);

void store_amount_logic(struct player & Player, int & amount, int price);
void after_fighting_logic(struct player & Player);


#endif
