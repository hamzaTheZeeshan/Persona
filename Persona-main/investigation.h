#ifndef INVESTIGATION_H
#define INVESTIGATION_H

#include <queue>  // Built-in priority queue
#include <string>
#include "database.h"

using namespace std;

struct MatchResult {
    string cnic;
    string name;
    double similarityScore;
    
    // Constructor
    MatchResult(string c = "", string n = "", double score = 0.0) 
        : cnic(c), name(n), similarityScore(score) {}
    
    // Overload < for MAX HEAP (higher scores first)
    bool operator<(const MatchResult& other) const {
        return similarityScore < other.similarityScore;
    }
};

// Function declarations
void findPerpetrator(sqlite3* DB);
double calculateSimilarity(const double traits1[], const double traits2[], int size);

#endif