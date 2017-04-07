//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#ifndef ISAAccountH
#define ISAAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"
#include "SavingsAccount.h"

#include <fstream>
using namespace std;


class ISAAccount : public SavingsAccount
{
public:
	//constructors & destructor
	ISAAccount();
	ISAAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList);
	virtual ~ISAAccount();

	double getMaximumYearlyDeposit() const;
	double getCurrentYearlyDeposit() const;
	Date getEndDepositPeriod() const;
	void updateCurrentYearlyDeposit(double amount);
	bool canDeposit(double amount) const;

	virtual const string prepareFormattedStatement() const;
	virtual bool canWithdraw(double amount) const;
	virtual void recordDeposit(double amountToDeposit);
	virtual bool canTransferIn(double transferAmount) const;

	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& ISAAccount::putAccountDetailsInStream(ostream& os) const;

private:
	//data items
	double maximumYearlyDeposit_;
	double currentYearlyDeposit_;
	double updateCurrentYearlyDeposit();
	Date endDepositPeriod_;
};

#endif
