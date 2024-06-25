
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const string fileName = "Filee.txt";
const string fileUsers = "FileUsers.txt";

enum enChoose {
	show_Clients_List = 1, add_New_Client = 2, delete_Client = 3,
	updata_Client = 4, find_Client = 5, trans_Action = 6, ManageUsers = 7, exit_Program = 8
};

enum enChooseManageUser {
	listUser = 1, newUser = 2, deleteUser = 3, updateUser = 4,
	findUser = 5, main_menu = 6
};

enum enChooseTransactions {
	deposit = 1, withdraw = 2,
	totalBalances = 3, mainMenu = 4
};

struct stDataUsers {
	string userName, password;
	int permissions;
	bool showClientsList = false, addNewClients = false, deleteClients = false,
		updateClients = false, findClients = false, ifUser = false, transActions = false,
		manageUsers = false;
};

struct stData {
	string accountNumber, pinCode, name, phone, accountBalance;
};

stDataUsers userDataFile;

void login();
stDataUsers access(stDataUsers&, bool);
void showMainScreen(short);
void ManageUsersScreen(short);
void showTransactionsList(vector<stData>&, short);

vector<string> enterInfoLinesInVector(string line, string separetor) {

	vector<string> result;

	short pos = 0;
	string temp;

	while ((pos = line.find(separetor)) != string::npos) {

		temp = line.substr(0, pos);
		if (temp != "") {
			result.push_back(temp);
		}

		line = line.erase(0, pos + separetor.length());

	}

	if (line != "") {
		result.push_back(line);
	}

	return result;
}

stData informationClient(string line, string separetor) {
	stData info;

	vector<string> vInfo = enterInfoLinesInVector(line, separetor);

	info.accountNumber = vInfo.at(0);
	info.pinCode = vInfo.at(1);
	info.name = vInfo.at(2);
	info.phone = vInfo.at(3);
	info.accountBalance = vInfo.at(4);

	return info;
}

stDataUsers informationUsers(string line, string separetor) {
	stDataUsers info;

	vector<string> vInfo = enterInfoLinesInVector(line, separetor);

	info.userName = vInfo.at(0);
	info.password = vInfo.at(1);
	info.permissions = stoi(vInfo.at(2));
	info.showClientsList = stoi(vInfo.at(3));
	info.addNewClients = stoi(vInfo.at(4));
	info.deleteClients = stoi(vInfo.at(5));
	info.updateClients = stoi(vInfo.at(6));
	info.findClients = stoi(vInfo.at(7));
	info.transActions = stoi(vInfo.at(8));
	info.manageUsers = stoi(vInfo.at(9));

	return info;
}

vector<stDataUsers> getUsersDataFromFile(string fileUsers) {

	vector<stDataUsers> getUsersDataFile;

	fstream theFile;
	theFile.open(fileUsers, ios::in);

	if (theFile.is_open()) {

		string line;
		stDataUsers user;

		while (getline(theFile, line)) {

			if (line != "") {

				user = informationUsers(line, "#//#");
				getUsersDataFile.push_back(user);

			}
		}
		theFile.close();
	}

	return getUsersDataFile;

}

vector<stData> getDataFromFile(string fileName) {

	vector<stData> getbankDataFile;
	fstream theFile;
	theFile.open(fileName, ios::in);

	if (theFile.is_open()) {

		string line;
		stData client;

		while (getline(theFile, line)) {

			if (line != "") {

				client = informationClient(line, "#//#");
				getbankDataFile.push_back(client);

			}
		}
		theFile.close();
	}

	return getbankDataFile;

}

string convertDataClientToFile(stData info, string delim) {
	string line = "";

	line += info.accountNumber + delim;
	line += info.pinCode + delim;
	line += info.name + delim;
	line += info.phone + delim;
	line += info.accountBalance;

	return line;
}

string convertDataUserToFile(stDataUsers info, string delim) {
	string line = "";

	line += info.userName + delim;
	line += info.password + delim;
	line += to_string(info.permissions) + delim;
	line += to_string(info.showClientsList) + delim;
	line += to_string(info.addNewClients) + delim;
	line += to_string(info.deleteClients) + delim;
	line += to_string(info.updateClients) + delim;
	line += to_string(info.findClients) + delim;
	line += to_string(info.transActions) + delim;
	line += to_string(info.manageUsers);

	return line;
}

void falseChoose() {

	cout << "\n------------------------------------------" << endl;
	cout << "Access Denied," << endl;
	cout << "You Dont Have Permission To Do this," << endl;
	cout << "Please Conact Your Admin." << endl;
	cout << "------------------------------------------" << endl;
}

void printDataClient(stData info) {

	cout << "\nthe following are the client details:" << endl;

	cout << "\nAccount Number: " << info.accountNumber << endl;
	cout << "Pin Code: " << info.pinCode << endl;
	cout << "Name: " << info.name << endl;
	cout << "Phone: " << info.phone << endl;
	cout << "Account Balance: " << info.accountBalance << endl;

}

void printDataUser(stDataUsers info) {

	cout << "\nthe following are the user details:" << endl;

	cout << "\nUsername: " << info.userName << endl;
	cout << "Password: " << info.password << endl;
	cout << "Permissions: " << info.permissions << endl;

}

bool ifFoundClient(string& accountNumber, stData& infoUser) {

	return (infoUser.accountNumber == accountNumber);

}

bool ifFoundUser(string& Username, stDataUsers& infoUser) {
	return (infoUser.userName == Username);
}

stData FindClientPosition(bool& isClientAlreadyFound, vector<stData>& bankDataFile) {
	string accountNumber;
	stData position;

	cout << "please enter account number: "; cin >> accountNumber;

	for (short i = 0; i < bankDataFile.size(); i++) {

		if (ifFoundClient(accountNumber, bankDataFile.at(i))) {

			stData findAccount = bankDataFile.at(i);
			printDataClient(findAccount);

			isClientAlreadyFound = true;
			position = findAccount;

			return position;
		}
	}

	cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!" << endl;
	return position;
}

stDataUsers findUserPosition(bool& isUserAlreadyFound, vector<stDataUsers>& usersDataFile) {

	string userName;
	stDataUsers position;

	cout << "please enter Username: "; cin >> userName;

	if (userName == "Admin") {

		position.ifUser = true;
		return position;

	}

	for (short i = 0; i < usersDataFile.size(); i++) {

		if (ifFoundUser(userName, usersDataFile.at(i))) {

			stDataUsers findAccount = usersDataFile.at(i);
			printDataUser(findAccount);

			isUserAlreadyFound = true;
			position = findAccount;

			return position;
		}
	}

	cout << "\nUser with Username (" << userName << ") is Not Found!" << endl;
	return position;

}

stDataUsers findUserPositionAndPrint(bool& isUserAlreadyFound, vector<stDataUsers>& usersDataFile) {

	string userName;
	stDataUsers position;

	cout << "please enter Username: "; cin >> userName;

	for (short i = 0; i < usersDataFile.size(); i++) {

		if (ifFoundUser(userName, usersDataFile.at(i))) {

			stDataUsers findAccount = usersDataFile.at(i);
			printDataUser(findAccount);

			isUserAlreadyFound = true;
			position = findAccount;

			return position;
		}
	}

	cout << "\nClient with Account Number (" << userName << ") is Not Found!" << endl;
	return position;
}

void showFindClientScreen(vector<stData>& bankDataFile) {

	cout << "-------------------------------------" << endl;
	cout << "\tFind Client Screen" << endl;
	cout << "-------------------------------------\n" << endl;

	bool isClientAlreadyFound = false;

	FindClientPosition(isClientAlreadyFound, bankDataFile);

}

void showFindUserScreen(vector<stDataUsers>& usersDataFile) {

	cout << "-------------------------------------" << endl;
	cout << "\tFind User Screen" << endl;
	cout << "-------------------------------------\n" << endl;

	bool isUserAlreadyFound = false;

	findUserPositionAndPrint(isUserAlreadyFound, usersDataFile);
}

stData updateClientData(stData info) {


	cout << "Enter PinCode: ";
	getline(cin >> ws, info.pinCode);

	cout << "Enter Name: ";
	getline(cin, info.name);

	cout << "Enter Phone: ";
	getline(cin, info.phone);

	cout << "Enter Account Balance: ";
	getline(cin, info.accountBalance);

	return info;
}

stDataUsers updateUserData(stDataUsers& info) {

	cout << "Enter Password: ";
	getline(cin, info.password);

	char fullAccess;
	cout << "\nDo You Want to Give Full Access? y/n?"; cin >> fullAccess;

	if (fullAccess == 'y' || fullAccess == 'Y') access(info, true);

	else access(info, false);

	return info;
}

void updateClient(vector<stData>& bankDataFile, stData& position) {

	string line;
	fstream theFile;
	theFile.open(fileName, ios::out);

	cout << endl << endl;

	if (theFile.is_open()) {

		for (short i = 0; i < bankDataFile.size(); i++) {
			if (bankDataFile.at(i).accountNumber == position.accountNumber) {
				bankDataFile.at(i) = updateClientData(bankDataFile.at(i));
			}

			line = convertDataClientToFile(bankDataFile.at(i), "#//#");
			theFile << line << endl;
		}

		theFile.close();
	}

}

void updateUsers(vector<stDataUsers>& usersDataFile, stDataUsers& position) {

	string line;
	fstream theFile;
	theFile.open("FileUsers.txt", ios::out);

	cout << endl << endl;

	if (theFile.is_open()) {

		for (short i = 0; i < usersDataFile.size(); i++) {
			if (usersDataFile.at(i).userName == position.userName) {
				usersDataFile.at(i) = updateUserData(usersDataFile.at(i));
			}

			line = convertDataUserToFile(usersDataFile.at(i), "#//#");
			theFile << line << endl;
		}

		theFile.close();
	}

}

void showUpdateClientScreen(vector<stData>& bankDataFile) {

	cout << "-------------------------------------" << endl;
	cout << "\tUpdate Client Screen" << endl;
	cout << "-------------------------------------\n" << endl;

	bool isClientAlreadyFound = false;
	stData position = FindClientPosition(isClientAlreadyFound, bankDataFile);

	char YesUpdate;
	if (isClientAlreadyFound) {

		cout << "Are You Sure You Want Update This Client? y/n "; cin >> YesUpdate;

		if (YesUpdate == 'Y' || YesUpdate == 'y') {
			updateClient(bankDataFile, position);
			cout << "\n\nClient Updated Successfully";
		}

	}

}

void showUpdateUsersScreen(vector<stDataUsers>& usersDataFile) {

	cout << "-------------------------------------" << endl;
	cout << "\tUpdate Users Screen" << endl;
	cout << "-------------------------------------\n" << endl;

	bool isUserAlreadyFound = false;
	stDataUsers position = findUserPosition(isUserAlreadyFound, usersDataFile);

	char YesUpdate;
	if (isUserAlreadyFound) {

		cout << "Are You Sure You Want Update This Client? y/n "; cin >> YesUpdate;

		if (YesUpdate == 'Y' || YesUpdate == 'y') {
			updateUsers(usersDataFile, position);
			cout << "\n\nClient Updated Successfully";
		}

	}

}

void deleteClient(vector<stData>& bankDataFile, stData& position) {

	string line;
	fstream theFile;
	theFile.open(fileName, ios::out);

	if (theFile.is_open()) {

		for (short i = 0; i < bankDataFile.size(); i++) {
			if (bankDataFile.at(i).accountNumber != position.accountNumber) {

				line = convertDataClientToFile(bankDataFile.at(i), "#//#");
				theFile << line << endl;
			}
		}
		theFile.close();
	}
}

void deleteUsers(vector<stDataUsers>& usersDataFile, stDataUsers& position) {

	string line;
	fstream theFile;
	theFile.open(fileUsers, ios::out);

	if (theFile.is_open()) {

		for (short i = 0; i < usersDataFile.size(); i++) {
			if (usersDataFile.at(i).userName != position.userName) {

				line = convertDataUserToFile(usersDataFile.at(i), "#//#");
				theFile << line << endl;
			}
		}
		theFile.close();
	}
}

void addClients(string result) {

	fstream theFile;
	theFile.open("Filee.txt", ios::out | ios::app);

	if (theFile.is_open()) {
		theFile << result << endl;

		theFile.close();
	}
}

void addUsers(string result) {

	fstream theFile;
	theFile.open("FileUsers.txt", ios::out | ios::app);

	if (theFile.is_open()) {
		theFile << result << endl;

		theFile.close();
	}
}

void showDeleteClientScreen(vector<stData>& bankDataFile) {

	cout << "-------------------------------------" << endl;
	cout << "\tDelete Client Screen" << endl;
	cout << "-------------------------------------\n" << endl;

	bool isClientAlreadyFound = false;
	stData position = FindClientPosition(isClientAlreadyFound, bankDataFile);

	char YesDelete;
	if (isClientAlreadyFound) {

		cout << "Are You Sure You Want Delete This Client? y/n? "; cin >> YesDelete;

		if (YesDelete == 'Y' || YesDelete == 'y') {
			deleteClient(bankDataFile, position);
			cout << "\n\nClient Deleted Successfully";
		}

	}

}

void showDeleteUserScreen(vector<stDataUsers>& usersDataFile) {

	cout << "-------------------------------------" << endl;
	cout << "\tDelete User Screen" << endl;
	cout << "-------------------------------------\n" << endl;

	bool isUserAlreadyFound = false;
	stDataUsers position = findUserPosition(isUserAlreadyFound, usersDataFile);

	if (position.ifUser) {
		cout << "You Can not Delete This User" << endl;
		return;
	}

	char YesDelete;
	if (isUserAlreadyFound) {

		cout << "\nAre You Sure You Want Delete This User? y/n? "; cin >> YesDelete;

		if (YesDelete == 'Y' || YesDelete == 'y') {
			deleteUsers(usersDataFile, position);
			cout << "\n\nUser Deleted Successfully";
		}

	}
}

bool isFindClientByAccNumber_toAddNewClient(string accNumber, vector<stData>& bankDataFile) {
	for (short i = 0; i < bankDataFile.size(); i++) {
		if (accNumber == bankDataFile.at(i).accountNumber) return true;
	}
	return false;
}

bool isFindUserByUserName(string userName, vector<stDataUsers>& usersDataFile) {
	for (short i = 0; i < usersDataFile.size(); i++) {
		if (userName == usersDataFile.at(i).userName) return true;
	}
	return false;
}

stData ReadNewClient(vector<stData>& bankDataFile) {

	stData info;

	cout << "Enter Account Number: ";
	getline(cin >> ws, info.accountNumber);

	while (isFindClientByAccNumber_toAddNewClient(info.accountNumber, bankDataFile)) {

		cout << "Client With [" << info.accountNumber << "] Already Exists, Another Account Number ? ";
		getline(cin, info.accountNumber);

	}

	cout << "Enter PinCode: ";
	getline(cin, info.pinCode);

	cout << "Enter Name: ";
	getline(cin, info.name);

	cout << "Enter Phone: ";
	getline(cin, info.phone);

	cout << "Enter Account Balance: ";
	getline(cin, info.accountBalance);

	return info;
}

stDataUsers access(stDataUsers& info, bool check = false) {

	char enterAccess;

	if (check) {

		info.addNewClients = true;
		info.deleteClients = true;
		info.findClients = true;
		info.showClientsList = true;
		info.updateClients = true;
		info.permissions = -1;
		info.transActions = true;
		info.manageUsers = true;


		return info;

	}

	else {

		info.permissions = 17;
		cout << "Do You Want to Give Access to :\n" << endl;

		cout << "Show Clients List y/n? "; cin >> enterAccess;
		(enterAccess == 'y' || enterAccess == 'Y') ? info.showClientsList = true : info.showClientsList = false;

		cout << "Add New Client y/n? "; cin >> enterAccess;
		(enterAccess == 'y' || enterAccess == 'Y') ? info.addNewClients = true : info.addNewClients = false;

		cout << "Delete Client y/n? "; cin >> enterAccess;
		(enterAccess == 'y' || enterAccess == 'Y') ? info.deleteClients = true : info.deleteClients = false;

		cout << "Update Client y/n? "; cin >> enterAccess;
		(enterAccess == 'y' || enterAccess == 'Y') ? info.updateClients = true : info.updateClients = false;

		cout << "Find Client y/n? "; cin >> enterAccess;
		(enterAccess == 'y' || enterAccess == 'Y') ? info.findClients = true : info.findClients = false;

		cout << "Transactions y/n? "; cin >> enterAccess;
		(enterAccess == 'y' || enterAccess == 'Y') ? info.transActions = true : info.transActions = false;

		cout << "Manage Users y/n? "; cin >> enterAccess;
		(enterAccess == 'y' || enterAccess == 'Y') ? info.manageUsers = true : info.manageUsers = false;

	}

	return info;

}

stDataUsers ReadNewUser(vector<stDataUsers>& usersDataFile) {

	stDataUsers info;

	cout << "Enter Username: ";
	getline(cin >> ws, info.userName);

	while (isFindUserByUserName(info.userName, usersDataFile)) {

		cout << "User With [" << info.userName << "] Already Exists, Another Username ? ";
		getline(cin, info.userName);

	}

	cout << "Enter Password: ";
	getline(cin, info.password);

	char fullAccess;
	cout << "\nDo You Want to Give Full Access? y/n?"; cin >> fullAccess;

	if (fullAccess == 'y' || fullAccess == 'Y') access(info, true);

	else access(info);

	return info;

}

void showAddClientScreen(vector<stData>& bankDataFile) {

	char addMoreClient = 'y';

	do {
		system("cls");

		cout << "-------------------------------------" << endl;
		cout << "\tAdd New Client Screen" << endl;
		cout << "-------------------------------------\n" << endl;
		cout << "\nAdding New Client:" << endl;

		string addClient = "";
		stData info = ReadNewClient(bankDataFile);
		addClient += convertDataClientToFile(info, "#//#");

		addClients(addClient);

		cout << "\n\nClient Added Succsessfully, do You Want Add More Clients? y/n? "; cin >> addMoreClient;

	} while (addMoreClient == 'Y' || addMoreClient == 'y');
}

void showAddUserScreen(vector<stDataUsers>& usersDataFile) {

	char addMoreUser = 'y';

	do {
		system("cls");

		cout << "-------------------------------------" << endl;
		cout << "\tAdd New User Screen" << endl;
		cout << "-------------------------------------\n" << endl;
		cout << "\nAdding New User:" << endl;

		string addUser = "";
		stDataUsers info = ReadNewUser(usersDataFile);
		addUser += convertDataUserToFile(info, "#//#");

		addUsers(addUser);

		cout << "\n\nUser Added Succsessfully, do You Want Add More Users? y/n? "; cin >> addMoreUser;

	} while (addMoreUser == 'Y' || addMoreUser == 'y');

}

void showEndScreen() {

	system("cls");

	cout << "-------------------------------------" << endl;
	cout << "\tProgram End :-)" << endl;
	cout << "-------------------------------------\n" << endl;
	return;
}

void printDataOfClient(stData client) {

	cout << "|" << setw(15) << left << client.accountNumber;
	cout << "|" << setw(10) << left << client.pinCode;
	cout << "|" << setw(40) << left << client.name;
	cout << "|" << setw(12) << left << client.phone;
	cout << "|" << setw(12) << left << client.accountBalance;
}

void printDataOfUser(stDataUsers user) {

	cout << "|" << setw(15) << left << user.userName;
	cout << "|" << setw(10) << left << user.password;
	cout << "|" << setw(40) << left << user.permissions;

}

void showClientsList(vector<stData>& bankDataFile) {

	cout << "\n\t\t\t\t\tClient List (" << bankDataFile.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "|" << setw(15) << left << "Account Number";
	cout << "|" << setw(10) << left << "Pin Code";
	cout << "|" << setw(40) << left << "Account Name";
	cout << "|" << setw(12) << left << "Phone";
	cout << "|" << setw(12) << left << "Balance";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (stData& client : bankDataFile) {

		printDataOfClient(client);
		cout << endl;

	}

	cout << "_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

void showUsersList(vector<stDataUsers>& usersDataFile) {
	cout << "\n\t\t\t\t\tClient List (" << usersDataFile.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "|" << setw(15) << left << "User Name";
	cout << "|" << setw(10) << left << "Password";
	cout << "|" << setw(40) << left << "Permissions";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (stDataUsers& user : usersDataFile) {

		printDataOfUser(user);
		cout << endl;

	}

	cout << "_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void Update_After_Deposite_Withdraw(stData& position, vector<stData>& bankDataFile) {

	string line;
	fstream theFile;
	theFile.open(fileName, ios::out);

	cout << endl << endl;

	if (theFile.is_open()) {

		for (short i = 0; i < bankDataFile.size(); i++) {

			if (bankDataFile.at(i).pinCode == position.pinCode) {

				bankDataFile.at(i).accountBalance = position.accountBalance;

			}

			line = convertDataClientToFile(bankDataFile.at(i), "#//#");
			theFile << line << endl;

		}

		theFile.close();
	}

}

string depositTransaction(short depositAmount, string accountBalance) {

	string totalBalance = to_string(stoi(accountBalance) + depositAmount);

	char testDeposit;
	cout << "Are you sure you want perform this transaction? y/n ? "; cin >> testDeposit;

	return (tolower(testDeposit) == 'y') ? totalBalance : accountBalance;
}

void showDepositeScreen(vector<stData>& bankDataFile) {

	short depositAmount;

	cout << "------------------------------------------" << endl;
	cout << "\tDeposite Screen" << endl;
	cout << "------------------------------------------\n" << endl;

	bool isClientAlreadyFound = false;
	stData position;

	while (!isClientAlreadyFound) {

		position = FindClientPosition(isClientAlreadyFound, bankDataFile);

	}

	cout << "------------------------------------------\n" << endl;
	cout << "please enter deposit amount? "; cin >> depositAmount;

	while (cin.fail() || depositAmount <= 0) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (depositAmount < 0) cout << "enter positeve number, ";
		cout << "please enter another deposit amount? "; cin >> depositAmount;
	}

	string testChangeValue = position.accountBalance;

	position.accountBalance = depositTransaction(depositAmount, position.accountBalance);

	if (testChangeValue != position.accountBalance) {

		cout << "\nDone succssesfly new balance, new balance is: " << position.accountBalance;

		Update_After_Deposite_Withdraw(position, bankDataFile);
	}
}

string withdrawTransaction(short withdrawAmount, string accountBalance) {

	while (cin.fail() || withdrawAmount > stoi(accountBalance) || withdrawAmount <= 0) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (withdrawAmount <= 0) cout << "This value is not true, ";
		else cout << "Amount Exceeds the balance, you can withdraw up to : " << accountBalance << endl;
		cout << "please enter withard amount? "; cin >> withdrawAmount;

	}

	string totalBalance = to_string(stoi(accountBalance) - withdrawAmount);

	char testwithdraw;
	cout << "Are you sure you want perform this transaction? y/n ? "; cin >> testwithdraw;

	return (tolower(testwithdraw) == 'y') ? totalBalance : accountBalance;
}

void showWithdrawScreen(vector<stData>& bankDataFile) {
	short withdrawAmount;

	cout << "------------------------------------------" << endl;
	cout << "\tWithard Screen" << endl;
	cout << "------------------------------------------\n" << endl;

	bool isClientAlreadyFound = false;
	stData position;

	while (!isClientAlreadyFound) {

		position = FindClientPosition(isClientAlreadyFound, bankDataFile);

	}

	cout << "------------------------------------------\n" << endl;
	cout << "please enter withard amount? "; cin >> withdrawAmount;

	while (cin.fail() || withdrawAmount <= 0) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (withdrawAmount <= 0) cout << "This value is not true, " <<
			"please enter withard amount? "; cin >> withdrawAmount;

	}

	string testChangeValue = position.accountBalance;

	position.accountBalance = withdrawTransaction(withdrawAmount, position.accountBalance);

	if (testChangeValue != position.accountBalance) {

		cout << "\nDone succssesfly new balance, new balance is: " << position.accountBalance;

		Update_After_Deposite_Withdraw(position, bankDataFile);
	}

}

void printTotalBalancesMenu(stData& client) {

	cout << "|" << setw(15) << left << client.accountNumber;
	cout << "|" << setw(40) << left << client.name;
	cout << "|" << setw(42) << left << client.accountBalance;

}

void showTotalBalances(vector<stData>& bankDataFile) {

	cout << "\n\t\t\t\t\tBalances List (" << bankDataFile.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "|" << setw(15) << left << "Account Number";
	cout << "|" << setw(40) << left << "Account Name";
	cout << "|" << setw(42) << left << "Balance";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	int totalBalances = 0;

	for (stData& client : bankDataFile) {

		totalBalances += stoi(client.accountBalance);
		printTotalBalancesMenu(client);
		cout << endl;

	}

	cout << "_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\tTotal Balances = " << totalBalances << endl;

}

void chooseOperationTransctions(short chooseTransaction, vector<stData>& bankDataFile, short position) {

	system("cls");

	switch (chooseTransaction) {

	case enChooseTransactions::deposit: {
		showDepositeScreen(bankDataFile);
		break;
	}
	case enChooseTransactions::withdraw: {
		showWithdrawScreen(bankDataFile);
		break;
	}
	case enChooseTransactions::totalBalances: {
		showTotalBalances(bankDataFile);
		break;
	}
	case enChooseTransactions::mainMenu: {
		showMainScreen(position);
		break;
	}
	}

	cout << "\nPress Any Key To Go Back To Main Menu...";
	system("pause>0");
	showTransactionsList(bankDataFile, position);

}

void showTransactionsList(vector<stData>& bankDataFile, short position) {

	system("cls");
	short chooseTransaction;

	cout << "------------------------------------------" << endl;
	cout << "\tTransactions Menu Screen" << endl;
	cout << "------------------------------------------" << endl;
	cout << "\t[1] Deposit." << endl;
	cout << "\t[2] Withdraw." << endl;
	cout << "\t[3] Total Balances." << endl;
	cout << "\t[4] Main Menu." << endl;
	cout << "------------------------------------------" << endl;
	cout << "Choose What Do You Want To Do? [1 to 4]? "; cin >> chooseTransaction;

	while (cin.fail() || chooseTransaction < 1 || chooseTransaction > 4) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Choose What Do You Want To Do? [1 to 4]? "; cin >> chooseTransaction;

	}
	chooseOperationTransctions(chooseTransaction, bankDataFile, position);
}

void chooseOperationManage(short chooseManage, vector<stDataUsers>& usersDataFile, short position) {

	system("cls");

	switch (chooseManage) {

	case enChooseManageUser::listUser: {
		showUsersList(usersDataFile);
		break;
	}
	case enChooseManageUser::newUser: {
		showAddUserScreen(usersDataFile);
		break;
	}
	case enChooseManageUser::deleteUser: {
		showDeleteUserScreen(usersDataFile);
		break;
	}
	case enChooseManageUser::updateUser: {
		showUpdateUsersScreen(usersDataFile);
		break;
	}
	case enChooseManageUser::findUser: {
		showFindUserScreen(usersDataFile);
		break;
	}
	case enChooseManageUser::main_menu: {
		showMainScreen(position);
		break;
	}
	}

	cout << "\nPress Any Key To Go Back To Manage Users Menu...";
	system("pause>0");
	ManageUsersScreen(position);

}

void ManageUsersScreen(short position) {

	vector<stDataUsers> usersDataFile = getUsersDataFromFile(fileUsers);

	system("cls");
	short chooseManage;

	cout << "------------------------------------------" << endl;
	cout << "\tManage Users Menu Screen" << endl;
	cout << "------------------------------------------" << endl;
	cout << "\t[1] List Users." << endl;
	cout << "\t[2] Add New User." << endl;
	cout << "\t[3] Delete User." << endl;
	cout << "\t[4] Update User." << endl;
	cout << "\t[5] Find User." << endl;
	cout << "\t[6] Main Menu." << endl;
	cout << "------------------------------------------" << endl;
	cout << "Choose What Do You Want To Do? [1 to 6]? "; cin >> chooseManage;

	while (cin.fail() || chooseManage < 1 || chooseManage > 6) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Choose What Do You Want To Do? [1 to 6]? "; cin >> chooseManage;

	}
	chooseOperationManage(chooseManage, usersDataFile, position);
}

void chooseWhatDoYouWant(short chooseOption, stDataUsers& userDataFile, vector<stData>& bankDataFile, short position) {

	system("cls");

	switch (chooseOption) {

	case enChoose::show_Clients_List: {
		(userDataFile.showClientsList) ? showClientsList(bankDataFile) : falseChoose();
		break;
	}
	case enChoose::add_New_Client: {
		(userDataFile.addNewClients) ? showAddClientScreen(bankDataFile) : falseChoose();
		break;
	}
	case enChoose::delete_Client: {
		(userDataFile.deleteClients) ? showDeleteClientScreen(bankDataFile) : falseChoose();
		break;
	}
	case enChoose::updata_Client: {
		(userDataFile.updateClients) ? showUpdateClientScreen(bankDataFile) : falseChoose();
		break;
	}
	case enChoose::find_Client: {
		(userDataFile.findClients) ? showFindClientScreen(bankDataFile) : falseChoose();
		break;
	}
	case enChoose::trans_Action: {
		(userDataFile.transActions) ? showTransactionsList(bankDataFile, position) : falseChoose();
		break;
	}
	case enChoose::ManageUsers: {
		(userDataFile.manageUsers) ? ManageUsersScreen(position) : falseChoose();
		break;
	}
	case enChoose::exit_Program: {
		login();
		return;
	}
	}

	cout << "\n\nPress Any Key To Go Back To Main Menu...";
	system("pause>0");
	showMainScreen(position);

}

void showMainScreen(short position) {

	vector<stDataUsers> usersDataFile = getUsersDataFromFile(fileUsers);
	vector<stData> bankDataFile = getDataFromFile(fileName);
	short chooseOption;

	system("cls");

	cout << "================================================" << endl;
	cout << "\t\tMain Menu Screen" << endl;
	cout << "================================================" << endl;
	cout << "\t[1] Show Client List." << endl;
	cout << "\t[2] Add New Client." << endl;
	cout << "\t[3] Delete Client." << endl;
	cout << "\t[4] Update Client Info." << endl;
	cout << "\t[5] Find Client." << endl;
	cout << "\t[6] Transactions." << endl;
	cout << "\t[7] Manage Users." << endl;
	cout << "\t[8] Log Out." << endl;
	cout << "================================================" << endl;
	cout << "Choose What Do You Want To Do? [1 to 8]? "; cin >> chooseOption;

	while (cin.fail() || chooseOption < 1 || chooseOption > 8) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Choose What Do You Want To Do? [1 to 8]? "; cin >> chooseOption;

	}

	userDataFile = usersDataFile.at(position);

	chooseWhatDoYouWant(chooseOption, userDataFile, bankDataFile, position);

}

bool isTheSamePassword(stDataUsers usersDataFile, string pass) {
	return (usersDataFile.password == pass);
}

bool isUserFound(short& position, vector<stDataUsers>& usersDataFile, string userName) {

	for (int i = 0; i < usersDataFile.size(); i++) {
		if (usersDataFile.at(i).userName == userName) return true;
		else position++;

	}
	return false;
}

void printLoginScreen() {

	system("cls");

	cout << "-------------------------------------" << endl;
	cout << "\tLogin Screen" << endl;
	cout << "-------------------------------------" << endl;

}

void login() {

	vector<stDataUsers> usersDataFile = getUsersDataFromFile(fileUsers);
	string userName, password;
	short position = 0;

	printLoginScreen();

	do {

		cout << "Enter Username: "; cin >> userName;

		if (!isUserFound(position, usersDataFile, userName)) {

			printLoginScreen();
			cout << "Invalid Username!" << endl;

		}

	} while (!isUserFound(position, usersDataFile, userName));


	do {

		cout << "Enter Password: "; cin >> password;

		if (!isTheSamePassword(usersDataFile.at(position), password))  cout << "Invalid Password!" << endl;

	} while (!isTheSamePassword(usersDataFile.at(position), password));

	showMainScreen(position);

}

int main() {

	login();

	return 0;
}