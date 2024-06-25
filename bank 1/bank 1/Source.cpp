
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

void showMainScreen();

const string fileName = "Filee.txt";

enum enChoose { show_Clients_List = 1, add_New_Client = 2, delete_Client = 3, updata_Client = 4, find_Client = 5, exit_Program = 6 };

struct stData {
	string accountNumber, pinCode, name, phone, accountBalance;
};

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

void printDataClient(stData info) {

	cout << "\nthe following are the client details:" << endl;

	cout << "\nAccount Number: " << info.accountNumber << endl;
	cout << "Pin Code: " << info.pinCode << endl;
	cout << "Name: " << info.name << endl;
	cout << "Phone: " << info.phone << endl;
	cout << "Account Balance: " << info.accountBalance << endl;

}

bool ifFoundClient(string& accountNumber, stData& infoUser) {

	return (infoUser.accountNumber == accountNumber);

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

	cout << "\nClient with Account Number (" << accountNumber << ") is Not Found!";
	return position;
}

void showFindClientScreen(vector<stData>& bankDataFile) {

	cout << "-------------------------------------" << endl;
	cout << "\tFind Client Screen" << endl;
	cout << "-------------------------------------\n" << endl;

	bool isClientAlreadyFound = false;

	FindClientPosition(isClientAlreadyFound, bankDataFile);

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

void addClients(string result) {

	fstream theFile;
	theFile.open("Filee.txt", ios::out | ios::app);

	if (theFile.is_open()) {
		theFile << result << endl;

		theFile.close();
	}
}

bool isFindClientByAccNumber_toAddNewClient(string accNumber, vector<stData>& bankDataFile) {
	for (short i = 0; i < bankDataFile.size(); i++) {
		if (accNumber == bankDataFile.at(i).accountNumber) return false;
	}
	return true;
}

stData ReadNewClient(vector<stData>& bankDataFile) {

	stData info;

	cout << "Enter Account Number: ";
	getline(cin >> ws, info.accountNumber);

	while (!isFindClientByAccNumber_toAddNewClient(info.accountNumber, bankDataFile)) {

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

void showEndScreen() {

	system("cls");

	cout << "-------------------------------------" << endl;
	cout << "\tProgram End :-)" << endl;
	cout << "-------------------------------------\n" << endl;
}

void printDataOfClient(stData client) {

	cout << "|" << setw(15) << left << client.accountNumber;
	cout << "|" << setw(10) << left << client.pinCode;
	cout << "|" << setw(40) << left << client.name;
	cout << "|" << setw(12) << left << client.phone;
	cout << "|" << setw(12) << left << client.accountBalance;
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

void chooseWhatDoYouWant(short chooseOption, vector<stData>& bankDataFile) {

	system("cls");

	switch (chooseOption) {

	case enChoose::show_Clients_List: {
		showClientsList(bankDataFile);
		break;
	}
	case enChoose::add_New_Client: {
		showAddClientScreen(bankDataFile);
		break;
	}
	case enChoose::delete_Client: {
		showDeleteClientScreen(bankDataFile);
		break;
	}
	case enChoose::updata_Client: {
		showUpdateClientScreen(bankDataFile);
		break;
	}
	case enChoose::find_Client: {
		showFindClientScreen(bankDataFile);
		break;
	}
	case enChoose::exit_Program: {
		showEndScreen();
		return;
	}
	}

	cout << "\n\nPress Any Key To Go Back To Main Menu...";
	system("pause>0");
	showMainScreen();

}

void showMainScreen() {

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
	cout << "\t[6] Exit." << endl;
	cout << "================================================" << endl;
	cout << "Choose Wat Do You Want To Do? [1 to 6]? "; cin >> chooseOption;

	while (cin.fail() || chooseOption < 1 || chooseOption > 6) {

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Choose Wat Do You Want To Do? [1 to 6]? "; cin >> chooseOption;

	}

	chooseWhatDoYouWant(chooseOption, bankDataFile);

}

int main() {

	showMainScreen();

	return 0;
}