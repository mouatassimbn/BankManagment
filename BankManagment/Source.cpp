/*
                     Programed by :      Mouatassim Boulahsen
					 Date :              19/12/2018
					 Goal :              A bank management software...
					 Bank Name :         MSBN

					 Features to add :
					 -save info(accounts and all info,tranfers history, other info) offline -> x
					 --Improve the create account data -> v
					 ---Be able to get out of repeating the wrong info at every login -> v
					 ----Optimize the program -> x
					 -----Loans menu -> v
					 ------Transactions history...  -> v
					 -------ADD SECURITY TO THE PROGRAM !!!! -> x
					 --------Add reason to delete account -> v 
					 ---------Add the history of bank menu -> v
					 ----------Deleted account menu  -> v
					 -----------Make the bank profit -> v
					 ------------Loan history -> x
					 ------------Make a histoory menu that groups every history....
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include <Windows.h>
#include <wchar.h>
#include <cmath>

using namespace std;
// structs
struct client { // struct of client
	string m_name; // the name of the client
	string m_adress; // the adress of the client
	string m_phoneNumber; // the phone number of the client
	string m_nasNumber; // the NAS number of the client
	string m_typeOfAccount; // the type of the account
	string m_timeOfCreation; // the time of creation of account
	string m_timeOfDelete; // the time of deletion of account
	string m_reasonOfDeletion; // stores the reason of deletion
	string m_reasonOfLoan; // stores the reason of loan
	double m_accountBalance; // The balance of the client
	double m_loanBalance; // the loan
	int m_accountNumber; // the account number
	int m_password; // the password of the account
	int m_timeOfsaving; //time that money will be blocked for
};

// Global variables and constants
const double TRANSACTION_FEE = 1.50;
const double SAVINGS_INTEREST = 1.25;

// definition of function
void setup(client &bank); // setup the srand 
int returnAccountNumber(); // returns a random account number
bool transferTheMoney(client &sender, double &amount, client &receiver, client &fee); // transfer money fonction
char verifyInfoCorrect(char choix1, char choix2); // verifies the choice of user
string getTime();
void historyOfBank();
double savingsRates(client account);

int main(void) {
	client MSBN; // main bank account
	setup(MSBN); // sets up the srand 
	// Declare variables and initialize them...
	vector<client> listOfClients; // vector of struct clients : it stores the clients
	vector<client> listOfDeletedAccounts; // vector of struct clients : it stored deleted accounts
	vector<string> transferHistory; // vector of strings : it stores the history of transactions
	vector<string> loansHistory;
	int choiceMain = 0, numClient = 0, accountNum = 0, pwd = 0, tries = 0, choice = 0, receiver = 0; // initates int variables
	bool found = true, transaction = false; // initiats bool variables
	double amount = 0; // initiats the amount to be stansfered
	char allInfoCorrect = NULL; // bool if the info is correct
	// start of output
	system("color f5"); // change the color of the console to black-blue
	do { // start of main menu
		system("cls"); // clear the screen

		// output main menu...
		cout << "\t\t\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM \n\n" << endl // title of program
			<< "\t\t\t\t\t===== WELCOME TO THE MAIN MENU of MSBN ===== \n\n\n" << endl; // title of menu
																				
	    // List of menu
		cout << "\t\t\t\t1 - Creat new account" << endl 
			<< "\t\t\t\t2 - Update information of existing account" << endl
			<< "\t\t\t\t3 - Check the details of existing account" << endl
			<< "\t\t\t\t4 - Removing existing account" << endl
			<< "\t\t\t\t5 - View customer's list" << endl
			<< "\t\t\t\t6 - Transactions" << endl
			<< "\t\t\t\t7 - All transactions history" << endl
			<< "\t\t\t\t8 - Deleted accounts" << endl
			<< "\t\t\t\t9 - Loans" << endl
			<< "\t\t\t\t10 - Loans history" << endl
			<< "\t\t\t\t12 - About us" << endl
			<< "\t\t\t\t13 - Exit \n\n" << endl;

		cout << "\t\t\tEnter your choice (1,2,3,4,5,6,7,8,9,10,11 or 13): "; // ask the user to input his choics
		cin >> choiceMain; // input of user

		while (!cin || choiceMain < 1 || choiceMain > 14) { // verify if the user entered valid choices
			cin.clear(); // clears error flags
			cin.ignore(); // ignore next new line
			cout << "\t\t\t[ERROR] : Your choice seems to not be available..." << endl // ourput error text
				<< "\t\t\t-> Please enter new choice : "; // asks the user for new input
			cin >> choiceMain; // input of user
		}

		if (choiceMain != 13) { // verify if the user doesn't want to quit the program

			system("cls"); // clears the screen

			switch (choiceMain) { // choice of user

			case 1: // menu 1 : creat account..
				listOfClients.push_back(client()); // adds a client to the list of clients
				cout << "\t\t\t\t\t===== CREAT A NEW ACCOUNT ===== \n\n\n" << endl; // title of menu

				// info about the bank and welcome text
				cout << "\t\t\t Welcome new client! we're glad that you decided to creat an account with our bank..." << endl
					 << "\t\t\t MSBN is one of the biggest banks in canada and our mission is always earning the right to be our clients’ first choice" << endl
					 << "\n\t\t\t We need you to enter some personal informations about you. \n\n\n" << endl;

				do {
					cin.clear(); // clears error flags
					cin.ignore(); // ignore next new line

					cout << "Enter your full name : "; // asks the user for full name
					getline(cin, listOfClients[numClient].m_name); // gets the input of user

					cout << "Enter your NAS number : "; // asks the user for their NAS number
					getline(cin, listOfClients[numClient].m_nasNumber); // get the the input of user

					cout << "Enter your adress : "; // asks thee user for their Adress
					getline(cin, listOfClients[numClient].m_adress); // get the input of user

					cout << "Enter your phone number : "; // asks the user for their phone number
					getline(cin, listOfClients[numClient].m_phoneNumber); // gets the input of user

					cout << "Enter your type of account ((C)hecking or (S)avings ): "; // asks the user wants a checking or savings account
					if (verifyInfoCorrect('C', 'S') == 'C') // verify if the valid returned value of the function is equal to C
						listOfClients[numClient].m_typeOfAccount = "Checkings"; // set the type of account to Checkings
					else { // if not
						listOfClients[numClient].m_typeOfAccount = "Savings"; // set the type of account to Savings
						cout << "\n The effects will take way less than a year obviously! you will get the interest next time you check your balance\n" << endl;
						cout << "\nEnter the time of saving (in years): ";
						cin >> listOfClients[numClient].m_timeOfsaving;
					}

					cout << "Enter the starting balance : "; // asks the user for starting balance
					cin >> listOfClients[numClient].m_accountBalance; // get the input of user 

					Sleep(2000); // sleep for 2s
					// ask the user to verify it's info...
					cout << "\n\n==== Please verify your info :" << endl  // output personal info
						<< "\n\nYour full name -> " << listOfClients[numClient].m_name << endl
						<< "Your adress -> " << listOfClients[numClient].m_adress << endl
						<< "Your NAS number -> " << listOfClients[numClient].m_nasNumber << endl
						<< "Your phone number -> " << listOfClients[numClient].m_phoneNumber << endl
						<< "You are appying for a " << listOfClients[numClient].m_typeOfAccount << " account." << endl
						<< "The starting balance of your account is : " << fixed << setprecision(2) << listOfClients[numClient].m_accountBalance << " $" << endl;

					cout << "\n\nAre all the info shown above correct ((Y)es or (N)o) : "; // ask the user if all the info above are correct
					allInfoCorrect = verifyInfoCorrect('Y', 'N'); // assign the valid returned value to the variable 

				} while (allInfoCorrect == 'N'); // repeat if the input of user is NO
				// output after the user answering yes
				cout << "By answering (Yes): i've verified all the info above and they're my real and valid info.." << endl
					 << "Your account is getting created at the moment" << endl
					 << "Please be patient for a moment..." << endl 
					 << "\n\n\n-> you will receive your account number shortly. And you will proceed into the last step..." << endl;
				
				listOfClients[numClient].m_accountNumber = returnAccountNumber(); // assign the returned number to the account number member of the client
				Sleep(1200); // sleep for 1.2s
				
				// output that the process is done and ouput the account number
				cout << "\n=== Done === \n" << endl
					<< "Your acount number is : " << listOfClients[numClient].m_accountNumber << endl << endl;

				cout << "Please enter your password (4 digits) : "; // ask the user about the password
				cin >> listOfClients[numClient].m_password; // get the input of user

				while (!cin || listOfClients[numClient].m_password < 1000 || listOfClients[numClient].m_password > 10000) { // verify if the user entered PIN
					cin.clear(); // clears error flags
					cin.ignore(); // ignore next new line
					cout << "[ERROR] : your Pin isn't 4 digits" << endl // ourput error text
						<< "\t\t\t-> Please enter new PIN: "; // asks the user for new input
					cin >> listOfClients[numClient].m_password; // input of user
				}

				Sleep(1200); // sleep for 1.2s
				cout << "\n\nThank you for creating your account with us !!!" << endl // output the thank you text...
					 << " -> Please remember your account number and password...\n\n" << endl;
				listOfClients[numClient].m_accountBalance = savingsRates(listOfClients[numClient]);
				listOfClients[numClient].m_timeOfCreation = getTime();
				numClient++; // adds one to the num cients

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause the program
				break; // break from the menu

			case 2: // menu 2 : Update information of existing account
				tries = 0; // reset tries variable to 0
				do {
					system("cls"); // clear thee screen
				    cout << "\t\t\t\t\t===== Modifies the details of existing account ===== \n\n\n" << endl; // title of menu

					if (!found) // verify if found is false
						cout << "[ERROR] : The info entered doesn't match any of our accounts" << endl; // output error

					cout << "\t\t\t\tEnter your account number : "; // ask the user for account number
					cin >> accountNum; // input of user

					cout << "\t\t\t\tEnter your password : "; // ask the user for password
					cin >> pwd; // input of user

					for (size_t i = 0; i < listOfClients.size(); i++) { // loops through the list of clients array

						if (accountNum == listOfClients[i].m_accountNumber && pwd == listOfClients[i].m_password) { // verify if the inputs of user match the the info an account
							system("cls"); // clears the screen

							// output info of user
							cout << "=== Welcome " << listOfClients[i].m_name << " ====" << endl;
							cout << "\n\nYour full name -> " << listOfClients[i].m_name << endl
								<< "Your adress -> " << listOfClients[i].m_adress << endl
								<< "Your NAS number -> " << listOfClients[i].m_nasNumber << endl
								<< "Your phone number -> " << listOfClients[numClient].m_phoneNumber << endl
								<< "You have a " << listOfClients[i].m_typeOfAccount << " account." << endl
								<< "Your balance is " << fixed << setprecision(2) << listOfClients[i].m_accountBalance << " $" << endl;

							do {
								cout << endl << "======================================================" << endl; // separator

								// output choices
								cout << "\n1 - Name" << endl
									<< "2 - Adress" << endl
									<< "3 - NAS number" << endl
									<< "4 - Phone number" << endl
									<< "5 - Type of account" << endl;

								switch (choice) { // choice of user...

								case 1: // change name
									cout << "[NEW] : Enter your full name : "; // ask the user for new full name
									getline(cin, listOfClients[i].m_name); // get input of user
									break;

								case 2: // change adress
									cout << "[NEW] : Enter your adress : "; // ask the user for new adress
									getline(cin, listOfClients[numClient].m_adress); // get input of user
									break;

								case 3: // change NAS number
									cout << "[NEW] : Enter your NAS number : "; // ask the user for new NAS number
									getline(cin, listOfClients[i].m_nasNumber); // get the input of user
									break;

								case 4: // change phone number
									cout << "[NEW] : Enter your phone number : "; // ask the user for new phone number
									getline(cin, listOfClients[i].m_phoneNumber); // get the input of user
									break;

								case 5:
									cout << "[NEW] : Enter the type of account ((C)hecking or (S)avings ): "; // ask the user for new type of account
									if (verifyInfoCorrect('C', 'S') == 'C') // verify if the valid returned input of user is equal to checking
										listOfClients[i].m_typeOfAccount = "Checkings"; // set the type of account to checkings
									else // if not
										listOfClients[i].m_typeOfAccount = "Savings"; // set the type of account to savings 
									break;
								}
								cout << "\n\nDo you wanna change other info ((Y)es or (N)o) : "; // verify if theuser wanna change other info

								allInfoCorrect = verifyInfoCorrect('Y', 'N'); // get the verified input of user and assign it to the variable

							} while (allInfoCorrect == 'Y'); // repear if the input is equal to Yes

							found = true; // set found to true
							break; // break from loop
						}
						else // if not
							found = false; // set found to false
					}

					cout << "\n\nDo you wanna retry((Y)es or (N)o) : "; // ask the user if all the info above are correct
					allInfoCorrect = verifyInfoCorrect('Y', 'N'); // assign the valid returned value to the variable 
				} while (allInfoCorrect == 'Y'); // repeat when the input of user is equal to Yes

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause the program
				break; // break from the menu

			case 3: // menu 3 : check information on account 
				tries = 0; // reset tries to 0
				do {
					system("cls"); // clear the screen
					cout << "\t\t\t\t\t===== Check the details of existing account ===== \n\n\n" << endl; // title of menu
				

					if (!found) // verify if found is false
						cout << "[ERROR] : The info entered doesn't match any of our accounts" << endl; // ouput error text

					cout << "\t\t\t\tEnter your account number : "; // asks the user for account number
					cin >> accountNum; // get input of user
					cout << "\t\t\t\tEnter your password : "; // asks the user for password
					cin >> pwd; // get the input of user

					for (size_t i = 0; i < listOfClients.size(); i++) {

						if (accountNum == listOfClients[i].m_accountNumber && pwd == listOfClients[i].m_password) { // verify if inputs of user equal to the info of an existing account
							system("cls"); // clears screen
							// ouputs account info
							cout << "=== Welcome " << listOfClients[i].m_name << " ====" << endl; 
							cout << "\n\nYour full name -> " << listOfClients[i].m_name << endl
								<< "Your adress -> " << listOfClients[i].m_adress << endl
								<< "Your NAS number -> " << listOfClients[i].m_nasNumber << endl
								<< "Your phone number -> " << listOfClients[numClient].m_phoneNumber << endl
								<< "You have a " << listOfClients[i].m_typeOfAccount << " account." << endl
								<< "Your balance is " << fixed << setprecision(2) << listOfClients[i].m_accountBalance << " $" << endl;
							
							found = true; // set found to true
							break; // break from loop
						}
						else // if not 
							found = false; // set found to false
					}

					cout << "\n\nDo you wanna retry((Y)es or (N)o) : "; // ask the user if all the info above are correct
					allInfoCorrect = verifyInfoCorrect('Y', 'N'); // assign the valid returned value to the variable 
				} while (allInfoCorrect == 'Y'); // repeat when the input of user is equal to Yes

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause the program
				break; // break from menu

			case 4:  // remove an account...
				tries = 0; // reset tries to 0
				do {
					system("cls"); // clear the screen
					cout << "\t\t\t\t\t===== remove an account account ===== \n\n\n" << endl; // title of menu

					if (!found) // verify if found is false
						cout << "[ERROR] : The info entered doesn't match any of our accounts" << endl; // output error text

					cout << "\t\t\t\tEnter your account number : "; // ask the user for account number
					cin >> accountNum;  // get input of user

					cout << "\t\t\t\tEnter your password : "; // ask the user for account password
					cin >> pwd; // get input of user

					for (size_t i = 0; i < listOfClients.size(); i++) { // loops through the list of clients
						if (accountNum == listOfClients[i].m_accountNumber && pwd == listOfClients[i].m_password) { // vrify is the inputs of user is equal to an accounts info
							system("cls"); // clears the screen 
							// ouput account info...
							cout << "=== Welcome " << listOfClients[i].m_name << " ==== \n" << endl
								<< "You have a " << listOfClients[i].m_typeOfAccount << " account." << endl
								<< "Your balance is " << fixed << setprecision(2) << listOfClients[i].m_accountBalance << " $" << endl;
							cout << "\n\n\t[WARNING] : If you leave any balance in your account, when you delete it. It will be kept by the bank until we find a solution !!" << endl;
							
							cout << "\n\nDo you really want to remove your account ((Y)es or (N)o)? "; // ask the user if he want to remouve account...
							if (verifyInfoCorrect('Y', 'N') == 'Y') { // verify the input of user is equal to y;
								// put reason to delete account...
								cin.clear(); // clears error flags
								cin.ignore(); // ignore next new line
								cout << "===== Please enter the reason you wanna delete your account : ======\n" << endl;
								getline(cin,listOfClients[i].m_reasonOfDeletion);
								cout << "\n====================================================================" << endl;
								// end of reason

								listOfClients[i].m_timeOfDelete = getTime(); // set the time of deletion
								listOfDeletedAccounts.push_back(listOfClients[i]); // push the to be deleted account to deletedAccount array
								listOfClients.erase(listOfClients.begin() + i); // deletes account

								Sleep(1200); // sleep for 1.2s
								cout << "Your account has been deleted!" << endl // output that the account has been deleted
									<< "We're sorry to part from you. We wish you change your mind" << endl;
							}
							else { // if not 
								cout << "\nThank you for changing your mind !!!" << endl; // output text
							}
							found = true; // set found to true
							break; // break from the loop
						}
						else // if not
							found = false; // set found to false
					} 

					cout << "\n\nDo you wanna retry((Y)es or (N)o) : "; // ask the user if all the info above are correct
					allInfoCorrect = verifyInfoCorrect('Y', 'N'); // assign the valid returned value to the variable 
				} while (allInfoCorrect == 'Y'); // repeat when the input of user is equal to Yes

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu

			case 5: // menu 5 : show costumers list...
				cout << "\t\t\t\t\t===== Our costumers ===== \n\n\n" << endl; // title of menu

				cout << "\n\t[NUMBER CLIENTS] : " << listOfClients.size() << "\n\n" << endl; // ouput number of clients

				for (size_t i = 0; i < listOfClients.size(); i++) { // loop through the list of clients...
					// output every account info
					cout << "\t\tClient # " << (i + 1) << "\t|\t" << listOfClients[i].m_accountNumber << "\t|\t" << listOfClients[i].m_name << "\t|\t" << listOfClients[i].m_typeOfAccount << " | " << fixed << setprecision(2) << listOfClients[i].m_accountBalance << " $" << endl
						<< "\t\t -> Time of creation : " << listOfClients[i].m_timeOfCreation << endl;
				}

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause the program
				break; // break from menu

			case 6: // menu 6 : transfer money...
				tries = 0; // reset the tries value to 0
				
				do {
					system("cls"); // clear the screen
					cout << "\t\t\t\t\t===== transfer money ===== \n\n\n" << endl;  // title of menu

					if (!found) // verify if found is false
						cout << "[ERROR] : The info entered doesn't match any of our accounts" << endl; // ouput error text

					cout << "\t\t\t\tEnter your account number : "; // ask the user to enter account number
					cin >> accountNum; // get input of user...

					cout << "\t\t\t\tEnter your password : "; // ask the user to enter account password
					cin >> pwd; // get input of user

					for (size_t i = 0; i < listOfClients.size(); i++) { // loops through the list of clients

						if (accountNum == listOfClients[i].m_accountNumber && pwd == listOfClients[i].m_password) { // verify if the input of user is equal to one of the accounts
							system("cls"); // clears screen

							cout << "\t\t=== Welcome " << listOfClients[i].m_name << " ==== \n" << endl; // output name of client
							do {

								cout << "[WARNING] : Please remember that every transfer cost you 1.50 $\n" << endl;
								cout << "\n\n\tThe account number of the receiver : "; // asks the user to enter the account number of receiver
								cin >> receiver; // get the input of user
								cout << "\tThe amount to be transfered : "; // asks the user to enter the amount to be transfered
								cin >> amount; // get the input of user

								for (size_t j = 0; j < listOfClients.size(); j++) { // loops through the list of clients

									if (listOfClients[j].m_accountNumber == receiver) { // verify if the account of the reciever exists
										transaction = transferTheMoney(listOfClients[i], amount, listOfClients[j], MSBN); // call the transfer the money fonction and assign the return to th variable
										break; // break from the loop
									} 
									else { // if not
										transaction = false; // set the transaction into true
									}
								}

								Sleep(2000); // sleep for 2s

								if (transaction) { // verify if the transaction is true
									cout << "\n\n[SUCESS] : Your money was sent...." << endl; // output sucess text
									string str = "\t\t\t--\t" + to_string(listOfClients[i].m_accountNumber) + "\t->\t| " + to_string(amount) + " |\t->\t" + to_string(receiver) + "\t|\t at " + getTime() + "\t|"; // log the transaction
									transferHistory.push_back(str); // push the string into the history of transactions array
								}
								else { // if not
									cout << "[ERROR] : The account number/amount you entered doesn't exist or unavailable for the moment..." << endl; // output error text
								}

								cout << "\n\nYou want to have other transaction ((Y)es or (N)o) : "; // ask the user if he want to do another transaction
								allInfoCorrect = verifyInfoCorrect('Y', 'N'); // assign the verified input of user into the variable
							} while (allInfoCorrect == 'Y'); // repeat if input of user is equal to Yes

							found = true; // set found to true
							break; // break from loop
						}
						else // if not
							found = false; // set found to false
					}

					if (found) // verify if found is true
						break; // break from loop

					cout << "\n\nDo you wanna retry((Y)es or (N)o) : "; // ask the user if all the info above are correct
					allInfoCorrect = verifyInfoCorrect('Y', 'N'); // assign the valid returned value to the variable 
				} while (allInfoCorrect == 'Y'); // repeat when the input of user is equal to Yes

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu

			case 7: // menu 7 : transfers history...
				cout << "\t\t\t\t\t===== transfers history ===== \n\n\n" << endl;  // title of menu

				for (size_t i = 0; i < transferHistory.size(); i++) { // loops through transfers history array
					cout << transferHistory[i] << endl; // ouput transfers info
				}

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu

			case 8: // menu 8: deleted accounts
				cout << "\t\t\t\t\t===== transfers history ===== \n\n\n" << endl;  // title of menu

				cout << "\n\t[NUMBER DELETED ACCOUNT] : " << listOfDeletedAccounts.size() << "\n\n" << endl; // ouput number of clients

				for (size_t i = 0; i < listOfDeletedAccounts.size(); i++) { // loop through the list of clients...
					// output every account info
					cout << "\t\tClient # " << (i + 1) << "\t|\t" << listOfDeletedAccounts[i].m_accountNumber << "\t|\t" << listOfDeletedAccounts[i].m_name << "\t|\t" << listOfDeletedAccounts[i].m_typeOfAccount << " | " << fixed << setprecision(2) << listOfDeletedAccounts[i].m_accountBalance << " $" << endl
						<< "\t\t -> Time of creation : " << listOfDeletedAccounts[i].m_timeOfCreation << "\t|\t Time of deletion : " << listOfDeletedAccounts[i].m_timeOfDelete << endl
						<< "\t\t  -> Reason of deletion : " << listOfDeletedAccounts[i].m_reasonOfDeletion << " |"<< endl;
				}

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu
				
			case 9: // menu 9 : loan menu
				tries = 0; // reset the tries to 0;
				do {
					system("cls"); // clear the screen
					cout << "\t\t\t\t\t===== Loans ===== \n\n\n" << endl;  // title of menu

					if (!found) // verify if found is false
						cout << "[ERROR] : The info entered doesn't match any of our accounts" << endl; // ouput error text

					cout << "\t\t\t\tEnter your account number : "; // asks the user for account number
					cin >> accountNum; // get input of user
					cout << "\t\t\t\tEnter your password : "; // asks the user for password
					cin >> pwd; // get the input of user

					for (size_t i = 0; i < listOfClients.size(); i++) {

						if (accountNum == listOfClients[i].m_accountNumber && pwd == listOfClients[i].m_password) { // verify if inputs of user equal to the info of an existing account
							system("cls"); // clears screen

							cout << "How much do you wanna take as a loan (in $): "; // ask the user for the amount of the loan
							cin >> listOfClients[i].m_loanBalance; // get the input of the user

							cin.clear(); // clears error flags
							cin.ignore(); // ignores next new lineS
							cout << "\n===== Reason of the loan ===========" << endl;
							getline(cin,listOfClients[i].m_reasonOfLoan);
							cout << "====================================\n" << endl;

							if (listOfClients[i].m_loanBalance > (MSBN.m_accountBalance * (1.3/ 100.0))) { // verify if the bank can afford this loan
								listOfClients[i].m_loanBalance = 0; // no loan is granted
								cout << "\n\n[SORRY] : We seem that we can't grant you that amount a loan!" << endl // output error
									<< " -> Please retry another amount..." << endl;
							}
							else { // loan is granted
								MSBN.m_accountBalance -= listOfClients[i].m_loanBalance; // the loan is granted...
								listOfClients[i].m_accountBalance += listOfClients[i].m_loanBalance; // add the amount to the balance
								MSBN.m_loanBalance += listOfClients[i].m_loanBalance; // addthe loan to the total of loans given by the bank
								// output
								cout << "\n\n[SUCESS] : you got a loan!!!" << endl
									<< " -> Please be wise with the new money you got access to.." << endl
									<< "[INFO] : The interest for beign late if -> 2.6%/month" << endl
									<< "[INFO] : You can choose to pay the intrest every month" << endl
									<< "[INFO] : The loan can be taken back or changed anytime your financial situation changes" << endl
									<< "[INFO] : You get a period with no interest -> 4 months" << endl
									<< "[WARNING] : You're responsible for making the payments on time" << endl;
								// log the loan in the history ledger
								loansHistory.push_back("Account # " + to_string(listOfClients[i].m_accountNumber) + "\t|\t Took a loan of " + to_string(listOfClients[i].m_loanBalance) + " $ For" + listOfClients[i].m_reasonOfLoan + "\t|\n\t-> At : " + getTime());
							}

							found = true; // set found to true
							break; // break from loop
						}
						else // if not 
							found = false; // set found to false
					}

					cout << "\n\nDo you wanna retry((Y)es or (N)o) : "; // ask the user if all the info above are correct
					allInfoCorrect = verifyInfoCorrect('Y', 'N'); // assign the valid returned value to the variable 
				} while (allInfoCorrect == 'Y'); // repeat when the input of user is equal to Yes

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu

			case 10: // menu 10 : loan history
				cout << "\t\t\t\t\t===== Loans  history ===== \n\n\n" << endl;  // title of menu
				cout << "\n\t[NUMBER OF LOANS] : " << loansHistory.size() << "\n\n" << endl; // ouput number of clients
				for (size_t i = 0; i < loansHistory.size(); i++) {
					cout << "\t\t" << loansHistory[i] << endl;
				}
				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu

			case 11 : // menu 11 : about us
				historyOfBank(); // call of function about us

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu

			case 14: // hidden menu : MSBN account
				cout << "\t\t\t\t\t===== MSBN ACCOUNT ===== \n\n\n" << endl;  // title of menu
				cout << "\n\n[NAME] -> " << MSBN.m_name << endl
					<< "[TYPE OF ACCOUNT] --> " << MSBN.m_typeOfAccount << endl
					<< "[BALANCE] ---> " << MSBN.m_accountBalance << " $" << endl
					<< "[TOTAL OF LOANS GIVEN] ----> " << MSBN.m_loanBalance << " $" << endl;

				cout << "\n\n" << endl; // skip lines
				system("PAUSE"); // pause program
				break; // break from menu
			};
		}
	} while (choiceMain != 13);



	// end of program
	cout << "\n\n\n\t\t\tThank you for using a MSBN Bank program...\n\n" << endl; // ouput end of program text
	system("PAUSE"); // pause program
	return(0); // end
}

void setup(client &bank)
{
	srand(static_cast<unsigned int> (time(NULL))); // sets up srand
	rand(); // call the first rand();

	// the account of the bank
	bank.m_name = "MSBN";
	bank.m_typeOfAccount = "Main Account";
	bank.m_accountBalance = 1000000;
	bank.m_accountNumber = 5092000;
	bank.m_password = 2018;
	bank.m_timeOfCreation = "Thursday 20/12/2018 05:06";
}

int returnAccountNumber()
{
	int value = 0; // declare a value and inisitalize it to 0;

	for (int i = 0; i < ((rand() % 100) + 5); i++) // loops until a random number between 5 and 100...
		value = ((rand() % 9000000) + 100000); // get a random number between 1 000 000 and 10 000 000 and assign it to value

	return value; // return the random account
}

bool transferTheMoney(client &sender, double &amount, client &receiver, client &fee)
{
	if (sender.m_accountBalance >= (amount + TRANSACTION_FEE)) { // verify if the senders balance is enough to send the amount
		sender.m_accountBalance -= (amount + TRANSACTION_FEE); // substracts the amount from the senders account
		fee.m_accountBalance += TRANSACTION_FEE;
		receiver.m_accountBalance += amount; // add the amount to the receiver account
		return true; // returns true

	} else //if it's the senders balance isn't enough to send the amount
	return false; // return false..
}

char verifyInfoCorrect(char choix1, char choix2)
{
	char value = NULL; // Declare and initialize the character value
	cin >> value; // input of user
	value = toupper(value); // turn it into upper case

	while (value != choix1 && value != choix2) {  // verify if the input isn't equal to both parametres 
		cin.clear();  // clear error flags
		cin.ignore(); // ignore next new line

		cerr << "[Error] : La valeur que vous avez entrez n'est pas valide !" << endl; // output an error
		cout << "Entrer la nouvelle valeur : "; // ask the user to enter a new value
		cin >> value; // new input of user
		value = toupper(value); // put the value into upper case and assign it to the variable
	}

	return value; // return valide input
}

string getTime()
{
	string date = ""; 
	SYSTEMTIME st = { 0 };

	GetLocalTime(&st);

	date = to_string(st.wYear) + "/" + to_string(st.wMonth) + "/" + to_string(st.wDay) + "  " + to_string(st.wHour) + ":" + to_string(st.wMinute) + ":" + to_string(st.wSecond) + ":" + to_string(st.wMilliseconds);

	return date;
}

void historyOfBank()
{
	cout << "\t\t\t\t\t===== About us ===== \n\n\n" << endl;  // title of menu

	cout << "Always earning the right to be our clients first choice"<< endl
		 << "The MSBN History site has been created to remember and celebrate our heritage and the \ngenerations of men and women who transformed \nour company into a leader in Canada and a growing force in countries around the world." << endl
		 << "Over the years we have invested in the future by delivering quality \nproducts, creating jobs, protecting the environment, \nrespecting diversity and making a difference in the communities that we serve.\nOur shared values of service, teamwork, responsibility, diversity and integrity \nhelp guide our behaviours and decisions, inspire us to lead in diversity and inclusion and define what it means to be a responsible corporate citizen." << endl
		 << "Today, approximately 79, 000 client - focused and committed employees help us earn the right to be our clients’ first choice, \ndifferentiating us as an exceptional source of advice for the 16 million clients worldwide that we serve." << endl;
}

double savingsRates(client account)
{
	return account.m_accountBalance* pow((1 + SAVINGS_INTEREST / 100), account.m_timeOfsaving); // return the balance with interest
}
