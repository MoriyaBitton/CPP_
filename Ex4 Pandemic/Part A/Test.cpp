#include <iostream>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "doctest.h"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"

using namespace std;
using namespace pandemic;

// ----------------------------
// All Data
// ----------------------------

const vector<City> all_cities{
    City::Algiers, City::Atlanta, City::Baghdad, City::Bangkok, City::Beijing, City::Bogota, City::BuenosAires, City::Cairo, City::Chennai,
    City::Chicago, City::Delhi, City::Essen, City::HoChiMinhCity, City::HongKong, City::Istanbul, City::Jakarta, City::Johannesburg,
    City::Karachi, City::KePasio, City::Khartoum, City::Kinshasa, City::Kolkata, City::Lagos, City::Lima, City::London, City::LosAngeles,
    City::Madrid, City::Manila, City::MexicoCity, City::Miami, City::Milan, City::Montreal, City::Moscow, City::Mumbai, City::NewYork,
    City::Osaka, City::Paris, City::Riyadh, City::SanFrancisco, City::Santiago, City::SaoPaulo, City::Seoul, City::Shanghai, City::StPetersburg,
    City::Sydney, City::Taipei, City::Tehran, City::Tokyo, City::Washington};

const map<City, Color> cities_by_color{
    {City::Algiers, Color::Black}, {City::Atlanta, Color::Blue}, {City::Baghdad, Color::Black}, {City::Bangkok, Color::Red}, {City::Beijing, Color::Red}, {City::Bogota, Color::Yellow}, {City::BuenosAires, Color::Yellow}, {City::Cairo, Color::Black}, {City::Chennai, Color::Black}, {City::Chicago, Color::Blue}, {City::Delhi, Color::Black}, {City::Essen, Color::Blue}, {City::HoChiMinhCity, Color::Red}, {City::HongKong, Color::Red}, {City::Istanbul, Color::Black}, {City::Jakarta, Color::Red}, {City::Johannesburg, Color::Yellow}, {City::Karachi, Color::Black}, {City::Khartoum, Color::Yellow}, {City::Kinshasa, Color::Yellow}, {City::Kolkata, Color::Black}, {City::Lagos, Color::Yellow}, {City::Lima, Color::Yellow}, {City::London, Color::Blue}, {City::LosAngeles, Color::Yellow}, {City::Madrid, Color::Blue}, {City::Manila, Color::Red}, {City::MexicoCity, Color::Yellow}, {City::Miami, Color::Yellow}, {City::Milan, Color::Blue}, {City::Montreal, Color::Blue}, {City::Moscow, Color::Black}, {City::Mumbai, Color::Black}, {City::NewYork, Color::Blue}, {City::Osaka, Color::Red}, {City::Paris, Color::Blue}, {City::Riyadh, Color::Black}, {City::SanFrancisco, Color::Blue}, {City::Santiago, Color::Yellow}, {City::SaoPaulo, Color::Yellow}, {City::Seoul, Color::Red}, {City::Shanghai, Color::Red}, {City::StPetersburg, Color::Blue}, {City::Sydney, Color::Red}, {City::Taipei, Color::Red}, {City::Tehran, Color::Black}, {City::Tokyo, Color::Red}, {City::Washington, Color::Blue}};

const map<City, vector<City>> cities_connection{
    {City::Algiers, {City::Madrid, City::Paris, City::Istanbul, City::Cairo}},
    {City::Atlanta, {City::Chicago, City::Miami, City::Washington}},
    {City::Baghdad, {City::Tehran, City::Istanbul, City::Cairo, City::Riyadh, City::Karachi}},
    {City::Bangkok, {City::Kolkata, City::Chennai, City::Jakarta, City::HoChiMinhCity, City::HongKong}},
    {City::Beijing, {City::Shanghai, City::Seoul}},
    {City::Bogota, {City::MexicoCity, City::Lima, City::Miami, City::SaoPaulo, City::BuenosAires}},
    {City::BuenosAires, {City::Bogota, City::SaoPaulo}},
    {City::Cairo, {City::Algiers, City::Istanbul, City::Baghdad, City::Khartoum, City::Riyadh}},
    {City::Chennai, {City::Mumbai, City::Delhi, City::Kolkata, City::Bangkok, City::Jakarta}},
    {City::Chicago, {City::SanFrancisco, City::LosAngeles, City::MexicoCity, City::Atlanta, City::Montreal}},
    {City::Delhi, {City::Tehran, City::Karachi, City::Mumbai, City::Chennai, City::Kolkata}},
    {City::Essen, {City::London, City::Paris, City::Milan, City::StPetersburg}},
    {City::HoChiMinhCity, {City::Jakarta, City::Bangkok, City::HongKong, City::Manila}},
    {City::HongKong, {City::Bangkok, City::Kolkata, City::HoChiMinhCity, City::Shanghai, City::Manila, City::Taipei}},
    {City::Istanbul, {City::Milan, City::Algiers, City::StPetersburg, City::Cairo, City::Baghdad, City::Moscow}},
    {City::Jakarta, {City::Chennai, City::Bangkok, City::HoChiMinhCity, City::Sydney}},
    {City::Johannesburg, {City::Kinshasa, City::Khartoum}},
    {City::Karachi, {City::Tehran, City::Baghdad, City::Riyadh, City::Mumbai, City::Delhi}},
    {City::Khartoum, {City::Cairo, City::Lagos, City::Kinshasa, City::Johannesburg}},
    {City::Kinshasa, {City::Lagos, City::Khartoum, City::Johannesburg}},
    {City::Kolkata, {City::Delhi, City::Chennai, City::Bangkok, City::HongKong}},
    {City::Lagos, {City::SaoPaulo, City::Khartoum, City::Kinshasa}},
    {City::Lima, {City::MexicoCity, City::Bogota, City::Santiago}},
    {City::London, {City::NewYork, City::Madrid, City::Essen, City::Paris}},
    {City::LosAngeles, {City::SanFrancisco, City::Chicago, City::MexicoCity, City::Sydney}},
    {City::Madrid, {City::London, City::NewYork, City::Paris, City::SaoPaulo, City::Algiers}},
    {City::Manila, {City::Taipei, City::SanFrancisco, City::HoChiMinhCity, City::Sydney}},
    {City::MexicoCity, {City::LosAngeles, City::Chicago, City::Miami, City::Lima, City::Bogota}},
    {City::Miami, {City::Atlanta, City::MexicoCity, City::Washington, City::Bogota}},
    {City::Milan, {City::Essen, City::Paris, City::Istanbul}},
    {City::Montreal, {City::Chicago, City::Washington, City::NewYork}},
    {City::Moscow, {City::StPetersburg, City::Istanbul, City::Tehran}},
    {City::Mumbai, {City::Karachi, City::Delhi, City::Chennai}},
    {City::NewYork, {City::Montreal, City::Washington, City::London, City::Madrid}},
    {City::Osaka, {City::Taipei, City::Tokyo}},
    {City::Paris, {City::Algiers, City::Essen, City::Madrid, City::Milan, City::London}},
    {City::Riyadh, {City::Baghdad, City::Cairo, City::Karachi}},
    {City::SanFrancisco, {City::LosAngeles, City::Chicago, City::Tokyo, City::Manila}},
    {City::Santiago, {City::Lima}},
    {City::SaoPaulo, {City::Bogota, City::BuenosAires, City::Lagos, City::Madrid}},
    {City::Seoul, {City::Beijing, City::Shanghai, City::Tokyo}},
    {City::Shanghai, {City::Beijing, City::HongKong, City::Taipei, City::Seoul, City::Tokyo}},
    {City::StPetersburg, {City::Essen, City::Istanbul, City::Moscow}},
    {City::Sydney, {City::Jakarta, City::Manila, City::LosAngeles}},
    {City::Taipei, {City::Shanghai, City::HongKong, City::Osaka, City::Manila}},
    {City::Tehran, {City::Baghdad, City::Moscow, City::Karachi, City::Delhi}},
    {City::Tokyo, {City::Seoul, City::Shanghai, City::Osaka, City::SanFrancisco}},
    {City::Washington, {City::Atlanta, City::NewYork, City::Montreal, City::Miami}}};

// ----------------------------
// Helper Random Function
// ----------------------------

City random_city()
{
    size_t rand_city = (size_t)rand() % 48;
    for (int i = 0; i < 48; i++)
    {
        for (const auto &city : all_cities)
        {
            if (i == rand_city)
            {
                return city;
            }
            i++;
        }
    }
    return City::Madrid;
}

Color random_color()
{
    int rand_indx = rand() % 4;
    switch (rand_indx)
    {
    case 1:
        return Black;
        break;

    case 2:
        return Blue;
        break;

    case 3:
        return Red;
        break;

    default:
        return Yellow;
        break;
    }
}

City get_connect_city(City city)
{
    int connected_cities = cities_connection.at(city).size();
    int n = rand() % connected_cities;
    return cities_connection.at(city)[(size_t)n];
}

bool is_connect(City city1, City city2)
{
    bool ans = false;
    for (auto &city : cities_connection.at(city1))
    {
        if (city == city2)
        {
            ans = true;
        }
    }
    return ans;
}

void take_n_cards(Player &player, int n)
{
    for (int i = 0; i < n; i++)
    {
        City rand_city = random_city();
        player.take_card(rand_city);
    }
}

void n_cards_by_given_color(Player &player, Color color, int n)
{
    set<City> ans;
    while (ans.size() < n)
    {
        for (const auto &pair : _cities_by_color)
        {
            if (pair.second == color)
            {
                ans.insert(pair.first);
            }
        }
    }

    // add the random picked cards to the player cards
    for (City city_i : ans)
    {
        player.take_card(city_i);
    }
}

void build_n_research_stations(Board board, int n)
{
    int counter = 0;
    while (counter < n)
    {
        City city = random_city();
        board.add_research_stations(city);
        counter++;
    }
}

// ----------------------------
// Test Cases
// ----------------------------

TEST_CASE("Initialization")
{

    // Board
    Board board;
    CHECK(board.is_clean());

    // Player && Roles
    City city = random_city();
    CHECK_NOTHROW(OperationsExpert operationsExpert(board, city););
    CHECK_NOTHROW(Dispatcher dispatcher(board, city););
    CHECK_NOTHROW(Scientist scientist(board, city, 4););
    CHECK_NOTHROW(Researcher researcher(board, city););
    CHECK_NOTHROW(Medic medic(board, city););
    CHECK_NOTHROW(Virologist virologist(board, city););
    CHECK_NOTHROW(GeneSplicer geneSplicer(board, city););
    CHECK_NOTHROW(FieldDoctor fieldDoctor(board, city););
}

TEST_CASE("Operator's")
{
    Board board;
    SUBCASE("operator []")
    {
        for (size_t i = 0; i < all_cities.size(); i++)
        {
            City city = all_cities[i];
            board[city] = i;
        }

        for (size_t i = 0; i < 48; i++)
        {
            CHECK_EQ(board[all_cities[i]], i);
        }
    }

    SUBCASE("operator <<")
    {
        stringstream os;
        CHECK_NOTHROW(os << board;);
    }
}

TEST_CASE("Player - Iligal/ ligal action")
{
    Board board;
    SUBCASE("drive")
    {
        City city_from = random_city();
        City city_to = random_city();
        OperationsExpert operationsExpert(board, city_from);

        if (is_connect(city_from, city_to))
        {
            CHECK_NOTHROW(operationsExpert.drive(city_to));
        }
        else
        {
            CHECK_THROWS(operationsExpert.drive(city_to));
        }
    }

    SUBCASE("fly_direct")
    {
        City city_from = random_city();
        City city_to = random_city();
        FieldDoctor fieldDoctor(board, city_from);
        int n = rand() % 10;
        take_n_cards(fieldDoctor, n);

        // check if it possible to fly
        if (fieldDoctor.in_my_cards(city_from))
        {
            int num_of_cards = fieldDoctor.num_of_my_cards();
            CHECK_NOTHROW(fieldDoctor.fly_direct(city_to));

            // check if the player throw card after the fly
            CHECK(fieldDoctor.num_of_my_cards() == (num_of_cards - 1));
        }
        else
        {
            CHECK_THROWS(fieldDoctor.fly_direct(city_to););
        }
    }

    SUBCASE("fly_charter")
    {
        City city_from = random_city();
        Dispatcher dispatcher(board, city_from);
        int n = rand() % 4;
        take_n_cards(dispatcher, n);
        City city_to = random_city();

        // check if it possible to fly
        if (dispatcher.in_my_cards(city_from) == 1 && city_from != city_to)
        {
            CHECK_NOTHROW(dispatcher.fly_charter(city_to));

            // check if the player throw card after the fly
            CHECK(dispatcher.in_my_cards(city_from) == 0);
        }
        else
        {
            CHECK_THROWS(dispatcher.fly_charter(city_to));
        }
    }

    SUBCASE("fly_shuttle")
    {
        City city_from = random_city();
        City city_to = random_city();
        build_n_research_stations(board, 10);
        Researcher researcher(board, city_from);

        if ((board.has_research_stations(city_from)) && (board.has_research_stations(city_to)))
        {
            CHECK_NOTHROW(researcher.fly_shuttle(city_to));
        }
        else
        {
            // there is no reaserch station in one of the two cities : "city_to", "city_from"
            CHECK_THROWS(researcher.fly_shuttle(city_to));
        }
    }

    SUBCASE("build")
    {
        City city_from = random_city();
        Medic medic(board, city_from);
        take_n_cards(medic, 16);
        build_n_research_stations(board, 10);
        City city_to = random_city();

        if (medic.in_my_cards(city_from))
        {
            if (board.has_research_stations(city_from))
            {
                CHECK_NOTHROW(medic.build());
                // didn't throw current city card
                CHECK(medic.in_my_cards(city_from) == 1);
            }
            else
            {
                CHECK_NOTHROW(medic.build());
                // throw current city card
                CHECK(medic.in_my_cards(city_from) == 0);
            }
        }
        else
        {
            // Player dosent have the current city card
            CHECK_THROWS(medic.build());
        }
    }

    SUBCASE("discover_cure")
    {
        City city_from = random_city();
        Virologist virologist(board, city_from);
        Color color = random_color();
        n_cards_by_given_color(virologist, color, 5);

        if (board.has_research_stations(city_from))
        {
            int num_of_cards = virologist.num_of_my_cards();
            CHECK_NOTHROW(virologist.discover_cure(color));

            if (board.cure_discoverd(city_from))
            {
                // the player dosent need to throw 5 cards because there is a cure
                CHECK(virologist.num_of_my_cards() == num_of_cards);
            }
            else
            {
                // the player need to throw 5 cards
                CHECK(virologist.num_of_my_cards() == (num_of_cards - 5));
            }
        }
        else
        {
            // there is no reaserch station in this current city
            CHECK_THROWS(virologist.discover_cure(color));
        }
    }

    SUBCASE("treat")
    {
        City cur_city = random_city();
        GeneSplicer geneSplicer(board, cur_city);

        if (board.disease_level(cur_city) != 0)
        {
            int disease_level = board.disease_level(cur_city);
            CHECK_NOTHROW(geneSplicer.treat(cur_city));
            if (board.cure_discoverd(cur_city))
            {
                CHECK(board.disease_level(cur_city) == 0);
            }
            else
            {
                CHECK(board.disease_level(cur_city) == (disease_level - 1));
            }
        }
        else
        {
            CHECK_THROWS(geneSplicer.treat(cur_city));
        }
    }
}

TEST_CASE("Test OperationsExpert")
{
    // Init
    Board board;
    City cur_city = random_city();
    OperationsExpert operationsExpert(board, cur_city);

    take_n_cards(operationsExpert, 10);

    // Test
    if (operationsExpert.in_my_cards(cur_city))
    {
        CHECK_NOTHROW(operationsExpert.build());
        CHECK_EQ(operationsExpert.in_my_cards(cur_city), 1);
    }
    else
    {
        CHECK_NOTHROW(operationsExpert.build());
    }
}

TEST_CASE("Test Dispatcher")
{
    // Init
    Board board;
    City city_from = random_city();
    Dispatcher dispatcher(board, city_from);

    City city_to = random_city();
    dispatcher.take_card(city_to);
    build_n_research_stations(board, 10);

    // Test
    CHECK_NOTHROW(dispatcher.fly_direct(city_to));
    if (board.has_research_stations(city_to))
    {
        CHECK_EQ(dispatcher.in_my_cards(city_to), 1);
    }
    else
    {
        CHECK_EQ(dispatcher.in_my_cards(city_to), 0);
    }
}

TEST_CASE("Test Scientist")
{
    // Init
    Board board;
    City cur_city = random_city();
    int n = rand() % 4;
    Scientist scientist(board, cur_city, n);

    Color color = random_color();
    take_n_cards(scientist, 10);
    n_cards_by_given_color(scientist, color, n);
    build_n_research_stations(board, 10);
    int num_of_cards = scientist.num_of_my_cards();

    // Test
    if (board.has_research_stations(cur_city))
    {
        CHECK_NOTHROW(scientist.discover_cure(color));
        if (board.cure_discoverd(color))
        {
            CHECK_EQ(scientist.num_of_my_cards(), num_of_cards);
        }
        else
        {
            CHECK_EQ(scientist.num_of_my_cards(), num_of_cards - n);
        }
    }
    else
    {
        CHECK_THROWS(scientist.discover_cure(color));
    }
}

TEST_CASE("Test Researcher")
{
    // Init
    Board board;
    City cur_city = random_city();
    Researcher researcher(board, cur_city);

    Color color = random_color();
    n_cards_by_given_color(researcher, color, 5);
    take_n_cards(researcher, 10);
    build_n_research_stations(board, 10);
    int num_of_cards = researcher.num_of_my_cards();

    // Test
    CHECK_NOTHROW(researcher.discover_cure(color));
    if (board.cure_discoverd(cur_city))
    {
        CHECK_EQ(researcher.num_of_my_cards(), num_of_cards);
    }
    else
    {
        CHECK_EQ(researcher.num_of_my_cards(), num_of_cards - 5);
    }
}

TEST_CASE("Test Medic")
{
    // Init
    Board board;
    City cur_city = random_city();
    Medic medic(board, cur_city);

    // Test (treat)
    CHECK_NOTHROW(board[cur_city] = 10);
    CHECK_NOTHROW(medic.treat(cur_city));
    CHECK_EQ(board.disease_level(cur_city), 0);

    // Discover all cures
    board.remove_cures();
    board.add_research_stations(cur_city);
    n_cards_by_given_color(medic, Color::Black, 5);
    n_cards_by_given_color(medic, Color::Blue, 5);
    n_cards_by_given_color(medic, Color::Red, 5);
    n_cards_by_given_color(medic, Color::Yellow, 5);

    CHECK_NOTHROW(medic.discover_cure(Color::Black));
    CHECK_NOTHROW(medic.discover_cure(Color::Blue));
    CHECK_NOTHROW(medic.discover_cure(Color::Red));
    CHECK_NOTHROW(medic.discover_cure(Color::Yellow));

    // Test (drive)
    City drive_to = random_city();
    if (is_connect(cur_city, drive_to))
    {
        CHECK_NOTHROW(board[drive_to] = 10);
        CHECK_NOTHROW(medic.drive(drive_to));
        CHECK_EQ(board[drive_to], 0);
    }

    // Test (fly_direct)
    City fly_direct_to = random_city();
    medic.take_card(fly_direct_to);
    CHECK_NOTHROW(board[fly_direct_to] = 10);
    CHECK_NOTHROW(medic.fly_direct(fly_direct_to));
    CHECK_EQ(board[fly_direct_to], 0);

    // Test (fly_charter)
    City fly_charter_to = random_city();
    medic.take_card(fly_direct_to); /*fly_direct_to == current city*/
    CHECK_NOTHROW(board[fly_charter_to] = 10);
    CHECK_NOTHROW(medic.fly_direct(fly_charter_to));
    CHECK_EQ(board[fly_charter_to], 0);

    // Test (fly_shuttle)
    City fly_shuttle_to = random_city();
    board.add_research_stations(fly_charter_to); /*fly_charter_to == current city*/
    board.add_research_stations(fly_shuttle_to);
    CHECK_NOTHROW(board[fly_shuttle_to] = 10);
    CHECK_NOTHROW(medic.fly_shuttle(fly_shuttle_to));
    CHECK_EQ(board[fly_shuttle_to], 0);
}

TEST_CASE("Test Virologist")
{
    // Init
    Board board;
    City cur_city = random_city();
    Virologist virologist(board, cur_city);

    City city_to_cure = random_city();
    take_n_cards(virologist, 10);

    // Test
    CHECK_NOTHROW(board[city_to_cure] = 10);
    if (city_to_cure != cur_city)
    {
        if (virologist.in_my_cards(city_to_cure))
        {
            CHECK_NOTHROW(virologist.treat(city_to_cure));
            CHECK_EQ(virologist.in_my_cards(city_to_cure), 0);
        }
        else
        {
            CHECK_THROWS(virologist.treat(city_to_cure));
        }
    }
    else /*cur_city == city_to_cure*/
    {
        CHECK_NOTHROW(virologist.treat(city_to_cure));
    }
}

TEST_CASE("Test GeneSplicer")
{
    // Init
    Board board;
    City cur_city = random_city();
    GeneSplicer geneSplicer(board, cur_city);

    Color color = random_color();
    build_n_research_stations(board, 10);
    n_cards_by_given_color(geneSplicer, Color::Black, 4);
    n_cards_by_given_color(geneSplicer, Color::Blue, 4);
    n_cards_by_given_color(geneSplicer, Color::Red, 4);
    n_cards_by_given_color(geneSplicer, Color::Yellow, 4);
    int num_of_cards = geneSplicer.num_of_my_cards(); /*16*/

    // Test
    if (board.has_research_stations(cur_city))
    {
        CHECK_NOTHROW(geneSplicer.discover_cure(color));
        CHECK_EQ(geneSplicer.num_of_my_cards(), num_of_cards /*16*/);
    }
    else
    {
        // there is no 5 cards from any color
        CHECK_THROWS(geneSplicer.discover_cure(color));
    }
}

TEST_CASE("Test FieldDoctor")
{
    // Init
    Board board;
    City cur_city = random_city();
    FieldDoctor fieldDoctor(board, cur_city);

    City city_to_cure = get_connect_city(cur_city);

    // Test
    CHECK_NOTHROW(board[city_to_cure] = 10);
    CHECK_NOTHROW(fieldDoctor.treat(city_to_cure));
    CHECK_EQ(board[city_to_cure], 9);

    board.add_research_stations(cur_city);
    Color color = cities_by_color.at(city_to_cure);
    n_cards_by_given_color(fieldDoctor, color, 5);
    fieldDoctor.discover_cure(color);

    CHECK_NOTHROW(fieldDoctor.treat(city_to_cure));
    CHECK_EQ(board[city_to_cure], 0);
}