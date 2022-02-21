#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace ariel;
using namespace std;

ifstream units_file{"units.txt"};

TEST_CASE("Units of different dimensions")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "USD"};
    NumberWithUnits b{2, "ton"};
    NumberWithUnits c{12, "m"};
    NumberWithUnits d{3, "hour"};
    NumberWithUnits e{41, "g"};
    NumberWithUnits f{60, "sec"};

    CHECK_THROWS(a + b);
    CHECK_THROWS(c += d);
    CHECK_THROWS(d - c);
    CHECK_THROWS(b - c);
    CHECK_THROWS(e -= a);
    CHECK_THROWS(f - c);
}

TEST_CASE("Units of same dimensions")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "USD"};
    NumberWithUnits b{2, "ton"};
    NumberWithUnits c{12, "m"};
    NumberWithUnits d{3, "hour"};
    NumberWithUnits e{41, "g"};
    NumberWithUnits f{60, "sec"};

    CHECK_NOTHROW(a * 2);
    CHECK_NOTHROW(b *= 4);
    CHECK_NOTHROW(d++);
    CHECK_NOTHROW(f -= d);
    CHECK_NOTHROW(--c);
    CHECK_NOTHROW(10 *= e);
}

TEST_CASE("Units with Upper and Lower letters are illigal types")
{
    CHECK_THROWS(NumberWithUnits(1, "Km"));
    CHECK_THROWS(NumberWithUnits(3, "Usd"));
    CHECK_THROWS(NumberWithUnits(2, "IlS"));
    CHECK_THROWS(NumberWithUnits(4, "Sec"));
    CHECK_THROWS(NumberWithUnits(5, "KILOGRAM"));
    CHECK_THROWS(NumberWithUnits(6, "MIN"));
    CHECK_THROWS(NumberWithUnits(6, "Ton"));
    CHECK_THROWS(NumberWithUnits(6, "GR"));
}

TEST_CASE("operators: (+), (-)")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits a{2, "ILS"};
    NumberWithUnits b{2, "USD"};
    NumberWithUnits c{10, "sec"};
    NumberWithUnits d{3, "hour"};
    CHECK_EQ(a + b, NumberWithUnits{8.66, "ILS"});
    CHECK_EQ(b + a, NumberWithUnits{2.6006, "USD"});
    CHECK_EQ(c + d, NumberWithUnits{10810, "sec"});
    CHECK_EQ(d + c, NumberWithUnits{3.00278, "hour"});
}

TEST_CASE("operators: (+=), (-=)")
{
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{5, "km"};
    NumberWithUnits b{5000, "cm"};

    CHECK((a += b) == NumberWithUnits{5.05, "km"});
    CHECK(a == NumberWithUnits{5.05, "km"});

    CHECK((b += a) == NumberWithUnits{510000, "cm"});
    CHECK(b == NumberWithUnits{510000, "cm"});

    CHECK((a -= b) == NumberWithUnits{-0.05, "km"});
    CHECK(a == NumberWithUnits{-0.05, "km"});

    CHECK((b -= a) == NumberWithUnits{515000, "cm"});
    CHECK(b == NumberWithUnits{515000, "cm"});
}

TEST_CASE("Comparison operators: (>), (<), (>=), (<=), (==), (!=)")
{
    NumberWithUnits::read_units(units_file);

    CHECK_GT(NumberWithUnits{10000, "m"}, NumberWithUnits{0.9, "km"});
    CHECK_NE(NumberWithUnits{0.9, "km"}, NumberWithUnits{10000, "m"});

    CHECK_LT(NumberWithUnits{0.5, "ton"}, NumberWithUnits{550, "kg"});
    CHECK_NE(NumberWithUnits{0.5, "ton"}, NumberWithUnits{550, "kg"});

    CHECK_GT(NumberWithUnits{30, "min"}, NumberWithUnits{0.25, "hour"});
    CHECK_NE(NumberWithUnits{0.25, "hour"}, NumberWithUnits{30, "min"});

    CHECK_LT(NumberWithUnits{110, "ILS"}, NumberWithUnits{35, "USD"});
    CHECK_NE(NumberWithUnits{110, "ILS"}, NumberWithUnits{35, "USD"});

    CHECK_EQ(NumberWithUnits{3, "ton"}, NumberWithUnits{3000000, "g"});
    CHECK_EQ(NumberWithUnits{1800, "sec"}, NumberWithUnits{0.5, "hour"});
    CHECK_LT(NumberWithUnits{33.033, "ILS"}, NumberWithUnits{10, "USD"});
}

TEST_CASE("operators: inc/dec")
{
    NumberWithUnits::read_units(units_file);
    NumberWithUnits millionDollars{1000000, "USD"};

    CHECK(millionDollars++ == NumberWithUnits{1000000, "USD"});
    CHECK(millionDollars == NumberWithUnits{1000001, "USD"});

    CHECK(++millionDollars == NumberWithUnits{1000002, "USD"});
    CHECK(millionDollars == NumberWithUnits{1000002, "USD"});

    CHECK(millionDollars-- == NumberWithUnits{1000002, "USD"});
    CHECK(millionDollars == NumberWithUnits{1000001, "USD"});

    CHECK(--millionDollars == NumberWithUnits{1000000, "USD"});
    CHECK(millionDollars == NumberWithUnits{1000000, "USD"});
}

TEST_CASE("Multiplication operators: (float*x), (x*float), (x*=float), (float*=x)")
{
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2.5, "hour"};

    CHECK((a * 0.5) == NumberWithUnits{1.25, "hour"});
    CHECK((2.7 * a) == NumberWithUnits{6.75, "hour"});

    CHECK((a *= 5.3) == NumberWithUnits{13.25, "hour"});
    CHECK(a == NumberWithUnits{13.25, "hour"});

    double b = 2.05;
    CHECK((b *= a) == NumberWithUnits{27.1625, "hour"});
    CHECK(NumberWithUnits{27.1625, "hour"} == NumberWithUnits{27.1625, "hour"});
}

TEST_CASE("operator: (<<)")
{
    ostringstream out_a;
    NumberWithUnits a{7.8989, "km"};
    out_a << a;
    CHECK_EQ(out_a.str(), "7.8989[km]");

    NumberWithUnits b{9, "ILS"};
    ostringstream out_b;
    out_b << b;
    CHECK_EQ(out_b.str(), "9[ILS]");

    NumberWithUnits c{5, "g"};
    ostringstream out_c;
    out_c << c;
    CHECK_EQ(out_c.str(), "5[g]");

    NumberWithUnits d{100, "ton"};
    ostringstream out_d;
    out_d << d;
    CHECK_EQ(out_d.str(), "100[ton]");

    NumberWithUnits e{15, "hour"};
    ostringstream out_e;
    out_e << e;
    CHECK_EQ(out_e.str(), "15[hour]");
}

TEST_CASE("operator: (>>)")
{
    NumberWithUnits n{2, "km"};

    istringstream a{"700 [ kg ]"};
    a >> n;
    CHECK_EQ(n, NumberWithUnits{700, "kg"});

    istringstream b{"56[sec] "};
    b >> n;
    CHECK_EQ(n, NumberWithUnits{56, "sec"});

    istringstream c{"14[USD]"};
    c >> n;
    CHECK_EQ(n, NumberWithUnits{14, "USD"});

    istringstream d{"-6[ m]"};
    d >> n;
    CHECK_EQ(n, NumberWithUnits{-6, "m"});

    istringstream e{"-9.7[hour ]"};
    e >> n;
    CHECK_EQ(n, NumberWithUnits{-9.7, "hour"});
}
