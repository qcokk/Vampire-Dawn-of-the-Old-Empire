#include <iostream>
#include <cstdlib>
#include <ctime>
#include "main.h"
#include "opportunity_card.h"
using namespace std;

// to add an used card from the trash opportunity card deck
void add_trash_card_deck (Node * & deck, int & size, int card)
{
        Node * p = new Node;
        p->card = card;
        p->next = deck;
        deck = p;
        size ++;
}

// generate the following layout when the player gets a opportunity card
void opportunity_card_graphics(player & Player)
{
    
    cout << "You have got the following opportunity card:" << endl;

    if (Player.opportunity_card == 1)
    {
        cout << "********OPPORTUNITY CARD**********" << endl;
        cout << "In the next round, you can..." << endl;
        cout << "Reduce the monster’s health by 50%" << endl;
        cout << "But..." << endl;
        cout << "Your health will be reduced by 10%" << endl;
        cout << "**********************************" << endl;
    }
    if (Player.opportunity_card == 2)
    {
        cout << "****************OPPORTUNITY CARD*******************" << endl;
        cout << "In the next round, you can..." << endl;
        cout << "Double all values in the next round" << endl;
        cout << "But..." << endl;
        cout << "Your intelligence will be reduced to 0" << endl;
        cout << "***************************************************" << endl;
    }
    if (Player.opportunity_card == 3)
    {
        cout << "*************OPPORTUNITY CARD*************" << endl;
        cout << "In the next round, you can:" << endl;
        cout << "Use any magic you want in the next round!!" << endl;
        cout << "WARNING: Choose “Combat” in your next" << endl;
        cout << "fight, else this card will become invalid" << endl;
        cout << "******************************************" << endl;
    }
    if (Player.opportunity_card == 4) 
    {
        cout << "******************OPPORTUNITY CARD*******************" << endl;
        cout << "In the next round, you can:" << endl;
        cout << "Double your intelligence index the final intelligence" << endl;
        cout << "has not reach the maxmium" << endl;
        cout << "*****************************************************" << endl;
    }
    if (Player.opportunity_card == 5)
    {
        cout << "**********************OPPORTUNITY CARD********************" << endl;
        cout << "In the next round, you can..." << endl;
        cout << "Freeze one small monster in a town (you only need to fight" << endl;
        cout << "for one small monster in the next town!!)" << endl;
        cout << "And..." << endl;
        cout << "Your strength and defense power will increase accordingly" << endl;
        cout << "WARNING: This card will become invalid when the target is " << endl;
        cout << "not small monster." << endl;
        cout << "**********************************************************" << endl;
    }

    return;
}


// randomly generate an opportunity card for the player that havn't been used before
void opportunity_card_logic(player & Player)
{                       
          
  
    int card;
    Node * current = Player.trash_opportunity_card_deck;
    srand(time(NULL));
    card = rand() % 5 + 1; 
    bool used = false;
    for (int i=0;i<Player.trash_deck_size;++i)
    {
      if (Player.trash_opportunity_card_deck->card == card)
      {
        used = true;
        break;
      }
      current = Player.trash_opportunity_card_deck->next;
    }
  
  while (used)
    {
      srand(time(NULL));
      card = rand() % 5 + 1; 
      used = false;
      for (int i=0;i<Player.trash_deck_size;++i)
    {
      if (Player.trash_opportunity_card_deck->card == card)
      {
        used = true;
        break;
      }
      current = Player.trash_opportunity_card_deck->next;
    }
    }
  if (card == 1) Player.opportunity_card = 1;
  else if (card == 2) Player.opportunity_card = 2;
  else if (card == 3) Player.opportunity_card = 3;
  else if (card == 4) Player.opportunity_card = 4;
  else if (card == 5) Player.opportunity_card = 5;
    add_trash_card_deck(Player.trash_opportunity_card_deck,     Player.trash_deck_size, Player.opportunity_card);
  return;
}

// using the opportunity card
void use_opportunity_card(player & Player, monster & Monster)
{
  if (Player.opportunity_card == 1)
  {
    Monster.health*=0.5;
  }
  return;
}
