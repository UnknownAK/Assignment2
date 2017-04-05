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
#include "BankAccount.h"

#include <fstream>
using namespace std;


class ChildAccount : public BankAccount
{
public:
	//constructors & destructor
	ChildAccount();
	ChildAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList);
	virtual ~ChildAccount();

	double getMaximumPaidIn() const;
	double getMinimumPaidIn() const;
	virtual istream& getAccountDataFromStream(istream& is);
	virtual ostream& ChildAccount::putAccountDetailsInStream(ostream& os) const;

private:
	//data items
	double maximumPaidIn_;
	double minimumPaidIn_;
};

#endif
