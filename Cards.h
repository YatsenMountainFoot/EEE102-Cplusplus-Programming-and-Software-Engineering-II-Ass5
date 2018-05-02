#ifndef _CARDS
#define _CARDS

#include <iostream>
#include <time.h>
#include <string>
#include <cstdlib>

using namespace std;

enum {spade, heart, diamond, club, MAX = 52};

struct card {
	string suit = "";
	int points = 0;
};

//cards for one round
class Cards {
private:
	int numOfHit = 0;
	int cardsHit[MAX]; // since 4*1 + 4* 2 + 4*3 =  4 + 8 + 12 = 22 > 21, when 12 cards must bust
public: 
	Cards();
	card hitCard();
};


#endif