#include "Cards.h"

Cards::Cards() {
	
	srand((unsigned)time(NULL));
	 
	for (int i = 0; i < MAX; i++){
		int temp = rand()%52;	// 0...51
		int repetitionFlag = false;

		for (int j = 0; j < i; j++){
			if (cardsHit[j] == temp)
				repetitionFlag = true;
		}

		if (!repetitionFlag)
			cardsHit[i] = temp;
		else
			i--;
	}
	//for (int i = 0; i < MAX; i++) // cheater & checker
		//std::cout << cardsHit[i] << "\t" ;
	std::cout << std::endl;
}

card Cards::hitCard() {
	string suit;
	card cd;
		switch ((int)cardsHit[numOfHit]/13)
		{
		case spade:
			suit = "spade";
			break;
		case heart:
			suit = "heart";
			break;
		case diamond:
			suit = "diamond";
			break;
		case club:
			suit = "club";
			break;
		default:
			break;
		}
		
		cd.points = (cardsHit[numOfHit] % 13) + 1;
		cd.suit = suit;
		numOfHit++;

		return cd;
}
	
