#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

int main() {
    ifstream file("Delimiter_file.txt");

    if (!file) {
        cout << "Error: Cannot open file." << endl;
        return 1;
    }

    char ch;
    string number = "";

    cout << "\nDetected Tokens:\n\n";

    while (file.get(ch)) {
        if (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']') {
            cout << ch << " -> Delimiter" << endl;
        }

        if (isdigit(ch) || ch == '.') {
            number += ch;
        } else {
            if (number.length() > 0) {
                int dotCount = 0;
                for (int i = 0; i < number.length(); i++) {
                    if (number[i] == '.') {
                        dotCount++;
                    }
                }

                if (dotCount == 0) {
                    cout << number << " -> Integer" << endl;
                } else if (dotCount == 1 && number[0] != '.' && number[number.length() - 1] != '.') {
                    cout << number << " -> Real Number" << endl;
                } else {
                    cout << number << " -> Invalid Number Format" << endl;
                }

                number = "";
            }
        }
    }

    if (number.length() > 0) {
        int dotCount = 0;
        for (int i = 0; i < number.length(); i++) {
            if (number[i] == '.') {
                dotCount++;
            }
        }

        if (dotCount == 0) {
            cout << number << " -> Integer" << endl;
        } else if (dotCount == 1 && number[0] != '.' && number[number.length() - 1] != '.') {
            cout << number << " -> Real Number" << endl;
        } else {
            cout << number << " -> Invalid Number Format" << endl;
        }
    }

    file.close();
    return 0;
}
