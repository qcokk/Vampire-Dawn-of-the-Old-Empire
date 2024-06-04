//---include required header files---
#include "User_Interface.h"
#include "In_game_user_interface.h"
#include "main.h"
#include "check_index.h"
#include "index_calculator.h"
#include "file_io.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
//-----------------------------------

using namespace std;

//---start of ruler functions---

// function: standard divider to divide lines (hyphen '-' version)
void print_ruler_divider_hyphen_version()
{
    cout << "-----------------------------------------------------------------" << endl;
}

// function: standard divider to divide lines (star '*' version)
void print_ruler_divider_star_version()
{
    cout << "*****************************************************************" << endl;
}

//---end of ruler functions---

//---start of animation functions---

// from the data of old game status manager file
// to a list of files to be selected by the user
// assume the book consists of at least 1 record
void file_graphics(vector<string> book)
{
    cout << endl;
    print_ruler_divider_hyphen_version();
    cout << "Game Save Manager (Max Storage = 5)" << endl;
    print_ruler_divider_hyphen_version();
    cout << "No. | Date created | Game Progress" << endl;
    for (int i = 0; i < book.size(); i++)
    {
        file_book_graphics(book[i]);
    }
    print_ruler_divider_hyphen_version();
    cout << "Yout Input: (e.g. 1) ";
    return;
}

// change the book content to readable contents
void file_book_graphics(string str)
{
    istringstream iss(str);
    string num, date_created_yr, date_created_mon, date_created_day;
    string status, trash;
    iss >> trash >> trash >> num;
    iss >> trash >> trash >> date_created_mon >> date_created_day;
    iss >> trash >> date_created_yr >> trash >> status;

    if (date_created_mon == "Jan") date_created_mon = "01";
    else if (date_created_mon == "Feb") date_created_mon = "02";
    else if (date_created_mon == "Mar") date_created_mon = "03";
    else if (date_created_mon == "Apr") date_created_mon = "04";
    else if (date_created_mon == "May") date_created_mon = "05";
    else if (date_created_mon == "Jun") date_created_mon = "06";
    else if (date_created_mon == "Jul") date_created_mon = "07";
    else if (date_created_mon == "Aug") date_created_mon = "08";
    else if (date_created_mon == "Sep") date_created_mon = "09";
    else if (date_created_mon == "Oct") date_created_mon = "10";
    else if (date_created_mon == "Nov") date_created_mon = "11";
    else if (date_created_mon == "Dec") date_created_mon = "12";

    if (date_created_day.length() == 1) date_created_day = "0" + date_created_day;

    cout << num << " | " << date_created_day << "/" << date_created_mon;
    cout << "/" << date_created_yr << "   | ";

    int duke, boss;
    if (status[0] == 'A')
    {
        duke = 0;
        boss = 0;
    }
    else if (status[0] == 'B')
    {
        duke = 1;
        boss = 0;
    }
    else if (status[0] == 'C')
    {
        duke = 2;
        boss = 0;
    }
    else if (status[0] == 'D')
    {
        duke = 3;
        boss = 0;
    }
    else if (status[0] == 'S')
    {
        if (status[1] == '0')
        {
            duke = 4;
            boss = 0;
        }
        else if (status[1] == '1')
        {
            duke = 4;
            boss = 1;
        }
    }

    //cout << "Status: " << status << endl;
    cout << "Duke (" << duke << "/4) & Boss (" << boss << "/1)" << endl;
    return;
}


// Area: Game opening (everytime)
void game_open_animation_graphics()
{
    //cout << setfill('*');
    //cout << setw(65) << "" << endl;
    //cout << "01234567890123456789012345678901234567890123456789012345678901234" << endl;
    print_ruler_divider_star_version();
    this_thread::sleep_for(chrono::milliseconds(200));
    print_ruler_divider_star_version();
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "              ******        ******          *****                " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "              **    **      **    **      **     **              " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "              **    **      **    **    **                       " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "              ******        ******      **                       " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "              **   **       **          **     ****              " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "              **    **      **            **     **              " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "              **      **    **              *****                " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    print_ruler_divider_star_version();
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "            **                                     **            " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "          **                                         **          " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "        ** Welcome to \"Vampire: Dawn of the Old Empire\" **        " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "          **                                         **          " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "            **                                     **            " << endl;
    this_thread::sleep_for(chrono::milliseconds(200));
    print_ruler_divider_star_version();
    this_thread::sleep_for(chrono::milliseconds(200));
    cout << "***Press enter to continue***";
    cin.ignore();
    cout << endl;
    return;
}

// Area: Winning 
void winning_graphics()
{
    cout << setfill('*');
    print_ruler_divider_star_version();
    cout << setw(29) << "";
    cout << "YOU WIN";
    cout << setw(29) << "" << endl;
    print_ruler_divider_star_version();
    return;
}

// Area: Losing
void losing_graphics()
{
    cout << setfill('*');
    print_ruler_divider_star_version();
    cout << setw(28) << "";
    cout << "GAME OVER";
    cout << setw(28) << "" << endl;
    print_ruler_divider_star_version();
    return;
}

// Area: Normal Exit
void exiting_graphics()
{
    cout << setfill('*');
    print_ruler_divider_star_version();
    cout << setw(29) << "";
    cout << "BYE BYE";
    cout << setw(29) << "" << endl;
    print_ruler_divider_star_version();
    return;
}

// Area: New Game Story
void game_story_load_graphics()
{
    // load story
    string s = "Long long time ago, there was an empire called \"United Kingdom of Prosea\", civilians inside were all having a wonderful life every day.";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
    cout << endl;
    cout << "***Press enter to continue***";
    cin.ignore();
    cout << endl;
    s = "It was supposed to continue forever until a dark night, a triad's head occasionally found and opened a pandora box which released an undead vampire original to the world.";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
    cout << endl;
    cout << "***Press enter to continue***";
    cin.ignore();
    cout << endl;
    s = "After that, he occupied the entire country and built his own vampire country called \"Bloodtopia\".";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
        cout << endl;
        cout << "***Press enter to continue***";
        cin.ignore();
        cout << endl;
    s = "Another 4 vampires were born to support operating the country and each of them creates their own towns.";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
        cout << endl;
        cout << "***Press enter to continue***";
        cin.ignore();
        cout << endl;
    s = "The vampire dukes chose some potential human, and turned them to weakened-vampires. ";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
        cout << endl;
        cout << "***Press enter to continue***";
        cin.ignore();
        cout << endl;
    s = "The vampire god instructed the 4 vampire dukes to catch children from their corresponding towns to supply fresh blood for the god.";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
        cout << endl;
        cout << "***Press enter to continue***";
        cin.ignore();
        cout << endl;
    s = "You, as the only descendant of the royal family of the old empire, are a courageous warrior who wants to save the children and liberate the old empire. ";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
        cout << endl;
        cout << "***Press enter to continue***";
        cin.ignore();
        cout << endl;
    s = "After today, you will start your journey to fight with the vampire power by progressively strengthening your power by various adventures. Good luck!!";
    for (int i = 0; i < s.length(); ++i)
        {
            cout << s[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(30));
        }
    cout << endl;
    cout << "***Press enter to continue***";
    cin.ignore();
    cout << endl;
}

//---end of animation functions---

//---start of menu function---

// Area: Initial Game load Menu
void initial_game_load_menu_graphics()
{
    print_ruler_divider_hyphen_version();
    cout << "User Profile Menu" << endl;
    print_ruler_divider_hyphen_version();
    cout << "1. Start new game" << endl;
    cout << "2. Load old game save" << endl;
    cout << "3. Exit" << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your input: ";
    return;
}

// Area: Enter Game Menu
void ingame_menu_graphics()
{
    cout << endl;
    cout << "--------------------- Welcome to the town! ---------------------";
    cout << endl;
    cout << "What do you want to do?" << endl;
    cout << endl;
    cout << "1. Display Status" << endl;
    cout << "2. Display Map" << endl;
    cout << "3. Go to the Store" << endl;
    cout << "4. Go to Fight with the Vampires" << endl;
    cout << "5. Exit" << endl;
    cout << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your Input: ";
    return;
}

// Area: Exit Game Manu
void ingame_exit_game_menu_graphics()
{
    print_ruler_divider_hyphen_version();
    cout << "Exit Menu" << endl;
    print_ruler_divider_hyphen_version();
    cout << "1. Resume" << endl;
    cout << "2. Confirm to Exit" << endl;
    print_ruler_divider_hyphen_version();
    cout << "Your input: ";
    return;
}

//---end of menu function---

//---start of logics functions

// output the file name to be opened
string file_logic()
{
    vector<string> temp;
    string file_name;
    temp = file_manager();
    string user_input;
    getline(cin, user_input);
    if (user_input != "1" && user_input != "2" && user_input != "3" && user_input != "4" && user_input != "5")
    {
        cout << endl;
        cout << "Invalid input. Please enter again. " << endl;
        cout << endl;
        file_graphics(temp);
        return file_logic();
    }
    else
    {
        int num = stoi(user_input);
        istringstream iss(temp[num-1]);
        iss >> file_name;
    }
    return file_name;
}


// To process the initial game load menu
player initial_game_load_menu_logic()
{
    player Player;
    
    string user_input;
    getline( cin , user_input );
    
    if ( user_input == "1" ) 
    {    
        cout << endl;

        // start new game
        string name;
        cout << "Insert your Name: ";
        getline( cin , name );
        
        cout << endl;
        
        cout << "Hello " << name << "! Here we start your adventure!!" << endl;
        cout << endl;
        
        Player = initial_player_creation(name);
        
        // Introduce our game story
        game_story_load_graphics();

        // Show some options for the player to choose
        // for performing various actions
        ingame_menu_graphics();
        ingame_menu_logic(Player);
    }
    else 
    {
        if ( user_input == "2" )
        {
            // temp : the data extracted from the 
            // old file manager file
            vector<string> temp;
            temp = file_manager();
            if ( temp.size() < 1 )
            {
                cout << "Old game save not found." << endl;
                initial_game_load_menu_graphics();
                return initial_game_load_menu_logic();
            }
            else
            {
                file_graphics( temp );
                string file_name;
                file_name = file_logic();
                load_files(Player, file_name);
                return Player;
            }
        }
        else 
        {
            if ( user_input == "3" )
            {
                // declare a string to confirm the exit decision
                string confirm_input;
                while ( true )
                {
                    cout << "Confirm to Exit? (Y/N) ";
                    getline( cin , confirm_input );
                    if ( confirm_input == "Y" || confirm_input == "y" )
                    {
                        exiting_graphics();
                        exit(0);
                    }
                    if ( confirm_input == "N" || confirm_input == "n" )
                    {
                        initial_game_load_menu_graphics();
                        return initial_game_load_menu_logic();
                        break;
                    }
                    cout << "Invalid input. Please enter again. " << endl;
                    cout << endl;
                }
            }
            else
            {
                // input not 1 / 2 / 3
                cout << "Invalid input. Please enter again. " << endl;
                cout << endl;
                initial_game_load_menu_graphics();
                return initial_game_load_menu_logic();
            }
        }
    }
    return Player;
}

// To process the in-game menu
void ingame_menu_logic(player & Player)
{
    string user_input;
    getline(cin, user_input);
    
    if (user_input == "1")
    {
        display_graphics(Player);
        display_logic(Player);
    }
    else if (user_input == "2")
    {
        map_graphics(Player , 1);
        map_logic(Player);
    }
    else if (user_input == "3")
    {
        store_main_menu_graphics(Player);
        store_logic(Player);
    }
    else if (user_input == "4")
    {
        // fighting part
        fight_graphics(Player);
        fight_logic(Player);
    }
    else if (user_input == "5"){
        ingame_exit_game_menu_graphics();
        ingame_exit_game_menu_logic(Player);
    }
    else 
    {
        cout << "Invalid input. Please enter again. " << endl;
        cout << endl;
        cout << "Your Input: ";
        ingame_menu_logic(Player);
    }
    return;
}

// To process the in-game exit menu
void ingame_exit_game_menu_logic(player Player)
{
    string user_input;
    getline( cin , user_input );
    
    if ( user_input == "1" ) 
        cout << "Implement resume function" << endl;
    else
    {
        if ( user_input == "2" )
        {
            // declare a string to confirm the save decision
            string confirm_input;
            while ( true )
            {
                cout << "Do you Want to Save (Y/N) ";
                getline( cin , confirm_input );
                
                if ( confirm_input == "Y" || confirm_input == "y" )
                {
                    string file_name;
                    vector<string> v = file_manager();
                    if (v.size() <= 4) file_name = to_string(v.size() + 1) + "RPG.txt";
                    else if (v.size() == 5) file_name = "5RPG.txt";
                    save_file_manager(Player, v.size(), v);
                    save_files(Player, file_name);
                    cout << "Game saved successfully!" << endl;
                    exiting_graphics();
                    exit(0);
                }
                if ( confirm_input == "N" || confirm_input == "n")
                {
                    exiting_graphics();
                    exit(0);
                }
                
                cout << "Invalid input. Please enter again. " << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "Invalid input. Please enter again. " << endl;
            cout << endl;
            ingame_exit_game_menu_graphics();
            ingame_exit_game_menu_logic(Player);
            return;
        }
    }
    return;
}

//---end of logics functions


//---start of user input control functions---

void press_to_continue()
{
    cout << "...Press Enter to Continue...";
    cin.ignore();
    cout << endl;
}

//--- end of user input control functions---
