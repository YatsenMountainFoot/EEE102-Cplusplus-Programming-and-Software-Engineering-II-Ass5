#ifndef _ACCOUNT
#define _ACCOUNT

#include <string>

using std::string;
const int startingDeposit = 100;

class Account {
private:
	string accountID;		//use phone number as ID
	string accountName;//player's name
	string accountPIN;	//personal identification number
	string accountGender = "Male";
	string accountRegion = "Jiang Su";
	string accountMotto = "NeverSayDie";
	int accountDeposit = startingDeposit;//account balance
	int accountNumOfGames = 0;

public:
	~Account();
	Account();
	Account(string id, string name, string pin);	//Construct Account object BY creating
	Account(string id, string name, string pin, string gender, string region, string motto);
	Account(string id, string name, string pin, string accountGender, string accountRegion, string accountMotto, int depo, int numOfGames);//Construct Account object BY reading history
	string getAccountID()const;
	string getAccountName()const;
	string getAccountPIN()const;
	string getAccountGender()const;
	string getAccountRegion()const;
	string getAccountMotto()const;
	int getAccountDeposit()const;
	int getAccountNumOfGames()const;
	void loseBet(int x);
	void winBet(int x);
	void gamePlayed();
	
};

#endif