#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <ctime>
#include <string.h>

#include "main.h"
#include "file_io.h"
#include "User_Interface.h"
#include "check_index.h"
#include "In_game_user_interface.h"
#include "index_calculator.h"
#include "opportunity_card.h"
using namespace std;

// save game settings when the player opts to exit game
void save_files(player Player, string file_name)
{
    ofstream fout;
    fout.open(file_name.c_str());

    if (fout.fail())
    {
        exit(1);
    }

    fout << "Old Game Settings: " << endl;
    fout << "Name: " << Player.name << endl;
    fout << "Health: " << Player.health << endl;
    fout << "Strength: " << Player.strength << endl;
    fout << "Defense_Power: " << Player.defense_power << endl;
    fout << "Intelligence: " << Player.intelligence << endl;
    fout << "Money: " << Player.money << endl;
    fout << endl;

    fout << "Magic_Size: " << Player.magic_size << endl;
    fout << Player.magic[1] << endl;
    fout << Player.magic[2] << endl;
    fout << endl;
    fout << "Opportunity_card: " << Player.opportunity_card << endl;
    fout << "Trash_deck_Size: " << Player.trash_deck_size << endl;
    Node * current = Player.trash_opportunity_card_deck;
    if (current == nullptr) fout << "NULL" << endl;
    else
    {
        for (int i=0;i<Player.trash_deck_size;++i)
        {
            fout << current->card << " ";
            current = current->next;
        }
    }
    fout << endl;
    fout << endl;

    fout<< "Health_Potion: " << Player.potions["health"] << endl;
    fout << "Strength_Potion: " << Player.potions["strength"] << endl;
    fout << "Defense_Potion: " << Player.potions["defense"] << endl;
    fout << "Intelligence_Potion: " << Player.potions["intelligence"] << endl;
    fout << endl;
    
    fout<< "Town: " << Player.current_progress[0] << endl;
    fout << "Monster: " << Player.current_progress[1] << endl;
    fout << endl;

    fout << "Defeat_Town_A: " << Player.defeat_a << endl;
    fout << "Defeat_Town_B: " << Player.defeat_b << endl;
    fout << "Defeat_Town_C: " << Player.defeat_c << endl;
    fout << "Defeat_Town_D: " << Player.defeat_d << endl;
    fout << endl;

    fout << "Town_A: " << endl;
    fout << "Duke: " << endl;
    fout << "health: " << Player.town_a.duke.health << endl;
    fout << "damage_per_round: " << Player.town_a.duke.damage_per_round << endl;
    fout << "defense_power: " << Player.town_a.duke.defense_power << endl;
    fout << "defeated: " << Player.town_a.duke.defeated << endl;
    fout << "anger_level: " << Player.town_a.duke.current_anger_level << endl;
    fout << "Small_mon_1: " << endl;
    fout << "health: " << Player.town_a.small_mon_1.health << endl;
    fout << "damage_per_round: " << Player.town_a.small_mon_1.damage_per_round << endl;
    fout << "defense_power: " << Player.town_a.small_mon_1.defense_power << endl;
    fout << "defeated: " << Player.town_a.small_mon_1.defeated << endl;
    fout << "anger_level: " << Player.town_a.small_mon_1.current_anger_level << endl;
    fout << "Small_mon_2: " << endl;
    fout << "health: " << Player.town_a.small_mon_2.health << endl;
    fout << "damage_per_round: " << Player.town_a.small_mon_2.damage_per_round << endl;
    fout << "defense_power: " << Player.town_a.small_mon_2.defense_power << endl;
    fout << "defeated: " << Player.town_a.small_mon_2.defeated << endl;
    fout << "anger_level: " << Player.town_a.small_mon_2.current_anger_level << endl;
    fout << endl;

    fout << "Town_B: " << endl;
    fout << "Duke: "<< endl;
    fout << "health: " << Player.town_b.duke.health << endl;
    fout << "damage_per_round: " << Player.town_b.duke.damage_per_round << endl;
    fout << "defense_power: " << Player.town_b.duke.defense_power << endl;
    fout << "defeated: " << Player.town_b.duke.defeated << endl;
    fout << "anger_level: " << Player.town_b.duke.current_anger_level << endl;
    fout << "Small_mon_1: " << endl;
    fout << "health: " << Player.town_b.small_mon_1.health << endl;
    fout << "damage_per_round: " << Player.town_b.small_mon_1.damage_per_round << endl;
    fout << "defense_power: " << Player.town_b.small_mon_1.defense_power << endl;
    fout << "defeated: " << Player.town_b.small_mon_1.defeated << endl;
    fout << "anger_level: " << Player.town_b.small_mon_1.current_anger_level << endl;
    fout << "Small_mon_2: "<< endl;
    fout << "health: " << Player.town_b.small_mon_2.health << endl;
    fout << "damage_per_round: " << Player.town_b.small_mon_2.damage_per_round << endl;
    fout << "defense_power: " << Player.town_b.small_mon_2.defense_power << endl;
    fout << "defeated: " << Player.town_b.small_mon_2.defeated << endl;
    fout << "anger_level: " << Player.town_b.small_mon_2.current_anger_level << endl;
    fout << endl;

    fout << "Town_C: " << endl;
    fout << "Duke: " << endl;
    fout << "health: " << Player.town_c.duke.health << endl;
    fout << "damage_per_round: " << Player.town_c.duke.damage_per_round << endl;
    fout << "defense_power: " << Player.town_c.duke.defense_power << endl;
    fout << "defeated: " << Player.town_c.duke.defeated << endl;
    fout << "anger_level: " << Player.town_c.duke.current_anger_level << endl;
    fout << "Small_mon_1: " << endl;
    fout << "health: " << Player.town_c.small_mon_1.health << endl;
    fout << "damage_per_round: " << Player.town_c.small_mon_1.damage_per_round << endl;
    fout << "defense_power: " << Player.town_c.small_mon_1.defense_power << endl;
    fout << "defeated: " << Player.town_c.small_mon_1.defeated << endl;
    fout << "anger_level: " << Player.town_c.small_mon_1.current_anger_level << endl;
    fout << "Small_mon_2: " << endl;
    fout << "health: " << Player.town_c.small_mon_2.health << endl;
    fout << "damage_per_round: " << Player.town_c.small_mon_2.damage_per_round << endl;
    fout << "defense_power: " << Player.town_c.small_mon_2.defense_power << endl;
    fout << "defeated: " << Player.town_c.small_mon_2.defeated << endl;
    fout << "anger_level: " << Player.town_c.small_mon_2.current_anger_level << endl;
    fout << endl;

    fout << "Town_D: " << endl;
    fout << "Duke: " << endl;
    fout << "health: " << Player.town_d.duke.health << endl;
    fout << "damage_per_round: " << Player.town_d.duke.damage_per_round << endl;
    fout << "defense_power: " << Player.town_d.duke.defense_power << endl;
    fout << "defeated: " << Player.town_d.duke.defeated << endl;
    fout << "anger_level: " << Player.town_d.duke.current_anger_level << endl;
    fout << "Small_mon_1: " << endl;
    fout << "health: " << Player.town_d.small_mon_1.health << endl;
    fout << "damage_per_round: " << Player.town_d.small_mon_1.damage_per_round << endl;
    fout << "defense_power: " << Player.town_d.small_mon_1.defense_power << endl;
    fout << "defeated: " << Player.town_d.small_mon_1.defeated << endl;
    fout << "anger_level: " << Player.town_d.small_mon_1.current_anger_level << endl;
    fout << "Small_mon_2: " << endl;
    fout << "health: " << Player.town_d.small_mon_2.health << endl;
    fout << "damage_per_round: " << Player.town_d.small_mon_2.damage_per_round << endl;
    fout << "defense_power: " << Player.town_d.small_mon_2.defense_power << endl;
    fout << "defeated: " << Player.town_d.small_mon_2.defeated << endl;
    fout << "anger_level: " << Player.town_d.small_mon_2.current_anger_level << endl;
    fout << endl;
    
    fout << "Final_Boss: " << endl;
    fout << "health: " << Player.boss.health << endl;
    fout << "damage_per_round: " << Player.boss.damage_per_round << endl;
    fout << "defense_power: " << Player.boss.defense_power << endl;
    fout << "defeated: " << Player.boss.defeated << endl;
    fout << "anger_level: " << Player.boss.current_anger_level << endl;

    fout.close();
    return;
 
}

// load game settings when the player opts to load old game
void load_files (player & Player, string file_name)
{
    ifstream fin;
    fin.open(file_name.c_str());
    if (fin.fail())
    {
        exit(1);
    }
    string trash;
    fin >> trash >> trash;
    fin >> trash >> trash >> Player.name;
    fin >> trash >> Player.health;
    fin >> trash >> Player.strength;
    fin >> trash >> Player.defense_power;
    fin >> trash >> Player.intelligence;
    fin >> trash >> Player.money;

    fin >> trash >> Player.magic_size;
    fin >> Player.magic[1] >> Player.magic[2];
    fin >> trash >> Player.opportunity_card;
    fin >> trash >> Player.trash_deck_size;
    int card;
    if (Player.trash_deck_size == 0) fin >> trash;
    else
    {
        for (int i=0;i<Player.trash_deck_size;++i)
        {
            Node * p = new Node;
            fin >> card;
            p->card = card;
            p->next = Player.trash_opportunity_card_deck;
            Player.trash_opportunity_card_deck = p;
        }
    }

    fin >> trash >> Player.potions["health"];
    fin >> trash >> Player.potions["strength"];
    fin >> trash >> Player.potions["defense"];
    fin >> trash >> Player.potions["intelligence"];

    string temp1, temp2;
    fin >> trash >> temp1;
    fin >> trash >> temp2;
    temp1 = temp1 + temp2;
    Player.current_progress = temp1.c_str();
    
    fin >> trash >> Player.defeat_a;
    fin >> trash >> Player.defeat_b;
    fin >> trash >> Player.defeat_c;
    fin >> trash >> Player.defeat_d;

    fin >> trash >> trash;
    fin >> trash >> Player.town_a.duke.health;
    fin >> trash >> Player.town_a.duke.damage_per_round;
    fin >> trash >> Player.town_a.duke.defense_power;
    fin >> trash >> Player.town_a.duke.defeated;
    fin >> trash >> Player.town_a.duke.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_a.small_mon_1.health;
    fin >> trash >> Player.town_a.small_mon_1.damage_per_round;
    fin >> trash >> Player.town_a.small_mon_1.defense_power;
    fin >> trash >> Player.town_a.small_mon_1.defeated;
    fin >> trash >> Player.town_a.small_mon_1.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_a.small_mon_2.health;
    fin >> trash >> Player.town_a.small_mon_2.damage_per_round;
    fin >> trash >> Player.town_a.small_mon_2.defense_power;
    fin >> trash >> Player.town_a.small_mon_2.defeated;
    fin >> trash >> Player.town_a.small_mon_2.current_anger_level;

    fin >> trash >> trash;
    fin >> trash >> Player.town_b.duke.health;
    fin >> trash >> Player.town_b.duke.damage_per_round;
    fin >> trash >> Player.town_b.duke.defense_power;
    fin >> trash >> Player.town_b.duke.defeated;
    fin >> trash >> Player.town_b.duke.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_b.small_mon_1.health;
    fin >> trash >> Player.town_b.small_mon_1.damage_per_round;
    fin >> trash >> Player.town_b.small_mon_1.defense_power;
    fin >> trash >> Player.town_b.small_mon_1.defeated;
    fin >> trash >> Player.town_b.small_mon_1.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_b.small_mon_2.health;
    fin >> trash >> Player.town_b.small_mon_2.damage_per_round;
    fin >> trash >> Player.town_b.small_mon_2.defense_power;
    fin >> trash >> Player.town_b.small_mon_2.defeated;
    fin >> trash >> Player.town_b.small_mon_2.current_anger_level;

    fin >> trash >> trash;
    fin >> trash >> Player.town_c.duke.health;
    fin >> trash >> Player.town_c.duke.damage_per_round;
    fin >> trash >> Player.town_c.duke.defense_power;
    fin >> trash >> Player.town_c.duke.defeated;
    fin >> trash >> Player.town_c.duke.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_c.small_mon_1.health;
    fin >> trash >> Player.town_c.small_mon_1.damage_per_round;
    fin >> trash >> Player.town_c.small_mon_1.defense_power;
    fin >> trash >> Player.town_c.small_mon_1.defeated;
    fin >> trash >> Player.town_c.small_mon_1.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_c.small_mon_2.health;
    fin >> trash >> Player.town_c.small_mon_2.damage_per_round;
    fin >> trash >> Player.town_c.small_mon_2.defense_power;
    fin >> trash >> Player.town_c.small_mon_2.defeated;
    fin >> trash >> Player.town_c.small_mon_2.current_anger_level;
    
    fin >> trash >> trash;
    fin >> trash >> Player.town_d.duke.health;
    fin >> trash >> Player.town_d.duke.damage_per_round;
    fin >> trash >> Player.town_d.duke.defense_power;
    fin >> trash >> Player.town_d.duke.defeated;
    fin >> trash >> Player.town_d.duke.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_d.small_mon_1.health;
    fin >> trash >> Player.town_d.small_mon_1.damage_per_round;
    fin >> trash >> Player.town_d.small_mon_1.defense_power;
    fin >> trash >> Player.town_d.small_mon_1.defeated;
    fin >> trash >> Player.town_d.small_mon_1.current_anger_level;
    fin >> trash;
    fin >> trash >> Player.town_d.small_mon_2.health;
    fin >> trash >> Player.town_d.small_mon_2.damage_per_round;
    fin >> trash >> Player.town_d.small_mon_2.defense_power;
    fin >> trash >> Player.town_d.small_mon_2.defeated;
    fin >> trash >> Player.town_d.small_mon_2.current_anger_level;

    fin >> trash;
    fin >> trash >> Player.boss.health;
    fin >> trash >> Player.boss.damage_per_round;
    fin >> trash >> Player.boss.defense_power;
    fin >> trash >> Player.boss.defeated;
    fin >> trash >> Player.boss.current_anger_level;


    fin.close();
    return;

}

// to turn the contents in the file manager file
// to the string vector container 
vector<string> file_manager()
{
    vector<string> game_file_book;

    ifstream fin("old_game_status_manager.txt");

    if ( fin.fail() )
        exit(1);

    string temp;
    
    while (getline(fin, temp))
    {
		game_file_book.push_back(temp);
    }

		fin.close();
    return game_file_book;
}

// to update the file manager text file
// all newly saved game save will be appended to the text file
void save_file_manager(player Player, int current_size, vector<string> v)
{
    ofstream fout;
    if (current_size <= 4)
    {
        fout.open("old_game_status_manager.txt", ios::app);
    
        if ( fout.fail() )
            exit(1);

        string name, name2;
        name = to_string(current_size + 1) + "RPG.txt";
        name2 = "00" + to_string(current_size + 1);
        time_t tmNow = time(0);
        char * dt = ctime(&tmNow);
        if (dt[strlen(dt)-1] == '\n') dt[strlen(dt)-1] = '\0';
        fout << name << " / " << name2 << " / " << dt << " / " << Player.current_progress << endl;

        fout.close();
        
    }
    else
    {
        fout.open("old_game_status_manager.txt");

        if ( fout.fail() )
            exit(1);

        fout << v[0] << endl;
        fout << v[1] << endl;
        fout << v[2] << endl;
        fout << v[3] << endl;

        string name, name2;
        name = "5RPG.txt";
        name2 = "005";
        time_t tmNow = time(0);
        char * dt = ctime(&tmNow);
        if (dt[strlen(dt)-1] == '\n') dt[strlen(dt)-1] = '\0';
        fout << name << " / " << name2 << " / " << dt << " / " << Player.current_progress << endl;

        fout.close();
    }
    
}
