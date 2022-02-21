#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "OperationsExpert.hpp"
#include "Player.hpp"

using namespace std;
using namespace pandemic;

OperationsExpert &OperationsExpert::build()
{
    _board.add_research_stations(_cur_city);
    return *this;
}
