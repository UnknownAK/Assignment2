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
	os << minimumBalance_ << "\n";							//get balance
	return os;
}

const string SavingsAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	os << "\nMINIMUM BALANCE:         \234" << setw(10) << getMinimumBalance();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}
bool SavingsAccount::canWithdraw(double amount) const 
{
	BankAccount::canWithdraw(amount);

	if (minimumBalance_ > (getBalance() - amount))
	{
		return false;
	}
	else
		return true;
}

//option 10
bool SavingsAccount::canTransferOut(double transferAmount) const
{
	string meme;

	meme = cin.get();

	if ((getBalance() - transferAmount) < minimumBalance_)
	{
		cout << "\nCANNOT TRANSFER MORE THAN THE MINIMUM BALANCE";
		return false;
	}

	else

		cout << "\n" << meme;
		BankAccount::canTransferOut(transferAmount);
}
