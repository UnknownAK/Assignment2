//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction(const Transaction& tr) {
    listOfTransactions_.addInFront(tr);
}
const Transaction TransactionList::newestTransaction() const {
    return (listOfTransactions_.first());
}

const TransactionList TransactionList::olderTransactions() const {
	TransactionList trlist(*this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
	listOfTransactions_.deleteFirst();
}
void TransactionList::deleteGivenTransaction(const Transaction& tr) {
    listOfTransactions_.deleteOne(tr);
}
int TransactionList::size() const {
    return (listOfTransactions_.length());
}

const string TransactionList::toFormattedString() const {
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os_transactionlist << tempTrList.newestTransaction().toFormattedString() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return (os_transactionlist.str());
}

ostream& TransactionList::putDataInStream(ostream& os) const {
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList(*this);
	while (! (tempTrList.size() == 0))
    {
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return os;
}
istream& TransactionList::getDataFromStream(istream& is) {
//read in (unformatted) transaction list from input stream
	Transaction aTransaction;
	is >> aTransaction;	//read first transaction
	while (is) 	//while not end of file
	{
		listOfTransactions_.addAtEnd(aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}

double TransactionList::getTotalTransactions() const {
	double totalDeposits(0.0);
	TransactionList tempTrList(*this);
	while (tempTrList.size() > 0) //list is not empty
	{
		totalDeposits += tempTrList.newestTransaction().getAmount();
		tempTrList.deleteFirstTransaction();
	}
	return totalDeposits;
}



TransactionList TransactionList::getAllDepositTransactions() const {
	TransactionList trlDeposits;
	TransactionList tempTrList(*this);

	while (tempTrList.size() > 0)
	{
		if (tempTrList.newestTransaction().getAmount() > 0.0)
			trlDeposits.addNewTransaction(tempTrList.newestTransaction());
		tempTrList.deleteFirstTransaction();
	}
	return trlDeposits;
}

//option 6
TransactionList TransactionList::getMostRecentTransactions(int userAmount) const
{
	TransactionList requestedTransactions;
	TransactionList tempList(*this);
	
	if (userAmount > tempList.size())
	{
		userAmount = tempList.size();
	}

	for (int i = 0; i < userAmount; i++)
	{
		requestedTransactions.addNewTransaction(tempList.newestTransaction());
		tempList.deleteFirstTransaction();
	}

	return requestedTransactions;
}

//option 7a
TransactionList TransactionList::getTransactionsForAmount(double a) const
{
	TransactionList trlAmounts;
	TransactionList tempTrList(*this);

	while (tempTrList.size() > 0)
	{
		if (tempTrList.newestTransaction().getAmount() == a)
			trlAmounts.addNewTransaction(tempTrList.newestTransaction());
		tempTrList.deleteFirstTransaction();
	}

	return trlAmounts;
}

//option 7b
TransactionList TransactionList::getTransactionsForTitle(string t) const
{
	TransactionList trlTitles;
	TransactionList tempTrList(*this);

	while (tempTrList.size() > 0)
	{
		if (tempTrList.newestTransaction().getTitle() == t)
			trlTitles.addNewTransaction(tempTrList.newestTransaction());
		tempTrList.deleteFirstTransaction();
	}

	return trlTitles;
}

//option 7c
TransactionList TransactionList::getTransactionsForDate(string d) const
{
	TransactionList trlDate;
	TransactionList tempTrList(*this);

	while (tempTrList.size() > 0)
	{
		if (tempTrList.newestTransaction().getDate().toFormattedString() == d)
			trlDate.addNewTransaction(tempTrList.newestTransaction());
		tempTrList.deleteFirstTransaction();
	}

	return trlDate;
}

//option 8
TransactionList TransactionList::getTransactionsUpToDate(Date d) const
{
	TransactionList trlDates;
	TransactionList tempTrList(*this);

	while (tempTrList.size() > 0)
	{
		if ((tempTrList.newestTransaction().getDate()) < d)
			trlDates.addNewTransaction(tempTrList.newestTransaction());
		tempTrList.deleteFirstTransaction();
	}

	return trlDates;
}


//TransactionList TransactionList::getTransactionsUpToDate(Date d, TransactionList trlList) const
//{
//	TransactionList tempTrList;
//
//	if (trlList.size() == 0)
//	{
//		return tempTrList;
//	}
//	else if (trlList.newestTransaction().getDate() < d)
//	{		
//		return tempTrList;
//	}
//
//	//make this recursive 
//	
//}


//option 8 
void TransactionList::deleteTransactionsUpToDate(const Date& d)
{
	//partially works, doesnt clear if the date provided is in between existing transactions

	int s = size();

	for (int i(0); i < s; i++)
	{
		if (newestTransaction().getDate() < d)
		{
			deleteFirstTransaction();
		}
	}	
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const TransactionList& aTransactionList) {
    return (aTransactionList.putDataInStream(os));
}
istream& operator>>(istream& is, TransactionList& aTransactionList) {
	return (aTransactionList.getDataFromStream(is));
}
