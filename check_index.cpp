#include <iostream>
#include "check_index.h"
using namespace std;

// checking the indexes of player
// To check if the value of strength of player is within the range or not
void check_strength(int & val)
{
    if (val > 10000)
        val = 10000;
    else if (val < 0)
        val = 0;
    return;
}

// To check if the value of defense power of player is within the range or not
void check_defense_power(int & val)
{
    if (val > 1000)
        val = 1000;
    else if (val < 0)
        val = 0;
    return;
}

// To check if the value of intelligence of player is within the range or not
void check_intelligence(int & val)
{
    if (val > 10000)
        val = 10000;
    else if (val < 0)
        val = 0;
    return;
}

// To check if the value of health of player is within the range or not
void check_health(int & val)
{
    if (val > 1000)
        val = 1000;
    else if (val < 0)
        val = 0;
    return;
}
