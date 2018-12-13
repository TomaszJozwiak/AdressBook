#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Contact
{
    int id = 0;
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

void saveContactToFile (Contact singleContact)
{
    fstream addressBook;
    addressBook.open("AddressBook.txt", ios::out | ios::app);

    if(addressBook.good() == true)
    {
        addressBook << singleContact.id << '|';
        addressBook << singleContact.firstName << '|';
        addressBook << singleContact.lastName << '|';
        addressBook << singleContact.phoneNumber << '|';
        addressBook << singleContact.email << '|';
        addressBook << singleContact.address << '|';
        addressBook.close();

        cout << "Kontakt dodany" << endl;
        system("pause");
    }
    else
        cout << "Nie udalo sie otworzyc pliku" << endl;
}

void addContact(vector<Contact> &contacts)
{
    Contact singleContact;

    system("cls");
    cout << "Dodawanie adresata" << endl;

    if (contacts.empty() == true)
        singleContact.id = 1;
    else
        singleContact.id = contacts.back().id + 1;

    cout << "Podaj imie: " << endl;
    singleContact.firstName = loadText();
    cout << "Podaj nazwisko: " << endl;
    singleContact.lastName = loadText();
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

void saveAllContactsToFile (vector<Contact> &contacts)
{
    fstream addressBook;
    string lineWithContactData = "";
    addressBook.open("AddressBook.txt", ios::out);

    if(addressBook.good() == true)
    {
        for (vector<Contact>::iterator itr = contacts.begin(); itr != contacts.end(); itr ++)
        {
            lineWithContactData += intToStringConversion(itr->id) + '|';
            lineWithContactData += itr->firstName + '|';
            lineWithContactData += itr->lastName + '|';
            lineWithContactData += itr->phoneNumber + '|';
            lineWithContactData += itr->email + '|';
            lineWithContactData += itr->address + '|';

            addressBook << lineWithContactData << endl;
            lineWithContactData = "";
        }
        addressBook.close();
    }
    else
        cout << "Nie udalo sie zapisac kontaktow do pliku" << endl;
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
                singleContact.firstName = singleContactData;
                break;
            case 3:
                singleContact.lastName = singleContactData;
                break;
            case 4:
                singleContact.phoneNumber = singleContactData;
                break;
            case 5:
                singleContact.email = singleContactData;
                break;
            case 6:
                singleContact.address = singleContactData;
                break;
            }
            singleContactData = "";
            dataNumber++;
        }
    return singleContact;
}

void loadContactsFromFile (vector<Contact> &contacts)
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
            contacts.push_back(singleContact);
        }
        addressBook.close();
    }
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
                    itr = contacts.erase(itr);
                    cout << endl << "Kontakt usuniety" << endl;
                    saveAllContactsToFile(contacts);
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
                    cout << endl << "Imie zostalo zmienione" << endl;
                    saveAllContactsToFile(contacts);
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    itr->lastName = loadText();
                    cout << endl << "Nazwisko zostalo zmienione" << endl;
                    saveAllContactsToFile(contacts);
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    itr->phoneNumber = loadText();
                    cout << endl << "Numer telefonu zostal zmieniony" << endl;
                    saveAllContactsToFile(contacts);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    itr->email = loadText();
                    cout << endl << "Email zostal zmieniony" << endl;
                    saveAllContactsToFile(contacts);
                    break;
                case '5':
                    cout << "Podaj nowe adres: ";
                    itr->address = loadText();
                    cout << endl << "Adres zostal zmieniony" << endl;
                    saveAllContactsToFile(contacts);
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
    char choiceFromMenu;

    loadContactsFromFile(contacts);

    while (true)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA - MENU GLOWNE" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj na nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Wyjscie z programu" << endl;
        cout << "Twoj wybor: ";
        cin >> choiceFromMenu;

        switch (choiceFromMenu)
        {
        case '1':
            addContact(contacts);
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
            exitProgram();
            break;
        default:
            cout << "Polecenie niepoprawne. Wpisz cyfre z menu" << endl;
            break;
        }
    }
    return 0;
}
