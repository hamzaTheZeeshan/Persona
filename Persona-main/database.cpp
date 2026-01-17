#include "database.h"
#include "Person.h"
#include <iostream>
using namespace std;

sqlite3* openDatabase(const string &dbName)
{
    sqlite3 *DB;
    int exit = sqlite3_open(dbName.c_str(), &DB);
    
    if (exit)
        cout << "Error opening database: " << sqlite3_errmsg(DB) << endl;
    else
        cout << "Database opened/created successfully.\n";
    
    return DB;
}

void createTable(sqlite3 *DB)
{
    string sql = "CREATE TABLE IF NOT EXISTS PERSON ("
                 "CNIC TEXT PRIMARY KEY, "
                 "NAME TEXT, "
                 "FATHER_NAME TEXT, "
                 "ADDRESS TEXT, "
                 "GENDER TEXT, "
                 "AGE INT, "
                 "HEIGHT REAL, "
                 "OPENNESS REAL, "
                 "CONSCIENTIOUSNESS REAL, "
                 "EXTRAVERSION REAL, "
                 "AGREEABLENESS REAL, "
                 "NEUROTICISM REAL, "
                 "HONESTY REAL, "
                 "EMPATHY REAL, "
                 "PATIENCE REAL, "
                 "CREATIVITY REAL, "
                 "DISCIPLINE REAL, "
                 "CONFIDENCE REAL, "
                 "ADAPTABILITY REAL);";
    
    char *errMsg = 0;
    int exit = sqlite3_exec(DB, sql.c_str(), 0, 0, &errMsg);
    
    if (exit != SQLITE_OK)
    {
        cout << "Error creating table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    else
        cout << "Table created successfully.\n";
}
void editPerson(sqlite3* DB, const string& cnic) {
    // First check if person exists
    string checkSql = "SELECT * FROM PERSON WHERE CNIC = ?;";
    sqlite3_stmt* checkStmt;
    
    if (sqlite3_prepare_v2(DB, checkSql.c_str(), -1, &checkStmt, 0) != SQLITE_OK) {
        cout << " Error preparing check statement\n";
        return;
    }
    
    sqlite3_bind_text(checkStmt, 1, cnic.c_str(), -1, SQLITE_TRANSIENT);
    
    if (sqlite3_step(checkStmt) != SQLITE_ROW) {
        cout << " Person with CNIC " << cnic << " not found!\n";
        sqlite3_finalize(checkStmt);
        return;
    }
    
    sqlite3_finalize(checkStmt);
    
    // Get new data from user
    Person p;
    string newCnic, name, fatherName, address, gender;
    int age;
    float height;
    double openness, conscientiousness, extraversion, agreeableness, neuroticism;
    double honesty, empathy, patience, creativity, discipline, confidence, adaptability;
    
    cout << "\n=== EDIT PERSON ===\n";
    cout << "Leave field blank to keep current value.\n";

cout << "New CNIC (" << cnic << ", format: XXXXX-XXXXXXX-X): ";
getline(cin, newCnic);
if (newCnic.empty()) {
    newCnic = cnic;
} else if (!isValidCNIC(newCnic)) {
    cout << "Invalid CNIC format! Must be 13 digits with hyphens (XXXXX-XXXXXXX-X). Keeping original CNIC.\n";
    newCnic = cnic;
}

// For Name
cout << "New Name: ";
getline(cin, name);
if (!name.empty() && !isValidName(name)) {
    cout << "Invalid name! Only letters, spaces, hyphens and periods allowed. Keeping original name.\n";
    name = "";
}

// For Father Name
cout << "New Father Name: ";
getline(cin, fatherName);
if (!fatherName.empty() && !isValidName(fatherName)) {
    cout << "Invalid father name! Only letters, spaces, hyphens and periods allowed. Keeping original father name.\n";
    fatherName = "";
}

cout << "New Address: ";
getline(cin, address);

// For Gender
cout << "New Gender (M/F): ";
getline(cin, gender);
if (!gender.empty()) {
    if (!isValidGender(gender)) {
        cout << "Invalid gender! Please enter 'M' or 'F' only. Keeping original gender.\n";
        gender = "";
    } else {
        // Convert to uppercase for consistency
        if (gender == "m") gender = "M";
        if (gender == "f") gender = "F";
    }
}

// For Age
cout << "New Age: ";
string ageStr;
getline(cin, ageStr);
if (!ageStr.empty()) {
    try {
        age = stoi(ageStr);
        if (!isValidAge(age)) {
            cout << "Invalid age! Must be between 1-120. Keeping original age.\n";
            age = 0;
        }
    } catch (...) {
        cout << "Invalid age format! Keeping original age.\n";
        age = 0;
    }
} else {
    age = 0;
}

// For Height
cout << "New Height (cm, 50-250): ";
string heightStr;
getline(cin, heightStr);
if (!heightStr.empty()) {
    try {
        height = stof(heightStr);
        if (!isValidHeight(height)) {
            cout << " Invalid height! Must be between 50-250 cm. Keeping original height.\n";
            height = 0.0f;
        }
    } catch (...) {
        cout << "Invalid height format! Keeping original height.\n";
        height = 0.0f;
    }
} else {
    height = 0.0f;
}
    
    cout << "\nNew Personality Traits (0.0-1.0, leave blank to keep current):\n";
    
    cout << "Openness: ";
    string opennessStr;
    getline(cin, opennessStr);
    openness = opennessStr.empty() ? -1.0 : stod(opennessStr);
    
    cout << "Conscientiousness: ";
    string conscientiousnessStr;
    getline(cin, conscientiousnessStr);
    conscientiousness = conscientiousnessStr.empty() ? -1.0 : stod(conscientiousnessStr);
    
    cout << "Extraversion: ";
    string extraversionStr;
    getline(cin, extraversionStr);
    extraversion = extraversionStr.empty() ? -1.0 : stod(extraversionStr);
    
    cout << "Agreeableness: ";
    string agreeablenessStr;
    getline(cin, agreeablenessStr);
    agreeableness = agreeablenessStr.empty() ? -1.0 : stod(agreeablenessStr);
    
    cout << "Neuroticism: ";
    string neuroticismStr;
    getline(cin, neuroticismStr);
    neuroticism = neuroticismStr.empty() ? -1.0 : stod(neuroticismStr);
    
    cout << "Honesty: ";
    string honestyStr;
    getline(cin, honestyStr);
    honesty = honestyStr.empty() ? -1.0 : stod(honestyStr);
    
    cout << "Empathy: ";
    string empathyStr;
    getline(cin, empathyStr);
    empathy = empathyStr.empty() ? -1.0 : stod(empathyStr);
    
    cout << "Patience: ";
    string patienceStr;
    getline(cin, patienceStr);
    patience = patienceStr.empty() ? -1.0 : stod(patienceStr);
    
    cout << "Creativity: ";
    string creativityStr;
    getline(cin, creativityStr);
    creativity = creativityStr.empty() ? -1.0 : stod(creativityStr);
    
    cout << "Discipline: ";
    string disciplineStr;
    getline(cin, disciplineStr);
    discipline = disciplineStr.empty() ? -1.0 : stod(disciplineStr);
    
    cout << "Confidence: ";
    string confidenceStr;
    getline(cin, confidenceStr);
    confidence = confidenceStr.empty() ? -1.0 : stod(confidenceStr);
    
    cout << "Adaptability: ";
    string adaptabilityStr;
    getline(cin, adaptabilityStr);
    adaptability = adaptabilityStr.empty() ? -1.0 : stod(adaptabilityStr);
    
    // Build dynamic UPDATE query
    string sql = "UPDATE PERSON SET ";
    bool first = true;
    
    if (!newCnic.empty() && newCnic != cnic) {
        sql += "CNIC = ?";
        first = false;
    }
    
    if (!name.empty()) {
        if (!first) sql += ", ";
        sql += "NAME = ?";
        first = false;
    }
    
    if (!fatherName.empty()) {
        if (!first) sql += ", ";
        sql += "FATHER_NAME = ?";
        first = false;
    }
    
    if (!address.empty()) {
        if (!first) sql += ", ";
        sql += "ADDRESS = ?";
        first = false;
    }
    
    if (!gender.empty()) {
        if (!first) sql += ", ";
        sql += "GENDER = ?";
        first = false;
    }
    
    if (age > 0) {
        if (!first) sql += ", ";
        sql += "AGE = ?";
        first = false;
    }
    
    if (height > 0) {
        if (!first) sql += ", ";
        sql += "HEIGHT = ?";
        first = false;
    }
    
    // Add personality traits
    if (openness >= 0) {
        if (!first) sql += ", ";
        sql += "OPENNESS = ?";
        first = false;
    }
    
    if (conscientiousness >= 0) {
        if (!first) sql += ", ";
        sql += "CONSCIENTIOUSNESS = ?";
        first = false;
    }
    
    if (extraversion >= 0) {
        if (!first) sql += ", ";
        sql += "EXTRAVERSION = ?";
        first = false;
    }
    
    if (agreeableness >= 0) {
        if (!first) sql += ", ";
        sql += "AGREEABLENESS = ?";
        first = false;
    }
    
    if (neuroticism >= 0) {
        if (!first) sql += ", ";
        sql += "NEUROTICISM = ?";
        first = false;
    }
    
    if (honesty >= 0) {
        if (!first) sql += ", ";
        sql += "HONESTY = ?";
        first = false;
    }
    
    if (empathy >= 0) {
        if (!first) sql += ", ";
        sql += "EMPATHY = ?";
        first = false;
    }
    
    if (patience >= 0) {
        if (!first) sql += ", ";
        sql += "PATIENCE = ?";
        first = false;
    }
    
    if (creativity >= 0) {
        if (!first) sql += ", ";
        sql += "CREATIVITY = ?";
        first = false;
    }
    
    if (discipline >= 0) {
        if (!first) sql += ", ";
        sql += "DISCIPLINE = ?";
        first = false;
    }
    
    if (confidence >= 0) {
        if (!first) sql += ", ";
        sql += "CONFIDENCE = ?";
        first = false;
    }
    
    if (adaptability >= 0) {
        if (!first) sql += ", ";
        sql += "ADAPTABILITY = ?";
        first = false;
    }
    
    sql += " WHERE CNIC = ?;";
    
    // Execute update
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cout << "Error preparing update statement\n";
        return;
    }
    
    int paramIndex = 1;
    
    // Bind parameters in the same order as in SQL
    if (!newCnic.empty() && newCnic != cnic) {
        sqlite3_bind_text(stmt, paramIndex++, newCnic.c_str(), -1, SQLITE_TRANSIENT);
    }
    
    if (!name.empty()) {
        sqlite3_bind_text(stmt, paramIndex++, name.c_str(), -1, SQLITE_TRANSIENT);
    }
    
    if (!fatherName.empty()) {
        sqlite3_bind_text(stmt, paramIndex++, fatherName.c_str(), -1, SQLITE_TRANSIENT);
    }
    
    if (!address.empty()) {
        sqlite3_bind_text(stmt, paramIndex++, address.c_str(), -1, SQLITE_TRANSIENT);
    }
    
    if (!gender.empty()) {
        sqlite3_bind_text(stmt, paramIndex++, gender.c_str(), -1, SQLITE_TRANSIENT);
    }
    
    if (age > 0) {
        sqlite3_bind_int(stmt, paramIndex++, age);
    }
    
    if (height > 0) {
        sqlite3_bind_double(stmt, paramIndex++, height);
    }
    
    // Bind personality traits
    if (openness >= 0) sqlite3_bind_double(stmt, paramIndex++, openness);
    if (conscientiousness >= 0) sqlite3_bind_double(stmt, paramIndex++, conscientiousness);
    if (extraversion >= 0) sqlite3_bind_double(stmt, paramIndex++, extraversion);
    if (agreeableness >= 0) sqlite3_bind_double(stmt, paramIndex++, agreeableness);
    if (neuroticism >= 0) sqlite3_bind_double(stmt, paramIndex++, neuroticism);
    if (honesty >= 0) sqlite3_bind_double(stmt, paramIndex++, honesty);
    if (empathy >= 0) sqlite3_bind_double(stmt, paramIndex++, empathy);
    if (patience >= 0) sqlite3_bind_double(stmt, paramIndex++, patience);
    if (creativity >= 0) sqlite3_bind_double(stmt, paramIndex++, creativity);
    if (discipline >= 0) sqlite3_bind_double(stmt, paramIndex++, discipline);
    if (confidence >= 0) sqlite3_bind_double(stmt, paramIndex++, confidence);
    if (adaptability >= 0) sqlite3_bind_double(stmt, paramIndex++, adaptability);
    
    // Bind WHERE condition
    sqlite3_bind_text(stmt, paramIndex, cnic.c_str(), -1, SQLITE_TRANSIENT);
    
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << "Person updated successfully!\n";
    } else {
        cout << "Error updating person: " << sqlite3_errmsg(DB) << "\n";
    }
    
    sqlite3_finalize(stmt);
}
void deletePerson(sqlite3* DB, const string& cnic) {
    string sql = "DELETE FROM PERSON WHERE CNIC = ?;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cout << "Error preparing delete statement\n";
        return;
    }
    
    sqlite3_bind_text(stmt, 1, cnic.c_str(), -1, SQLITE_TRANSIENT);
    
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << " Person deleted successfully!\n";
    } else {
        cout << "Error deleting person\n";
    }
    
    sqlite3_finalize(stmt);
}
void savePerson(sqlite3 *DB, const Person &p)
{
    string sql = "INSERT INTO PERSON VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
    
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cout << "Error preparing statement\n";
        return;
    }
    
    sqlite3_bind_text(stmt, 1, p.getCNIC().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, p.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, p.getFatherName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, p.getAddress().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, p.getGender().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, p.getAge());
    sqlite3_bind_double(stmt, 7, p.getHeight());
    sqlite3_bind_double(stmt, 8, p.getOpenness());
    sqlite3_bind_double(stmt, 9, p.getConscientiousness());
    sqlite3_bind_double(stmt, 10, p.getExtraversion());
    sqlite3_bind_double(stmt, 11, p.getAgreeableness());
    sqlite3_bind_double(stmt, 12, p.getNeuroticism());
    sqlite3_bind_double(stmt, 13, p.getHonesty());
    sqlite3_bind_double(stmt, 14, p.getEmpathy());
    sqlite3_bind_double(stmt, 15, p.getPatience());
    sqlite3_bind_double(stmt, 16, p.getCreativity());
    sqlite3_bind_double(stmt, 17, p.getDiscipline());
    sqlite3_bind_double(stmt, 18, p.getConfidence());
    sqlite3_bind_double(stmt, 19, p.getAdaptability());
    
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << " Person saved to database!\n";
    } else {
        cout << " Error saving: " << sqlite3_errmsg(DB) << "\n";
    }
    
    sqlite3_finalize(stmt);
}

void displayAllPersons(sqlite3 *DB)
{
    string sql = "SELECT * FROM PERSON;";
    sqlite3_stmt *stmt;
    
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cout << "Error reading database\n";
        return;
    }
    
    cout << "\n========== ALL PERSONS IN DATABASE ==========\n";
    
    int count = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        count++;
        cout << "\n--- Person " << count << " ---\n";
        cout << "CNIC: " << sqlite3_column_text(stmt, 0) << endl;
        cout << "Name: " << sqlite3_column_text(stmt, 1) << endl;
        cout << "Father Name: " << sqlite3_column_text(stmt, 2) << endl;
        cout << "Address: " << sqlite3_column_text(stmt, 3) << endl;
        cout << "Gender: " << sqlite3_column_text(stmt, 4) << endl;
        cout << "Age: " << sqlite3_column_int(stmt, 5) << endl;
        cout << "Height: " << sqlite3_column_double(stmt, 6) << " cm" << endl;
        cout << "\nPersonality Traits:\n";
        cout << "Openness: " << sqlite3_column_double(stmt, 7) << endl;
        cout << "Conscientiousness: " << sqlite3_column_double(stmt, 8) << endl;
        cout << "Extraversion: " << sqlite3_column_double(stmt, 9) << endl;
        cout << "Agreeableness: " << sqlite3_column_double(stmt, 10) << endl;
        cout << "Neuroticism: " << sqlite3_column_double(stmt, 11) << endl;
        cout << "Honesty: " << sqlite3_column_double(stmt, 12) << endl;
        cout << "Empathy: " << sqlite3_column_double(stmt, 13) << endl;
        cout << "Patience: " << sqlite3_column_double(stmt, 14) << endl;
        cout << "Creativity: " << sqlite3_column_double(stmt, 15) << endl;
        cout << "Discipline: " << sqlite3_column_double(stmt, 16) << endl;
        cout << "Confidence: " << sqlite3_column_double(stmt, 17) << endl;
        cout << "Adaptability: " << sqlite3_column_double(stmt, 18) << endl;
    }
    
    if (count == 0) {
        cout << "No persons found in database.\n";
    } else {
        cout << "\nTotal persons: " << count << endl;
    }
    
    sqlite3_finalize(stmt);
}