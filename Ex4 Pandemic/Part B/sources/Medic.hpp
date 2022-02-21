#pragma once

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"

namespace pandemic
{
    class Medic : public Player
    {
    public:
        Medic(Board &_board, City c) : Player(_board, c) {}
        Medic &treat(City city) override;
        void medic_arrive() override;
        std::string role() const override
        {
            return "Medic";
        }
    };
}