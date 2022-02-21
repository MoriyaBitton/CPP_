#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class Virologist : public Player
    {
    public:
        Virologist(Board &_board, City c) : Player(_board, c) {}
        Virologist &treat(City) override;
        std::string role() const override
        {
            return "Virologist";
        }
    };
}