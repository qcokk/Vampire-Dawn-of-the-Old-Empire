#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>

#include "main.h"
#include "index_calculator.h"
using namespace std;

// to create new player
player initial_player_creation(string namee)
{
    srand( time(NULL) );
    
    player new_Player;
    new_Player.name = namee;
    new_Player.health = 100;
    new_Player.strength = 100;
    new_Player.defense_power = 100;
    new_Player.intelligence = 100;
    new_Player.money = 100;
    new_Player.magic_size = 0;
    new_Player.magic[1] = 0;
    new_Player.magic[2] = 0;
    new_Player.opportunity_card = 0;
    new_Player.trash_opportunity_card_deck = nullptr;
    new_Player.trash_deck_size = 0;

    new_Player.potions["health"] = 0;
    new_Player.potions["strength"] = 0;
    new_Player.potions["defense"] = 0;
    new_Player.potions["intelligence"] = 0; 

    new_Player.current_progress = "A0";

    new_Player.defeat_a = false;
    new_Player.defeat_b = false;
    new_Player.defeat_c = false;
    new_Player.defeat_d = false;
    new_Player.defeat_boss = false;

    new_Player.town_a.small_mon_1.current_anger_level = "NO";
    new_Player.town_a.small_mon_2.current_anger_level = "NO";
    new_Player.town_b.small_mon_1.current_anger_level = "NO";
    new_Player.town_b.small_mon_2.current_anger_level = "NO";
    new_Player.town_c.small_mon_1.current_anger_level = "NO";
    new_Player.town_c.small_mon_2.current_anger_level = "NO";
    new_Player.town_d.small_mon_1.current_anger_level = "NO";
    new_Player.town_d.small_mon_2.current_anger_level = "NO";
    new_Player.town_a.duke.current_anger_level = "NO";
    new_Player.town_b.duke.current_anger_level = "NO";
    new_Player.town_c.duke.current_anger_level = "NO";
    new_Player.town_d.duke.current_anger_level = "NO";
    new_Player.boss.current_anger_level = "NO";
    
    new_Player.town_a.small_mon_1.health = rand() % 31 + 50;
    new_Player.town_a.small_mon_1.damage_per_round = rand() % 5 + 50;
    new_Player.town_a.small_mon_1.defense_power = rand() % 5 + 50;
    new_Player.town_a.small_mon_1.defeated = false;
    new_Player.town_a.small_mon_2.health = rand() % 121 + 200;
    new_Player.town_a.small_mon_2.damage_per_round = rand() % 17 + 100;
    new_Player.town_a.small_mon_2.defense_power = rand() % 17 + 300;
    new_Player.town_a.small_mon_2.defeated = false;
    new_Player.town_a.duke.health = 500;
    new_Player.town_a.duke.damage_per_round = 125;
    new_Player.town_a.duke.defense_power = 500;
    new_Player.town_a.duke.defeated = false;

    new_Player.town_b.small_mon_1.health = rand() % 31 + 1500;
    new_Player.town_b.small_mon_1.damage_per_round = rand() % 6 + 150;
    new_Player.town_b.small_mon_1.defense_power = rand() % 11 + 700;
    new_Player.town_b.small_mon_1.defeated = false;
    new_Player.town_b.small_mon_2.health = rand() % 100 + 2000;
    new_Player.town_b.small_mon_2.damage_per_round = rand() % 8 + 200;
    new_Player.town_b.small_mon_2.defense_power = rand() % 15 + 900;
    new_Player.town_b.small_mon_2.defeated = false;
    new_Player.town_b.duke.health = 2500;
    new_Player.town_b.duke.damage_per_round = 300;
    new_Player.town_b.duke.defense_power = 1500;
    new_Player.town_b.duke.defeated = false;

    new_Player.town_c.small_mon_1.health = rand() % 31 + 2800;
    new_Player.town_c.small_mon_1.damage_per_round = rand() % 31 + 250;
    new_Player.town_c.small_mon_1.defense_power = rand() % 16 + 1700;
    new_Player.town_c.small_mon_1.defeated = false;
    new_Player.town_c.small_mon_2.health = rand() % 61 + 3300;
    new_Player.town_c.small_mon_2.damage_per_round = rand() % 37 + 300;
    new_Player.town_c.small_mon_2.defense_power = rand() % 19 + 2000;
    new_Player.town_c.small_mon_2.defeated = false;
    new_Player.town_c.duke.health = 3800;
    new_Player.town_c.duke.damage_per_round = 400;
    new_Player.town_c.duke.defense_power = 2500;
    new_Player.town_c.duke.defeated = false;

    new_Player.town_d.small_mon_1.health = rand() % 200 + 4200;
    new_Player.town_d.small_mon_1.damage_per_round = rand() % 101 + 400;
    new_Player.town_d.small_mon_1.defense_power = rand() % 21 + 3000;
    new_Player.town_d.small_mon_1.defeated = false;
    new_Player.town_d.small_mon_2.health = rand() % 200 + 4800;
    new_Player.town_d.small_mon_2.damage_per_round = rand() % 126 + 500;
    new_Player.town_d.small_mon_2.defense_power = rand() % 26 + 3500;
    new_Player.town_d.small_mon_2.defeated = false;
    new_Player.town_d.duke.health = 7500;
    new_Player.town_d.duke.damage_per_round = 800;
    new_Player.town_d.duke.defense_power = 4000;
    new_Player.town_d.duke.defeated = false;

    new_Player.boss.health = rand() % 1501 + 6000;
    new_Player.boss.damage_per_round = rand() % 501 + 1500;
    new_Player.boss.defense_power = rand() % 500 + 5000;
    new_Player.boss.defeated = false;

    return new_Player;
}

// After winning each monster, all basic index of the player will be 
// enlarged by a floating factor
void after_winning_index_increment(player & Player)
{
    if (Player.health < 100)
        Player.health *= (double) 2.5;
    else if (Player.health >= 100 && Player.health < 200)
        Player.health *= (double) 2;
    else if (Player.health >= 200 && Player.health < 300)
        Player.health *= (double) 1.7;
    else if (Player.health >= 300 && Player.health < 400)
        Player.health *= (double) 1.5;
    else
        Player.health *= (double) 1.2;
    
    if (Player.strength < 1000)
        Player.strength *= (double) 1.7;
    else if (Player.strength >= 1000 && Player.strength < 2000)
        Player.strength *= (double) 1.5;
    else if (Player.strength >= 2000 && Player.strength < 3000)
        Player.strength *= (double) 1.3;
    else if (Player.strength >= 3000 && Player.strength < 4000)
        Player.strength *= (double) 1.2;
    else
        Player.strength *= (double) 1.1;

    if (Player.defense_power < 1000)
        Player.defense_power *= (double) 1.7;
    else if (Player.defense_power >= 1000 && Player.defense_power < 2000)
        Player.defense_power *= (double) 1.5;
    else if (Player.defense_power >= 2000 && Player.defense_power < 3000)
        Player.defense_power *= (double) 1.3;
    else if (Player.defense_power >= 3000 && Player.defense_power < 4000)
        Player.defense_power *= (double) 1.3;
    else
        Player.defense_power *= (double) 1.2;

    Player.intelligence += 50;

    check_health(Player.health);
    check_strength(Player.strength);
    check_defense_power(Player.defense_power);
    check_intelligence(Player.intelligence);
    
    return;
}

// calculate the earning of money per round
void calculate_money (int & money, bool is_duke)
{
    if (is_duke) money += 100;
    else money += 50;
    return;
}

// Different portions of aspects available in the store
// buying health portion in store
void buy_health (int & money)
{
    money -= 75;
    return;
}

// buying strength portion in store
void buy_strength (int & money)
{
    money -=50;
    return;
}

// buying defense portion in store
void buy_defense (int & money)
{
    money-=50;
    return;
}

// buying intelligtnce portion in store
void buy_intelligence (int & money
){
    money-=25;
    return;
}

// buying magic in store
void buy_magic(map<int, int> & magic, int & magic_size, int & intelligence, int choice)
{
    if (intelligence == 0) return;

    //if (magic_size % 3 == 0) grow_magic_array(magic, magic_size);
    if (choice == 1)
    {
        if (intelligence <= 100)
            intelligence -= 30;
        else intelligence *= 0.3;
        magic[1] += 1;
        //magic[magic_size] = 1;
        magic_size++;
    }
    else if (choice ==2)
    {
        if (intelligence <= 100)
            intelligence -= 25;
        else intelligence *= 0.25;
        magic[2] += 1;
        //magic[magic_size] = 2;
        magic_size++;
    }
    return;
}
