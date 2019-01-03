#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include "user.h"

using namespace std;


    string User::loadText()
{
    string text;
    cin.sync();
    getline (cin, text);
    return text;
}


string User::intToStringConversion (int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}


void User::saveUserToFile (User singleUser)
{
    fstream usersList;
    usersList.open("Users.txt", ios::out | ios::app);

    if(usersList.good() == true)
    {
        usersList << singleUser.id << '|';
        usersList << singleUser.name << '|';
        usersList << singleUser.password << '|' << endl;
        usersList.close();

        cout << "Uzytkownik zarejestrowany" << endl;
        system("pause");
    }
    else
        cout << "Nie udalo sie otworzyc pliku" << endl;
}


User User::getUserData (string userDataFromOneLine)
{
    User singleUser;
    string singleUserData = "";
    int dataNumber = 1;

    for (int letterPosition = 0; letterPosition < userDataFromOneLine.length(); letterPosition++)
        if (userDataFromOneLine[letterPosition] != '|')
            singleUserData += userDataFromOneLine[letterPosition];
        else
        {
            switch(dataNumber)
            {
            case 1:
                singleUser.id = atoi(singleUserData.c_str());
                break;
            case 2:
                singleUser.name = singleUserData;
                break;
            case 3:
                singleUser.password = singleUserData;
                break;
            }
            singleUserData = "";
            dataNumber++;
        }
    return singleUser;
}


void User::userRegistration()
{
    User singleUser;

    system("cls");
    cout << "Dodawanie uzytkownika" << endl;

    if (users.empty() == true)
        singleUser.id = 1;
    else
        singleUser.id = users.back().id + 1;

    cout << "Podaj nazwe: " << endl;
    singleUser.name = loadText();

    for (vector<User>::iterator itr = users.begin(); itr != users.end(); itr ++)
    {
        if (itr->name == singleUser.name)
        {
            cout << "Nazwa uzytkownika juz istnieje. Wprowadz nowa nazwe: ";
            singleUser.name = loadText();
            itr = users.begin();
        }
    }

    cout << "Podaj haslo: " << endl;
    singleUser.password = loadText();

    users.push_back(singleUser);
    saveUserToFile(singleUser);
}


int User::login()
{
    string name = "";
    string password = "";

    system("cls");
    if(!users.empty())
    {
        cout << "Podaj nazwe uzytkownika: " << endl;
        name = loadText();

        for (vector<User>::iterator itr = users.begin(); itr != users.end(); itr ++)
        {
            if (itr->name == name)
            {
                for (int attempt = 0; attempt < 3; attempt ++)
                {
                    cout << "Podaj haslo. Pozostalo prob " << 3 - attempt << ": ";
                    password = loadText();

                    if (itr->password == password)
                    {
                        cout << "Zalogowales sie" << endl;
                        system("pause");
                        return itr->id;
                    }
                }
                cout << "Podales 3 razy zle haslo. Powrot do menu glownego" << endl;
                system("pause");
                return 0;
            }
        }
        cout << "Nie ma uzytkownika z takim loginem" << endl;
        system("pause");
        return 0;
    }
    cout << "Brak uzytkownikow w systemie" << endl;
    system("pause");
    return 0;
}


void User::saveAllUsersToFile ()
{
    fstream usersList;
    string lineWithContactData = "";
    usersList.open("Users.txt", ios::out);

    if(usersList.good() == true)
    {
        for (vector<User>::iterator itr = users.begin(); itr != users.end(); itr ++)
        {
            lineWithContactData += intToStringConversion(itr->id) + '|';
            lineWithContactData += itr->name + '|';
            lineWithContactData += itr->password + '|';

            usersList << lineWithContactData << endl;
            lineWithContactData = "";
        }
        usersList.close();
    }
    else
        cout << "Nie udalo sie zapisac kontaktow do pliku" << endl;
}

void User::loadUsersFromFile ()
{
    User singleUser;
    string userDataFromOneLine;

    fstream usersList;
    usersList.open("Users.txt", ios::in);

    if(usersList.good()==true)
    {
        while(getline(usersList, userDataFromOneLine))
        {
            singleUser = getUserData(userDataFromOneLine);
            users.push_back(singleUser);
        }
        usersList.close();
    }
}
