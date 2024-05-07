#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/*
* S0 = Waiting
* S1 = Language Choice
* S2 = Request PIN
* S3 = Authorization
* S4 = Main Menu
* S5 = Deposit
* S6 = Withdraw
* S7 = Balance Service
* S8 = Transfer
* S9 = Exit
* S10 = Change Balance
* S11 = Receipt
* S12 = Check Balance
* S13 = Money Out
* S14 = Success
*/

//Struct Of Bank Account
struct BankAccount
{
	string name;
	string account_number;
	int balance;
	string pin_code;
};

//Read From CSV File To An Array
vector<BankAccount> readCsv(const string& filename)
{
	vector<BankAccount> accounts;
	ifstream file(filename);

	if (!file.is_open())
	{
		cerr << "Error Opening File: " << filename << "!" << endl;
		return accounts;
		exit(0);
	}

	//Skip First Row
	string header;
	getline(file, header);

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		BankAccount account;
		getline(iss, account.name, ',');
		getline(iss, account.account_number, ',');
		iss >> account.balance;

		// Read the rest of the line to get the pin code
		getline(iss >> ws, account.pin_code);
		// Remove leading ',' from pin_code
		account.pin_code = account.pin_code.substr(1);

		accounts.push_back(account);
	}

	file.close();
	return accounts;
}

//Return Desired Account Into A Variable
BankAccount returnAccount(const string& account_number , const vector<BankAccount> accounts)
{
	for (const auto& account : accounts)
	{
		if (account_number == account.account_number)
		{
			return account;
		}
	}
	return BankAccount{ "", "", 0, "" };
}

//Check Avaliability Of Account Into Database
bool validAccount(BankAccount acc)
{
	if (acc.account_number == "")
	{
		return false;
	}

	return true;
}


int main()
{
	//Reading Database
	string filename = "Reference Model/atm_database.csv";
	vector<BankAccount> accounts = readCsv(filename);

	//For Testing The ReadCSV Function
	for (const auto& account : accounts)
	{
		cout << "Account Number: " << account.account_number << endl;
		cout << "Name: " << account.name << endl;
		cout << "Balance: " << account.balance << endl;
		cout << "PIN Code: " << account.pin_code << endl;

		cout << endl << endl;
	}


	//opening a text file to store the outputs
	fstream outputs;
	outputs.open("outputs_cpp.txt");


	//Variable For States
	int state = 0;

	//User Account Information
	BankAccount user_account;

	//Input Variables
	string account_number = "-1";
	string pin_code = "-1";
	string language_choice; //Dummy Variable

	int withdrawal_amount = -1,
		deposit_amount = -1,
		transfer_amount = -1,
		operation = -1;

	//Condition Variables
	bool insert_card,
		 authorization_request = 1,
		 invalid_pin = 0,
		 card_removal = 0,
		 deposit = 0,
		 withdraw = 0,
		 balance_service = 0,
		 transfer = 0,
		 exit = 0;

	/*************************************************************************************************/

	while (!exit)
	{
		switch (state)
		{
		case (0): //Waiting Page

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			cout << "Please Insert Card & Account Number: ";
			outputs << endl << "State (" << state << ")" << endl;


			cin >> account_number;
			outputs << "Inserted Account Number: " + account_number << endl;

			user_account = returnAccount(account_number, accounts);

			if(!validAccount(user_account))
			{
				cout << endl << "Wrong Input, No State Transition";
				outputs << "test 1: wrong account entered\n" << endl;
				state = 0;
			}
			else
			{
			    outputs << "test 2: Right account entered\n" << endl;
				insert_card = 1;
				state = 1;
			}
			break;

		case (1): //Language Choice Page

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;

			state = 2;
			cout << "Please Enter Choice Of Language" << endl;
			cin >> language_choice;
			outputs << "selected Language: " + language_choice <<endl;

			break;


		case (2): //Request PIN

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;

			cout << "Enter PIN Code: ";
			cin >> pin_code;
			outputs << "Entered pin code: " + pin_code << endl;

			state = 3;

		case (3): //Authorization

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;

			if (pin_code == user_account.pin_code)
			{
				cout << "Checking With Database...";
				outputs << "Pin code entered correctly" << endl;
				state = 4;
			}
			else
			{
				cout << "Invalid Pin Code!";
				outputs << "Pin code entered wrong" << endl;
				invalid_pin = 1;
				authorization_request = 0;
				state = 2;
			}
			break;

		case (4): //Main Menu

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;

			deposit = 0;
			withdraw = 0;
			balance_service = 0;
			transfer = 0;

			cout << "Authorization Success!" << endl << endl
				<< "Main Menu" << endl
				<< "1- Deposit" << endl
				<< "2- Withdraw" << endl
				<< "3- Balance Service" << endl
				<< "4- Money Transfer" << endl
				<< "5- Exit" << endl;
			cout << "Enter Your Choice: ";
			cin >> operation;
            outputs << "Entered operation: ";

			switch (operation)
			{
			case (1):
				deposit = 1;
				outputs << "deposit\n" << endl;
				state = 5;
				break;

			case (2):
				withdraw = 1;
				outputs << "withdraw\n" << endl;
				state = 6;
				break;

			case (3):
				balance_service = 1;
				outputs << "balance service\n" << endl;
				state = 7;
				break;

			case (4):
				transfer = 1;
				outputs << "transfer\n" << endl;
				state = 8;
				break;

			case (5):
				state = 9;
				outputs << "Exit\n" << endl;
				break;

			default:
				cout << "Invalid Choice Of Operation, No State Transition!";
				outputs << "Invalid Choice Of Operation\n" << endl;
				state = 4;
			}
			break;

		case (5): //Deposit Page

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;

			cout << "Deposit Page" << endl;
			cout << "Enter Deposit Amount: ";
			cin >> deposit_amount;
			outputs << "deposit_amount: ";
			outputs << deposit_amount << endl;

			if (deposit_amount > 0)
			{
				state = 10;
			}
			else
			{
			    outputs << "invalid amount entered" <<endl;
				cout << "Invalid Amount Entered, No State Transition!";
				state = 5;
			}
			break;

		case (6): //Withdraw

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Withdraw Page" << endl;
			cout << "Enter Withdrawal Amount: ";

			cin >> withdrawal_amount;
			outputs << "withdraw amount: ";
			outputs << withdrawal_amount << endl;

			state = 12;

			break;

		case (7): //Balance Service

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Balance Service Page" << endl;
			outputs << "Balance Service Page" << endl;

			state = 11;
			break;

		case(8): //Transfer Page

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Transfer Page" << endl;
			cout << "Enter Transfer Amount: ";
			cin >> transfer_amount;
			outputs << "transfer amount: ";
			outputs << transfer_amount << endl;

			state = 12;

			break;

		case(9): //Exit Page

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			outputs << "System has been terminated"<<endl;
			cout << "Exit Page" << endl;
			cout << "Thank You...See You Soon" << endl;
			cout << endl << "-----------------------------------------------------------" << endl;

			card_removal = 1;
			exit = 1;
			break;

		case (10): //Change Balance

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Changing Balance...";

			if (deposit)
			{
			    outputs << "current balance: ";
			    outputs << user_account.balance << endl;

 				user_account.balance = user_account.balance + deposit_amount;

                outputs << "New balance: ";
			    outputs << user_account.balance << endl;

				state = 11;
			}

			if (withdraw)
			{
			    outputs << "current balance: ";
			    outputs << user_account.balance << endl;

				user_account.balance = user_account.balance - withdrawal_amount;

				outputs << "New balance: ";
			    outputs << user_account.balance << endl;

				state = 13;
			}

			if (transfer)
			{
				outputs << "current balance: ";
			    outputs << user_account.balance << endl;

				user_account.balance = user_account.balance - transfer_amount;

				outputs << "New balance: ";
			    outputs << user_account.balance << endl;

				state = 14;
			}

			break;

		case (11): //Reciept

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Reciept" << endl;

			cout << "Account Balance = " << user_account.balance;
			outputs << "Reciept: " << endl;
			outputs << "New balance: ";
            outputs << user_account.balance << endl;

			state = 4;
			break;

		case (12): //Check Balance

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Checking Balance...." << endl;

			if (withdraw)
			{
				if (withdrawal_amount <= user_account.balance)
				{
				    outputs << "Balance checked" <<endl;
					state = 10;
				}
				else
				{
				    outputs << "invalid withdrawn amount" << endl;
					cout << "Invalid Amount Entered!";
					state = 4;
				}
			}
			else
			{
				if (transfer_amount <= user_account.balance)
				{
				    outputs << "Balance checked" <<endl;
					state = 10;
				}
				else
				{
				    outputs << "invalid withdrawn amount" << endl;
					cout << "Invalid Amount Entered!" << endl;
					state = 4;
				}
			}
			break;


		case (13): //Money Out

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Here Is Your Cash!";
			outputs << "money out: ";
			outputs << withdrawal_amount << endl;

			state = 4;
			break;

		case (14): //Success

			cout << endl << "-----------------------------------------------------------" << endl;
			cout << endl << "You Are In State (" << state << ")" << endl << endl;
			outputs << endl << "State (" << state << ")" << endl;
			cout << "Transfer Succeed!";
			outputs << "Transfer Succeed" << endl;
			state = 4;
			break;
		}
	}
	outputs.close();
	//4090 4095 english 4081 4095 1 287 2 19 3 1 287 4 18 2 4094 3 1 287 4 4094 7 5
}
