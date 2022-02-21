#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class FieldDoctor : public Player
    {
    public:
        FieldDoctor(Board &_board, City c) : Player(_board, c) {}
        FieldDoctor &treat(City city) override;
        std::string role() const override
        {
            return "FieldDoctor";
        }
    };
}