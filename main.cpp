#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include "user.h"

using namespace std;

struct Contact
{
    int id = 0, userID = 0;
    string firstName = "", lastName = "", phoneNumber = "", email = "", address = "";
};

string loadText()
{
    string text;
    cin.sync();
    getline (cin, text);
    return text;
}

void exitProgram()
{
    cout << "Program zakonczony" << endl;
    exit(0);
}

string intToStringConversion (int number)
{
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

string changeFirstLetterToLargeAndRestToSmall(string text)
{
    if (!text.empty())
    {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        text[0] = toupper(text[0]);
    }
    return text;
}

void saveContactToFile (Contact singleContact)
{
    fstream addressBook;
    addressBook.open("AddressBook.txt", ios::out | ios::app);

    if(addressBook.good() == true)
    {
        addressBook << singleContact.id << '|';
        addressBook << singleContact.userID << '|';
        addressBook << singleContact.firstName << '|';
        addressBook << singleContact.lastName << '|';
        addressBook << singleContact.phoneNumber << '|';
        addressBook << singleContact.email << '|';
        addressBook << singleContact.address << '|' << endl;
        addressBook.close();

        cout << "Kontakt dodany" << endl;
    }
    else
        cout << "Nie udalo sie otworzyc pliku" << endl;
}

Contact getContactData (string contactDataFromOneLine)
{
    Contact singleContact;
    string singleContactData = "";
    int dataNumber = 1;

    for (int letterPosition = 0; letterPosition < contactDataFromOneLine.length(); letterPosition++)
        if (contactDataFromOneLine[letterPosition] != '|')
            singleContactData += contactDataFromOneLine[letterPosition];
        else
        {
            switch(dataNumber)
            {
            case 1:
                singleContact.id = atoi(singleContactData.c_str());
                break;
            case 2:
                singleContact.userID = atoi(singleContactData.c_str());
                break;
            case 3:
                singleContact.firstName = singleContactData;
                break;
            case 4:
                singleContact.lastName = singleContactData;
                break;
            case 5:
                singleContact.phoneNumber = singleContactData;
                break;
            case 6:
                singleContact.email = singleContactData;
                break;
            case 7:
                singleContact.address = singleContactData;
                break;
            }
            singleContactData = "";
            dataNumber++;
        }
    return singleContact;
}


int getContactID ()
{
    Contact singleContact;
    string contactDataFromOneLine;
    int contactID = 0;

    fstream addressBook;
    addressBook.open("AddressBook.txt", ios::in);

    if(addressBook.good()==true)
    {
        while(getline(addressBook, contactDataFromOneLine))
        {
            singleContact = getContactData(contactDataFromOneLine);
            contactID = singleContact.id;
        }
        addressBook.close();
    }
    return contactID;
}


void addContact(vector<Contact> &contacts, int userID)
{
    Contact singleContact;

    system("cls");
    cout << "Dodawanie adresata" << endl;

    if (getContactID() == 0)
        singleContact.id = 1;
    else
        singleContact.id = getContactID() + 1;

    singleContact.userID = userID;
    cout << "Podaj imie: " << endl;
    singleContact.firstName = loadText();
    singleContact.firstName = changeFirstLetterToLargeAndRestToSmall(singleContact.firstName);
    cout << "Podaj nazwisko: " << endl;
    singleContact.lastName = loadText();
    singleContact.lastName = changeFirstLetterToLargeAndRestToSmall(singleContact.lastName);
    cout << "Podaj telefon: " << endl;
    singleContact.phoneNumber = loadText();
    cout << "Podaj email: " << endl;
    singleContact.email = loadText();
    cout << "Podaj adres: " << endl;
    singleContact.address = loadText();

    contacts.push_back(singleContact);
    saveContactToFile(singleContact);
}


void searchByFirstName(vector <Contact> &contacts)
{
    string firstName = "";
    int numberOfContacts = 0;

    system("cls");
    if(!contacts.empty())
    {
        cout << "Wyszukiwanie adresatow po imieniu" << endl;
        cout << "Podaj imie: ";

        firstName = loadText();

        firstName = changeFirstLetterToLargeAndRestToSmall(firstName);

        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr ++)
        {
            if (itr->firstName == firstName)
            {
                cout << endl;
                cout << "ID:        " << itr->id << endl;
                cout << "Imie:      " << itr->firstName << endl;
                cout << "Nazwisko:  " << itr->lastName << endl;
                cout << "Telefon:   " << itr->phoneNumber << endl;
                cout << "Email:     " << itr->email << endl;
                cout << "Adres:     " << itr->address << endl;
                numberOfContacts++;
            }
        }
        if (numberOfContacts == 0)
            cout << "Nie znaleziono osob o takim imieniu" << endl;
        else
            cout << endl << "Liczba znalezionych osob o imieniu: " << firstName << " wynosi: " << numberOfContacts << endl;
    }
    else
        cout << "Brak kontaktow w ksiazce adresowej" << endl;

    system("pause");
}

void searchByLastName(vector <Contact> &contacts)
{
    string lastName = "";
    int numberOfContacts = 0;

    system("cls");
    if(!contacts.empty())
    {
        cout << "Wyszukiwanie adresatow po nazwisku" << endl;
        cout << "Podaj nazwisko: ";

        lastName = loadText();

        lastName = changeFirstLetterToLargeAndRestToSmall(lastName);

        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr ++)
        {
            if (itr->lastName == lastName)
            {
                cout << endl;
                cout << "ID:        " << itr->id << endl;
                cout << "Imie:      " << itr->firstName << endl;
                cout << "Nazwisko:  " << itr->lastName << endl;
                cout << "Telefon:   " << itr->phoneNumber << endl;
                cout << "Email:     " << itr->email << endl;
                cout << "Adres:     " << itr->address << endl;
                numberOfContacts++;
            }
        }
        if (numberOfContacts == 0)
            cout << "Nie znaleziono osob o takim nazwisku" << endl;
        else
            cout << endl << "Liczba znalezionych osob o nazwisku: " << lastName << " wynosi: " << numberOfContacts << endl;
    }
    else
        cout << "Brak kontaktow w ksiazce adresowej" << endl;

    system("pause");
}

void showAllContacts(vector <Contact> &contacts)
{
    system("cls");
    if(!contacts.empty())
    {
        cout << "Spis wszystkich adresatow" << endl;

        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr ++)
        {
            {
                cout << endl;
                cout << "ID:        " << itr->id << endl;
                cout << "Imie:      " << itr->firstName << endl;
                cout << "Nazwisko:  " << itr->lastName << endl;
                cout << "Telefon:   " << itr->phoneNumber << endl;
                cout << "Email:     " << itr->email << endl;
                cout << "Adres:     " << itr->address << endl;
            }
            cout << endl;
        }
    }
    else
        cout << "Brak kontaktow w ksiazce adresowej" << endl;

    system("pause");
}


void loadContactsFromFile (vector<Contact> &contacts, int userID)
{
    Contact singleContact;
    string contactDataFromOneLine;

    fstream addressBook;
    addressBook.open("AddressBook.txt", ios::in);

    if(addressBook.good()==true)
    {
        while(getline(addressBook, contactDataFromOneLine))
        {
            singleContact = getContactData(contactDataFromOneLine);
            if (singleContact.userID == userID)
            {
                contacts.push_back(singleContact);
            }
        }
        addressBook.close();
    }
}

Contact getSingleContactData(vector<Contact> &contacts, int contactID)
{
    Contact singleContact;

    for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr ++)
    {
        if (itr->id == contactID)
        {

            singleContact.id = itr->id;
            singleContact.userID = itr->userID;
            singleContact.firstName = itr->firstName;
            singleContact.lastName = itr->lastName;
            singleContact.phoneNumber = itr->phoneNumber;
            singleContact.email = itr->email;
            singleContact.address = itr->address;
        }
    }
    return singleContact;
}

void saveContactToTemporaryFile (Contact singleContact)
{
    fstream addressTemporaryBook;
    addressTemporaryBook.open("AddressBook_temporary.txt", ios::out | ios::app);

    if(addressTemporaryBook.good() == true)
    {
        addressTemporaryBook << singleContact.id << '|';
        addressTemporaryBook << singleContact.userID << '|';
        addressTemporaryBook << singleContact.firstName << '|';
        addressTemporaryBook << singleContact.lastName << '|';
        addressTemporaryBook << singleContact.phoneNumber << '|';
        addressTemporaryBook << singleContact.email << '|';
        addressTemporaryBook << singleContact.address << '|' << endl;
        addressTemporaryBook.close();
    }
    else
        cout << "Nie udalo sie otworzyc pliku" << endl;
}

void saveEditedFiles (vector<Contact> contacts, int contactID)
{
    Contact editedContact = getSingleContactData(contacts, contactID);
    Contact contactFromTextFile;
    string loadedLine = "";

    fstream addressBookEditingFiles;

    addressBookEditingFiles.open("AddressBook.txt", ios::in);


    if(addressBookEditingFiles.good() == true)
    {
        while(getline(addressBookEditingFiles, loadedLine))
        {
            contactFromTextFile = getContactData (loadedLine);
            if (contactFromTextFile.id == contactID)
            {
                saveContactToTemporaryFile (editedContact);
            }
            else
            {
                saveContactToTemporaryFile (contactFromTextFile);
            }
        }
        addressBookEditingFiles.close();
        remove("AddressBook.txt");
        rename ("AddressBook_temporary.txt", "AddressBook.txt");
    }
    else
        cout << "Nie udalo sie otworzyc pliku" << endl;

}

void saveDelatedFiles (int contactID)
{
    Contact contactFromTextFile;
    string loadedLine = "";

    fstream addressBookSavedFiles;

    addressBookSavedFiles.open("AddressBook.txt", ios::in);

    if(addressBookSavedFiles.good() == true)
    {
        while(getline(addressBookSavedFiles, loadedLine))
        {
            contactFromTextFile = getContactData (loadedLine);
            if (contactFromTextFile.id != contactID)
            {
                saveContactToTemporaryFile (contactFromTextFile);
            }
        }
        addressBookSavedFiles.close();
        remove("AddressBook.txt");
        rename ("AddressBook_temporary.txt", "AddressBook.txt");
    }
    else
        cout << "Nie udalo sie otworzyc pliku 13" << endl;
}

void deleteContact(vector<Contact> &contacts)
{
    int idOfDeletedContact;
    char sign;
    bool doContactExist;

    system("cls");
    if (!contacts.empty())
    {
        cout << "Usuwanie kontaktu" << endl;
        cout << "Podaj id kontaktu, ktory chcesz usunac" << endl;
        cin >> idOfDeletedContact;

        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr++)
        {
            if (itr->id == idOfDeletedContact)
            {
                doContactExist = true;
                cout << endl << "Potwierdz usuniecie, wciskajac klawisz 't': ";
                cin >> sign;
                if (sign == 't')
                {
                    saveDelatedFiles(idOfDeletedContact);
                    itr = contacts.erase(itr);
                    cout << endl << "Kontakt usuniety" << endl;
                    break;
                }
                else
                {
                    cout << "Kontakt nie zostal usuniety" << endl;
                    break;
                }
            }
        }
        if (doContactExist == false)
            cout << "Wybrany kontakt nie istnieje" << endl;
    }
    else
        cout << "Brak kontaktow w ksiazce adresowej" << endl;

    system("pause");
}

void editContact (vector<Contact> &contacts)
{
    int contactID;
    char choice;
    bool doContactExist = false;

    system("cls");
    if (!contacts.empty())
    {
        cout << "Edycja kontaktu" << endl;
        cout << "Podaj ID kontaktu, w ktorych chcesz zmienic dane: " << endl;
        cin >> contactID;

        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr++)
        {
            if (itr->id == contactID)
            {
                doContactExist = true;

                cout << "Jakie dane chcesz edytowac?" << endl;
                cout << "1 - Imie" << endl;
                cout << "2 - Nazwisko" << endl;
                cout << "3 - Telefon" << endl;
                cout << "4 - Email" << endl;
                cout << "5 - Adres" << endl;
                cout << "6 - Powrot" << endl;
                cin >> choice;

                switch (choice)
                {
                case '1':
                    cout << "Podaj nowe imie: ";
                    itr->firstName = loadText();
                    itr->firstName = changeFirstLetterToLargeAndRestToSmall(itr->firstName);
                    cout << endl << "Imie zostalo zmienione" << endl;
                    saveEditedFiles (contacts, contactID);
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    itr->lastName = loadText();
                    itr->lastName = changeFirstLetterToLargeAndRestToSmall(itr->lastName);
                    cout << endl << "Nazwisko zostalo zmienione" << endl;
                    saveEditedFiles (contacts, contactID);
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    itr->phoneNumber = loadText();
                    cout << endl << "Numer telefonu zostal zmieniony" << endl;
                    saveEditedFiles (contacts, contactID);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    itr->email = loadText();
                    cout << endl << "Email zostal zmieniony" << endl;
                    saveEditedFiles (contacts, contactID);
                    break;
                case '5':
                    cout << "Podaj nowe adres: ";
                    itr->address = loadText();
                    cout << endl << "Adres zostal zmieniony" << endl;
                    saveEditedFiles (contacts, contactID);
                    break;
                case '6':
                    cout << "Powrot do menu glownego" << endl;
                    break;
                }
            }
        }
        if (doContactExist == false)
            cout << "Wybrany kontakt nie istnieje" << endl;
    }
    else
        cout << "Brak kontaktow w ksiazce adresowej" << endl;

    system("pause");
}

int main()
{
    vector<Contact> contacts;
    User user;
    char choiceFromMenu;
    int menuView = 0;
    int userID = 0;

    user.loadUsersFromFile();

    while (true)
    {
        if (menuView == 0)
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA - MENU GLOWNE" << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Wyjscie z programu" << endl;
            cout << "Twoj wybor: ";
            cin >> choiceFromMenu;

            switch (choiceFromMenu)
            {
            case '1':
                userID = user.login();
                if (userID != 0)
                {
                    loadContactsFromFile(contacts, userID);
                    menuView = 1;
                }
                break;
            case '2':
                user.userRegistration();
                break;
            case '9':
                exitProgram();
                break;
            default:
                cout << "Polecenie niepoprawne. Wpisz cyfre z menu" << endl;
                break;
            }
        }
        else if (menuView == 1)
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA - Menu po zalogowaniu " << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj na nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout << "Twoj wybor: ";
            cin >> choiceFromMenu;

            switch (choiceFromMenu)
            {
            case '1':
                addContact(contacts, userID);
                break;
            case '2':
                searchByFirstName(contacts);
                break;
            case '3':
                searchByLastName(contacts);
                break;
            case '4':
                showAllContacts(contacts);
                break;
            case '5':
                deleteContact(contacts);
                break;
            case '6':
                editContact (contacts);
                break;
            case '9':
                menuView = 0;
                contacts.clear();
                break;
            default:
                cout << "Polecenie niepoprawne. Wpisz cyfre z menu" << endl;
                break;
            }
        }
    }
    return 0;
}
