#include <iostream>
#include <string>
#include <iomanip>
#include <map>

#include "In_game_user_interface.h"
#include "User_Interface.h"
#include "index_calculator.h"
#include "check_index.h"
#include "main.h"
#include "opportunity_card.h"
#include "file_io.h"

using namespace std;

// Purpose: to calculate the angry index of a monster according to the change of monster's health
// Input: monster type current_mon + old health of the monster
// + new health of the monster
// Output: N/A (the anger index will change internally)
void caculate_monster_anger_level(monster & current_mon, int & old_health, int & new_health)
{
    // angry_index refers to the percentage decrease of monsters' health after one round
    int angry_index;
    double factor = (double) (old_health-new_health)/old_health;
    angry_index = factor * 100;
    
    if (angry_index >= 20 && angry_index <= 40) 
    {
        current_mon.current_anger_level = "LOW";
    }
    else if (angry_index>40 && angry_index<=60) 
    {
        current_mon.current_anger_level = "MID";
    }
    else if (angry_index>60) 
    {
        current_mon.current_anger_level = "HIGH";
    }
    
    return;
}

// Purpose: to calculate the final strength of monster according to
// the anger index calculated in the function above
// Input: monster type current_mon
// Output: final strength (integer)
int calculate_monster_strength(struct monster & current_mon)
{
    if (current_mon.current_anger_level == "LOW")
    {
        current_mon.current_anger_level = "NO";
        return current_mon.damage_per_round * 1.1;
    }
    else if (current_mon.current_anger_level == "MID")
    {
        current_mon.current_anger_level = "NO";
        return current_mon.damage_per_round * 1.25;
    }
    else if (current_mon.current_anger_level == "HIGH")
    {
        current_mon.current_anger_level = "NO";
        return current_mon.damage_per_round * 1.35;
    }
    else return current_mon.damage_per_round;
}

// Purpose: to calculate the final real health deduction per round
// Input: original health + defense + final strength of monster
// Output: N/A (the health will decrease internally)
void calculate_health(int & health, int & defense, int & damage)
{
    double factor = (double) (1-defense/(defense+200));
    health -= factor * damage;
    if (health < 0) health = 0;
    return;
}

// Purpose: to display the status of the player
// Input: the Player with player data type
// Output: the various information
void display_graphics(player Player) 
{
    cout << endl;
    print_ruler_divider_hyphen_version();
    cout << "                             Status                              " << endl;
    print_ruler_divider_hyphen_version();
    cout << endl;
    cout << "Name: " << Player.name << endl;
    cout << "Health: " << Player.health <<endl;
    cout << "Strength: " << Player.strength << endl;
    cout << "Defense: " << Player.defense_power <<endl;
    cout << "Intelligence: " << Player.intelligence << endl;
    cout << "Possessed Magic: ";
    if (Player.magic_size == 0) cout << "N/A" << endl;
    else 
    {
        if (Player.magic[1] != 0) 
        {
            cout << "1. Lighting Magic  x" << Player.magic[1] << endl;
            if (Player.magic[2] != 0) cout << "                 2. Incendio  x" << Player.magic[2] << endl;
        }
        else if (Player.magic[2] != 0) cout << "1. Incendio  x" << Player.magic[2] << endl;
    }
    cout << "Money: " << Player.money << endl;
    cout << endl;
    print_ruler_divider_hyphen_version();
    cout << "***Press enter to return to Grand Menu***" << endl;
    return;
}

// Purpose: to display the map
// Input : Player with player data type + display_index
// display_index == 1 --> Not fight scene (won't show the mon progress)
// display_index == 2 --> Fight scene (show the mon progress)
// Output: display the map and the mon progress if available
void map_graphics(player Player , int display_index)
{
    // status_a / b / c / d represents the whether the 
    // town A / B / C / D has been defeated respectively
    char status_a, status_b, status_c, status_d;
    string status_boss;
    
    // check the status of current game profile
    // in order to change the indicators to be
    // displayed in the map
    if (Player.defeat_a) status_a = 'X'; // town A
    else status_a = 'A';
    if (Player.defeat_b) status_b = 'X'; // town B
    else status_b = 'B';
    if (Player.defeat_c) status_c = 'X'; // town C
    else status_c = 'C';
    if (Player.defeat_d) status_d = 'X'; // town D
    else status_d = 'D';
    if (Player.defeat_boss) status_boss = " XX "; // final boss
    else status_boss = "BOSS";

    // structure of the map
    if (display_index == 1)
    {
        cout << endl;
        print_ruler_divider_hyphen_version();
        cout << "Map:" << endl;
        print_ruler_divider_hyphen_version();
    }
    cout << "******************** " << endl;
    cout << "*  " << status_a << "  *     *	 " << status_c << "  * " <<endl;
    cout << "*   *        *     * " << endl;
    cout << "****	" <<  status_boss << "   ****** " << endl;
    cout << "*  " << status_b << " *       *  " << status_d << "  *" << endl;
    cout << "******************** " << endl;

    // to check if the player is in the fight scene 
    // or just wanna display the map
    if ( display_index == 1 ) 
    {
        // display the structure of the horizontal map
        cout << "ME --> "; 
        if (!Player.defeat_a) cout << 'A';
        if (!Player.defeat_b) 
        {
            if (!Player.defeat_a) cout << " --> B";
            else cout << 'B'; 
        }
        if (!Player.defeat_c) 
        {
            if (!Player.defeat_a || !Player.defeat_b) cout << " --> C";
            else cout << 'C';
        }
        if (!Player.defeat_d) 
        {
            if (!Player.defeat_a || !Player.defeat_b || !Player.defeat_c) cout << " --> D";
            else cout << 'D';
        }
        cout << endl;
        print_ruler_divider_hyphen_version();
        cout << "***Press enter to return to Grand Menu***" << endl;
    }

    else if ( display_index == 2 )
    {
        // display the structure of the horizontal map
        // within the current town
        switch ( Player.current_progress[0] )
        {
            case 'A':
                cout << "A : ";
                break;
            case 'B':
                cout << "B: ";
                break;
            case 'C':
                cout << "C: ";
                break;
            case 'D':
                cout << "D: ";
                break;
            case 'S':
                cout << "BOSS : || FINAL BOSS ||" << endl;
                break;
        }

        if (Player.current_progress[0] != 'S')
        {
            switch ( Player.current_progress[1] )
            {
                case '0':
                    cout << "| ME | MON || DUKE" << endl;
                    break;
                case '1':
                    cout << "| X | ME || DUKE" << endl;
                    break;
                case '2':
                    cout << "| X | X || ME" << endl;
                    break;
            }
        }
    }
    
    return;
}

// Purpose: to display the information during the fight
// Input: Player with player data type
// Output: same as the purpose
void fight_graphics(player Player)
{
    // declare a variable of monster data type 
    // to store the status of the current fighting monster 
    // to be displayed
    monster current_mon;
    switch ( Player.current_progress[0] )
    {
        case 'A':
            switch ( Player.current_progress[1] )
            {
                case '0':
                    current_mon = Player.town_a.small_mon_1;
                    break;
                case '1':
                    current_mon = Player.town_a.small_mon_2;
                    break;
                case '2':
                    current_mon = Player.town_a.duke;
                    break;
            }
            break;
        case 'B':
            switch ( Player.current_progress[1] )
            {
                case '0':
                    current_mon = Player.town_b.small_mon_1;
                    break;
                case '1':
                    current_mon = Player.town_b.small_mon_2;
                    break;
                case '2':
                    current_mon = Player.town_b.duke;
                    break;
            }
            break;
        case 'C':
            switch ( Player.current_progress[1] )
            {
                case '0':
                    current_mon = Player.town_c.small_mon_1;
                    break;
                case '1':
                    current_mon = Player.town_c.small_mon_2;
                    break;
                case '2':
                    current_mon = Player.town_c.duke;
                    break;
            }
            break;
        case 'D':
            switch ( Player.current_progress[1] )
            {
                case '0':
                    current_mon = Player.town_d.small_mon_1;
                    break;
                case '1':
                    current_mon = Player.town_d.small_mon_2;
                    break;
                case '2':
                    current_mon = Player.town_d.duke;
                    break;
            }
            break;
        case 'S':
            current_mon = Player.boss;
            break;
    }
    cout << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your position:" << endl;
    print_ruler_divider_hyphen_version();
    map_graphics( Player , 2 );
    print_ruler_divider_hyphen_version();
    cout << "MON :                   ME :" << endl;
    cout << "Health      : " << setw(5) << right << current_mon.health << "  |  Health       : " << setw(5) << right << Player.health << endl;
    cout << "Strength    : " << setw(5) << right << current_mon.damage_per_round << "  |  Strength     : " << setw(5) << right << Player.strength << endl; 
    cout << "Defense     : " << setw(5) << right << current_mon.defense_power << "  |  Defense      : " << setw(5) << right << Player.defense_power << endl;
    cout << "Anger Level : " << setw(5) << right << current_mon.current_anger_level << "  |  Intelligence : " << setw(5) << right << Player.intelligence << endl;
    print_ruler_divider_hyphen_version();
    cout << "1. Combat" << endl;
    cout << "2. Use Potions" << endl;
    cout << "3. Choose Magic and Combat" << endl;
    // (just a small reminder) if the opportunity card is 3, no need to pass 'calculate_magic' function, just pass the 'use_magic' function
    cout << "4. Go back to the town" << endl;
    print_ruler_divider_hyphen_version();
    return;
}

// Purpose: to display the new status of player after the player has won a round
// if the monster defeated was a duke, the opportunity card will be shown
// Input: Player with player data type
// Output: same as the purpose
void after_fighting_graphics(player & Player)
{
    print_ruler_divider_hyphen_version();
    cout << "		          Congratulations!" << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your New Status: " << endl;
    cout << "Name: " << Player.name << endl;
    cout << "Health: " << Player.health << "/1000" << endl;
    cout << "Strength: " << Player.strength << "/10000" << endl;
    cout << "Defense: " << Player.defense_power << "/1000" << endl;
    cout << "Intelligence: " << Player.intelligence << "/10000" << endl;
    cout << "Possessed Magic: ";
    if (Player.magic_size == 0) cout << "N/A" << endl;
    else 
    {
        if (Player.magic[1] != 0) 
        {
            cout << "1. Lighting Magic  x" << Player.magic[1] << endl;
            if (Player.magic[2] != 0) cout << "                 2. Incendio  x" << Player.magic[2] << endl;
        }
        else if (Player.magic[2] != 0) cout << "1. Incendio  x" << Player.magic[2] << endl;
    }
    cout << "Money: ";
    
    if (Player.current_progress[1] == '1' || Player.current_progress[1] == '2') 
    {   
        Player.money+=50;
        cout << Player.money << "(+50)" << endl;
    }
    else if (Player.current_progress == "B0" || Player.current_progress == "C0" || Player.current_progress == "D0" || ( (Player.current_progress == "B1" || Player.current_progress == "C1" || Player.current_progress == "D1") && Player.opportunity_card == 5) ) 
    {
        Player.money+=100;
        cout << Player.money << "(+100)" << endl;
        cout << "You earn a chance for an opportunity card!" << endl;
        opportunity_card_graphics(Player);
    }
    print_ruler_divider_hyphen_version();

    cout << endl;
    cout << "What do you want to do next?" << endl;
    cout << endl;
    cout << "1. Continue the Fight" << endl;
    cout << "2. Go back to the Town" << endl;
    cout << "3. Exit" << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your Input: ";
}

// Purpose: to display the graphics of the main store
// Store: for player to buy potions and magic
// Input: Player with player data type
// Output: same as the purpose
void store_main_menu_graphics(player Player)
{
    cout << endl;
    print_ruler_divider_hyphen_version();
    cout << "                              Store                              " << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your Money: " << Player.money << endl;
    cout << endl;
    cout << "Your Bag:" << endl;
    cout << "health potion: " <<  Player.potions["health"] << endl;
    cout << "strength potion: " << Player.potions["strength"] << endl;
    cout << "defense potion: " << Player.potions["defense"] << endl;
    cout << "intelligence potion: " << Player.potions["intelligence"] << endl;
    cout << endl;
    cout << "Your Magic: ";
   if (Player.magic_size == 0) cout << "N/A" << endl;
    else 
    {
        if (Player.magic[1] != 0) 
        {
            cout << "1. Lighting Magic  x" << Player.magic[1] << endl;
            if (Player.magic[2] != 0) cout << "                 2. Incendio  x" << Player.magic[2] << endl;
        }
        else if (Player.magic[2] != 0) cout << "1. Incendio  x" << Player.magic[2] << endl;
    }
    print_ruler_divider_hyphen_version();
    cout << "1. Buy Potion" << endl;
    cout << "2. Buy Magic" << endl;
    cout << "3. Exit back to Grand Menu" << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your Input: ";
}

// Purpose: after choosing the 'buy potion' option, 
// the following graphics is supposed to be shown
// showing your money and the costs
// Input: amount of your money
// Output: same as the purpose
void buy_potion_graphics(int money)
{
    print_ruler_divider_hyphen_version();
    cout << "Your Money: " << money << endl;
    cout << endl;
    cout << "1. Health Potion       | Cost : 75" << endl;
    cout << "2. Strength Potion     | Cost : 50" << endl;
    cout << "3. defense Potion      | Cost : 50" << endl;
    cout << "4. Intelligence Potion | Cost : 25" << endl;
    print_ruler_divider_hyphen_version();
}

// Purpose: after choosing the 'buy magic' option, 
// the following graphics is supposed to be shown
// showing your money and the costs
// Input: amount of your money
// Output: same as the purpose
void buy_magic_graphics (player Player)
{
    print_ruler_divider_hyphen_version();
    cout << "Your Intelligence: " << Player.intelligence << endl;
    cout << "*************************List of Magic**************************" << endl;
    cout << "1. Lighting Magic" << endl;
    cout << "Requirements:" << endl;
    cout << "Intelligence index: " << ((Player.intelligence >= 100)? Player.intelligence*0.3: 30) << " per usage" << endl;
    cout << endl;
    cout << "Special Ability:" << endl;
    cout << "You can freeze the monster’s motion for the next round, which means" << endl;
    cout << " the monster cannot attack you in the next round." << endl;
    cout << endl;
    cout << endl;
    cout << "2. Incendio" << endl;
    cout << "Requirements: " << endl;
    cout << "Intelligence index: " << ((Player.intelligence >= 100)? Player.intelligence*0.25: 25) << " per usage" << endl;
    cout << endl;
    cout << "Special Ability:" << endl;
    cout << "You can create fire to create 1.5X damage on the monster!!" << endl;
    print_ruler_divider_star_version();
    print_ruler_divider_hyphen_version();
}

// Purpose: to serve as a link back to the grand menu
// after showing the status of the player
// Input: Player with player data type
// Output: N/A
void display_logic(player Player)
{
    cin.ignore();
    // Grand menu graphics
    ingame_menu_graphics();
    ingame_menu_logic(Player);
    return;
}

// Purpose: to serve as a link back to the grand menu
// after showing the map and the mon status if available
// Input: Player with player data type
// Output: N/A
void map_logic(player Player)
{
    cin.ignore();
    ingame_menu_graphics();
    ingame_menu_logic(Player);
    return;
}

// Purpose: to process the option chosen by player
// in the main store
// Input: Player with player data type
// Input inside the function: Option Input
// Output: Corresponding graphics and logic
void store_logic(player & Player)
{
    string user_input;
    getline(cin, user_input);
    
    if (user_input == "1")
    {
        buy_potion_graphics(Player.money);
         cout << "What do you want to buy? (Press 0 to exit) ";
        getline(cin, user_input);
        int price,amount=0;
        if (user_input == "1") price = 75;
        else if (user_input == "2") price = 50;
        else if (user_input == "3") price = 50;
        else if (user_input == "4") price = 25;
        else if (user_input == "0") 
        {
            ingame_menu_graphics();
            ingame_menu_logic(Player);
        }
        else 
        {
            cout << "Invalid input. Please enter again. " << endl;
            buy_potion_graphics(Player.money);
            store_logic(Player);
        }
        store_amount_logic(Player, amount,price);
        if (user_input == "1") 
        {
            for (int i=0;i<amount;++i)
            {
                buy_health(Player.money);
                Player.potions["health"]+=1;
            }
        }
        else if (user_input == "2") 
        {
            for (int i=0;i<amount;++i)
            {
                buy_strength(Player.money);
                Player.potions["strength"]+=1;
            }
        }
        else if (user_input == "3")
        {
            for (int i=0;i<amount;++i)
            {
                buy_defense(Player.money);
                Player.potions["defense"]+=1;
            }
        }
        else if (user_input == "4") 
        {
            for (int i=0;i<amount;++i)
            {
                buy_intelligence(Player.money);
                Player.potions["intnelligence"]+=1;
            }
        }
    }

    else if (user_input == "2")
    {
        buy_magic_graphics(Player);
         cout << "What do you want to buy ? (Press 0 to exit) ";
        getline(cin, user_input);
        if (user_input == "1") buy_magic(Player.magic, Player.magic_size,Player.intelligence, 1);
        else if (user_input == "2") buy_magic(Player.magic, Player.magic_size,Player.intelligence, 2);
        else if (user_input == "0") 
        {
            ingame_menu_graphics();
            ingame_menu_logic(Player);
        }
        else 
        {
            cout << "Invalid input. Please enter again. " << endl;
            store_main_menu_graphics(Player);
        }
    }

     else if (user_input == "3") 
    {
        ingame_menu_graphics();
        ingame_menu_logic(Player);
    }
    
    else
    {
        cout << "Invalid input. Please enter again. " << endl;
        store_main_menu_graphics(Player);
        store_logic(Player);
        return;
    }
    store_main_menu_graphics(Player);
    store_logic(Player);
    return;
}

// Purpose: to process the amount inserted by user
// Input: Player with player data type + amount inserted + price per one item
// Output: Corresponding graphics and logic
void store_amount_logic(player & Player, int & amount, int price)
{
    cout << "Amount : ";
    string user_input;
    getline(cin,user_input);
    bool is_int = true;
    
    // check if the user_input is an integer
    for (int i = 0 ; i < user_input.length() ; ++i )
    {
        if ( !isdigit( user_input[i] ) ) 
        {
            is_int = false;
            break;
        }
    }

    if (is_int)
    {
        int amountt;
        amountt = stoi(user_input);
        if (Player.money >= (amountt*price)) amount = amountt;
        else 
        {
            cout << "Not enough money, please enter a smaller amount" << endl;
            store_amount_logic(Player, amount, price);
        }
    }
    else 
    {
        cout << "Invalid input. Please enter again. " << endl;
        store_amount_logic(Player, amount, price);
    }
    return;
}

// to process the magic graphics when fighting
void fight_magic_gra()
{
    print_ruler_divider_hyphen_version();
    cout << "*************************List of Magic**************************" << endl;
    cout << "1. Lighting Magic" << endl;
    cout << "Requirements:" << endl;
    cout << "Intelligence index: (I*30%) per usage" << endl;
    cout << endl;
    cout << "Special Ability:" << endl;
    cout << "You can freeze the monster’s motion for the next round, which means " << endl;
    cout << "the monster cannot attack you in the next round." << endl;
    cout << endl;
    cout << "2. Incendio" << endl;
    cout << "Requirements:" << endl;
    cout << "Intelligence index: (I*25%) per usage" << endl;
    cout << "Special Ability:" << endl;
    cout << "You can create fire to create 1.5X damage on the monster!!" << endl;
    cout << "****************************************************************" << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your Input: ";
    return;
}

// to process the potion graphics when fighting
void fight_potion_gra(player Player)
{
    print_ruler_divider_hyphen_version();
    cout << "List of potions" << endl;
    print_ruler_divider_hyphen_version();
    cout << endl;
    cout << "Your Bag:" << endl;
    cout << "1. health potion: " <<  Player.potions["health"] << endl;
    cout << "2. strength potion: " << Player.potions["strength"] << endl;
    cout << "3. defense potion: " << Player.potions["defense"] << endl;
    cout << "4. intelligence potion: " << Player.potions["inteligence"] << endl;
    cout << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your Input: (Press '0' to return) ";
    return;
}

// to process the potion logic when fighting
void fight_potion_log(player & Player)
{
    string user_input;
    getline(cin, user_input);
    if (user_input == "1")
    {
        if (Player.potions["health"] == 0)
        {
            cout << "Error. Insufficient amount." << endl;
            cout << endl;
            fight_potion_gra(Player);
            fight_potion_log(Player);
            return;
        }
        else
        {
            Player.potions["health"] -= 1;
            Player.health *= 1.25;
            if (Player.health > 1000) Player.health = 1000;
            return;
        }
    }
    else if (user_input == "2")
    {
        if (Player.potions["strength"] == 0)
        {
            cout << "Error. Insufficient amount." << endl;
            cout << endl;
            fight_potion_gra(Player);
            fight_potion_log(Player);
            return;
        }
        else
        {
            Player.potions["strength"] -= 1;
            Player.strength *= 1.2;
            if (Player.strength > 10000) Player.strength = 10000;
            return;
        }
    }
    else if (user_input == "3")
    {
        if (Player.potions["defense"] == 0)
        {
            cout << "Error. Insufficient amount." << endl;
            cout << endl;
            fight_potion_gra(Player);
            fight_potion_log(Player);
            return;
        }
        else
        {
            Player.potions["defense"] -= 1;
            Player.defense_power *= 1.2;
            if (Player.defense_power > 1000) Player.defense_power = 1000;
            return;
        }
    }
    else if (user_input == "4")
    {
        if (Player.potions["inteligence"] == 0)
        {
            cout << "Error. Insufficient amount." << endl;
            cout << endl;
            fight_potion_gra(Player);
            fight_potion_log(Player);
            return;
        }
        else
        {
            Player.potions["inteligence"] -= 1;
            Player.intelligence *= 1.25;
            if (Player.intelligence > 10000) Player.intelligence = 10000;
            return;
        }
    }
    else if (user_input == "0") return;
    else
    {
        cout << "Error. Invalid input." << endl;
        cout << endl;
        fight_potion_gra(Player);
        fight_potion_log(Player);
        return;
    }
    return;
}

// for the main fight menu and values manipulating
void fight_logic(player & Player)
{
    string user_input;
    cout << "Your Input: ";
    getline(cin, user_input);

    if (user_input == "1")
    {
        monster * current_mon;
        switch ( Player.current_progress[0] )
        {
            case 'A':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_a.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_a.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_a.duke;
                        break;
                }
                break;
            case 'B':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_b.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_b.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_b.duke;
                        break;
                }
                break;
            case 'C':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_c.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_c.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_c.duke;
                        break;
                }
                break;
            case 'D':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_d.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_d.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_d.duke;
                        break;
                }
                break;
            case 'S':
                current_mon = &Player.boss;
                break;
            }

        int mon_old_health = (*current_mon).health;
        if (Player.opportunity_card == 1)
        {
            use_opportunity_card(Player, (*current_mon));
            Player.opportunity_card = 0;
        }
        else if (Player.opportunity_card == 3)
        {
            // display magic
            cout << endl;
            cout << "*********************Opportunity Card Bonus*********************" << endl;
            fight_magic_gra();

            string user_input;
            getline(cin, user_input);
            if (user_input == "1")
            {
                calculate_health((*current_mon).health, (*current_mon).defense_power, Player.strength);
                caculate_monster_anger_level((*current_mon), mon_old_health, (*current_mon).health);
            }
            else if (user_input == "2")
            {
                int mon_old_health = (*current_mon).health;
            
                int real_damage = calculate_monster_strength((*current_mon));
    
                // damage to monster
                int player_new_strength = Player.strength * 1.5;
                calculate_health((*current_mon).health, (*current_mon).defense_power, player_new_strength);
                
                if ((*current_mon).health != 0)
                {
                    // damage to player
                    calculate_health(Player.health, Player.defense_power, real_damage);  
                    caculate_monster_anger_level((*current_mon), mon_old_health, (*current_mon).health);
                }
            }
        }

        // normal fighting
        if (Player.opportunity_card != 3 && Player.opportunity_card != 5)
        {
            int real_damage = calculate_monster_strength(*current_mon);
            calculate_health((*current_mon).health, (*current_mon).defense_power, Player.strength);
            if ((*current_mon).health != 0)
            {
                calculate_health(Player.health, Player.defense_power, real_damage);
                if (Player.health <= 0)
                {
                    losing_graphics();
                    exit(0);
                }
            }
        }
        Player.opportunity_card = 0; // reset the opportunity
        if ((*current_mon).health == 0)
        {
            switch ( Player.current_progress[0] )
            {
                case 'A':
                    switch ( Player.current_progress[1] )
                    {
                        case '0':
                            Player.current_progress = "A1";
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                            after_fighting_graphics(Player);
                            after_fighting_logic(Player);
                            return;
                            break;
                        case '1':
                            Player.current_progress = "A2";
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                            after_fighting_graphics(Player);
                            after_fighting_logic(Player);
                            return;
                            break;
                        case '2':
                            Player.current_progress = "B0";
                            Player.defeat_a = true;
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                            opportunity_card_logic(Player);
                            if (Player.opportunity_card == 1)
                            {
                                Player.health*=0.9;
                            }
                            else if (Player.opportunity_card == 2)
                            {
                                Player.strength*=2;
                                if (Player.strength >= 10000)
                                    Player.strength = 10000;
                                      
                                Player.health*=2;
                                if (Player.health >= 1000)
                                    Player.health = 1000;
                                      
                                Player.defense_power*=2;
                                if (Player.defense_power >= 10000)
                                    Player.defense_power = 10000;
    
                                Player.intelligence = 0;
                            }
                            else if (Player.opportunity_card == 4)
                            {
                                Player.intelligence*=2;
                                if (Player.intelligence >= 10000)
                                        Player.intelligence = 10000;
                            }
                            else if (Player.opportunity_card == 5)
                            {
                                Player.current_progress = "B1";
                                current_mon = &Player.town_b.small_mon_1;
                                (*current_mon).defeated = true;
                                after_winning_index_increment(Player);
                            }
                            after_fighting_graphics(Player);
                            if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                            after_fighting_logic(Player);
                            return;
                            break;
                    }
                    break;
            case 'B':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        Player.current_progress = "B1";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '1':
                        Player.current_progress = "B2";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '2':
                        Player.current_progress = "C0";
                        Player.defeat_b = true;
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        opportunity_card_logic(Player);

                        if (Player.opportunity_card == 1)
                        {
                            Player.health*=0.9;
                        }
                        else if (Player.opportunity_card == 2)
                        {
                            Player.strength*=2;
                            if (Player.strength >= 10000)
                                Player.strength = 10000;
                                  
                            Player.health*=2;
                            if (Player.health >= 1000)
                                Player.health = 1000;
                                  
                            Player.defense_power*=2;
                            if (Player.defense_power >= 10000)
                                Player.defense_power = 10000;

                            Player.intelligence = 0;
                        }
                        else if (Player.opportunity_card == 4)
                        {
                            Player.intelligence*=2;
                            if (Player.intelligence >= 10000)
                                    Player.intelligence = 10000;
                        }
                        // if opportunity card is 5
                        // the card is needed to process here
                       else  if (Player.opportunity_card == 5)
                        {
                            Player.current_progress = "C1";
                            current_mon = &Player.town_c.small_mon_1;
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                        }
                        after_fighting_graphics(Player);
                        if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                        after_fighting_logic(Player);
                        return;
                        break;
                }
                break;
            case 'C':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        Player.current_progress = "C1";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '1':
                        Player.current_progress = "C2";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '2':
                        Player.current_progress = "D0";
                        Player.defeat_c = true;
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        opportunity_card_logic(Player);

                        if (Player.opportunity_card == 1)
                        {
                            Player.health*=0.9;
                        }
                        else if (Player.opportunity_card == 2)
                        {
                            Player.strength*=2;
                            if (Player.strength >= 10000)
                                Player.strength = 10000;
                                  
                            Player.health*=2;
                            if (Player.health >= 1000)
                                Player.health = 1000;
                                  
                            Player.defense_power*=2;
                            if (Player.defense_power >= 10000)
                                Player.defense_power = 10000;

                            Player.intelligence = 0;
                        }
                        else if (Player.opportunity_card == 4)
                        {
                            Player.intelligence*=2;
                            if (Player.intelligence >= 10000)
                                    Player.intelligence = 10000;
                        }
                        // if opportunity card is 5
                        // the card is needed to process here
                        else if (Player.opportunity_card == 5)
                        {
                            Player.current_progress = "D1";
                            current_mon = &Player.town_d.small_mon_1;
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                        }
                        after_fighting_graphics(Player);
                        if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                        after_fighting_logic(Player);
                        return;
                        break;
                }
                break;
            case 'D':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        Player.current_progress = "D1";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '1':
                        Player.current_progress = "D2";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '2':
                        Player.current_progress = "S0";
                        Player.defeat_d = true;
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        opportunity_card_logic(Player);
                        if (Player.opportunity_card == 1)
                        {
                            Player.health*=0.9;
                        }
                        if (Player.opportunity_card == 2)
                        {
                            Player.strength*=2;
                            if (Player.strength >= 10000)
                                Player.strength = 10000;
                                  
                            Player.health*=2;
                            if (Player.health >= 1000)
                                Player.health = 1000;
                                  
                            Player.defense_power*=2;
                            if (Player.defense_power >= 10000)
                                Player.defense_power = 10000;

                            Player.intelligence = 0;
                        }
                        else if (Player.opportunity_card == 4)
                        {
                            Player.intelligence*=2;
                            if (Player.intelligence >= 10000)
                                    Player.intelligence = 10000;
                        }
                        after_fighting_graphics(Player);
                        if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                        after_fighting_logic(Player);
                        return;
                        break;
                }
                break;
            case 'S':
                Player.current_progress = "S1";
                (*current_mon).defeated = true;
                winning_graphics();
                exit(0);
            }
        }
        caculate_monster_anger_level((*current_mon), mon_old_health, (*current_mon).health);
        fight_graphics(Player);
        fight_logic(Player);
        return;
    }
    else if (user_input == "2")
    {
        fight_potion_gra(Player);
        fight_potion_log(Player);
        fight_graphics(Player);
        fight_logic(Player);
        return;
    }
    else if (user_input == "3" )
    {
        if (Player.magic_size == 0) 
        {
            cout << "Error. You don't have any magic." << endl;
            fight_graphics(Player);
            fight_logic(Player);
            return;
        }
        
        monster * current_mon;
         switch ( Player.current_progress[0] )
        {
            case 'A':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_a.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_a.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_a.duke;
                        break;
                }
                break;
            case 'B':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_b.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_b.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_b.duke;
                        break;
                }
                break;
            case 'C':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_c.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_c.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_c.duke;
                        break;
                }
                break;
            case 'D':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        current_mon = &Player.town_d.small_mon_1;
                        break;
                    case '1':
                        current_mon = &Player.town_d.small_mon_2;
                        break;
                    case '2':
                        current_mon = &Player.town_d.duke;
                        break;
                }
                break;
            case 'S':
                current_mon = &Player.boss;
                break;
            }
        
        // display magic
        fight_magic_gra();

        if (Player.opportunity_card == 1)
        {
            use_opportunity_card(Player, (*current_mon));
            Player.opportunity_card = 0;
        }
        
        int mon_old_health = (*current_mon).health;
        string user_input;
        getline(cin, user_input);
        if (user_input == "1")
        {
            if (Player.magic[1] == 0) 
            {
                cout << "Error. You don't have this magic." << endl;
                fight_graphics(Player);
                fight_logic(Player);
                return;
            }
            calculate_health((*current_mon).health, (*current_mon).defense_power, Player.strength);
            caculate_monster_anger_level((*current_mon), mon_old_health, (*current_mon).health);

            Player.magic[1]--;
            Player.magic_size--;
        }
        else if (user_input == "2")
        {
            if (Player.magic[2] == 0) 
            {
                cout << "Error. You don't have this magic." << endl;
                fight_graphics(Player);
                fight_logic(Player);
                return;
            }
            int mon_old_health = (*current_mon).health;
        
            int real_damage = calculate_monster_strength((*current_mon));

            // damage to player
            calculate_health(Player.health, Player.defense_power, real_damage);

            // damage to monster
            int player_new_strength = Player.strength * 1.5;
            calculate_health((*current_mon).health, (*current_mon).defense_power, player_new_strength);
            
            caculate_monster_anger_level((*current_mon), mon_old_health, (*current_mon).health);

            Player.magic[2]--;
            Player.magic_size--;
        }

        if ((*current_mon).health == 0)
        {
            switch ( Player.current_progress[0] )
            {
                case 'A':
                    switch ( Player.current_progress[1] )
                    {
                        case '0':
                            Player.current_progress = "A1";
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                            after_fighting_graphics(Player);
                            after_fighting_logic(Player);
                            return;
                            break;
                        case '1':
                            Player.current_progress = "A2";
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                            after_fighting_graphics(Player);
                            after_fighting_logic(Player);
                            return;
                            break;
                        case '2':
                            Player.current_progress = "B0";
                            (*current_mon).defeated = true;
                            Player.defeat_a = true;
                            after_winning_index_increment(Player);
                            opportunity_card_logic(Player);
                            if (Player.opportunity_card == 1)
                            {
                                Player.health*=0.9;
                            }
                            else if (Player.opportunity_card == 2)
                            {
                                Player.strength*=2;
                                if (Player.strength >= 10000)
                                    Player.strength = 10000;
                                      
                                Player.health*=2;
                                if (Player.health >= 1000)
                                    Player.health = 1000;
                                      
                                Player.defense_power*=2;
                                if (Player.defense_power >= 10000)
                                    Player.defense_power = 10000;
    
                                Player.intelligence = 0;
                            }
                            else if (Player.opportunity_card == 4)
                            {
                                Player.intelligence*=2;
                                if (Player.intelligence >= 10000)
                                        Player.intelligence = 10000;
                            }
                            else if (Player.opportunity_card == 5)
                            {
                                Player.current_progress = "B1";
                                current_mon = &Player.town_b.small_mon_1;
                                (*current_mon).defeated = true;
                                after_winning_index_increment(Player);
                            }
                            after_fighting_graphics(Player);
                            if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                            after_fighting_logic(Player);
                            return;
                            break;
                    }
                    break;
            case 'B':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        Player.current_progress = "B1";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '1':
                        Player.current_progress = "B2";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '2':
                        Player.current_progress = "C0";
                        (*current_mon).defeated = true;
                        Player.defeat_b = true;
                        after_winning_index_increment(Player);
                        opportunity_card_logic(Player);

                        if (Player.opportunity_card == 1)
                        {
                            Player.health*=0.9;
                        }
                        else if (Player.opportunity_card == 2)
                        {
                            Player.strength*=2;
                            if (Player.strength >= 10000)
                                Player.strength = 10000;
                                  
                            Player.health*=2;
                            if (Player.health >= 1000)
                                Player.health = 1000;
                                  
                            Player.defense_power*=2;
                            if (Player.defense_power >= 10000)
                                Player.defense_power = 10000;

                            Player.intelligence = 0;
                        }
                        else if (Player.opportunity_card == 4)
                        {
                            Player.intelligence*=2;
                            if (Player.intelligence >= 10000)
                                    Player.intelligence = 10000;
                        }
                        // if opportunity card is 5
                        // the card is needed to process here
                        else if (Player.opportunity_card == 5)
                        {
                            Player.current_progress = "C1";
                            current_mon = &Player.town_c.small_mon_1;
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                        }
                        after_fighting_graphics(Player);
                        if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                        after_fighting_logic(Player);
                        return;
                        break;
                }
                break;
            case 'C':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        Player.current_progress = "C1";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '1':
                        Player.current_progress = "C2";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '2':
                        Player.current_progress = "D0";
                        (*current_mon).defeated = true;
                        Player.defeat_c = true;
                        after_winning_index_increment(Player);
                        opportunity_card_logic(Player);

                        if (Player.opportunity_card == 1)
                        {
                            Player.health*=0.9;
                        }
                        else if (Player.opportunity_card == 2)
                        {
                            Player.strength*=2;
                            if (Player.strength >= 10000)
                                Player.strength = 10000;
                                  
                            Player.health*=2;
                            if (Player.health >= 1000)
                                Player.health = 1000;
                                  
                            Player.defense_power*=2;
                            if (Player.defense_power >= 10000)
                                Player.defense_power = 10000;

                            Player.intelligence = 0;
                        }
                        else if (Player.opportunity_card == 4)
                        {
                            Player.intelligence*=2;
                            if (Player.intelligence >= 10000)
                                    Player.intelligence = 10000;
                        }
                        // if opportunity card is 5
                        // the card is needed to process here
                        else if (Player.opportunity_card == 5)
                        {
                            Player.current_progress = "D1";
                            current_mon = &Player.town_d.small_mon_1;
                            (*current_mon).defeated = true;
                            after_winning_index_increment(Player);
                        }
                        after_fighting_graphics(Player);
                        if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                        after_fighting_logic(Player);
                        return;
                        break;
                }
                break;
            case 'D':
                switch ( Player.current_progress[1] )
                {
                    case '0':
                        Player.current_progress = "D1";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '1':
                        Player.current_progress = "D2";
                        (*current_mon).defeated = true;
                        after_winning_index_increment(Player);
                        after_fighting_graphics(Player);
                        after_fighting_logic(Player);
                        return;
                        break;
                    case '2':
                        Player.current_progress = "S0";
                        (*current_mon).defeated = true;
                        Player.defeat_d = true;
                        after_winning_index_increment(Player);
                        opportunity_card_logic(Player);
                        if (Player.opportunity_card == 1)
                        {
                            Player.health*=0.9;
                        }
                        else if (Player.opportunity_card == 2)
                        {
                            Player.strength*=2;
                            if (Player.strength >= 10000)
                                Player.strength = 10000;
                                  
                            Player.health*=2;
                            if (Player.health >= 1000)
                                Player.health = 1000;
                                  
                            Player.defense_power*=2;
                            if (Player.defense_power >= 10000)
                                Player.defense_power = 10000;

                            Player.intelligence = 0;
                        }
                        else if (Player.opportunity_card == 4)
                        {
                            Player.intelligence*=2;
                            if (Player.intelligence >= 10000)
                                    Player.intelligence = 10000;
                        }
                        after_fighting_graphics(Player);
                        if (Player.opportunity_card == 2 || Player.opportunity_card == 4 || Player.opportunity_card == 5) Player.opportunity_card = 0;
                        after_fighting_logic(Player);
                        return;
                        break;
                }
                break;
            case 'S':
                Player.current_progress = "S1";
                (*current_mon).defeated = true;
                winning_graphics();
                exit(0);
            }
        }
        caculate_monster_anger_level((*current_mon), mon_old_health, (*current_mon).health);
        fight_graphics(Player);
        fight_logic(Player);
        return;
    }
    else if (user_input == "4")
    {
        ingame_menu_graphics();
        ingame_menu_logic(Player);
        return;
    }
    else
    {
        cout << "Invalid input. Please enter again. " << endl;
        cout << endl;
        fight_logic(Player);
        return;
    }
    return;
}

// Purpose: to process the logic 
// after winning the monsters
// Input: Player with player data type
void after_fighting_logic(player & Player)
{
    string user_input;
    getline(cin, user_input);
    if (user_input == "1")
    {
        fight_graphics(Player);
        fight_logic(Player);
        return;
    }
    else if (user_input == "2")
    {
        ingame_menu_graphics();
        ingame_menu_logic(Player);
        return;
    }
    else if (user_input == "3")
    {
        ingame_exit_game_menu_graphics();
        ingame_exit_game_menu_logic(Player);
        return;
    }
    else
    {
        cout << "Invalid input. Please enter again. " << endl;
        cout << "Your Input: ";
        after_fighting_logic(Player);
        return;
    }
}
