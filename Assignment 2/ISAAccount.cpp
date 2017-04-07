#include "ISAAccount.h"
#include "BankAccount.h"

ISAAccount::ISAAccount() : maximumYearlyDeposit_(), currentYearlyDeposit_(), endDepositPeriod_() {}
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
void ISAAccount::updateCurrentYearlyDeposit(double amount)
{
	currentYearlyDeposit_ += amount;
}

istream& ISAAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	SavingsAccount::getAccountDataFromStream(is);
	is >> maximumYearlyDeposit_;							//get balance
	is >> currentYearlyDeposit_;
	is >> endDepositPeriod_;
	return is;
}

ostream& ISAAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	SavingsAccount::putAccountDetailsInStream(os);
	os << maximumYearlyDeposit_ << "\n";							//get balance
	os << currentYearlyDeposit_ << "\n";
	os << endDepositPeriod_ << "\n";
	return os;
}

const string ISAAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	os << fixed << setprecision(2) << "\nMINIMUM BALANCE:                \234" << setw(10) << getMinimumBalance();
	os << fixed << setprecision(2) << "\nMAXIMUM YEARLY DEPOSIT:         \234" << setw(10) << getMaximumYearlyDeposit();
	os << fixed << setprecision(2) << "\nCURRENT YEARLY DEPOSIT:         \234" << setw(10) << getCurrentYearlyDeposit();
	os << "\nEND DEPOSIT PERIOD:	         " << getEndDepositPeriod().toFormattedString();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}

bool ISAAccount::canWithdraw(double amount) const
{
	if (SavingsAccount::canWithdraw(amount))
	{
		return true;
	}
}

void ISAAccount::recordDeposit(double amountToDeposit) 
{
	if (canDeposit(amountToDeposit))
	{
		BankAccount::recordDeposit(amountToDeposit);	
		updateCurrentYearlyDeposit(amountToDeposit);
	}

	else	//still displays success message but doesn't actually deposit into account
	{
		cout << "\nTRANSACTION IMPOSSIBLE";			
	}
}

bool ISAAccount::canDeposit(double amount) const
{
	if (Date::currentDate() < getEndDepositPeriod())
	{
		if (currentYearlyDeposit_ >= maximumYearlyDeposit_)
		{
			return false;
		}
		else
			return true;
	}

	else		//still displays success message but doesn't actually deposit into account
		return false;
}

//option 10

bool ISAAccount::canTransferIn(double transferAmount) const
{
	if (transferAmount + getCurrentYearlyDeposit() > maximumYearlyDeposit_)
	{
		cout << "\nCANNOT EXCEED MAXIMUM YEARLY DEPOSIT";
		return false;
	}

	else
		SavingsAccount::canTransferIn(transferAmount);

}