#include <iostream>
#include "NumberWithUnits.hpp"
#include <unordered_map>
using namespace std;

namespace ariel {

    const double EPS = 0.0001;
    static unordered_map<string, unordered_map<string, double>> units;
    static double converted;

    void NumberWithUnits::read_units(std::ifstream& file) {
        double a1 = 0;
        double a2 = 0;
        double tmp = 0;
        string t1;
        string t2;
        string equal;

        while (file >> a1 >> t1 >> equal >> a2 >> t2) {
            units[t1][t2] = a2;
            units[t2][t1] = 1/a2;

            for (auto& i: units[t2]) {
                tmp = a2 * i.second;
                units[t1][i.first] = tmp;
                units[i.first][t1] = 1/tmp;
            }

            for (auto& i: units[t1]) {
                tmp = (1/a2) * i.second;
                units[t2][i.first] = tmp;
                units[i.first][t2] = 1/tmp;
            }
        }
    }

    // ==============================Unary operators==============================
    NumberWithUnits NumberWithUnits::operator-() {
        exists(this->type);
        return NumberWithUnits(-this->u, this->type);
    }
    
    NumberWithUnits NumberWithUnits::operator+() {
        exists(this->type);
        return NumberWithUnits(+this->u, this->type);
    }

    // ==============================Binary operators==============================
    NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits& a) {
        NumberWithUnits tmp(this->u, this->type);
        if (!(NumberWithUnits::connected(tmp, a))) {
            throw invalid_argument("Units do not match - ["+a.type+"] cannot be converted to ["+tmp.type+"]");
        }
        this->u += converted;

        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& a) {
        NumberWithUnits tmp(this->u, this->type);
        if (!(NumberWithUnits::connected(tmp, a))) {
            throw invalid_argument("Units do not match - ["+a.type+"] cannot be converted to ["+tmp.type+"]");
        }
        return NumberWithUnits((this->u+converted), this->type);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& a) {
        NumberWithUnits tmp(this->u, this->type);
        if (!(NumberWithUnits::connected(tmp, a))) {
            throw invalid_argument("Units do not match - ["+a.type+"] cannot be converted to ["+tmp.type+"]");
        }
        return NumberWithUnits((this->u-converted), this->type);
    }

    NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits& a) {
        NumberWithUnits tmp(this->u, this->type);
        if (!(NumberWithUnits::connected(tmp, a))) {
            throw invalid_argument("Units do not match - ["+a.type+"] cannot be converted to ["+tmp.type+"]");
        }
        this->u -= converted;

        return *this;
    }

    // ==============================(++ / --) - (Prefix / Postfix)==============================
    NumberWithUnits& NumberWithUnits::operator++() {
        ++this->u;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int) {
        NumberWithUnits tmp(this->u++, this->type);
        return tmp;
    }

    NumberWithUnits& NumberWithUnits::operator--() {
        --this->u;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int) {
        NumberWithUnits tmp(this->u--, this->type);
        return tmp;
    }

    // ==============================Multiply==============================
    NumberWithUnits operator*(const NumberWithUnits& a, const double& number) {
        NumberWithUnits tmp((a.u * number), a.type);
        return tmp;
    }
    
    NumberWithUnits operator*(const double& number, const NumberWithUnits& a) {
        return a * number;
    }

    NumberWithUnits NumberWithUnits::operator*=(double number) {
        this->u *= number;
        return *this;
    }

    // ==============================Comparing operators==============================
    bool operator==(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (!(NumberWithUnits::connected(a1, a2))) {
            throw invalid_argument("Units do not match - ["+a2.type+"] cannot be converted to ["+a1.type+"]");
        }

        return (abs(a1.u - converted) < EPS);
    }

    bool operator!=(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        return (!(a1==a2));
    }

    bool operator>(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (!(NumberWithUnits::connected(a1, a2))) {
            throw invalid_argument("Units do not match - ["+a2.type+"] cannot be converted to ["+a1.type+"]");
        }

        return (a1.u - converted > 0);
    }

    bool operator>=(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (!(NumberWithUnits::connected(a1, a2))) {
            throw invalid_argument("Units do not match - ["+a2.type+"] cannot be converted to ["+a1.type+"]");
        }

        return (a1.u - converted >= 0);
    }

    bool operator<(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (!(NumberWithUnits::connected(a1, a2))) {
            throw invalid_argument("Units do not match - ["+a2.type+"] cannot be converted to ["+a1.type+"]");
        }

        return (a1.u - converted < 0);
    }

    bool operator<=(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (!(NumberWithUnits::connected(a1, a2))) {
            throw invalid_argument("Units do not match - ["+a2.type+"] cannot be converted to ["+a1.type+"]");
        }

        return (a1.u - converted <= 0);
    }
    
    // ==============================Output / Input==============================
    ostream& operator<< (ostream& os, const NumberWithUnits& a) {
        os << a.u << '[' << a.type << ']';
        return os;
    }

    static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
        char actualChar = 0;
        input >> actualChar;
        if (!input) {
            return input;
        }

        if (actualChar != expectedChar) {
            // failbit is for format error
            input.setstate(ios::failbit);
        }
        return input;
    }

    istream& operator>> (istream& is, NumberWithUnits& a) {
        string newtype;
        double newu = 0;

        ios::pos_type startPosition = is.tellg();

        if ( (!(is >> newu)) || (!getAndCheckNextCharIs(is,'[')) ||
            (!(is >> newtype))) {
            auto errorState = is.rdstate();
            is.clear();
            is.seekg(startPosition);
            is.clear(errorState);
        } else {
                ulong i = newtype.length() - 1;
                if (newtype.at(i) != ']') {
                    string last;
                    is >> last;
                    newtype += last;
                }
                i = newtype.length() - 1;
                newtype = newtype.substr(0,i);
                a = NumberWithUnits(newu, newtype);
            }

        return is;
    }
    
    /**
     *  Function for checking if units[a1] contains a2
     *  For example: a1 = (1, "m"), a2 = (1, "km")
     *  connected(a1, a2) - returns true
     *  Else: if a2 = (1, "g"), connected(a1, a2) will return false
    **/
    bool NumberWithUnits::connected(const NumberWithUnits& a1, const NumberWithUnits& a2) {
        if (units.find(a1.type) != units.end() && units[a1.type].find(a2.type) != units[a1.type].end()) { 
            converted = a2.u * units[a2.type][a1.type];
            return true;
        }

        return false;
    }

    void NumberWithUnits::exists(string& unit) {
        if (units.find(unit) == units.end()) {
            throw ("No such unit");
        }
    }

    void NumberWithUnits::print_map() {
        // For accessing outer map
        unordered_map<string, unordered_map<string, double> >::iterator itr;
  
        // For accessing inner map
        unordered_map<string, double>::iterator ptr;

        for (itr = units.begin(); itr != units.end(); itr++) {
  
            for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
                cout << "> " << itr->first
                    << " > " << ptr->first
                    << " = " << ptr->second << endl;
            }
            cout << endl;
        }
    }

};