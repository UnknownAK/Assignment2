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
	SavingsAccount::getAccountDataFromStream(is);							//get balance
	is >> minimumPaidIn_;
	is >> maximumPaidIn_;
	return is;
}

ostream& ChildAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << minimumPaidIn_ << "\n";
	os << maximumPaidIn_ << "\n";						//get balance
	return os;
}

const string ChildAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	os << fixed << setprecision(2) << "\nMINIMUM BALANCE:         \234" << setw(10) << getMinimumBalance();
	os << fixed << setprecision(2) << "\nMINIMUM PAID IN:         \234" << setw(10) << getMinimumPaidIn();
	os << fixed << setprecision(2) << "\nMAXIMUM PAID IN:         \234" << setw(10) << getMaximumPaidIn();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}

bool ChildAccount::canWithdraw(double amount) const
{
	cout << "\nCHILD ACCOUNT CANNOT WITHDRAW MONEY";
	return false;
}

void ChildAccount::recordDeposit(double amountToDeposit)
{
	if (canDeposit(amountToDeposit))
	{
		BankAccount::recordDeposit(amountToDeposit);
	}

	else	//still displays success message but doesn't actually deposit into account
	{
		cout << "\nTRANSACTION IMPOSSIBLE";
	}
}

bool ChildAccount::canDeposit(double amount) const
{
	if ((amount >= minimumPaidIn_) && (amount <= maximumPaidIn_))
	{
		return true;
	}
	else		//still displays success message but doesn't actually deposit into account
		return false;
}

bool ChildAccount::canTransferOut(double transferAmount) const
{
	cout << "\nCHILD ACCOUNT CANNOT TRANSFER";
	return false;		//cant transfer untill it is an adult account	
}

bool ChildAccount::canTransferIn(double transferAmount) const
{
	if ((transferAmount >= minimumPaidIn_) && (transferAmount <= maximumPaidIn_))
	{
		BankAccount::canTransferIn(transferAmount);
	}
	else
	{
		cout << "\nCANNOT EXCEED MINIMUM OR MAXIMUM PAID IN";
		return false;
	}
}