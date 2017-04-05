#include "ISAAccount.h"
#include "BankAccount.h"

ISAAccount::ISAAccount() : maximumYearlyDeposit_(50), currentYearlyDeposit_(50), endDepositPeriod_() {}
ISAAccount::ISAAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList) {}
ISAAccount::~ISAAccount() {}

double ISAAccount::getMaximumYearlyDeposit() const
{
	return maximumYearlyDeposit_;
}
double ISAAccount::getCurrentYearlyDeposit() const
{
	return currentYearlyDeposit_;
}
Date ISAAccount::getEndDepositPeriod() const
{
	return endDepositPeriod_;
}
//double ISAAccount::updateCurrentYearlyDeposit()
//{
//	currentYearlyDeposit_;
//}

istream& ISAAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	BankAccount::getAccountDataFromStream(is);
	is >> maximumYearlyDeposit_;							//get balance
	is >> currentYearlyDeposit_;
	is >> endDepositPeriod_;
	return is;
}

ostream& ISAAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	BankAccount::putAccountDetailsInStream(os);
	os << maximumYearlyDeposit_;							//get balance
	os << currentYearlyDeposit_;
	os << endDepositPeriod_;
	return os;
}

