#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>
#include <vector>

#include "main.h"
#include "check_index.h"
#include "In_game_user_interface.h"
#include "index_calculator.h"

void print_ruler_divider_hyphen_version();
void print_ruler_divider_star_version();

void file_graphics(vector<string> book);
void file_book_graphics(string str);

void game_open_animation_graphics();
void winning_graphics();
void losing_graphics();
void exiting_graphics();
void game_story_load_graphics();
void initial_game_load_menu_graphics();
void ingame_menu_graphics();
void ingame_exit_game_menu_graphics();

string file_logic();
player initial_game_load_menu_logic();
void ingame_menu_logic(struct player & Player);
void ingame_exit_game_menu_logic(struct player Player);

void press_to_continue();




#endif
