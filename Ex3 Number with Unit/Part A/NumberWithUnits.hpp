#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
using namespace std;

namespace ariel
{
  class NumberWithUnits
  {
  private:
    double _number;
    string _units;
    static map<string, map<string, double>> _unitConvertor;
    static void addConvertion(const string &unit1, const string &unit2);
    static double unitConvertor(double number /*change value*/, const string &unit1 /*from*/, const string &unit2 /*to*/);
    static string deleteSpaces(string str);

  public:
    NumberWithUnits(double num, string unit)
    {
      if (!_unitConvertor.contains(unit))
      {
        throw invalid_argument("Unit [ " + unit + " ] is not legal!");
      }
      this->_number = num;
      this->_units = unit;
    }
    ~NumberWithUnits() {}

    static void read_units(ifstream &units_file);

    // Overloading the arithmetic operators: {+, +=, -, -=}
    friend NumberWithUnits operator+(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend NumberWithUnits operator+(const NumberWithUnits &nwu);
    friend NumberWithUnits &operator+=(NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend NumberWithUnits operator-(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend NumberWithUnits operator-(const NumberWithUnits &nwu);
    friend NumberWithUnits &operator-=(NumberWithUnits &nwu1, const NumberWithUnits &nwu2);

    // Overloading the comparison operators: {>, >=, <, <=, ==, !=}
    friend int compare(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);

    friend bool operator>(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator>=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator<(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator<=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator==(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);
    friend bool operator!=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2);

    // Overloading the Increament\Decreament operators: {++x, x++, --x, x--}
    friend NumberWithUnits operator++(NumberWithUnits &nwu, int /*ignored*/); /* postfix decrement */
    friend NumberWithUnits &operator++(NumberWithUnits &nwu);                 /* prefix increment */
    friend NumberWithUnits operator--(NumberWithUnits &nwu, int /*ignored*/); /* postfix decrement */
    friend NumberWithUnits &operator--(NumberWithUnits &nwu);                 /* prefix increment */

    // Overloading the Multiplication operator: {number*x, x*number, x*=number, number*=x}
    friend NumberWithUnits operator*(NumberWithUnits &nwu, double num); // add const
    friend NumberWithUnits operator*(double num, NumberWithUnits &nwu);
    friend NumberWithUnits &operator*=(NumberWithUnits &nwu, double num);
    friend NumberWithUnits &operator*=(double num, NumberWithUnits &nwu);

    // Overloading the in\out stream operators: {<<, >>}
    friend ostream &operator<<(ostream &out, const NumberWithUnits &nwu);
    friend istream &operator>>(istream &in, NumberWithUnits &nwu);
  };
}
