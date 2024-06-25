#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short trys = 3;

        string Username, Password;
        do
        {

            if (trys == 1) {

                cout << "\nYou are Locked After 3 Failed Trials\n" << endl;
                return false;

            }

            if (LoginFaild)
            {
                cout << "\nInvalid Username/Password!" << endl;
                cout << "You Have " << --trys << " Trials to Login\n" << endl;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();
        return true;

    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        if (!_Login()) return false;

    }

};

