#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class Dispatcher : public Player
    {
    public:
        Dispatcher(Board &_board, City c) : Player(_board, c) {}
        Dispatcher &fly_direct(City city) override;
        std::string role() const override
        {
            return "Dispatcher";
        }
    };
}