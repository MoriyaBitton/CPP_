#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class OperationsExpert : public Player
    {
    public:
        OperationsExpert(Board &_board, City c) : Player(_board, c) {}
        OperationsExpert &build() override;
        std::string role() const override
        {
            return "OperationsExpert";
        }
    };
}