#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;

// C++ keywords set
const unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "class", "public",
    "private", "protected", "virtual", "template", "typename",
    "using", "namespace", "try", "catch", "throw", "bool", "true", "false"
};


const unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "++", "--", "==", "!=", "<", "<=", ">",
    ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "=", "+=",
    "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "->", ".",
    "?", ":", "::", ";", ",", "(", ")", "{", "}", "[", "]"
};

// Check if token is a valid identifier according to C++ rules (simplified)
bool isValidIdentifier(const string& token) {
    if (token.empty()) return false;
    if (!(isalpha(token[0]) || token[0] == '_')) return false;

    for (size_t i = 1; i < token.size(); ++i) {
        if (!(isalnum(token[i]) || token[i] == '_'))
            return false;
    }
    return true;
}

// Check if token is an operator
bool isOperator(const string& token) {
    return operators.find(token) != operators.end();
}

// Tokenize a single line of code and classify tokens
void tokenizeLine(const string& line) {
    size_t i = 0;
    while (i < line.length()) {
        // Skip whitespace
        if (isspace(line[i])) {
            ++i;
            continue;
        }

        // Attempt to match multi-char operators (3, 2, then 1 char)
        bool opFound = false;
        for (int len = 3; len >= 1; --len) {
            if (i + len <= line.length()) {
                string sub = line.substr(i, len);
                if (isOperator(sub)) {
                    cout << "Operator: " << sub << '\n';
                    i += len;
                    opFound = true;
                    break;
                }
            }
        }
        if (opFound) continue;

        // If starts with letter or underscore, parse identifier or keyword
        if (isalpha(line[i]) || line[i] == '_') {
            size_t start = i;
            while (i < line.length() && (isalnum(line[i]) || line[i] == '_')) {
                ++i;
            }
            string token = line.substr(start, i - start);

            if (keywords.find(token) != keywords.end())
                cout << "Keyword: " << token << '\n';
            else if (isValidIdentifier(token))
                cout << "Valid Identifier: " << token << '\n';
            else
                cout << "Invalid Identifier: " << token << '\n';

            continue;
        }

        // If starts with digit, parse number (integers only for now)
        if (isdigit(line[i])) {
            size_t start = i;
            while (i < line.length() && isdigit(line[i])) {
                ++i;
            }
            string token = line.substr(start, i - start);
            cout << "Number: " << token << '\n';
            continue;
        }

        // For any other single character, treat as unknown token
        cout << "Unknown token: " << line[i] << '\n';
        ++i;
    }
}

int main() {
    string filename;
    cout << "Enter source filename: ";
    getline(cin, filename);

    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: Could not open file '" << filename << "'\n";
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        tokenizeLine(line);
    }

    fin.close();
    return 0;
}