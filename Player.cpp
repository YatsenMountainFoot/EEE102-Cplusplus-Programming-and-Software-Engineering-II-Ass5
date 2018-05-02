#include "Player.h"
#include <iomanip>
using namespace std;

Player::Player() {

}

Player::Player(Account& s) {
	this->status = s;
}

bool Player::hitCard(Cards& cardsFate) {
	string suit = "0";		//suit
	int points = 0;			//points
	string pointsToString = "";
	
	if (totalPoints < 21) {
		suit = cardsFate.hitCard().suit;		// Get the card's suit 
		points = cardsFate.hitCard().points;	//calculate the card's points
		switch (points) {
		case 1:
			numOfA++;
			pointsToString = 'A';
			if (totalPoints + 11 <= 21) // if count A as 11 points leads to bust, count A as 1
				points = 11;
			break;
		case 2:
			pointsToString = '2';
			break;
		case 3:
			pointsToString = '3';
			break;
		case 4:
			pointsToString = '4';
			break;
		case 5:
			pointsToString = '5';
			break;
		case 6:
			pointsToString = '6';
			break;
		case 7:
			pointsToString = '7';
			break;
		case 8:
			pointsToString = '8';
			break;
		case 9:
			pointsToString = '9';
			break;
		case 10:
			pointsToString = "10";
			break;
		case 11:
			pointsToString = 'J';
			points = 10;
			break;
		case 12:
			pointsToString = 'Q';
			points = 10;
			break;
		case 13:
			pointsToString = 'K';
			points = 10;
			break;
		default:
			break;
		}
		totalPoints += points;
		if (totalPoints > 21 && numOfA > 0) {
			do {
				totalPoints -= 10;
				numOfA--;
			} while (totalPoints > 21 && numOfA != 0);
		}
		cout << setw(10) << suit << setw(4) << pointsToString << setw(4) <<points << " total points = " << setw(6) << totalPoints << endl;
		return true;
	}
	else{
		cout << endl << "Cannot hit more, already Bust!";
		return false;
	}
}
bool Player::stand() {
	return true;
}
bool Player::isLost() {
	return gameLost;
}

void Player::reset() {
	this->numOfA = 0;
	this->totalPoints = 0;
	this->betAmount = 0;
	this->gameLost = false;
}

void Player::isBust() {
	if ( totalPoints > 21)		// total points > 21, player bust
	{
		cout << this->status.getAccountName() << " is Lost." << endl;
		system("pause");
		gameLost = true;	// give the flag of lost value 
	}
}

void Player::AI(Player& p, Cards& cd) {
	this->betAmount = p.betAmount;
	cout << "Dealer's Turn" << endl;
	cout << "Dealer's second card: " << endl;
	this->hitCard(cd);
	if (this->isBlackJack()) {
		setResults(p, true, *this, false);
	}
	else{
	if (!p.isLost()) {
		while ((!this->isLost()) && (this->totalPoints < 17 || this->totalPoints < p.totalPoints)) {
			this->hitCard(cd);
			this->isBust();
		}
		if (!this->isLost() && this->totalPoints > p.totalPoints)
			p.gameLost = true;
	}
	else
		cout << "Haha, idot! You bust yourself!" << endl;
	}
}

bool Player::placeBet() {
	if (this->status.getAccountDeposit() <= 0){
		cout << "You are bankrupt! Unable to place bet!" << endl;
		return false;
	}
	if (this->status.getAccountDeposit() > 0){
		do{
		cout <<"You have " << this->status.getAccountDeposit() << " Please place your bet: ";
			do{
			betAmount = intParser();
			if (!(betAmount > 0))
				cout << "Bet must be a posivie number! ReEnter bet: ";
			} while (!(betAmount > 0));
		if (betAmount > this->status.getAccountDeposit())
			cout << "You are not so rich! Bet less!" << endl;
		} while (betAmount > this->status.getAccountDeposit());
		return true;
	}
}
bool Player::isBlackJack() {
	if (this->totalPoints == 21){
		cout << "BLACK JACK!" << endl;
		return true;
	}
	else
		return false;

}
void Player::increaseBet() {
	int betInc = 0;
	if (this->status.getAccountDeposit() == this->betAmount) {
		cout << "You have placed all your wealth! Sink or swim!" << endl;
	}
	if (this->status.getAccountDeposit() > this->betAmount) {
		cout << "Place the bet do you want to increase:";
		do {
			betInc = intParser();
			if (!(betInc > 0))
				cout << "Bet increase must be a posivie number! ReEnter bet inc: ";
		} while (!(betInc > 0));
		
		if (this->status.getAccountDeposit() >= (this->betAmount + betInc))
			this->betAmount += betInc;
		else
			cout << "You are not rich enough to place " << betInc << " points!"<< endl;
	}

}
void Player::loseBet() {
	
	this->status.loseBet(betAmount);
}
void Player::winBet() {
	this->status.winBet(betAmount);
}
Account Player::getAccount()const {
	return this->status;
}
void bjResults(Player& p1, Player& p2) {
	if(p2.totalPoints == 21){
		p1.gameLost = false;
		p2.gameLost = false;
	}
	if (p2.totalPoints < 21) {
		p1.gameLost = false;
		p2.gameLost = true;
	}
}
void setResults(Player& p1, bool a, Player& p2, bool b) {
	p1.gameLost = a;
	p2.gameLost = b;
}
void showInfo(Player& p1, Player& p2) {
	cout << "##############################################################" << endl;
	cout << "# Player" << setw(10) << p1.status.getAccountID() << "   Name " << setw(10) << p1.status.getAccountName()
		<< "  # Dealer" << setw(10) << p2.status.getAccountID() << "   Name " << setw(10) << p2.status.getAccountName() << " #" << endl;
	cout << "# Gender " << setw(6) << p1.status.getAccountGender()
		<< " | Region " << setw(12) << p1.status.getAccountRegion()
		<< "  # Gender " << setw(6) << p2.status.getAccountGender() 
		<< " | Region " << setw(12) << p2.status.getAccountRegion() << " #" << endl;
	cout << "# Wealth " << setw(6) << p1.status.getAccountDeposit()
		<< " | NumberOfGames " << setw(5) << p1.status.getAccountNumOfGames()
		<< "  # Wealth " << setw(6) << p2.status.getAccountDeposit()
		<< " | NumberOfGames " << setw(5) << p2.status.getAccountNumOfGames() << " #" << endl;
	cout << "# Motto " << setw(29) << p1.status.getAccountMotto()
		<< "  # Motto " << setw(29) << p2.status.getAccountMotto()
		<< " #" << endl;
	cout << "--------------------------------------------------------------" << endl;
	//bet display
	cout << "##############################################################" << endl;
}

void showAchievemnet(Player& p) {
	cout << "##############################################################" << endl;
	cout << "# Player" << setw(10) << p.status.getAccountID() << "   Name " << setw(10) << p.status.getAccountName() << "  #"<<endl;
	cout << "# Gender " << setw(6) << p.status.getAccountGender()
		<< " | Region " << setw(12) << p.status.getAccountRegion() <<" #"<< endl;
	cout << "# Wealth " << setw(6) << p.status.getAccountDeposit()
		<< " | NumberOfGames " << setw(5) << p.status.getAccountNumOfGames() <<" #" << endl;
	cout << "# Motto " << setw(29) << p.status.getAccountMotto()
		<< " #" << endl;
	cout << "--------------------------------------------------------------" << endl;
	//bet display
	cout << "##############################################################" << endl;
}

void Player::gamePlayed() {
	this->status.gamePlayed();
}

int intParser() {
	int temp;
	bool isErr = true;
	//while (input failed) or (input succeeded with redundant tail, clear steream and repeat)
	while ((isErr = !(cin >> temp)) || (!isErr && cin.get() != '\n')) {
		if (isErr) { cin.clear(); }
		//reset cin
		while (cin.get() != '\n')//clear a whole line
			continue;
		cout << "\t\tPlease enter an integer: ";
	}
	return temp;
}

