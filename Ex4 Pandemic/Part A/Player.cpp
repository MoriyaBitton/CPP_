#include <iostream>
#include <vector>

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

// ----------------------------------
// update
// ----------------------------------
Player &Player::take_card(City city)
{
    _cards.insert(city);
    return *this;
}

// empty player cards
void Player::remove_cards()
{
    _cards.clear();
}

// ----------------------------------
// action
// ----------------------------------
Player &Player::drive(City city)
{
    if (_cur_city == city)
    {
        throw invalid_argument{"Illegal action! you are alraedy in city: " + city_to_string(city)};
    }
    if (!Board::is_connect(_cur_city, city) && !Board::is_connect(city, _cur_city))
    {
        throw invalid_argument{"Illegal action! this Cities: " + city_to_string(_cur_city) + " and " + city_to_string(city) + ", are not connect."};
    }
    _cur_city = city;
    medic_arrive();
    return *this;
}

Player &Player::fly_direct(City city)
{
    if (_cur_city == city)
    {
        throw invalid_argument{"Illegal action! you are alraedy in city: " + city_to_string(city)};
    }
    if (_cards.count(city) == 0)
    {
        throw invalid_argument{"Illegal action! the player dosen\'t have " + city_to_string(city) + " card."};
    }
    _cards.erase(city);
    _cur_city = city;
    medic_arrive();
    return *this;
}

Player &Player::fly_charter(City city)
{
    if (_cur_city == city)
    {
        throw invalid_argument{"Illegal action! you are alraedy in city: " + city_to_string(city)};
    }
    if (_cards.count(_cur_city) == 0)
    {
        throw invalid_argument{"Illegal action! the player dosen\'t have " + city_to_string(_cur_city) + " card."};
    }
    _cards.erase(_cur_city);
    _cur_city = city;
    medic_arrive();
    return *this;
}

Player &Player::fly_shuttle(City city)
{
    if (_cur_city == city)
    {
        throw invalid_argument{"Illegal action! you are alraedy in city: " + city_to_string(city)};
    }
    if (!_board.has_research_stations(_cur_city) || !_board.has_research_stations(city))
    {
        throw invalid_argument{"Illegal action! the player dosen\'t have " + city_to_string(_cur_city) + " card."};
    }
    _cur_city = city;
    medic_arrive();
    return *this;
}

Player &Player::build()
{
    if (_cards.count(_cur_city) == 0)
    {
        throw invalid_argument{"Illegal action! the player dosen\'t have " + city_to_string(_cur_city) + " card."};
    }
    if (_board.has_research_stations(_cur_city))
    {
        cout << city_to_string(_cur_city) << ", already have a research stations." << endl;
        return *this;
    }
    _cards.erase(_cur_city);
    _board.add_research_stations(_cur_city);
    return *this;
}

Player &Player::discover_cure(Color color)
{
    if (_board.cure_discoverd(color))
    {
        return *this;
    }

    if (_board.has_research_stations(_cur_city))
    {
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
            throw invalid_argument{"Illegal action! try to cure where is no 5 cards of: " + color_to_string(color)};
        }
    }
    else
    {
        throw invalid_argument{"Illegal action! try to cure where is no research station in: " + city_to_string(_cur_city)};
    }
    return *this;
}

Player &Player::treat(City city)
{
    if (_board[_cur_city] == 0)
    {
        throw invalid_argument{"Illegal action! infection level is zero in: " + city_to_string(_cur_city)};
    }

    if (_board.cure_discoverd(_cur_city))
    {
        _board[_cur_city] = 0;
    }
    else
    {
        _board[_cur_city]--;
    }
    return *this;
}

// ----------------------------------
// my function
// ----------------------------------
bool Player::in_my_cards(City city)
{
    return (_cards.count(city) == 1);
}

int Player::num_of_my_cards()
{
    return _cards.size();
}

vector<City> Player::get_cards_by_color(Color color)
{
    vector<City> ans;
    for (const auto &card : _cards)
    {
        if (Board::color_of(card) == color)
        {
            ans.push_back(card);
        }
    }
    return ans;
}
