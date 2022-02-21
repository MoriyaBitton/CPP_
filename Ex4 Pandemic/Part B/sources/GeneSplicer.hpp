#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class GeneSplicer : public Player
    {
    private:
        int min_cards = 5;

    public:
        GeneSplicer(Board &_board, City c) : Player(_board, c) {}
        GeneSplicer &discover_cure(Color color) override;
        std::string role() const override
        {
            return "GeneSplicer";
        }
    };
}