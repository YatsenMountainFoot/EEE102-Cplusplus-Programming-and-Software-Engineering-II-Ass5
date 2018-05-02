#ifndef _PLAYER
#define _PLAYER
#include "Account.h"
#include "Cards.h"
#include <iostream>

using namespace std;
int intParser();

class Player {
	friend void showInfo(Player& p1, Player& p2);	//show the info for both player and dealer
	friend void showAchievemnet(Player& p);			//show the achievement of player
	friend void bjResults(Player& p1, Player& p2);	//set the game result with a player's Black Jack
	friend void setResults(Player& p1, bool a, Player& p2, bool b);	//set the game result
private: 
	Account status;	// interface data class between program and file
	int numOfA = 0;	// number of A's in player's hand
	int totalPoints = 0;//total points of cards in hand
	int betAmount = 0;	//the amount of current bet
	bool gameLost = false;	// indicator of the game results
public:
	Player();	//default constructor 
	Player(Account& s);	//constructor with account data
	bool hitCard(Cards& cardsFate);	//player hit card
	bool stand();	//player stand
	void isBust();	//check and set result indicator
	void reset();	//reset player
	bool isLost();
	bool placeBet();
	void increaseBet();
	void winBet();
	void loseBet();
	void gamePlayed();
	bool isBlackJack();
	Account getAccount()const;
	void AI(Player& p, Cards& cd);
};

#endif