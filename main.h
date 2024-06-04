#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <map>
#include <vector>

#include "User_Interface.h"
#include "check_index.h"
#include "In_game_user_interface.h"
#include "index_calculator.h"
#include "opportunity_card.h"
#include "file_io.h"

using namespace std;

struct Node
{
    int card;
    Node * next;
};

struct monster
{
    int health;
    int damage_per_round;
    int defense_power;

    bool defeated;

    // less than 20% --> current_anger_index = NO
    // [20-40] --> current_anger_level = LOW
    // (40-60] --> current_anger_level = MID
    // (>60) --> current_anger_level = HIGH
    string current_anger_level;
};

struct town
{
    monster duke;
    monster small_mon_1;
    monster small_mon_2;
};

struct player
{
    string name;
    int health;
    int strength;
    int defense_power;
    int intelligence;
    int money;

    // magic[0] : magic no.1
    // magic[1] : magic no.2
    map<int, int> magic;
    int magic_size;

    int opportunity_card;
    Node * trash_opportunity_card_deck;
    int trash_deck_size;

    //int health_potion;
    //int strength_potion;
    //int defense_potion;
    //int intelligence_potion;

    // potions["health"]
    // potions["strength"]
    // potions["defense"]
    // potions["intelligence"]
    map<string, int> potions;

    // First character : A / B / C / D / S
    // A / B / C / D : town a / b / c / d 
    // S : final boss
    // Second character : 0 / 1 / 2
    // For town :
    // 0 : small mon 1
    // 1 : small moon 2
    // 2 : duke
    // For final boss :
    // 0 : final boss
    // 1 : defeated final boss
    string current_progress;
    
    bool defeat_a;
    bool defeat_b;
    bool defeat_c;
    bool defeat_d;
    bool defeat_boss;
    
    town town_a;
    town town_b;
    town town_c;
    town town_d;
    
    monster boss;
};


int main();

#endif
