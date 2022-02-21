#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Dispatcher.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

Dispatcher &Dispatcher::fly_direct(City city)
{
    if (_cur_city == city)
    {
        throw invalid_argument{"Illegal action! Dispatcher alraedy in city: " + city_to_string(city)};
    }

    if (_board.has_research_stations(_cur_city))
    {
        _cur_city = city;
        return *this;
    }

    if (_cards.count(city) == 1)
    {
        _cards.erase(city);
        _cur_city = city;
        return *this;
    }

    throw invalid_argument{"Illegal action! Dispatcher try to fly direct from: " + city_to_string(_cur_city) + " to: " + city_to_string(city)};
}
