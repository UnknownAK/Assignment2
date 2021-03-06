//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#ifndef CurrentAccountH
#define CurrentAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"
#include "BankAccount.h"

#include <fstream>
using namespace std;


class CurrentAccount : public BankAccount
{
	public:
		//constructors & destructor
		CurrentAccount();
		CurrentAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList);
		virtual ~CurrentAccount();

		double getOverdraftLimit() const;
		virtual const string prepareFormattedStatement() const;
		virtual bool canTransferOut(double transferAmount) const;

		virtual istream& getAccountDataFromStream(istream& is);
		virtual ostream& CurrentAccount::putAccountDetailsInStream(ostream& os) const;

	private:
		//data items
		double overdraftLimit_;
};

#endif
