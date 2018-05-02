
#include "Account.h"
#include <iostream>

Account::~Account() {
	;
}
Account::Account() {
	accountID = "00000000";
	accountName = "TestAccount";
	accountPIN = "888888";
	accountDeposit = 100;
	accountNumOfGames = 0;
}
//Construct Account object BY creating
Account::Account(string id, string name, string pin) {
	accountID = id;
	accountName = name;
	accountPIN = pin;
	accountDeposit = 100;
	accountNumOfGames = 0;
}

//Construct Account object BY reading history
Account::Account(string id, string name, string pin, string gender, string region, string motto) {
	accountID = id;
	accountName = name;
	accountPIN = pin;
	accountGender = gender;
	accountRegion = region;
	accountMotto = motto;
	accountDeposit = 100;
	accountNumOfGames = 0;
}
Account::Account(string id, string name, string pin, string gender, string region, string motto, int depo = 100, int numOfGames = 0){
	accountID = id;
	accountName = name;
	accountPIN = pin;
	accountGender = gender;
	accountRegion = region;
	accountMotto = motto;
	accountDeposit = depo;
	accountNumOfGames = numOfGames;
}
string Account::getAccountID()const {
	return accountID;
}
string Account::getAccountName()const {
	return accountName;
}
string Account::getAccountPIN()const {
	return accountPIN;
}
int Account::getAccountDeposit()const {
	return accountDeposit;
}
int Account::getAccountNumOfGames()const {
	return accountNumOfGames;
}
string Account::getAccountGender()const {
	return accountGender;
}
string Account::getAccountRegion()const {
	return accountRegion;
}
string Account::getAccountMotto()const {
	return accountMotto;
}
 
void Account:: loseBet(int x) {
	accountDeposit -= x;
}

void Account::winBet(int x) {
	accountDeposit += x;
}

void Account::gamePlayed() {
	accountNumOfGames++;
}
