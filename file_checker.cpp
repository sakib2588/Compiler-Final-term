#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype>

using namespace std;

bool isValidIdentifier(const string& str) {
    if (str.empty()) return false;
    
    // First character must be letter or underscore
    if (!(isalpha(str[0]) || str[0] == '_')) {
        return false;
    }
    
    // Rest can be letters, digits, or underscores
    for (int i = 1; i < str.length(); ++i) {
        if (!(isalnum(str[i]) || str[i] == '_')) {
            return false;
        }
    }
    
    return true;
}

int main() {
    ifstream file("sampel.txt");
    
    if (!file.is_open()) {
        cout << "Error: Cannot open sampel.txt" << endl;
        return 1;
    }
    
    set<string> uniqueIdentifiers;
    string word;
    
    // Read words from file
    while (file >> word) {
        if (isValidIdentifier(word)) {
            uniqueIdentifiers.insert(word);
        }
    }
    
    file.close();
    
    if (uniqueIdentifiers.empty()) {
        cout << "No valid identifiers found in the file." << endl;
    } else {
        cout << "Valid unique identifiers found:" << endl;
        for (const string& identifier : uniqueIdentifiers) {
            cout << identifier << endl;
        }
    }
    
    return 0;
}