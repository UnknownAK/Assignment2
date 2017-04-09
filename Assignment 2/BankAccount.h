//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number: 23
//Team: Cameron Huntington, Brian Leow, Karl Derbyshire, Will Jones

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"

#include <fstream>
using namespace std;


class BankAccount {
public:
    //constructors & destructor
	BankAccount();
    BankAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList);
	virtual ~BankAccount();

	//getter (assessor) functions
    const string getAccountNumber() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
    bool	isEmptyTransactionList() const;

	//other operations
	virtual const string prepareFormattedStatement() const;		//virtual so it can be used by other account types

    virtual void recordDeposit(double amount);		//allows for maximum yearly deposit

	double maxWithdrawalAllowed() const;
	virtual bool canWithdraw(double amount) const;
    void recordWithdrawal(double amount);
	void produceAllDepositTransactions(string& str, double& total) const;

	static const string accountType(char n);
	void readInBankAccountFromFile(const string& fileName);
	void storeBankAccountInFile(const string& fileName) const;
	//functions to put data into and get data from streams
	ostream& putDataInStream(ostream& os) const;
	virtual ostream& putAccountDetailsInStream(ostream& os) const;
	istream& getDataFromStream(istream& is);
	virtual istream& getAccountDataFromStream(istream& is);

	const string prepareFormattedAccountDetails() const;
	const string prepareFormattedTransactionList() const;

	//option 6
	double produceMostRecentTransactions(int n, string& str) const;
	const string prepareFormattedMiniAccountDetails() const;

	//option 7
	int produceTransactionsForAmount(double a, string& str) const;
	int produceTransactionsForTitle(string t, string& str) const;
	int produceTransactionsForDate(string d, string& str) const;

	//option 8
	int produceTransactionsUpToDate(Date d, string& str) const;
	void recordDeletionOfTransactionUpToDate(Date d);

	//option 10
	virtual bool canTransferOut(double transferAmount) const;
	virtual bool canTransferIn(double transferAmount) const;
	void recordTransferOut(double transferAmount, string tAN);
	void recordTransferIn(double transferAmount, string aAN);

private:
    //data items
    string accountNumber_;
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;
 
	//support functions
	void updateBalance(double amount);
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const BankAccount&);	//output operator
istream& operator>>(istream&, BankAccount&);	    //input operator

#endif
