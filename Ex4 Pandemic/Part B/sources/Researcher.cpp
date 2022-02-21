#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Researcher.hpp"

using namespace std;
using namespace pandemic;

Researcher &Researcher::discover_cure(Color color)
{
    if (_board.cure_discoverd(color))
    {
        return *this;
    }

    vector<City> to_throw = get_cards_by_color(color);
    if (to_throw.size() >= min_cards)
    {
        for (size_t i = 0; i < min_cards; i++)
        {
            _cards.erase(to_throw.at(i));
        }
        _board.mark_as_cure(color);
    }
    else
    {
        throw invalid_argument{"Illegal action! Researcher try to cure where is no 5 cards of: " + color_to_string(color)};
    }

    return *this;
}
