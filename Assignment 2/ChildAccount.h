//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#ifndef ChildAccountH
#define ChildAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"
#include "SavingsAccount.h"

#include <fstream>
using namespace std;


class ChildAccount : public SavingsAccount
{
public:
	//constructors & destructor
	ChildAccount();
	ChildAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList);
	virtual ~ChildAccount();

	double getMaximumPaidIn() const;
	double getMinimumPaidIn() const;

	bool canDeposit(double amount) const;
	virtual const string prepareFormattedStatement() const;
	virtual bool canWithdraw(double amount) const;
	virtual void recordDeposit(double amountToDeposit);
	virtual bool canTransferOut(double transferAmount) const;
	virtual bool canTransferIn(double transferAmount) const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& ChildAccount::putAccountDetailsInStream(ostream& os) const;

private:
	//data items
	double maximumPaidIn_;
	double minimumPaidIn_;
};

#endif
