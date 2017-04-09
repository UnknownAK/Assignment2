//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 23
//Team: Cameron Huntington, Brian Leow, Karl Derbyshire, Will Jones


#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Date.h"
#include "Time.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class UserInterface {
public:
    void	showWelcomeScreen() const;
    void	showByeScreen() const;

	int		readInCardIdentificationCommand() const;
	int		readInAccountProcessingCommand() const;

	void	showErrorInvalidCommand() const;
    void	wait() const;
	const string	readInCardToBeProcessed() const;
    void	showValidateCardOnScreen(int validCode, const string& cardNum) const;
	void	showCardOnScreen(const string& cardSt) const;
	const string  readInAccountToBeProcessed() const;
	void	showValidateAccountOnScreen(int valid, const string& acctNum) const;
	void	showAllDepositsOnScreen(bool noTransaction, const string& str, double total) const;
    double	readInWithdrawalAmount() const;
    double	readInDepositAmount() const;

    void	showProduceBalanceOnScreen(double bal) const;
    void	showDepositOnScreen(bool auth, double deposit) const;
    void	showWithdrawalOnScreen(bool auth, double withdrawal) const;
    void	showStatementOnScreen(const string&) const;

	void showAllDepositTransactionsOnScreen(bool noTransaction, const string& str, double total) const;

	int readInNumberOfTransactions() const;

	//option 6
	void showMiniStatementOnScreen(bool isEmpty, double total, const string& mad, const string& str) const;
	int receiveTransactions() const;

	//option 7
	void showNoTransactionsOnScreen() const;
	void showSearchMenu() const;
	int readInSearchCommand() const;
	double readInAmount() const;
	void showMatchingTransactionsOnScreen(int n, const string& str) const;
	string readInText() const;

	//option 8
	Date readInValidDate(Date cd) const;
	void showTransactionsUpToDateOnScreen(bool isEmpty, Date d, int n, string str) const;
	bool readInConfirmDeletion() const;
	void showDeletionOfTransactionsUpToDateOnScreen(int n, Date d, bool deletionConfirmed) const;


	//option 9
	void showFundsAvailableOnScreen(bool empty, string mad, double m) const;

	//option 10
	double readInTransferAmount() const;
	void showTransferOnScreen(bool trOutOK, bool trInOK, double transferAmount) const;

	void displayMessages(int number, string text) const;

private:
    //support functions
	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu() const;
    int		readInCommand() const;
    double	readInPositiveAmount() const;

	int readInPositiveNumber() const;

	
};

#endif
