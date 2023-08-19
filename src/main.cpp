#include <iostream>
#include <string>
#include "md5.h"

using namespace std;

string url = "https://api.pwnedpasswords.com/range/";

int main() {
    while (true) {
        cout << "Enter password: ";
        string line;
        getline(cin, line);

        string md5Hash = md5(line);
        // md5Hash = md5Hash.substr(0,5);

        // cout << "\n" << md5Hash;
    }
}