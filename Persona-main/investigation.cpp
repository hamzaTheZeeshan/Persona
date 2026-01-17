#include "investigation.h"
#include <iostream>
#include <cmath>

using namespace std;

double calculateSimilarity(const double traits1[], const double traits2[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        double diff = traits1[i] - traits2[i];
        sum += diff * diff;
    }
    return 1.0 / (1.0 + sqrt(sum));
}

void findPerpetrator(sqlite3* DB) {
    cout << "\n=== PERPETRATOR FINDER ===\n";
    
    double targetTraits[12]; 
    const char* traitNames[] = {
        "Openness", "Conscientiousness", "Extraversion", "Agreeableness",
        "Neuroticism", "Honesty", "Empathy", "Patience",
        "Creativity", "Discipline", "Confidence", "Adaptability"
    };
    
    cout << "Enter suspected personality traits (0.0-1.0):\n";
    for (int i = 0; i < 12; i++) {
        cout << traitNames[i] << ": ";
        cin >> targetTraits[i];
    }
    cin.ignore();
    
    priority_queue<MatchResult> topMatches;
    
    string sql = "SELECT CNIC, NAME, OPENNESS, CONSCIENTIOUSNESS, EXTRAVERSION, "
                 "AGREEABLENESS, NEUROTICISM, HONESTY, EMPATHY, PATIENCE, "
                 "CREATIVITY, DISCIPLINE, CONFIDENCE, ADAPTABILITY FROM PERSON;";
    
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        cout << "Error reading database\n";
        return;
    }
    
    int totalProcessed = 0;
    int matchesFound = 0;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        totalProcessed++;
        
        double personTraits[12];
        for (int i = 0; i < 12; i++) {
            personTraits[i] = sqlite3_column_double(stmt, i + 2);
        }
        
        // Calculate similarity using ARRAYS
        double similarity = calculateSimilarity(targetTraits, personTraits, 12);
        
        string cnic = string((const char*)sqlite3_column_text(stmt, 0));
        string name = string((const char*)sqlite3_column_text(stmt, 1));
        
        // Add to priority queue if good match
        if (similarity > 0.3) {
            topMatches.push(MatchResult(cnic, name, similarity));
            matchesFound++;
        }
    }
    
    sqlite3_finalize(stmt);
    
    // 4. Display TOP 5 matches using priority queue
    cout << "\nSearch Complete:\n";
    cout << "• Database Records: " << totalProcessed << "\n";
    cout << "• Potential Matches: " << matchesFound << "\n";
    
    if (topMatches.empty()) {
        cout << "No matches found with similarity > 30%\n";
        return;
    }
    
    cout << "\nTOP 5 SUSPECTS (Highest Match First):\n";
    cout << "=========================================\n";
    
    // Create temporary array to store top matches for display
    MatchResult topFive[5]; // Fixed array for top 5
    int count = 0;
    
    // Get top 5 from priority queue
    while (!topMatches.empty() && count < 5) {
        topFive[count] = topMatches.top();
        topMatches.pop();
        count++;
    }
    
    // Display from array
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << topFive[i].name << "\n";
        cout << "   CNIC: " << topFive[i].cnic << "\n";
        cout << "   Match Confidence: " << (topFive[i].similarityScore * 100) << "%\n";
        
        // Show match quality
        if (topFive[i].similarityScore > 0.8) {
            cout << " HIGH PROBABILITY MATCH\n";
        } else if (topFive[i].similarityScore > 0.6) {
            cout << "  MEDIUM PROBABILITY MATCH\n";
        } else {
            cout << "  LOW PROBABILITY MATCH\n";
        }
        cout << "   --------------------\n";
    }
    
    // Show remaining matches count
    if (!topMatches.empty()) {
        cout << "... and " << topMatches.size() << " more potential matches\n";
    }
}