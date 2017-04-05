//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#ifndef CashPointH
#define CashPointH 

//---------------------------------------------------------------------------
//CashPoint: class declaration
//---------------------------------------------------------------------------

#include "CashCard.h"
#include "BankAccount.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"
#include "ChildAccount.h"
#include "ISAAccount.h"
#include "UserInterface.h"

#include <fstream>
#include <string>
#include <cassert>
using namespace std;

class CashPoint {
public:
	//constructors & destructor
	CashPoint();	//default constructor
	~CashPoint();	//destructor
    void activateCashPoint();
private:
	//data items
    BankAccount* p_theActiveAccount_;
    CashCard* p_theCashCard_;
    const UserInterface theUI_;

	//support functions
	void performCardCommand(int);
    void performAccountProcessingCommand(int);
    int  validateCard(const string&) const;
	int  validateAccount(const string&) const;
	void processOneCustomerRequests();
	void processOneAccountRequests();

    void performSubMenuCommand(int);
    //commands
    //option 1
    void m1_produceBalance() const;
    //option 2
    void m2_withdrawFromBankAccount();
    //option 3
    void m3_depositToBankAccount();
    //option 4
    void m4_produceStatement() const;
	//option 5
	void m5_showAllDepositsTransactions() const;
	//option 6
	void m6_showMiniStatement() const;
	//option 7
	void m7_searchForTransactions() const;
	void searchTransactions() const;
	void m7a_showTransactionsForAmount() const;
	void m7b_showTransactionsForTitle() const;
	void m7c_showTransactionsForDate() const;

	//option 8
	void m8_clearTransactionsUpToDate() const;

	//option 9
	void m9_showFundsAvailableOnAllAccounts();
    //support file handling functions and creation of dynamic objects

	//option 10
	void m10_transferCashToAnotherAccount();
	void attemptTransfer(BankAccount* transferAccount) const;
	void recordTransfer(double transferAmount, BankAccount* transferAccount) const;

    bool canOpenFile(const string&) const;
	static char checkAccountType(const string&);
	bool accountsListedOnCard(const string&) const;

	BankAccount* activateBankAccount(const string&);
	BankAccount* releaseBankAccount(BankAccount*, string);

    void activateCashCard(const string&);
	void releaseCashCard();
};

#endif
