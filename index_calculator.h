#ifndef INDEX_CALCULATOR_H
#define INDEX_CALCULATOR_H

#include "main.h"

#include <string>
#include <map>

using namespace std;

struct player initial_player_creation(string namee);

void after_winning_index_increment(struct player & Player);

void calculate_money (int & money, bool is_duke);

void buy_health (int &money);
void buy_strength (int & money);
void buy_defense (int & money);
void buy_intelligence (int & money);
void buy_magic(map<int, int> & magic, int & magic_size, int & intelligence, int choice);

#endif
