#include <bits/stdc++.h>
using namespace std;

// Reduced set of common keywords
const unordered_set<string> KEYWORDS = {
    "int", "char", "if", "else", "for", "while", "return", "class"
};

// Reduced set of multi-character operators
const unordered_set<string> MULTI_OPS = {
    "<<", ">>", "==", "!=", "<=", ">=", "&&", "||", "++", "--"
};

// Punctuation and single-character operators combined for brevity
const string SINGLE_CHARS = "+-*/%=<>!&|^~?:.{}(),;[]";

bool isIdentStart(char c) {
    return isalpha((unsigned char)c) || c == '_';
}
bool isIdentChar(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

void tokenize(const string& content, vector<pair<string, string>>& tokens) {
    size_t n = content.size();
    size_t i = 0;

    while (i < n) {
        char c = content[i];

        if (isspace((unsigned char)c)) { ++i; continue; }

        size_t start = i;

        // 1. Literal (String/Char)
        if (c == '"' || c == '\'') {
            char end_char = c;
            ++i;
            while (i < n) {
                if (content[i] == '\\') i += 2; // Skip escape sequence
                else if (content[i] == end_char) { ++i; break; }
                else ++i;
            }
            tokens.push_back({content.substr(start, i - start), "constant"});
            continue;
        }

        // 2. Identifier or Keyword
        if (isIdentStart(c)) {
            ++i;
            while (i < n && isIdentChar(content[i])) ++i;
            string tok = content.substr(start, i - start);
            if (KEYWORDS.count(tok)) tokens.push_back({tok, "keyword"});
            else tokens.push_back({tok, "identifier"});
            continue;
        }

        // 3. Number (Integer or Real)
        if (isdigit((unsigned char)c)) {
            bool hasDot = false;
            while (i < n && (isdigit((unsigned char)content[i]) || content[i] == '.')) {
                if (content[i] == '.') {
                    if (hasDot) break;
                    hasDot = true;
                }
                ++i;
            }
            tokens.push_back({content.substr(start, i - start), "constant"});
            continue;
        }

        // 4. Multi-char Operator (2-char)
        if (i + 1 < n) {
            string two = content.substr(i, 2);
            if (MULTI_OPS.count(two)) {
                tokens.push_back({two, "operator"});
                i += 2;
                continue;
            }
        }

        // 5. Single-char Operator or Punctuation
        if (SINGLE_CHARS.find(c) != string::npos) {
            string tok(1, c);
            string category = (string("{}(),;[]").find(c) != string::npos) ? "punctuation" : "operator";
            tokens.push_back({tok, category});
            ++i;
            continue;
        }

        // 6. Unknown
        tokens.push_back({string(1, c), "unknown"});
        ++i;
    }
}

int main() {
    const string filename = "sample.txt";
    ifstream in(filename);
    if (!in) {
        cerr << "Error: cannot open " << filename << "\n";
        return 1;
    }

    // Load file content
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    
    vector<pair<string,string>> tokens;
    tokenize(content, tokens);

    // Print tokens
    for (auto &p : tokens) {
        cout << p.first << " = " << p.second << "\n";
    }

    cout << "\nAll tokens processed.\n";
    return 0;
}