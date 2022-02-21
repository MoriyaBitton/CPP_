#pragma once

#include <iostream>
#include <set>
#include <vector>

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

namespace pandemic
{
    class Player
    {
    private:
        int min_cards = 5;

    protected:
        Board &_board;
        City _cur_city;
        std::set<City> _cards;

    public:
        Player(Board &board, City city) : _board(board), _cur_city(city) {}

        // update
        virtual std::string role() const = 0;
        Player &take_card(City c);
        void remove_cards();

        // action
        virtual Player &drive(City city);
        virtual Player &fly_direct(City city);
        virtual Player &fly_charter(City city);
        virtual Player &fly_shuttle(City city);
        virtual Player &build();
        virtual Player &discover_cure(Color color);
        virtual Player &treat(City city);

        // my function
        virtual void medic_arrive(){};
        bool in_my_cards(City city);
        int num_of_my_cards();
        std::vector<City> get_cards_by_color(Color color);
    };
}