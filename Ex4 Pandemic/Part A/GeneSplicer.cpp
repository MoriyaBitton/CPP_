#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "GeneSplicer.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

GeneSplicer &GeneSplicer::discover_cure(Color color)
{
    if (_board.cure_discoverd(color))
    {
        return *this;
    }

    if (_board.has_research_stations(_cur_city))
    {
        if (_cards.size() >= min_cards)
        {
            vector<City> to_throw;
            int count = 0;
            for (const auto &card : _cards)
            {
                if (count < min_cards)
                {
                    to_throw.push_back(card);
                }
                count++;
            }

            for (size_t i = 0; i < min_cards; i++)
            {
                _cards.erase(to_throw.at(i));
            }
            _board.mark_as_cure(color);
        }
        else
        {
            throw invalid_argument{"Illegal action! GeneSplicer try to cure where is no 5 cards."};
        }
    }

    else
    {
        throw invalid_argument{"Illegal action! GeneSplicer try to cure where is no research station in: " + city_to_string(_cur_city)};
    }
    return *this;
}
