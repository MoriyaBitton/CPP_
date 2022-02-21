#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

namespace ariel
{
  class NumberWithUnits
  {
  private:
    double _number;
    std::string _units;
    static std::map<std::string, std::map<std::string, double>> _unitConvertor;
    static void addConvertion(const std::string &unit1, const std::string &unit2);
    static double unitConvertor(double number /*change value*/, const std::string &unit1 /*from*/, const std::string &unit2 /*to*/);
    static std::string deleteSpaces(std::string str);

  public:
    NumberWithUnits(double num, const std::string &unit);
    ~NumberWithUnits() {}

    static void read_units(std::ifstream &units_file);

    // Overloading the arithmetic operators: {+, +=, -, -=}
    NumberWithUnits operator+(const NumberWithUnits &nwu2);
    NumberWithUnits operator+();
    NumberWithUnits &operator+=(const NumberWithUnits &nwu2);
    NumberWithUnits operator-(const NumberWithUnits &nwu2);
    NumberWithUnits operator-();
    NumberWithUnits &operator-=(const NumberWithUnits &nwu2);

    // Overloading the comparison operators: {>, >=, <, <=, ==, !=}
    friend int compare(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);

    friend bool operator>(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator>=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator<(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator<=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator==(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator!=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);

    // Overloading the Increament\Decreament operators: {++x, x++, --x, x--}
    NumberWithUnits operator++(int /*ignored*/); /* postfix decrement */
    NumberWithUnits &operator++();               /* prefix increment */
    NumberWithUnits operator--(int /*ignored*/); /* postfix decrement */
    NumberWithUnits &operator--();               /* prefix increment */

    // Overloading the Multiplication operator: {number*x, x*number, x*=number, number*=x}
    friend NumberWithUnits operator*(const NumberWithUnits &nwu, double num);
    friend NumberWithUnits operator*(double num, const NumberWithUnits &nwu);
    NumberWithUnits &operator*=(double num);

    // Overloading the in\out stream operators: {<<, >>}
    friend std::ostream &operator<<(std::ostream &out, const NumberWithUnits &nwu);
    friend std::istream &operator>>(std::istream &in, NumberWithUnits &nwu);
  };
}
