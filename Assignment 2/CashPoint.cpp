//Pascale Vacher - March 17
//OOP Assignment Task 1c - Semester 2
//Group Number:
//Team: (indicate member names, students numbers and courses)

#include "CashPoint.h"
#include "Date.h"

//---------------------------------------------------------------------------
//CashPoint: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CashPoint::CashPoint() : p_theActiveAccount_(nullptr), p_theCashCard_(nullptr), theUI_() {}

CashPoint::~CashPoint()
{
	assert(p_theActiveAccount_ == nullptr);
	assert(p_theCashCard_ == nullptr);
}

//____other public member functions

void CashPoint::activateCashPoint() {
	int command;
	theUI_.showWelcomeScreen();
	command = theUI_.readInCardIdentificationCommand();
	while (command != QUIT_COMMAND)
	{
		performCardCommand(command);
		theUI_.showByeScreen();
		command = theUI_.readInCardIdentificationCommand();
	}
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void CashPoint::performCardCommand(int option) {
	switch (option)
	{
	case 1:
	{
		string cashCardNum(theUI_.readInCardToBeProcessed());
		string cashCardFilename(FILEPATH + "card_" + cashCardNum + ".txt");	//read in card name & produce cashcard filename
		int validCardCode(validateCard(cashCardFilename));		//check valid card
		theUI_.showValidateCardOnScreen(validCardCode, cashCardNum);
		if (validCardCode == VALID_CARD) //valid card
		{
			//dynamically create a cash card and store card data
			activateCashCard(cashCardFilename);
			//display card data with available accounts
			string s_card(p_theCashCard_->toFormattedString());
			theUI_.showCardOnScreen(s_card);
			//process all request for current card (& bank accounts)
			processOneCustomerRequests();
			//free memory space used by cash card
			releaseCashCard();
		}
		break;
	}
	default:theUI_.showErrorInvalidCommand();
	}
}

int CashPoint::validateCard(const string& filename) const {
	//check that the card exists (valid)
	if (!canOpenFile(filename))   //invalid card
		return UNKNOWN_CARD;
	else
		//card empty (exist but no bank account listed on card)
		if (!accountsListedOnCard(filename))
			return EMPTY_CARD;
		else
			//card valid (exists and linked to at least one bank account)
			return VALID_CARD;
}

int CashPoint::validateAccount(const string& filename) const {
	//check that the account is valid 
	//NOTE: MORE WORK NEEDED here in case of transfer
	if (!canOpenFile(filename))
		//account does not exist
		return UNKNOWN_ACCOUNT;
	else
		//unaccessible account (exist but not listed on card)
		if (!p_theCashCard_->onCard(filename))
			return UNACCESSIBLE_ACCOUNT;
		else
			//account type not recognised
			if (BankAccount::accountType(checkAccountType(filename)) == "UNKNOWN")
				return UNKNOWN_ACCOUNT_TYPE;
			else
				//account valid (exists and accessible)
				return VALID_ACCOUNT;
}

void CashPoint::processOneCustomerRequests() {
	//process from one account
	//select active account and check that it is valid
	string anAccountNumber(theUI_.readInAccountToBeProcessed());
	string bankAccountFilename(FILEPATH + "account_" + anAccountNumber + ".txt");
	int validAccountCode(validateAccount(bankAccountFilename));  //check valid account
	theUI_.showValidateAccountOnScreen(validAccountCode, anAccountNumber);
	if (validAccountCode == VALID_ACCOUNT) //valid account: exists, accessible with card and not already open
	{
		//dynamically create a bank account to store data from file
		p_theActiveAccount_ = activateBankAccount(bankAccountFilename);
		//process all request for current card (& bank accounts)
		processOneAccountRequests();
		//store new state of bank account in file & free bank account memory space
		p_theActiveAccount_ = releaseBankAccount(p_theActiveAccount_, bankAccountFilename);
	}
}

void CashPoint::processOneAccountRequests() {
	int option;
	//select option from account processing menu
	option = theUI_.readInAccountProcessingCommand();
	while (option != QUIT_COMMAND)
	{
		performAccountProcessingCommand(option);   //process command for selected option
		theUI_.wait();
		option = theUI_.readInAccountProcessingCommand();   //select another option
	}
}
void CashPoint::performAccountProcessingCommand(int option) {
	switch (option)
	{
	case 1:	m1_produceBalance();
		break;
	case 2: m2_withdrawFromBankAccount();
		break;
	case 3:	m3_depositToBankAccount();
		break;
	case 4:	m4_produceStatement();
		break;
	case 5: m5_showAllDepositsTransactions();
		break;
	case 6: m6_showMiniStatement();
		break;
	case 7: m7_searchForTransactions();
		break;
	case 8: m8_clearTransactionsUpToDate();
		break;
	case 9: m9_showFundsAvailableOnAllAccounts();
		break;
	case 10: m10_transferCashToAnotherAccount();
		break;

	default:theUI_.showErrorInvalidCommand();
	}
}
//------ menu options
//---option 1
void CashPoint::m1_produceBalance() const {
	assert(p_theActiveAccount_ != nullptr);
	double balance(p_theActiveAccount_->getBalance());
	theUI_.showProduceBalanceOnScreen(balance);
}
//---option 2
void CashPoint::m2_withdrawFromBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToWithdraw(theUI_.readInWithdrawalAmount());
	bool transactionAuthorised(p_theActiveAccount_->canWithdraw(amountToWithdraw));
	if (transactionAuthorised)
	{   //transaction is accepted: money can be withdrawn from account
		p_theActiveAccount_->recordWithdrawal(amountToWithdraw);
	}   //else do nothing
	theUI_.showWithdrawalOnScreen(transactionAuthorised, amountToWithdraw);
}
//---option 3
void CashPoint::m3_depositToBankAccount() {
	assert(p_theActiveAccount_ != nullptr);
	double amountToDeposit(theUI_.readInDepositAmount());
	p_theActiveAccount_->recordDeposit(amountToDeposit);
	theUI_.showDepositOnScreen(true, amountToDeposit);
}
//---option 4
void CashPoint::m4_produceStatement() const {
	assert(p_theActiveAccount_ != nullptr);
	theUI_.showStatementOnScreen(p_theActiveAccount_->prepareFormattedStatement());
}
//--option 5
void CashPoint::m5_showAllDepositsTransactions() const{
	assert(p_theActiveAccount_ != nullptr);
	//1: noTransaction:= isEmptyTransactionList(): boolean
	bool noTransaction(p_theActiveAccount_->isEmptyTransactionList());
	string str;
	double total(0.0);
	//if (!noTransaction)
	//2: [not noTransaction] produceAllDepositTransactions(): string x double
	//; //	p_theActiveAccount_->produceAllDepositTransactions( str, total);
	//3: showAllDepositsOnScreen(noTransaction, str, total)
	//theUI_.showAllDepositsOnScreen(noTransaction, str, total);
}

//--option 6
void CashPoint::m6_showMiniStatement() const
{
	int amount = 0;
	bool isEmpty(p_theActiveAccount_->isEmptyTransactionList());
	TransactionList trl;
	string str, mad;
	double total = 0.0;

	assert(p_theActiveAccount_ != nullptr);

	while (amount < 1)
	{
		cout << "Enter number of recent transactions to receive: ";
		cin >> amount;
	}

	cout << "RECENT TRANSACTIONS REQUESTED AT " << Time::currentTime().toFormattedString() << " ON " << Date::currentDate().toFormattedString();

	if (!isEmpty)
	{
		total = p_theActiveAccount_->produceMostRecentTransactions(amount, str);
		mad = p_theActiveAccount_->prepareFormattedMiniAccountDetails();
		theUI_.showMiniStatementOnScreen(isEmpty, total, mad, str);
	}
}

//-----------------------------option 7---------------------------

void CashPoint::m7_searchForTransactions() const
{
	bool isEmpty(p_theActiveAccount_->isEmptyTransactionList());

	if (isEmpty)
	{
		theUI_.showNoTransactionsOnScreen();
	}

	else
	{
		searchTransactions();
	}
}

void CashPoint::searchTransactions() const
{
	int opt;

	theUI_.showSearchMenu();
	opt = theUI_.readInSearchCommand();

	switch (opt)
	{
		case 1:
			m7a_showTransactionsForAmount();
			break;
		case 2:
			m7b_showTransactionsForTitle();
			break;
		case 3:
			m7c_showTransactionsForDate();
			break;
		default:
			break;
	}
}

void CashPoint::m7a_showTransactionsForAmount() const
{
	double a(0);
	int n(0);
	string str;

	a = theUI_.readInAmount();
	n = p_theActiveAccount_->produceTransactionsForAmount(a, str);

	theUI_.showMatchingTransactionsOnScreen(n, str);
}

void CashPoint::m7b_showTransactionsForTitle() const
{
	string t = "";
	int n(0);
	string str;

	t = theUI_.readInText();
	n = p_theActiveAccount_->produceTransactionsForTitle(t, str);

	theUI_.showMatchingTransactionsOnScreen(n, str);
}

void CashPoint::m7c_showTransactionsForDate() const
{
	string d = "";
	int n(0);
	string str;

	d = theUI_.readInText();
	n = p_theActiveAccount_->produceTransactionsForDate(d, str);

	theUI_.showMatchingTransactionsOnScreen(n, str);
}

//-----------------------------option 8---------------------------

void CashPoint::m8_clearTransactionsUpToDate() const
{
	Date cd, d;
	string str;
	bool isEmpty(p_theActiveAccount_->isEmptyTransactionList());
	bool deletionConfirmed;

	int n(0);
	if (!isEmpty)
	{
		cd = p_theActiveAccount_->getCreationDate();
		d = theUI_.readInValidDate(cd);

		n = p_theActiveAccount_->produceTransactionsUpToDate(d, str);
		theUI_.showTransactionsUpToDateOnScreen(isEmpty, d, n, str);

		if (!str.empty())
		{
			deletionConfirmed = theUI_.readInConfirmDeletion();

			if (deletionConfirmed)
			{
				p_theActiveAccount_->recordDeletionOfTransactionUpToDate(d);
				theUI_.showDeletionOfTransactionsUpToDateOnScreen(n, d, deletionConfirmed);
			}
		}
	}
}

void CashPoint::m9_showFundsAvailableOnAllAccounts() 
{
	List<string> accts;
	bool empty;
	BankAccount* pacct;
	double m(0);
	string mad, filename;

	accts = p_theCashCard_->getAccountsList();
	empty = accts.isEmpty();
	
	while (!empty)
	{
		filename = "data/account_" + accts.first() + ".txt";
		pacct = activateBankAccount(filename);
		m += pacct->maxWithdrawalAllowed();
		mad = pacct->prepareFormattedMiniAccountDetails();
		releaseBankAccount(pacct, filename);
		accts.deleteFirst();
		empty = accts.isEmpty();
		theUI_.showFundsAvailableOnScreen(empty, mad, m);
	}	
}

void CashPoint::m10_transferCashToAnotherAccount() 
{
	string cardDetails, account, filename;
	char validAccountCode(0);
	BankAccount* transferAccount;

	cardDetails = p_theCashCard_->toFormattedString();
	theUI_.showCardOnScreen(cardDetails);
	account = theUI_.readInAccountToBeProcessed();

	filename = "data/account_" + account + ".txt";

	validAccountCode = validateAccount(filename);
	theUI_.showValidateAccountOnScreen(validAccountCode, account);

	if (validAccountCode == 0)
	{
		transferAccount = activateBankAccount(filename);
		checkAccountType(filename);
		transferAccount->readInBankAccountFromFile(filename);
		attemptTransfer(transferAccount);
		releaseBankAccount(transferAccount, filename);
	}
}

void CashPoint::attemptTransfer(BankAccount* transferAccount) const
{
	double transferAmount;
	bool trOutOK, trInOK;

	transferAmount = theUI_.readInTransferAmount();
	trOutOK = p_theActiveAccount_->canTransferOut(transferAmount);
	trInOK = p_theActiveAccount_->canTransferIn(transferAmount);

	if (trOutOK && trInOK)
	{
		recordTransfer(transferAmount, transferAccount);
	}
	theUI_.showTransferOnScreen(trOutOK, trInOK, transferAmount);

}
void CashPoint::recordTransfer(double transferAmount, BankAccount* transferAccount) const
{
	string tAN, aAN;

	tAN = transferAccount->getAccountNumber();
	p_theActiveAccount_->recordTransferOut(transferAmount, tAN);
	aAN = p_theActiveAccount_->getAccountNumber();
	transferAccount->recordTransferIn(transferAmount, aAN);
}



//------private file functions

bool CashPoint::canOpenFile(const string& filename) const {
	//check if a file already exist
	ifstream inFile;
	inFile.open(filename.c_str(), ios::in); 	//open file
	//if does not exist fail() return true
	return (!inFile.fail());	//close file automatically when inFile goes out of scope
}

bool CashPoint::accountsListedOnCard(const string& cashCardFileName) const {
	//check that card is linked with account data
	ifstream inFile;
	inFile.open(cashCardFileName.c_str(), ios::in); 	//open file
	assert(!inFile.fail()); //file should exist at this point 
	//check that it contains some info in addition to card number
	string temp;
	inFile >> temp; //read card number
	inFile >> temp;	//ready first account data or eof if end of file found
	return (!inFile.eof());
}

void CashPoint::activateCashCard(const string& filename) {
	//dynamically create a cash card to store data from file
	//effectively create the cash card instance with the data
	p_theCashCard_ = new CashCard;
	assert(p_theCashCard_ != nullptr);
	p_theCashCard_->readInCardFromFile(filename);
}

void CashPoint::releaseCashCard() {
	//release the memory allocated to the dynamic instance of a CashCard
	delete p_theCashCard_;
	p_theCashCard_ = nullptr;
}
//static member function
char CashPoint::checkAccountType(const string& filename)  {
	//(simply) identify type/class of account from the account number
	//start with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return filename[13]; //13th char from the filename ("data/account_101.txt")
}

BankAccount* CashPoint::activateBankAccount(const string& filename) {
	//check the type of the account (already checked for validity)
	char accType(checkAccountType(filename));
	//effectively create the active bank account instance of the appropriate class
	//and store the appropriate data read from the file
	BankAccount* p_BA(nullptr);
	switch (accType)
	{
		case BANKACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			p_BA = new BankAccount;    //points to a BankAccount object
			break;
		case CURRENTACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			p_BA = new CurrentAccount;    //points to a BankAccount object
			break;
		case SAVINGSACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			p_BA = new SavingsAccount;    //points to a BankAccount object
			break;
		case CHILDACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			p_BA = new ChildAccount;    //points to a BankAccount object
			break;
		case ISAACCOUNT_TYPE:	//NOT NEEDED WITH ABSTRACT CLASSES
			p_BA = new ISAAccount;    //points to a BankAccount object
			break;
	}
	assert(p_BA != nullptr);
	p_BA->readInBankAccountFromFile(filename); //read account details from file

	//use dynamic memory allocation: the bank account created will have to be released in releaseBankAccount
	return p_BA;
}

BankAccount* CashPoint::releaseBankAccount(BankAccount* p_BA, string filename) {
	//store (possibly updated) data back in file
	assert(p_BA != nullptr);
	p_BA->storeBankAccountInFile(filename);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}


//not sure whether we need this function or not

//CurrentAccount* CashPoint::releaseCurrentAccount(BankAccount* p_BA, string filename) {
//	//store (possibly updated) data back in file
//	assert(p_BA != nullptr);
//	p_BA->storeBankAccountInFile(filename);
//	//effectively destroy the bank account instance
//	delete p_BA;
//	return nullptr;
//}

