//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#ifndef SavingsAccountH
#define SavingsAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"
#include "BankAccount.h"

#include <fstream>
using namespace std;


class SavingsAccount : public BankAccount
{
public:
	//constructors & destructor
	SavingsAccount();
	SavingsAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList);
	virtual ~SavingsAccount();

	double getMinimumBalance() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& SavingsAccount::putAccountDetailsInStream(ostream& os) const;

private:
	//data items
	double minimumBalance_;
};

#endif
