#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include <ctime>
#include <sstream>
#include <stdexcept>

#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel
{
  map<string, map<string, double>> NumberWithUnits::_unitConvertor = {};
  // read methood: "1 <unit1> = <coef> <unit2>"
  void NumberWithUnits::read_units(ifstream &units_file)
  {
    string buff;
    string unit1;
    string unit2;
    double num1 = 0;
    double num2 = 0;
    while (units_file >> num1 >> unit1 >> buff >> num2 >> unit2)
    {
      _unitConvertor[unit1][unit2] = num2;
      _unitConvertor[unit2][unit1] = 1 / num2;

      // add to the Unit Convertor table
      addConvertion(unit1, unit2);
      addConvertion(unit2, unit1);
    }
  }

  void NumberWithUnits::addConvertion(const string &unit1, const string &unit2)
  {
    for (auto [key, value] : _unitConvertor[unit2])
    {
      double coef = _unitConvertor[unit1][unit2] * value;
      _unitConvertor[unit1][key] = coef;
      _unitConvertor[key][unit1] = 1 / coef;
    }
  }

  // Convert from unit 1 to unit 2
  double NumberWithUnits::unitConvertor(double number /*change value*/, const string &unit1 /*from*/, const string &unit2 /*to*/)
  {
    if (unit1 == unit2)
    {
      return number;
    }
    try
    {
      double coef = _unitConvertor.at(unit1).at(unit2);
      return (number * coef);
    }
    catch (const out_of_range &e)
    {
      throw invalid_argument{"Units do not match - [" + unit1 + "] cannot be converted to [" + unit2 + "]"};
    }
  }

  // Overloading the arithmetic operators: {+, +=, -, -=}
  NumberWithUnits operator+(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    double converted = NumberWithUnits::unitConvertor(nwu2._number /*change unit*/, nwu2._units /*from*/, nwu1._units /*to*/);
    return NumberWithUnits(nwu1._number + converted, nwu1._units);
  }

  NumberWithUnits operator+(const NumberWithUnits &nwu)
  {
    return nwu;
  }

  NumberWithUnits &operator+=(NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    nwu1._number += NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, nwu1._units);
    return nwu1;
  }

  NumberWithUnits operator-(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    double converted = NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, nwu1._units);
    return NumberWithUnits(nwu1._number - converted, nwu1._units);
  }

  NumberWithUnits operator-(const NumberWithUnits &nwu)
  {
    return NumberWithUnits(-nwu._number, nwu._units);
  }

  NumberWithUnits &operator-=(NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    nwu1._number -= NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, nwu1._units);
    return nwu1;
  }

  // Overloading the comparison operators: {>, >=, <, <=, ==, !=}
  int compare(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    double nwu2_as_unit1 = NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, nwu1._units);
    int ans = 0;
    if (nwu2_as_unit1 < nwu1._number)
    {
      ans = 1;
    }
    else if (nwu2_as_unit1 > nwu1._number)
    {
      ans = -1;
    }
    return ans;
  }

  bool operator>(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return !(nwu1 <= nwu2);
    // return (compare(nwu1, nwu2) == 1);
  }

  bool operator>=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return (compare(nwu1, nwu2) >= 0);
  }

  bool operator<(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return !(nwu1 >= nwu2);
    // return (compare(nwu1, nwu2) == -1);
  }

  bool operator<=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return (compare(nwu1, nwu2) <= 0);
  }

  bool operator==(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return (compare(nwu1, nwu2) == 0);
  }

  bool operator!=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return !(nwu1 == nwu2);
    // return (compare(nwu1, nwu2) != 0);
  }

  // Overloading the Increament\Decreament operators: {++x, x++, --x, x--}
  /* postfix decrement */
  NumberWithUnits operator++(NumberWithUnits &nwu, int /*ignored*/)
  {
    return NumberWithUnits(nwu._number++, nwu._units);
  }

  /* prefix increment */
  NumberWithUnits &operator++(NumberWithUnits &nwu)
  {
    nwu._number++;
    return nwu;
  }

  /* postfix decrement */
  NumberWithUnits operator--(NumberWithUnits &nwu, int /*ignored*/)
  {
    return NumberWithUnits(nwu._number--, nwu._units);
  }

  /* prefix increment */
  NumberWithUnits &operator--(NumberWithUnits &nwu)
  {
    nwu._number--;
    return nwu;
  }

  // Overloading the Multiplication operator: {number*x, x*number, x*=number, number*=x}
  NumberWithUnits operator*(NumberWithUnits &nwu, double num)
  {
    return NumberWithUnits(nwu._number * num, nwu._units);
  }

  NumberWithUnits operator*(double num, NumberWithUnits &nwu)
  {
    return NumberWithUnits(nwu._number * num, nwu._units);
  }

  NumberWithUnits &operator*=(NumberWithUnits &nwu, double num)
  {
    nwu._number *= num;
    return nwu;
    // return NumberWithUnits(nwu._number *= num, nwu._units);
  }

  NumberWithUnits &operator*=(double num, NumberWithUnits &nwu)
  {
    num *= nwu._number;
    nwu._number = num;
    return nwu;
    // return NumberWithUnits(num *= nwu._number, nwu._units);
  }

  // Overloading the in\out stream operators: {<<, >>}
  ostream &operator<<(ostream &out, const NumberWithUnits &nwu)
  {
    out << nwu._number << "[" << nwu._units << "]";
    return out;
  }

  string NumberWithUnits::deleteSpaces(string str)
  {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
  }

  istream &operator>>(istream &in, NumberWithUnits &nwu)
  {
    // string buff;
    // in >> buff; // may have spaces
    // buff = NumberWithUnits::deleteSpaces(buff); // dont have spaces
    // istringstream noSpacesStream{buff};
    // char a = 0;
    // char b = 0;
    // noSpacesStream >> nwu._number >> a >> nwu._units >> b;
    // if (a != '[' || b != ']')
    // {
    //   throw invalid_argument("The format should be: number[unit], Receive: " + buff);
    // }
    // return in;

    string str;
    double getNumber = 0;
    char bracket = 0;
    in >> getNumber;
    in >> skipws >> bracket;

    if (bracket != '[')
    {
      in.setstate(ios::failbit);
    }

    getline(in, str, ']'); 
    string getUnit = str.c_str() + str.find_first_not_of(' ');
    size_t first_space = getUnit.find_first_of(' ');
    if (getUnit.size() > first_space && first_space > 0)
    {
      getUnit.resize(first_space);
    }
    nwu._number = getNumber;
    nwu._units = getUnit;
    return in;
  }
}