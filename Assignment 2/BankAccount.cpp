//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "BankAccount.h"
#include "Constants.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount()
    : balance_(0.0)
{}
BankAccount::BankAccount(const string& acctNum, const Date& cD, double b, const TransactionList& trList)
    : accountNumber_(acctNum), 
      creationDate_(cD),
      balance_(b),
      transactions_(trList)
{}
BankAccount::~BankAccount()
{}


//____other public member functions

const string BankAccount::getAccountNumber() const {
    return accountNumber_;
}
const Date BankAccount::getCreationDate() const {
    return creationDate_;
}
double BankAccount::getBalance() const {
    return balance_;
}
const TransactionList BankAccount::getTransactions() const {
    return transactions_;
}
bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}

void BankAccount::recordDeposit(double amountToDeposit) {
    //create a deposit transaction
	Transaction aTransaction("deposit_to_ATM", amountToDeposit);
    //update active bankaccount
    transactions_.addNewTransaction(aTransaction);		//update transactions_
    updateBalance(amountToDeposit);			//increase balance_
}

double BankAccount::maxWithdrawalAllowed() const {
//return borrowable amount
    return balance_;
}
bool BankAccount::canWithdraw(double amountToWithdraw ) const {
//check if enough money in account
	return amountToWithdraw <= maxWithdrawalAllowed();
}

void BankAccount::recordWithdrawal(double amountToWithdraw) {
	//create a withdrawal transaction
    Transaction aTransaction("withdrawal_from_ATM", -amountToWithdraw);
    //update active bankaccount
    transactions_.addNewTransaction(aTransaction);		//update transactions_
    updateBalance(-amountToWithdraw);			//decrease balance_
}

const string BankAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	os << prepareFormattedTransactionList();
	return os.str();
}

void BankAccount::produceAllDepositTransactions(string& str, double& total) const{
	//2.1: trl := getAllDepositTransactions():TransactionList
	TransactionList trl(transactions_.getAllDepositTransactions());

	//2.2: total:= getTotalTransactions(): double
	total = trl.getTotalTransactions();
	//2.3: str:= toFormattedString(): string
	str = trl.toFormattedString();
}

//option 6
double BankAccount::produceMostRecentTransactions(int amount, string& str) const
{
	//Transaction tr;
	TransactionList trl;

	double total(0.0);

	trl = transactions_.getMostRecentTransactions(amount);
	total = trl.getTotalTransactions();
	str = trl.toFormattedString();

	return total;
}

//option 7a
int BankAccount::produceTransactionsForAmount(double a, string& str) const
{
	TransactionList trl;
	int n;

	trl = transactions_.getTransactionsForAmount(a);
	n = trl.size();
	str = trl.toFormattedString();

	return n;
}

//option 7b
int BankAccount::produceTransactionsForTitle(string t, string& str) const
{
	TransactionList trl;
	int n;

	trl = transactions_.getTransactionsForTitle(t);
	n = trl.size();
	str = trl.toFormattedString();

	return n;
}

//option 7c
int BankAccount::produceTransactionsForDate(string d, string& str) const
{
	TransactionList trl;
	int n;

	trl = transactions_.getTransactionsForDate(d);
	n = trl.size();
	str = trl.toFormattedString();

	return n;
}

//option 8
int BankAccount::produceTransactionsUpToDate(Date d, string& str) const
{
	TransactionList trl;
	int n;

	trl = transactions_.getTransactionsUpToDate(d);
	n = trl.size();
	str = trl.toFormattedString();

	return n;
}

//option 8
void BankAccount::recordDeletionOfTransactionUpToDate(Date d)
{
	transactions_.deleteTransactionsUpToDate(d);
}

//option 10
bool BankAccount::canTransferOut(double transferAmount) const
{
	if (transferAmount <= 0)
	{
		return(false); 
	}
	else if (transferAmount > balance_)
	{
		return (false); //if amount to transfer is more than the current balance
	}
	else
	{
		return (true); //can transfer out
	}
}

bool BankAccount::canTransferIn(double transferAmount) const
{
	if (transferAmount < 0)
	{
		return(false);
	}
	else
	{
		return (true); //can always transfer into accounts??
	}
}
void BankAccount::recordTransferOut(double transferAmount, string tAN) 
{
	//create a withdrawal transaction
	Transaction aTransaction("transfer_out_to_" + tAN, -transferAmount);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(-transferAmount);			//decrease balance_
}
void BankAccount::recordTransferIn(double transferAmount, string aAN)
{
	//create a withdrawal transaction
	Transaction aTransaction("transfer_in_from_" + aAN, transferAmount);
	//update active bankaccount
	transactions_.addNewTransaction(aTransaction);		//update transactions_
	updateBalance(transferAmount);			//decrease balance_
}
void BankAccount::readInBankAccountFromFile(const string& fileName) {
	ifstream fromFile;
	fromFile.open(fileName.c_str(), ios::in); 	//open file in read mode
	if (fromFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        fromFile >> (*this);  	//read  all info from bank account file
    fromFile.close();			//close file: optional here
}

void BankAccount::storeBankAccountInFile(const string& fileName) const {
	ofstream toFile;
	toFile.open(fileName.c_str(), ios::out);	//open copy file in write mode
	if (toFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}
ostream& BankAccount::putDataInStream(ostream& os) const {
//put (unformatted) BankAccount details in stream
	putAccountDetailsInStream(os);			//put bank account core information in stream
	if (transactions_.size() != 0)
		os << transactions_;				//put all transactions, one per line
	return os;
}
ostream& BankAccount::putAccountDetailsInStream(ostream& os) const {
	//put (unformatted) BankAccount details in stream
	os << accountNumber_ << "\n";			//put account number
	os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	return os;
}
istream& BankAccount::getDataFromStream(istream& is) {
//get BankAccount details from stream
	getAccountDataFromStream(is);			//get bank account ore information from stream
	is >> transactions_;					//get all transactions (if any)
	return is;
}
istream& BankAccount::getAccountDataFromStream(istream& is) {
	//get BankAccount details from stream
	is >> accountNumber_;					//get account number
	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance
	return is;
}
//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------
void BankAccount::updateBalance(double amount) {
    balance_ += amount;   //add/take amount to/from balance_
}
//static
const string BankAccount::accountType(char n)
{	//return account type ("BANK" for '0', "CURRENT" for '1', etc.) 
	string type;
	switch (n)
	{
		case BANKACCOUNT_TYPE:		type = "BANK"; break;
		case CURRENTACCOUNT_TYPE:	type = "CURRENT"; break;
		case SAVINGSACCOUNT_TYPE:	type = "SAVINGS"; break;
		case CHILDACCOUNT_TYPE:		type = "CHILD"; break;
		case ISAACCOUNT_TYPE:		type = "ISA"; break;
//etc..
		default:					type = "UNKNOWN";
	}
	return type;
}
const string BankAccount::prepareFormattedAccountDetails() const
{
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType(accountNumber_[0]) << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << accountNumber_;									//display account number
	os << "\nCREATION DATE:   " << creationDate_.toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_;	//display balance
	return os.str();
}

const string BankAccount::prepareFormattedMiniAccountDetails() const 
{
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT NUMBER:  " << accountNumber_;			//display account number
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_;	//display balance

	return os.str();
}

const string BankAccount::prepareFormattedTransactionList() const {
	ostringstream os;
	//list of transactions (or message if empty)
	if (! transactions_.size() == 0)
		os << "\n\nLIST OF TRANSACTIONS \n"	<< transactions_.toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!";
	return os.str();
}


//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<(ostream& os, const BankAccount& aBankAccount) {
//put (unformatted) BankAccount details in stream
    return aBankAccount.putDataInStream(os);
}
istream& operator>>(istream& is, BankAccount& aBankAccount) {
//get BankAccount details from stream
	return aBankAccount.getDataFromStream(is);
}
