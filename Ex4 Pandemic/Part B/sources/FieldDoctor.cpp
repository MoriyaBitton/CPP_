#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "FieldDoctor.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

FieldDoctor &FieldDoctor::treat(City city)
{
    if (Board::is_connect(_cur_city, city) || (_cur_city == city))
    {
        if (_board[city] == 0)
        {
            throw invalid_argument{"Illegal action! FieldDoctor try to treat, but infection level is zero in: " + city_to_string(_cur_city)};
        }

        if (_board.cure_discoverd(city))
        {
            _board[city] = 0;
        }
        else
        {
            _board[city]--;
        }
        return *this;
    }

    throw invalid_argument{"Illegal action! FieldDoctor try to treat in city: " + city_to_string(city) + ", who\'s not connect to current city: " + city_to_string(_cur_city)};
}
