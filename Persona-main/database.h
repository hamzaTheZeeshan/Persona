#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"
#include <string>
using namespace std;

class Person; // Forward declaration

sqlite3* openDatabase(const string &dbName);
void createTable(sqlite3 *DB);
void savePerson(sqlite3 *DB, const Person &p);
void displayAllPersons(sqlite3 *DB);
void deletePerson(sqlite3* DB, const string& cnic);
void editPerson(sqlite3* DB, const string& cnic);
bool isValidCNIC(const string& cnic);
bool isValidName(const string& name);
bool isValidGender(const string& gender);
bool isValidAge(int age);
bool isValidHeight(float height);
bool isValidTrait(double trait);
#endif