#include <iostream>
#include <fstream>

namespace ariel {
    class NumberWithUnits {

        double u;
        std::string type;

        public:
            NumberWithUnits(double number, std::string unit) {
                if (!exists(unit)) {
                    throw ("No such unit");
                }
                this->u = number;
                this->type = unit;
            }

            static void read_units(std::ifstream& file);
            static bool connected(const NumberWithUnits& a1, const NumberWithUnits& a2);
            static bool exists(std::string& unit);

            // Unary operators
            NumberWithUnits operator-();
            NumberWithUnits operator+();

            // Binary operators
            NumberWithUnits operator+(const NumberWithUnits& a);
            NumberWithUnits operator+=(const NumberWithUnits& a);
            NumberWithUnits operator-(const NumberWithUnits& a);
            NumberWithUnits operator-=(const NumberWithUnits& a);

            // ++ / -- (Prefix / postfix)
            NumberWithUnits& operator++();
            NumberWithUnits operator++(int);
            NumberWithUnits& operator--();
            NumberWithUnits operator--(int);

            // Multiply
            friend NumberWithUnits operator*(const NumberWithUnits& a, const double& number);
            friend NumberWithUnits operator*(const double& number, const NumberWithUnits& a);
            NumberWithUnits operator*=(double number);

            // Comparing operators
            friend bool operator==(const NumberWithUnits& a1, const NumberWithUnits& a2);
            friend bool operator!=(const NumberWithUnits& a1, const NumberWithUnits& a2);
            friend bool operator>(const NumberWithUnits& a1, const NumberWithUnits& a2);
            friend bool operator>=(const NumberWithUnits& a1, const NumberWithUnits& a2);
            friend bool operator<(const NumberWithUnits& a1, const NumberWithUnits& a2);
            friend bool operator<=(const NumberWithUnits& a1, const NumberWithUnits& a2);

            // Output / Input opertors
            friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& a);
            friend std::istream& operator>> (std::istream& is, NumberWithUnits& a);

    };

};