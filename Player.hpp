#pragma once
#include "Board.hpp"
//using namespace std;

namespace pandemic
{
    class Player
    {

    protected:
        pandemic::Board b;
        pandemic::City c;

    public:
        Player(pandemic::Board &b, pandemic::City c): b(b), c(c){}
        Player &drive(pandemic::City c);
        virtual Player &fly_direct(pandemic::City c);
        Player &fly_charter(pandemic::City c);
        Player &fly_shuttle(pandemic::City c);
        virtual Player &build();
        virtual Player &discover_cure(pandemic::Color c);
        virtual Player &treat(pandemic::City c);
        Player &take_card(pandemic::City c);
        std::string role();
    };

}