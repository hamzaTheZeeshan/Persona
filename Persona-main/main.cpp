#include <iostream>
#include "database.h"
#include "Person.h"
#include "investigation.h"
using namespace std;


void showMenu()
{
    cout << "\n========= NADRA INTELLIGENCE SYSTEM =========";
    cout << "\n1. Add a Person";
    cout << "\n2. Edit a Person";
    cout << "\n3. Delete a Person";
    cout << "\n4. Perpetrator Finder";
    cout << "\n5. Demographic Search";
    cout << "\n6. Future Career Prediction";
    cout << "\n7. Exit";
    cout << "\n=============================================\n";
    cout << "Enter your choice: ";
}

int main()
{
    sqlite3 *DB = openDatabase("persona.db");
    createTable(DB);
    int choice;

    while (true)
    {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            Person p;
            p.addPerson();
            savePerson(DB, p);
            break;
        }
        case 2:
        {
            string cnic;
            cout << "Enter CNIC to edit: ";
            getline(cin, cnic);
            editPerson(DB, cnic);
            break;
        }
        case 3:
        {
            string cnic;
            cout << "Enter CNIC to delete: ";
            getline(cin, cnic);
            deletePerson(DB, cnic);
            break;
        }

        case 4:
        {
            findPerpetrator(DB);
            break;
        }
        case 7:
            cout << "\nExiting program...\n";
            sqlite3_close(DB);
            return 0;
        default:
            cout << "\nInvalid choice! Try again.\n";
        }
    }

    return 0;
}