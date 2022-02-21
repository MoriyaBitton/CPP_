#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "NumberWithUnits.hpp"
using namespace std;

namespace ariel
{
  // read methood: "1 <unit1> = <coef> <unit2>"
  map<string, map<string, double>> NumberWithUnits::_unitConvertor = {};
  const double Epsilon = 0.001;

  NumberWithUnits::NumberWithUnits(double num, const std::string &unit)
  {
    if (_unitConvertor.count(unit) == 0)
    {
      throw invalid_argument{"Unit [ " + unit + " ] is not legal!"};
    }
    this->_number = num;
    this->_units = unit;
  }

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

      // add to the Unit Convertor to _unitConvertor table
      addConvertion(unit1, unit2);
      addConvertion(unit2, unit1);
    }
  }

  void NumberWithUnits::addConvertion(const string &unit1, const string &unit2)
  {
    // add unit2 convertion
    for (auto &pair : _unitConvertor[unit2])
    {
      double coef = _unitConvertor[unit1][unit2] * pair.second;
      _unitConvertor[unit1][pair.first] = coef;
      _unitConvertor[pair.first][unit1] = 1 / coef;
    }
    // add unit1 convertion
    for (auto &pair : _unitConvertor[unit1])
    {
      double coef = _unitConvertor[unit2][unit1] * pair.second;
      _unitConvertor[unit2][pair.first] = coef;
      _unitConvertor[pair.first][unit2] = 1 / coef;
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
  NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &nwu2)
  {
    double converted = NumberWithUnits::unitConvertor(nwu2._number /*change unit*/, nwu2._units /*from*/, this->_units /*to*/);
    return NumberWithUnits(this->_number + converted, this->_units);
  }

  NumberWithUnits NumberWithUnits::operator+()
  {
    return NumberWithUnits(+this->_number, this->_units);
  }

  NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &nwu2)
  {

    this->_number += NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, this->_units);
    return *this;
  }

  NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &nwu2)
  {
    double converted = NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, this->_units);
    return NumberWithUnits(this->_number - converted, this->_units);
  }

  NumberWithUnits NumberWithUnits::operator-()
  {
    return NumberWithUnits(-this->_number, this->_units);
  }

  NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &nwu2)
  {
    this->_number -= NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, this->_units);
    return *this;
  }

  // Overloading the comparison operators: {>, >=, <, <=, ==, !=}
  int compare(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    double nwu2_as_unit1 = NumberWithUnits::unitConvertor(nwu2._number, nwu2._units, nwu1._units);
    int ans = 0;
    if (nwu1._number - nwu2_as_unit1 > Epsilon)
    {
      ans = 1;
    }
    else if (nwu2_as_unit1 - nwu1._number > Epsilon)
    {
      ans = -1;
    }
    return ans;
  }

  bool operator>(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return !(nwu1 <= nwu2);
  }

  bool operator>=(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return (compare(nwu1, nwu2) >= 0);
  }

  bool operator<(const NumberWithUnits &nwu1, const NumberWithUnits &nwu2)
  {
    return !(nwu1 >= nwu2);
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
  }

  // Overloading the Increament\Decreament operators: {++x, x++, --x, x--}
  /* postfix decrement */
  NumberWithUnits NumberWithUnits::operator++(int /*ignored*/)
  {
    return NumberWithUnits((this->_number)++, this->_units);
  }

  /* prefix increment */
  NumberWithUnits &NumberWithUnits::operator++()
  {
    ++(this->_number);
    return *this;
  }

  /* postfix decrement */
  NumberWithUnits NumberWithUnits::operator--(int /*ignored*/)
  {
    return NumberWithUnits((this->_number)--, this->_units);
  }

  /* prefix increment */
  NumberWithUnits &NumberWithUnits::operator--()
  {
    --(this->_number);
    return *this;
  }

  // Overloading the Multiplication operator: {number*x, x*number, x*=number, number*=x}
  NumberWithUnits operator*(const NumberWithUnits &nwu, double num)
  {
    return NumberWithUnits(nwu._number * num, nwu._units);
  }

  NumberWithUnits operator*(double num, const NumberWithUnits &nwu)
  {
    return NumberWithUnits(nwu._number * num, nwu._units);
  }

  NumberWithUnits &NumberWithUnits::operator*=(double num)
  {
    this->_number *= num;
    return *this;
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
    char c1 = ' ';
    char c2 = ' ';
    string getUnit = " ";
    double getNumber = 0;

    in >> skipws >> getNumber >> c1 >> getUnit;

    size_t bracketIndx = getUnit.length() - 1;

    if (getUnit.at(bracketIndx) != ']')
    {
      in >> c2;
    }
    else
    {
      getUnit = getUnit.substr(0, bracketIndx);
    }

    nwu = NumberWithUnits(getNumber, getUnit);
    return in;
  }
}