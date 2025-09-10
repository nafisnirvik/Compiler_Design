#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cout << "Enter function declaration/definition: ";
    getline(cin, s);

    while (!s.empty() && isspace(s.front())) s.erase(s.begin());
    while (!s.empty() && isspace(s.back())) s.pop_back();

    string types[] = {"int ", "float ", "double ", "char ", "void "};
    bool typeOK = false;

    for (string t : types) {
        if (s.rfind(t, 0) == 0) { // starts with this type
            typeOK = true;
            break;
        }
    }

    if (typeOK) {
        size_t pos1 = s.find('(');
        size_t pos2 = s.find(')');
        if (pos1 != string::npos && pos2 != string::npos && pos2 > pos1) {
            string after = s.substr(pos2 + 1);
            while (!after.empty() && isspace(after.front())) after.erase(after.begin());

            if (after == ";" || after == "{ }") {
                cout << "Correct declaration/definition" << endl;
                return 0;
            }
        }
    }

    cout << "Incorrect declaration/definition" << endl;
    return 0;
}
