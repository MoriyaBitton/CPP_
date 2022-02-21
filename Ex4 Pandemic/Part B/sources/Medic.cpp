#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Medic.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

Medic &Medic::treat(City city)
{
    if (_cur_city != city)
    {
        throw invalid_argument{"Illegal action! Medic is not in city: " + city_to_string(city)};
    }

    if (_board[city] == 0)
    {
        throw invalid_argument{"Illegal action! Medic try to treat, but infection level is zero in: " + city_to_string(_cur_city)};
    }

    _board[city] = 0;
    return *this;
}

void Medic::medic_arrive()
{
    if (_board.cure_discoverd(_cur_city))
    {
        _board[_cur_city] = 0;
    }
}
