#include "ChildAccount.h"
#include "BankAccount.h"

ChildAccount::ChildAccount() : maximumPaidIn_(50), minimumPaidIn_(50) {}
ChildAccount::ChildAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList) {}
ChildAccount::~ChildAccount() {}

double ChildAccount::getMaximumPaidIn() const
{
	return maximumPaidIn_;
}

double ChildAccount::getMinimumPaidIn() const
{
	return minimumPaidIn_;
}


istream& ChildAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> maximumPaidIn_;							//get balance
	is >> minimumPaidIn_;
	return is;
}

ostream& ChildAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << maximumPaidIn_;						//get balance
	os << minimumPaidIn_;
	return os;
}

