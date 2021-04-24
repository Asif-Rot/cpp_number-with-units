#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace ariel;

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

ifstream units_file{"units.txt"};

TEST_CASE("Good NumberWithUnits code") {
    NumberWithUnits::read_units(units_file);
    NumberWithUnits u_km{2, "km"};
    NumberWithUnits u_m{300, "m"};
    NumberWithUnits u_g{5000, "g"};

    CHECK(u_km == NumberWithUnits(2, "km"));
    CHECK(u_km == NumberWithUnits(2000, "m"));
    CHECK_FALSE(u_km == NumberWithUnits(3, "km"));
    CHECK(++u_km == NumberWithUnits(3, "km"));
    CHECK(u_km+u_m == NumberWithUnits(3.3, "km"));
    CHECK_EQ(u_m++, NumberWithUnits(0.3, "km"));
    CHECK_THROWS(u_km-u_g);
}

TEST_CASE("Unary operators") {
    NumberWithUnits u_kg{3, "kg"};
    NumberWithUnits u_g{5000, "g"};

    CHECK_EQ(u_g, NumberWithUnits(5000, "g"));
    CHECK(-u_kg == NumberWithUnits(-3, "kg"));
    CHECK(-u_kg == NumberWithUnits(-3000, "g"));
}

TEST_CASE("Binary operators") {
    NumberWithUnits::read_units(units_file);
    NumberWithUnits u_kg{3, "kg"};
    NumberWithUnits u_g{5000, "g"};
    NumberWithUnits u_ton{2, "ton"};
    NumberWithUnits u_hour{1, "hour"};
    NumberWithUnits u_min{9, "min"};
    NumberWithUnits u_sec{360, "sec"};

    CHECK_EQ(u_kg+u_g, NumberWithUnits(8, "kg"));
    CHECK(u_kg+u_g == NumberWithUnits(8000, "g"));
    CHECK(u_ton+u_g == NumberWithUnits(2.005, "ton"));
    CHECK_THROWS(u_ton+u_sec);
    CHECK((u_kg+=u_kg) == NumberWithUnits(6, "kg"));
    CHECK(u_hour-u_min == NumberWithUnits(0.85, "hour"));
    // cout << u_hour << endl;
    CHECK(u_hour-u_sec == NumberWithUnits(0.9, "hour"));
    // cout << u_kg << endl;
    CHECK((u_ton-=u_kg) == NumberWithUnits(1.994, "ton"));
    CHECK_THROWS(u_ton-u_hour);
    CHECK_THROWS(u_sec-=u_kg);
    CHECK_THROWS(u_min+=u_g);
}

TEST_CASE("++ / -- (Prefix / Postfix)") {
    NumberWithUnits::read_units(units_file);
    NumberWithUnits u_kg{2, "kg"};
    NumberWithUnits u_g{450, "g"};

    CHECK((u_kg++) == NumberWithUnits(2, "kg"));
    // cout << u_kg << endl;
    CHECK((u_kg) == NumberWithUnits(3, "kg"));
    CHECK((++u_kg) == NumberWithUnits(4, "kg"));
    CHECK((u_kg++) == NumberWithUnits(4000, "g"));
    CHECK((u_kg--) == NumberWithUnits(5000, "g"));
    CHECK((u_kg) == NumberWithUnits(4, "kg"));
    CHECK((--u_kg) == NumberWithUnits(3, "kg"));
    CHECK((u_g++) == NumberWithUnits(450, "g"));
    CHECK((u_g) == NumberWithUnits(451, "g"));
    CHECK((++u_g) == NumberWithUnits(452, "g"));
    CHECK((u_g++) == NumberWithUnits(0.452, "kg"));
    CHECK((--u_g) == NumberWithUnits(452, "g"));
}

TEST_CASE("Multiply") {
    NumberWithUnits::read_units(units_file);
    NumberWithUnits u_km{2, "km"};
    NumberWithUnits u_sec{350, "sec"};
    NumberWithUnits u_USD{3.56, "USD"};
    NumberWithUnits u_ILS{10, "ILS"};

    CHECK((u_km*4) == NumberWithUnits(8, "km"));
    CHECK((u_ILS*2) == NumberWithUnits(20, "ILS"));
    CHECK((u_ILS*=3.33) == NumberWithUnits(10, "USD"));
    CHECK((u_ILS) == NumberWithUnits(33.3, "ILS"));
    CHECK((2*u_sec) == NumberWithUnits(700, "sec"));
    CHECK((3*u_sec) == NumberWithUnits(17.5, "min"));
}

TEST_CASE("Comparing operators (== != > >= < <=)") {
    NumberWithUnits::read_units(units_file);
    bool t;
    NumberWithUnits u_km{2, "km"};
    NumberWithUnits u_m{2000, "m"};
    NumberWithUnits u_cm{100, "cm"};
    NumberWithUnits u_hour{1, "hour"};
    NumberWithUnits u_min{2, "min"};
    NumberWithUnits u_sec{360, "sec"};

    CHECK_EQ(u_km, u_km);
    CHECK(u_km == u_m);
    CHECK_EQ(u_km, u_m);
    CHECK_FALSE(u_km != u_m);
    CHECK(u_m == u_m);
    u_m++;
    CHECK_EQ(u_m, u_m);
    CHECK(u_m > u_km);
    CHECK_GT(u_m, u_km);
    CHECK_FALSE(u_km >= u_m);
    CHECK(u_hour > u_min);
    CHECK(u_min < u_hour);
    CHECK(u_min <= u_hour);
    CHECK_LE(u_min, u_hour);
    CHECK(u_sec > u_min);
    CHECK_NE(u_km, u_m);
    CHECK_GE(u_hour, u_sec);
    CHECK_LT(u_cm, u_km);
    CHECK_THROWS(t = (u_km < u_hour));
    CHECK_NOTHROW(t = (u_km > u_cm));

}

TEST_CASE("Input / Output operators") {
    NumberWithUnits::read_units(units_file);
    NumberWithUnits u_kg{3, "kg"};

    istringstream simple_input{"1[kg]"};
    simple_input >> u_kg;
    CHECK((u_kg) == NumberWithUnits(1, "kg"));
    istringstream simple_input1{"   5 [ kg ] "};
    simple_input1 >> u_kg;
    CHECK((u_kg) == NumberWithUnits(5, "kg"));
    CHECK_NOTHROW(cout << u_kg << endl);
}



    // NumberWithUnits u_km{2, "km"};
    // NumberWithUnits u_m{300, "m"};
    // NumberWithUnits u_cm{100, "cm"};
    // NumberWithUnits u_kg{3, "kg"};
    // NumberWithUnits u_g{5000, "g"};
    // NumberWithUnits u_ton{2, "ton"};
    // NumberWithUnits u_hour{1, "hour"};
    // NumberWithUnits u_min{2, "min"};
    // NumberWithUnits u_sec{350, "sec"};
    // NumberWithUnits u_USD{3.56, "USD"};
    // NumberWithUnits u_ILS{14.4, "ILS"};

