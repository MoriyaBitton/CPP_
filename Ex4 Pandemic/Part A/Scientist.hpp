#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class Scientist : public Player
    {
    private:
        int _n_cards;

    public:
        Scientist(Board &_board, City c, int n) : Player(_board, c), _n_cards(n) {}
        Scientist &discover_cure(Color color) override;
        std::string role() const override
        {
            return "Scientist";
        }
    };
}