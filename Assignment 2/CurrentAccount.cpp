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
	os << overdraftLimit_ << "\n";							//get balance
	return os;
}

const string CurrentAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	os << fixed << setprecision(2) << "\nOVERDRAFT:       \234" << setw(10) << getOverdraftLimit();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}

//option 10
bool CurrentAccount::canTransferOut(double transferAmount) const
{
	if (transferAmount <= getBalance() + getOverdraftLimit())
	{
		BankAccount::canTransferOut(transferAmount);
		cout << "\nTRANSFER SUCCESSFULLY";
	}
	else
	{
		cout << "\nCANNOT EXCEED OVERDRAFT LIMIT";
		return false;
	}
}
