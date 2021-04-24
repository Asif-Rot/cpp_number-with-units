#include <iostream>
#include "NumberWithUnits.hpp"
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;
using namespace ariel;
ifstream units_file{"myunits1.txt"};

int main () {
    NumberWithUnits::read_units(units_file);
    string ans;
    cout << "Hello and welcome to the ultimate converter !" << endl;
    cout << "We can convert from one unit to another with almost any type of unit you wish for." << endl;
    cout << "Of-course, there are limitations, you will not be able to convert years to kilograms obviously." << endl;
    cout << "Let's have a look at the units you can convert:" << endl;

    string line;
    ifstream ReadFile("myunits1.txt");
    while (getline (ReadFile, line)) {
        cout << line << endl;
    }
    ReadFile.close();

    cout << "\nAs you can see above, 1 km is 1000 m, but the converter can do the opposite as well!" << endl;
    cout << "Let's see what it means:" << endl;
    cout << "100 m in km is: " << NumberWithUnits(0, "km") + NumberWithUnits(100, "m") << endl;
    cout << "Now, Let's try something a bit more difficult to see that you understand how it works" << endl;
    cout << "Please tell me how much is 300 g (grams) in kg (kilograms):" << endl;
    cin >> ans;
    while (ans != "0.3") {
        cout << "Wrong, please try again:" << endl;
        cin >> ans;
    }
    cout << "That's correct, the answer is indeed " << NumberWithUnits(0, "kg") + NumberWithUnits(300, "g") << endl;
    cout << "\nSo.... now that we know what is the converter is all about," << endl; 
    while (true) {
        cout << "\nWhat type of unit would you like to convert? (kg, g , km , m...)" << endl;
        ans = "";
        NumberWithUnits a(0, "km");
        while (true) {
            try {
                cin >> ans;
                string type = ans;
                ans = "";
                double u;
                cout << "Number of units?" << endl;
                cin >> ans;
                istringstream(ans) >> u;
                a = NumberWithUnits(u, type);
                break;
            }
            catch (const char * str) {
                cout << "Exception: " << str << endl;
                cout << "Please try again from the options above: " << endl;
            }
        }

        cout << "To which unit would you like to convert it to? (remember to follow the rules above)" << endl;
        ans = "";
        NumberWithUnits b(0, "km");
        while (true) {
            try {
                cin >> ans;
                b = NumberWithUnits(0, ans);
                break;
            }
            catch (const char * str) {
                cout << "Exception: " << str << endl;
                cout << "Please try again from the options above: " << endl;
            }
            catch (const invalid_argument &invalid) {
                cout << "Exception: " << invalid.what() << endl;
                cout << "Please try again from the options above: " << endl;
            }
        }

        cout << "\nThe result is: " << b + a << endl;
        cout << "\nWould you like to continue? (You can quit anytime with CTRL+C)" << endl;
        ans = "";
        cin >> ans;
        if (ans == "no")
            exit(0);
    }
}