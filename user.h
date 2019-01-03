#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

class User
{
    int id = 0;
    string name = "", password = "";
    vector<User> users;

public:

    string loadText();
    string intToStringConversion (int number);
    void saveUserToFile (User singleUser);
    User getUserData (string userDataFromOneLine);
    void userRegistration();
    int login();
    void saveAllUsersToFile ();
    void loadUsersFromFile ();
};
