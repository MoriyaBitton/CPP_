#include <algorithm>
#include <iostream>

#include "Board.hpp"
#include "City.hpp"

using namespace std;
using namespace pandemic;

// constructor to build a new board
Board::Board()
{
    for (int c = (int)City::Algiers; c <= (int)City::Washington; c++)
    {
        _disease_cube[(City)c] = 0;
    }
    _cure_color.clear();
    _research_stations.clear();
}

// read & change disease level
int &Board::operator[](City city)
{
    return _disease_cube[city];
}

// output operator - include:
// 1. disease level in each one of the cities
// 2. treatment that discover untill now
// 3. research station that build untill here
ostream &pandemic::operator<<(ostream &os, const Board &board)
{
    os << "\n--------------------------- BOARD ---------------------------" << endl;

    // 1.
    os << "\nDisease level in each city:" << endl;
    for (const auto &pair : board._disease_cube)
    {
        os << "\t" << city_to_string(pair.first) << " : " << pair.second << endl;
    }

    // 2.
    os << "\nDiseases that have a cure:" << endl;
    for (const auto &color : board._cure_color)
    {
        os << "\t" << color_to_string(color) << endl;
    }

    // 3.
    os << "\nResearch stations:" << endl;
    for (const auto &city_rs : board._research_stations)
    {
        os << "\t" << city_to_string(city_rs) << endl;
    }

    os << "\n------------------------- END BOARD -------------------------" << endl;
    return os;
}

// return true if: disease level == 0 in every city
bool Board::is_clean() const
{
    for (const auto &city_disease : this->_disease_cube)
    {
        if (city_disease.second != 0)
        {
            return false;
        }
    }
    return true;
}

// remove discoverd treatment from the board
void Board::remove_cures()
{
    _cure_color.clear();
}

// ----------------------------------
// my functions
// ----------------------------------
Color Board::color_of(City city)
{
    return _cities_by_color.at(city);
}

bool Board::cure_discoverd(City city)
{
    return (cure_discoverd(color_of(city)));
}

bool Board::cure_discoverd(Color color)
{
    return (_cure_color.count(color) == 1);
}

bool Board::is_connect(const City &city1, const City &city2)
{
    return (_connect_cities.at(city1).count(city2) == 1);
}

bool Board::has_research_stations(City city)
{
    return (_research_stations.count(city) != 0);
}

void Board::add_research_stations(City city)
{
    _research_stations.insert(city);
}

int Board::disease_level(City city)
{
    return (_disease_cube.at(city));
}

void Board::mark_as_cure(Color color)
{
    _cure_color.insert(color);
}

map<City, set<City>> Board::_connect_cities{
    {Algiers, {Madrid, Paris, Istanbul, Cairo}},
    {Atlanta, {Chicago, Miami, Washington}},
    {Baghdad, {Tehran, Istanbul, Cairo, Riyadh, Karachi}},
    {Bangkok, {Kolkata, Chennai, Jakarta, HoChiMinhCity, HongKong}},
    {Beijing, {Shanghai, Seoul}},
    {Bogota, {MexicoCity, Lima, Miami, SaoPaulo, BuenosAires}},
    {BuenosAires, {Bogota, SaoPaulo}},
    {Cairo, {Algiers, Istanbul, Baghdad, Khartoum, Riyadh}},
    {Chennai, {Mumbai, Delhi, Kolkata, Bangkok, Jakarta}},
    {Chicago, {SanFrancisco, LosAngeles, MexicoCity, Atlanta, Montreal}},
    {Delhi, {Tehran, Karachi, Mumbai, Chennai, Kolkata}},
    {Essen, {London, Paris, Milan, StPetersburg}},
    {HoChiMinhCity, {Jakarta, Bangkok, HongKong, Manila}},
    {HongKong, {Bangkok, Kolkata, HoChiMinhCity, Shanghai, Manila, Taipei}},
    {Istanbul, {Milan, Algiers, StPetersburg, Cairo, Baghdad, Moscow}},
    {Jakarta, {Chennai, Bangkok, HoChiMinhCity, Sydney}},
    {Johannesburg, {Kinshasa, Khartoum}},
    {Karachi, {Tehran, Baghdad, Riyadh, Mumbai, Delhi}},
    {Khartoum, {Cairo, Lagos, Kinshasa, Johannesburg}},
    {Kinshasa, {Lagos, Khartoum, Johannesburg}},
    {Kolkata, {Delhi, Chennai, Bangkok, HongKong}},
    {Lagos, {SaoPaulo, Khartoum, Kinshasa}},
    {Lima, {MexicoCity, Bogota, Santiago}},
    {London, {NewYork, Madrid, Essen, Paris}},
    {LosAngeles, {SanFrancisco, Chicago, MexicoCity, Sydney}},
    {Madrid, {London, NewYork, Paris, SaoPaulo, Algiers}},
    {Manila, {Taipei, SanFrancisco, HoChiMinhCity, HongKong, Sydney}},
    {MexicoCity, {LosAngeles, Chicago, Miami, Lima, Bogota}},
    {Miami, {Atlanta, MexicoCity, Washington, Bogota}},
    {Milan, {Essen, Paris, Istanbul}},
    {Montreal, {Chicago, Washington, NewYork}},
    {Moscow, {StPetersburg, Istanbul, Tehran}},
    {Mumbai, {Karachi, Delhi, Chennai}},
    {NewYork, {Montreal, Washington, London, Madrid}},
    {Osaka, {Taipei, Tokyo}},
    {Paris, {Algiers, Essen, Madrid, Milan, London}},
    {Riyadh, {Baghdad, Cairo, Karachi}},
    {SanFrancisco, {LosAngeles, Chicago, Tokyo, Manila}},
    {Santiago, {Lima}},
    {SaoPaulo, {Bogota, BuenosAires, Lagos, Madrid}},
    {Seoul, {Beijing, Shanghai, Tokyo}},
    {Shanghai, {Beijing, HongKong, Taipei, Seoul, Tokyo}},
    {StPetersburg, {Essen, Istanbul, Moscow}},
    {Sydney, {Jakarta, Manila, LosAngeles}},
    {Taipei, {Shanghai, HongKong, Osaka, Manila}},
    {Tehran, {Baghdad, Moscow, Karachi, Delhi}},
    {Tokyo, {Seoul, Shanghai, Osaka, SanFrancisco}},
    {Washington, {Atlanta, NewYork, Montreal, Miami}}};
