#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class Researcher : public Player
    {
    private:
        int min_cards = 5;

    public:
        Researcher(Board &_board, City c) : Player(_board, c) {}
        Researcher &discover_cure(Color color) override;
        std::string role() const override
        {
            return "Researcher";
        }
    };
}