#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include "Account.h"
#include "Cards.h"
#include "Player.h"

using namespace std;
using std::cout;
const char* fileBJ = "blackJack.dat";
enum {exitGame, logIn, newAccount, achievement};
enum {lenAccountID=20, lenAccountName = 20, lenAccountPIN = 10, lenAccountGender = 6, lenAccountRegion = 12, lenAccountMotto =29};
char charParser();

vector<Account> testVector();
vector<Account> readAccountList(const char* filename);
void writeAccountList(const char* filename, vector<Account> x);

bool logInAndPlay(Account& x, string id, string pin);
Account oneTurnBlackJack(Account& x);
void registerNewAccount(vector<Account>& accountList);
void controlPannel(vector<Account>& accountList);
inline void eatline() { while (std::cin.get() != '\n') continue; }

struct accountFlatened {
	char accountID[lenAccountID+1];		//use phone number as ID
	char accountName[lenAccountName+1];//player's name
	char accountPIN[lenAccountPIN+1];
	char accountGender[lenAccountGender+1];
	char accountRegion[lenAccountRegion+1];
	char accountMotto[lenAccountMotto+1];
	int accountDeposit;
	int accountNumOfGames;
};

int main() {
	Account currentAccount;
	
	vector<Account> aL = readAccountList(fileBJ);
	controlPannel(aL);
	writeAccountList(fileBJ, aL);

	cout << "Done.\n";
	
	return 0;
}

void controlPannel(vector<Account>& accountList) {
	bool exitFlag = false;
	int select = 0;
	Account currentAccount;
	string ID = "";
	string PIN = "";
	bool logInSuccess = true;
	while (exitFlag != true) {
		cout << "0 = exit, 1 = LogIn, 2=CreateNewAccount, 3=AchievementList" << endl;
		select = intParser();
		switch (select) {
		case exitGame:
			exitFlag = true;
			break;

		case logIn:
			
			cout << "Please Enter your account ID: " << endl;
			getline(cin, ID);
			cout << "Please Enter your account PIN" << endl;
			getline(cin, PIN);
			for (auto &x : accountList) {
				if (logInSuccess = logInAndPlay(x, ID, PIN))
				x = oneTurnBlackJack(x);
			}
			if (!logInSuccess)
				cout << "Cannot find account. Wrong ID or PIN Entered" << endl;
			break;

		case newAccount:
			registerNewAccount(accountList);
			break;

		case achievement:
			for (auto &x : accountList) {
				showAchievemnet(Player(x));
			}
			break;

		default:
			break;
		}

	}

}

char charParser() {
	char temp;
	bool isErr = true;
	//while (input failed) or (input succeeded with redundant tail, clear steream and repeat)
	while ((isErr = !(cin >> temp)) || (!isErr && cin.get() != '\n')) {
		if (isErr) { cin.clear(); }
		//reset cin
		while (cin.get() != '\n')//clear a whole line
			continue;
		cout << "\t\tPlease enter a character: ";
	}
	return temp;
}

Account oneTurnBlackJack(Account& x) {
	int tempCmd;
	Player p = Player(x);
	Player dealer = Player(Account("007", "James", "888888", "Male", "Las Vegas", "YourMoneyIsMine", 999999, 999999));
	showInfo(p, dealer);
	bool success = 0;
	bool playAgainFlag = false;
	char ch = '\0';
	do {
		p.reset();
		dealer.reset();
		ch = '\0';
		success = 0;
	Cards packOfCards = Cards();

	if (p.placeBet()) {
		cout << "Game starts!" << endl;
		cout << "Here are the dealer's initial cards:" << endl;
		dealer.hitCard(packOfCards);
		cout << setw(10) << "XXXXXXXX" << setw(4) << "XX" << setw(4) << "XX" << " total points = " << setw(6) << "XX" << endl;
		cout << "Here are your intial two cards:" << endl;
		p.hitCard(packOfCards);
		p.hitCard(packOfCards);
		if (p.isBlackJack()) {
			cout << "Another card of dealer:";
			dealer.hitCard(packOfCards);
			bjResults(p, dealer);
		}
		else{
		do {	//one turn begins here

			cout << "Please give command: ";
			cout << "1 Hit, 2 Stand, 3 Increasebet" << endl;
			tempCmd = intParser();
			switch (tempCmd) {
			case 1:
				p.hitCard(packOfCards);
				p.isBust();
				success = p.isLost();
				break;
			case 2:
				success = p.stand();
				break;
			case 3:
				p.increaseBet();
				break;
			default:
				break;
			}
		} while (!success);

		dealer.AI(p, packOfCards); // one turn end, calculate bet
		}

		if (p.isLost()) {
			p.loseBet();
			dealer.winBet();
			cout << "You lost bet" << endl;
		}
		if (dealer.isLost()) {
			p.winBet();
			dealer.loseBet();
			cout << "You wins bet" << endl;
		}
		if (!p.isLost() && !dealer.isLost()) {
			cout << "PUSH" << endl;
		}
		p.gamePlayed();
		showInfo(p, dealer);
	}
	cout << "Play for another time?(Y/N): ";
	ch = charParser();
	if (ch == 'y' || ch == 'Y')
		playAgainFlag = true;
	else
		playAgainFlag = false;
	} while (playAgainFlag);
	return p.getAccount(); // ´æÒÉ
}

vector<Account> readAccountList(const char* filename) {
	accountFlatened aF;
	vector<Account> accountList;
	// caution!
	cout << fixed << right;

	//show initial constents
	ifstream fin;
	fin.open(filename, ios_base::in | ios_base::binary); //binary file
														 //NOTE: some system doesn't accept ios_base::binary mode

	if (fin.is_open()) {
		
		while (fin.read((char*)&aF, sizeof aF)) {
			bool repetitionFlag = false;
			Account x = Account(aF.accountID, aF.accountName, aF.accountPIN, aF.accountGender, aF.accountRegion, aF.accountMotto, aF.accountDeposit, aF.accountNumOfGames);
			for (auto & y : accountList) {
				if (!(y.getAccountID().compare(x.getAccountID()))) //if ID not repeatd set flag false
					repetitionFlag = true;
			}
			if (!repetitionFlag) { // if not repeated push back
				accountList.push_back(x);
			}
		}
		fin.close();
	}
	return accountList;
}

void writeAccountList(const char* filename, vector<Account> x) {
	//Add new data
	accountFlatened aF;
	vector<Account>::iterator ptr;
	ofstream fout(filename, ios_base::out | ios_base::trunc | ios_base::binary);
	//NOTE: some systems don't accept the ios_base::binary mode
	if (!fout.is_open()) {
		cerr << "Cant't open " << filename << " file for output:\n";
		exit(EXIT_FAILURE);
	}

	for (ptr = x.begin(); ptr != x.end(); ptr++) {
		strcpy_s(aF.accountName, ptr->getAccountName().c_str());
		strcpy_s(aF.accountID, ptr->getAccountID().c_str());
		strcpy_s(aF.accountPIN, ptr->getAccountPIN().c_str());
		strcpy_s(aF.accountGender, ptr->getAccountGender().c_str());
		strcpy_s(aF.accountRegion, ptr->getAccountRegion().c_str());
		strcpy_s(aF.accountMotto, ptr->getAccountMotto().c_str());
		aF.accountDeposit = ptr->getAccountDeposit();
		aF.accountNumOfGames = ptr->getAccountNumOfGames();
		fout.write((char*)& aF, sizeof aF);
	}
	fout.close();
}

bool logInAndPlay(Account& x, string id, string pin) {
	if (!(x.getAccountID().compare(id) || x.getAccountPIN().compare(pin))){
		cout << "Log in successfully. Game Starts!" << endl;
		return true;
	}
	else
		cout << "Looking for Account... " << endl;
	return false;
}

void registerNewAccount(vector<Account>& accountList) {
	//Add new data
	accountFlatened aF;
	
	bool alreadyRegisteredFlag = false;
	bool strLengthFitFlag = true;
	string accountID;
	string accountName;
	string accountPIN;
	string accountGender;
	string accountRegion;
	string accountMotto;

	do{
		strLengthFitFlag = true;
		if (alreadyRegisteredFlag)
			cout << "Sorry, this ID has been registered.";
		cout << "Enter account ID: ";
		getline(cin, accountID);
		for (auto & x : accountList) {
			if (!(accountID.compare(x.getAccountID()))) //if ID not repeatd set flag false
				alreadyRegisteredFlag = true;
		}
		if (accountID.size() > lenAccountID)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, ID length cannot exceed " << lenAccountID << " characters";
	} while (alreadyRegisteredFlag || (!strLengthFitFlag));

	
	do{
		strLengthFitFlag = true;
		cout << "Enter the ACCOUNT name : ";//(enter a blank line to quit)
		getline(cin, accountName);
		if (accountName.size() > lenAccountName)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, ID length cannot exceed " << lenAccountName << " characters";
	} while ((!strLengthFitFlag));
	
	
	do {
		strLengthFitFlag = true;
		cout << "Enter the account's PIN: ";
		getline(cin, accountPIN);
		if (accountPIN.size() > lenAccountPIN)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, ID length cannot exceed " << lenAccountPIN << " characters";
	} while ((!strLengthFitFlag));

	do {
		strLengthFitFlag = true;
		cout << "Enter the account's Gender: ";
		getline(cin, accountGender);
		if (accountGender.size() > lenAccountGender)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, ID length cannot exceed " << lenAccountGender << " characters";
	} while ((!strLengthFitFlag));
		
	do {
		strLengthFitFlag = true;
		cout << "Enter the account's Region: ";
		getline(cin, accountRegion);
		if (accountRegion.size() > lenAccountRegion)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, ID length cannot exceed " << lenAccountRegion << " characters";
	} while ((!strLengthFitFlag));
		
	do {
		strLengthFitFlag = true;
		cout << "Enter the account's Motto: ";
		getline(cin, accountMotto);
		if (accountMotto.size() > lenAccountMotto)
			strLengthFitFlag = false;
		if (!strLengthFitFlag)
			cout << "Sorry, ID length cannot exceed " << lenAccountMotto << " characters";
	} while ((!strLengthFitFlag));
	
	Account temp = Account(accountID, accountName, accountPIN, accountGender, accountRegion, accountMotto);
	
	accountList.push_back(temp);
}

vector<Account> testVector() {
	vector<Account> x;

	x.push_back(Account("sz1920105", "HUIWAN", "970105"));

	return x;
}



