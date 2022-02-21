#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Scientist.hpp"

using namespace std;
using namespace pandemic;

Scientist &Scientist::discover_cure(Color color)
{
    if (_board.cure_discoverd(color))
    {
        return *this;
    }

    if (_board.has_research_stations(_cur_city))
    {
        vector<City> to_throw = get_cards_by_color(color);
        if (to_throw.size() >= _n_cards)
        {
            for (size_t i = 0; i < _n_cards; i++)
            {
                _cards.erase(to_throw.at(i));
            }
            _board.mark_as_cure(color);
        }
        else
        {
            throw invalid_argument{"Illegal action! Scientist try to cure where is no enough cards of: " + color_to_string(color)};
        }
    }
    else
    {
        throw invalid_argument{"Illegal action! Scientist try to cure where is no research station " + city_to_string(_cur_city)};
    }
    return *this;
}
