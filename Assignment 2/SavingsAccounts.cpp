#include "SavingsAccount.h"
#include "BankAccount.h"

SavingsAccount::SavingsAccount() : minimumBalance_(50) {}
SavingsAccount::SavingsAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList) {}
SavingsAccount::~SavingsAccount() {}

double SavingsAccount::getMinimumBalance() const
{
	return minimumBalance_;
}

istream& SavingsAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> minimumBalance_;							//get balance
	return is;
}

ostream& SavingsAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << minimumBalance_;							//get balance
	return os;
}

