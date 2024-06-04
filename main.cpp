#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>

#include "User_Interface.h"
#include "check_index.h"
#include "In_game_user_interface.h"
#include "index_calculator.h"
#include "opportunity_card.h"
#include "file_io.h"

using namespace std;


int main() 
{
    player Player;
    game_open_animation_graphics();
    initial_game_load_menu_graphics();
    Player = initial_game_load_menu_logic();
    ingame_menu_graphics();
    ingame_menu_logic(Player);
    return 0;
}
