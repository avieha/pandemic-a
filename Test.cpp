#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Dispatcher.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "Medic.hpp"
#include "OperationsExpert.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "Virologist.hpp"
#include "doctest.h"
#include <vector>
#include <map>

using namespace std;
using namespace pandemic;

const vector<City> cities{
    Algiers, Atlanta, Baghdad, Bangkok, Beijing, Bogota, BuenosAires,
    Cairo, Chennai, Chicago, Delhi, Essen, HoChiMinhCity, HongKong,
    Istanbul, Jakarta, Johannesburg, Karachi, KePasio, Khartoum,
    Kinshasa, Kolkata, Lagos, Lima, London, LosAngeles, Madrid,
    Manila, MexicoCity, Miami, Milan, Montreal, Moscow, Mumbai, NewYork,
    Osaka, Paris, Riyadh, SanFrancisco, Santiago, SaoPaulo, Seoul, Shanghai,
    StPetersburg, Sydney, Taipei, Tehran, Tokyo, Washington};

const map<City, vector<City>> connections{
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


/*function to get a random color*/

static Color rand_color()
{
    vector<Color> v = {Blue, Red, Yellow, Black};
    srand(time(0));
    int num = rand() % 5;
    int i = 0;
    for (const auto &c : v)
    {
        if (num == i)
        {
            return c;
        }
        i++;
    }
    return Yellow;
}

/**function to get a random city**/

static City rand_city()
{
    srand(time(0));
    int num = rand() % 49;
    int i = 0;
    for (const auto &c : cities)
    {
        if (num == i)
        {
            return c;
        }
        i++;
    }
    return Taipei;
}

/**function to get a random adjacent city**/

static City rand_adj_city(City c)
{
    srand(time(0));
    int num = rand() % 49;
    int i = 0;
    for (auto &t : connections.at(c))
    {
        if (num == i)
        {
            return t;
        }
    }
    return (connections.at(c))[0];
}

TEST_CASE("Board test")
{
    Board board;
    CHECK(board.is_clean());
    City c;
    for (int i = 0; i < 20; i++)
    {
        c = rand_city();
        CHECK(board[c] == 0);
    }
}

TEST_CASE("Dispatcher test")
{
    Board board;
    City r_city = rand_city();
    Dispatcher d(board, r_city);
    CHECK(d.role() == "Dispatcher");
    d.take_card(r_city);
    d.build();
    for (int i = 0; i < 20; i++)
    {
        r_city = rand_city();
        CHECK_NOTHROW(d.fly_direct(r_city));
        d.build();
    }
}

TEST_CASE("FieldDoctor test")
{
    Board board;
    City c = rand_city();
    for (int i = 0; i < 0; i++)
    {
        c = rand_city();
        FieldDoctor f{board, c};
        f.take_card(c);
        CHECK(f.role() == "FieldDoctor");
        for (const auto &con_city : connections.at(c))
        {
            CHECK_THROWS(f.treat(con_city));
            board[con_city] = 5;
            int i = 5;
            while (i-- > 0)
            {
                CHECK_NOTHROW(f.treat(con_city));
            }
        }
    }
}

TEST_CASE("GeneSplicer test")
{
    Board board;
    City c = rand_city();
    GeneSplicer g{board, c};
    g.take_card(c);
    CHECK(g.role() == "GeneSplicer");
    Color color;
    for (int i = 0; i < 20; i++)
    {
        color = rand_color();
        c = rand_city();
        g.take_card(c);
        CHECK_THROWS(g.discover_cure(color)); // no research station!
        g.build();
        CHECK_THROWS(g.discover_cure(color)); // there are no 5 cards!
        for (int j = 0; j < 4; j++)
        {
            g.take_card(rand_city());
        }
        CHECK_NOTHROW(g.discover_cure(color)); // not necessarily the same color
    }
}

TEST_CASE("Medic test")
{
    Board board;
    City c = rand_city();
    Medic m{board, c};
    CHECK(m.role() == "Medic");
    for (int i = 0; i < 20; i++)
    {
        CHECK(board[c] == 0);
        board[c] = 5;
        m.take_card(c);
        CHECK_NOTHROW(m.treat(c));
        CHECK(board[c] == 0);
        c = rand_city();
    }
}

TEST_CASE("OperationsExpert test")
{
    Board board;
    City c = rand_city();
    OperationsExpert o{board, c};
    CHECK(o.role() == "OperationsExpert");
    CHECK_NOTHROW(o.build()); // possible even without cards
    for (int i = 0; i < 20; i++)
    {
        c = rand_city();
        o.drive(c);
        for (const auto &ni : connections.at(c))
        {
            CHECK_NOTHROW(o.drive(ni));
            CHECK_NOTHROW(o.build());
        }
    }
}

TEST_CASE("Researcher test")
{
    Board board;
    City c = rand_city();
    Color r_color = rand_color();
    Researcher r{board, c};
    CHECK(r.role() == "Researcher");
    CHECK_THROWS(r.discover_cure(r_color)); // no card taken
    for (int i = 0; i < 20; i++)
    {
        c = rand_city();
        r_color = rand_color();
        r.take_card(c);
        r.drive(c);
        for (const auto &ni : connections.at(c))
        {
            CHECK_NOTHROW(r.drive(ni));
            CHECK_NOTHROW(r.discover_cure(r_color));
        }
    }
}

TEST_CASE("Scientist test")
{
    Board board;
    srand(time(0));
    for (int i = 0; i < 20; i++)
    {
        City c = rand_city();
        int num = rand() % 5;
        Scientist s{board, c, num};
        Color color = rand_color();
        CHECK_THROWS(s.discover_cure(color)); // no build() was done
        s.build();
        CHECK_THROWS(s.discover_cure(color)); // not even 1 card taken
        for (int j = 1; j <= num; j++)
        {
            s.take_card(c);
        }
        CHECK_NOTHROW(s.discover_cure(color));
    }
}

TEST_CASE("Virologist test")
{
    for (int i = 0; i < 20; i++)
    {
        Board board;
        City c = rand_city();
        Virologist v{board, c};
        CHECK_THROWS(v.treat(c)); // no cubes of disease.
        CHECK(v.role() == "Virologist");
        for (City city : connections.at(c))
        {
            CHECK_THROWS(v.treat(city));// no cards!!
        }
        CHECK_NOTHROW(board[c] = 5);
        CHECK_NOTHROW(v.take_card(c));
        CHECK_NOTHROW(v.treat(c));
        CHECK(board[c] == 4);
    }
}