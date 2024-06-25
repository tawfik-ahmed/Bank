#pragma once

#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include <fstream>
#include "clsDate.h"

class clsTransferScreen : protected clsScreen
{

private:

	static string _LoadDataTransferToLine(float transferAmount, clsBankClient Client1, clsBankClient Client2, string Space = "#//#") {

		string line = "";
		line += clsDate::GetSystemDateTimeString() + Space;
		line += Client1.AccountNumber() + Space;
		line += Client2.AccountNumber() + Space;
		line += to_string(transferAmount) + Space;
		line += to_string(Client1.AccountBalance) + Space;
		line += to_string(Client2.AccountBalance) + Space;
		line += CurrentUser.UserName;

		return line;

	}

	static void _TransferLog(float transferAmount, clsBankClient Client1, clsBankClient Client2) {

		string line;
		fstream MyFile;

		line = _LoadDataTransferToLine(transferAmount, Client1, Client2);

		MyFile.open("trasferLog.txt", ios::out | ios::app);

		if (MyFile.is_open()) {


			MyFile << line << endl;

			MyFile.close();

		}
	}

public:

	static void TransferScreen() {

		string Title = "\t  Transfer Screen";
		_DrawScreenHeader(Title);

		string accountNumber;
		cout << "\n\nPlease Enter Account Number To Transfer From: ";
		accountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountNumber)) {

			cout << "Account Number is not Found, Enter Another Account Number: ";
			accountNumber = clsInputValidate::ReadString();

		}

		clsBankClient Client1 = clsBankClient::Find(accountNumber);
		clsBankClient::Print(Client1);

		string accountNumber2;
		cout << "\n\nPlease Enter Account Number To Transfer To: ";
		accountNumber2 = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountNumber2)) {

			cout << "Account Number is not Found, Enter Another Account Number: ";
			accountNumber2 = clsInputValidate::ReadString();

		}	

		clsBankClient Client2 = clsBankClient::Find(accountNumber2);
		clsBankClient::Print(Client2);

		float transferAmount;
		cout << "\n\nEnter Transfer Amount: ";
		transferAmount = clsInputValidate::ReadNumber<float>();

		while (transferAmount > Client1.AccountBalance) {

			cout << "\nAmount Exceeds the Available Balance, Enter Another Amount: ";
			transferAmount = clsInputValidate::ReadNumber<float>();

		}

		char yesOrNo;
		cout << "Are You Sure You Want To Perform This Operation ? y/n ? ";
		cin >> yesOrNo;

		if (yesOrNo == 'y' || yesOrNo == 'Y') {

			Client1.Withdraw(transferAmount);
			Client2.Deposit(transferAmount);

		    _TransferLog(transferAmount, Client1, Client2);

		}

		cout << "Transfer Done Successfuly" << endl;

		clsBankClient::Print(Client1);
		clsBankClient::Print(Client2);

	}

};

