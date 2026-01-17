#include "Person.h"
#include <iostream>
using namespace std;
#include <cctype>
#include <regex>

// Validation functions
bool isValidCNIC(const string& cnic) {
    // Format: XXXXX-XXXXXXX-X (15 characters total)
    if (cnic.length() != 15) return false;
    
    // Check format: XXXXX-XXXXXXX-X
    for (int i = 0; i < 15; i++) {
        if (i == 5 || i == 13) {
            if (cnic[i] != '-') return false;
        } else {
            if (!isdigit(cnic[i])) return false;
        }
    }
    return true;
}

bool isValidName(const string& name) {
    // Name should only contain letters, spaces, and hyphens
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '-' && c != '.') {
            return false;
        }
    }
    return !name.empty();
}

bool isValidGender(const string& gender) {
    return (gender == "M" || gender == "F" || gender == "m" || gender == "f");
}

bool isValidAge(int age) {
    return (age >= 1 && age <= 120);
}

bool isValidHeight(float height) {
    return (height >= 50.0f && height <= 250.0f);
}

bool isValidTrait(double trait) {
    return (trait >= 0.0 && trait <= 1.0);
}

// Helper function to get validated input
string getValidatedCNIC() {
    string cnic;
    while (true) {
        cout << "Enter CNIC (format: XXXXX-XXXXXXX-X): ";
        getline(cin, cnic);
        
        if (isValidCNIC(cnic)) {
            break;
        } else {
            cout << " Invalid CNIC format! Must be 13 digits with hyphens (XXXXX-XXXXXXX-X)\n";
        }
    }
    return cnic;
}

string getValidatedName(const string& fieldName) {
    string name;
    while (true) {
        cout << "Enter " << fieldName << ": ";
        getline(cin, name);
        
        if (isValidName(name)) {
            break;
        } else {
            cout << " Invalid " << fieldName << "! Only letters, spaces, hyphens and periods allowed.\n";
        }
    }
    return name;
}

string getValidatedGender() {
    string gender;
    while (true) {
        cout << "Enter Gender (M/F): ";
        cin >> gender;
        cin.ignore();
        
        if (isValidGender(gender)) {
            // Convert to uppercase for consistency
            if (gender == "m") gender = "M";
            if (gender == "f") gender = "F";
            break;
        } else {
            cout << " Invalid gender! Please enter 'M' or 'F' only.\n";
        }
    }
    return gender;
}

int getValidatedAge() {
    int age;
    while (true) {
        cout << "Enter Age: ";
        cin >> age;
        
        if (cin.fail() || !isValidAge(age)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << " Invalid age! Please enter a number between 1 and 120.\n";
        } else {
            cin.ignore();
            break;
        }
    }
    return age;
}

float getValidatedHeight() {
    float height;
    while (true) {
        cout << "Enter Height (in cm, 50-250): ";
        cin >> height;
        
        if (cin.fail() || !isValidHeight(height)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << " Invalid height! Please enter a number between 50 and 250 cm.\n";
        } else {
            cin.ignore();
            break;
        }
    }
    return height;
}

double getValidatedTrait(const string& traitName) {
    double trait;
    while (true) {
        cout << traitName << " (0.0-1.0): ";
        cin >> trait;
        
        if (cin.fail() || !isValidTrait(trait)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << " Invalid value! Please enter a number between 0.0 and 1.0.\n";
        } else {
            break;
        }
    }
    return trait;
}
Person::Person()
{
    cnic = name = fatherName = address = gender = "";
    age = 0;
    height = 0.0f;
    openness = conscientiousness = extraversion = agreeableness = neuroticism =
        honesty = empathy = patience = creativity = discipline = confidence = adaptability = 0.0f;
}

void Person::addPerson()
{
    cout << "\n=== ADD NEW PERSON ===\n";
    
    // Get validated CNIC
    cnic = getValidatedCNIC();
    
    // Get validated names
    name = getValidatedName("Name");
    fatherName = getValidatedName("Father Name");
    
    cout << "Enter Address: ";
    getline(cin, address);
    
    // Get validated gender, age, height
    gender = getValidatedGender();
    age = getValidatedAge();
    height = getValidatedHeight();
    
    // Get validated personality traits
    cout << "\nEnter Personality Traits (0.0 - 1.0):\n";
    openness = getValidatedTrait("Openness");
    conscientiousness = getValidatedTrait("Conscientiousness");
    extraversion = getValidatedTrait("Extraversion");
    agreeableness = getValidatedTrait("Agreeableness");
    neuroticism = getValidatedTrait("Neuroticism");
    honesty = getValidatedTrait("Honesty");
    empathy = getValidatedTrait("Empathy");
    patience = getValidatedTrait("Patience");
    creativity = getValidatedTrait("Creativity");
    discipline = getValidatedTrait("Discipline");
    confidence = getValidatedTrait("Confidence");
    adaptability = getValidatedTrait("Adaptability");
    
    cin.ignore(); // Clear the input buffer
}

void Person::displayPerson() const
{
    cout << "\n--- Person Information ---\n";
    cout << "CNIC: " << cnic << endl;
    cout << "Name: " << name << endl;
    cout << "Father Name: " << fatherName << endl;
    cout << "Address: " << address << endl;
    cout << "Gender: " << gender << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << " cm" << endl;
    
    cout << "\n--- Personality Traits ---\n";
    cout << "Openness: " << openness << endl;
    cout << "Conscientiousness: " << conscientiousness << endl;
    cout << "Extraversion: " << extraversion << endl;
    cout << "Agreeableness: " << agreeableness << endl;
    cout << "Neuroticism: " << neuroticism << endl;
    cout << "Honesty: " << honesty << endl;
    cout << "Empathy: " << empathy << endl;
    cout << "Patience: " << patience << endl;
    cout << "Creativity: " << creativity << endl;
    cout << "Discipline: " << discipline << endl;
    cout << "Confidence: " << confidence << endl;
    cout << "Adaptability: " << adaptability << endl;
}

string Person::getCNIC() const { return cnic; }
string Person::getName() const { return name; }
string Person::getFatherName() const { return fatherName; }
string Person::getAddress() const { return address; }
string Person::getGender() const { return gender; }
int Person::getAge() const { return age; }
float Person::getHeight() const { return height; }
float Person::getOpenness() const { return openness; }
float Person::getConscientiousness() const { return conscientiousness; }
float Person::getExtraversion() const { return extraversion; }
float Person::getAgreeableness() const { return agreeableness; }
float Person::getNeuroticism() const { return neuroticism; }
float Person::getHonesty() const { return honesty; }
float Person::getEmpathy() const { return empathy; }
float Person::getPatience() const { return patience; }
float Person::getCreativity() const { return creativity; }
float Person::getDiscipline() const { return discipline; }
float Person::getConfidence() const { return confidence; }
float Person::getAdaptability() const { return adaptability; }