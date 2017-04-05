//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------

#include "ListT.h"
#include "Transaction.h"

#include <cassert> 	// for assert()
#include <sstream>

class TransactionList {
public:
	void   addNewTransaction(const Transaction&);
    const Transaction newestTransaction() const;
    const  TransactionList olderTransactions() const;
    void   deleteFirstTransaction();
    void   deleteGivenTransaction(const Transaction&);
	int    size() const;

	const string toFormattedString() const;		//return transactionlist as a (formatted) string
	ostream& putDataInStream(ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream(istream& is);	//receive TransactionList info from an input stream

	TransactionList getAllDepositTransactions() const;
	double getTotalTransactions() const;

	//option 6
	TransactionList getMostRecentTransactions(int userAmount) const;

	//option 7
	TransactionList getTransactionsForAmount(double a) const;
	TransactionList getTransactionsForTitle(string t) const;
	TransactionList getTransactionsForDate(string d) const;

	//option 8
	TransactionList getTransactionsUpToDate(Date d) const;
	void deleteTransactionsUpToDate(const Date& d);

private:
    List<Transaction> listOfTransactions_;	//list of transactions
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream&, const TransactionList&);	//insertion operator
istream& operator>>(istream& is, TransactionList& trl); //extraction operator

#endif

