#include "CurrentAccount.h"
#include "BankAccount.h"

CurrentAccount::CurrentAccount() : overdraftLimit_(50) {}
CurrentAccount::CurrentAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList) {}
CurrentAccount::~CurrentAccount() {}

double CurrentAccount::getOverdraftLimit() const
{
	return overdraftLimit_;
}

istream& CurrentAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> overdraftLimit_;							//get balance
	return is;
}

ostream& CurrentAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << overdraftLimit_;							//get balance
	return os;
}

