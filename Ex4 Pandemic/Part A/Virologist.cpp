#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Virologist.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

Virologist &Virologist::treat(City city)
{
    if (_board[city] == 0)
    {
        throw invalid_argument{"Illegal action! Virologist try to treat, but infection level is zero in: " + city_to_string(city)};
    }

    if (in_my_cards(city) || (_cur_city == city))
    {
        if (_board.cure_discoverd(city))
        {
            _board[city] = 0;
            _cards.erase(city);
        }
        else
        {
            _board[city]--;
            _cards.erase(city);
        }
        return *this;
    }

    throw invalid_argument{"Illegal action! Virologist dosen\'t have " + city_to_string(city) + " card"};
}
