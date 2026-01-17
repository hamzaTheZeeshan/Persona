#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
private:
    string cnic;
    string name;
    string fatherName;
    string address;
    string gender;
    int age;
    float height;
    float openness;
    float conscientiousness;
    float extraversion;
    float agreeableness;
    float neuroticism;
    float honesty;
    float empathy;
    float patience;
    float creativity;
    float discipline;
    float confidence;
    float adaptability;

public:
    Person();
    void addPerson();
    void displayPerson() const;

    string getCNIC() const;
    string getName() const;
    string getFatherName() const;
    string getAddress() const;
    string getGender() const;
    int getAge() const;
    float getHeight() const;
    float getOpenness() const;
    float getConscientiousness() const;
    float getExtraversion() const;
    float getAgreeableness() const;
    float getNeuroticism() const;
    float getHonesty() const;
    float getEmpathy() const;
    float getPatience() const;
    float getCreativity() const;
    float getDiscipline() const;
    float getConfidence() const;
    float getAdaptability() const;
    bool isValidCNIC(const string &cnic);
    bool isValidName(const string &name);
    bool isValidGender(const string &gender);
    bool isValidAge(int age);
    bool isValidHeight(float height);
    bool isValidTrait(double trait);
};

#endif