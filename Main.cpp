#include <iostream>
#include "NumberWithUnits.hpp"
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define CYAN        "\033[36m"
#define BOLDMAGENTA "\033[1m\033[35m"

using namespace std;
using namespace ariel;
ifstream units_file{"myunits1.txt"};

void questions ();

int main () {
    NumberWithUnits::read_units(units_file);
    // NumberWithUnits::print_map();
    string ans;
    cout << CYAN << "Hello and welcome to the ultimate converter !" << endl;
    cout << "We can convert from one unit to another with almost any type of unit you wish for." << endl;
    cout << "Of-course, there are limitations, you will not be able to convert years to kilograms obviously." << endl;
    cout << RESET << "\nLet's have a look at the units you can convert:" << endl;

    string line;
    ifstream ReadFile("myunits1.txt");
    while (getline (ReadFile, line)) {
        cout << line << endl;
    }
    ReadFile.close();

    cout << "\nAs you can see above, 1 km is 1000 m, but the converter can do the opposite as well!" << endl;
    cout << "Let's see what it means:" << endl;
    cout << "100 m in km is: " << NumberWithUnits(0, "km") + NumberWithUnits(100, "m") << endl;
    cout << "\nNow, Let's try something a bit more difficult to see that you understand how it works." << endl;
    questions();

    cout << "\nSo.... now that we know what is the converter is all about and had some fun," << endl; 
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
                cout << "Exception: " << RED << str << RESET << endl;
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
                cout << "\nThe result is: " << b + a << endl;
                break;
            }
            catch (const char * str) {
                cout << "Exception: " << RED << str << RESET << endl;
                cout << "Please try again from the options above: " << endl;
            }
            catch (const invalid_argument &invalid) {
                cout << "Exception: " << RED << invalid.what() << RESET << endl;
                cout << "Please try again from the options above: " << endl;
            }
        }

        cout << "\nWould you like to continue? (You can quit anytime with CTRL+C)" << endl;
        ans = "";
        cin >> ans;
        if (ans == "no")
            exit(0);
    }
}

void questions () {
    string ans = "";
    cout << "Please tell me how much is 300 g (grams) in kg (kilograms) - NUMBER ONLY:" << endl;
    cin >> ans;
    while (ans != "0.3") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << NumberWithUnits(0, "kg") + NumberWithUnits(300, "g") << endl;
    cout << RESET << "\nWe are not done! let's have some more fun :)" << endl;
    cout << "How much is 2kg * 4? - NUMBER ONLY"<< endl;
    ans = "";
    cin >> ans;
    while (ans != "8") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << NumberWithUnits(2, "kg") * 4 << endl << endl;
    
    cout << RESET << "Please say true or false, 2kg * 4 is the same as 4 * 2kg?" << endl;
    ans = "";
    cin >> ans;
    while (ans != "true") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << boolalpha;
    cout << GREEN << "That's correct, the answer is indeed " << (NumberWithUnits(2, "kg") * 4 == 4 * NumberWithUnits(2, "kg")) << RESET << endl << endl;
    
    cout << "Next question, is 2km longer than 2001m? (answer true or false)" << endl;
    ans = "";
    cin >> ans;
    while (ans != "false") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << (NumberWithUnits(2, "km") > NumberWithUnits(2001, "m")) << RESET << endl << endl;
    
    cout << "A few more questions, is 2000 m + 1 longer or equal to 3km - 1? (answer true or false)" << endl;
    ans = "";
    cin >> ans;
    while (ans != "true") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << (++NumberWithUnits(2000, "m") >= --NumberWithUnits(3, "km")) << RESET << endl << endl;
    
    cout << "How much is 8 years * (-1)? - NUMBER ONLY" << endl;
    NumberWithUnits a(0,"km");
    ans = "";
    cin >> ans;
    istringstream sample_input{ans + " [ year ] "};
    sample_input >> a;
    while (ans != "-8") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
        istringstream sample_input1{ans + " [ year ] "};
        sample_input1 >> a;
    }
    cout << GREEN << "That's correct, the answer is " << a << " and it's: " << (a <= -NumberWithUnits(8, "year")) << RESET << endl << endl;

    cout << "How much is 2 years - 6 month? - NUMBER ONLY" << endl;
    ans = "";
    cin >> ans;
    while (ans != "1.5") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << NumberWithUnits(2, "year") - NumberWithUnits(6, "month") << RESET << endl << endl;

    cout << "Is 3 hours - 1 different from 120 minutes + 1? (answer true or false)" << endl;
    ans = "";
    NumberWithUnits a_hour(2,"hour");
    NumberWithUnits a_min(120,"min");
    a_hour--;
    a_min++;
    cin >> ans;
    while (ans != "true") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << (a_hour != a_min) << RESET << endl << endl;

    cout << "How much is 6 tons + 1540 kg? - NUMBER ONLY" << endl;
    ans = "";
    NumberWithUnits a_ton(6,"ton");
    NumberWithUnits a_kg(1540,"kg");
    a_ton += a_kg;
    cin >> ans;
    while (ans != "7.54") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << a_ton << RESET << endl << endl;

    cout << "How much is 6 hours - 3600 seconds? - NUMBER ONLY" << endl;
    ans = "";
    NumberWithUnits a_hour1(6,"hour");
    NumberWithUnits a_sec(3600,"sec");
    a_hour1 -= a_sec;
    cin >> ans;
    while (ans != "5") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << a_hour1 << RESET << endl << endl;

    cout << BOLDMAGENTA << "LAST QUESTION!!\n" << RESET << "Is 5 years less than 60 month? (answer true or false)" << endl;
    ans = "";
    cin >> ans;
    while (ans != "false") {
        cout << RED << "Wrong, please try again:" << endl;
        cout << RESET;
        cin >> ans;
    }
    cout << GREEN << "That's correct, the answer is indeed " << (NumberWithUnits(5, "year") < NumberWithUnits(60, "month")) << RESET << endl << endl;
}