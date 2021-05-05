#pragma once
#include "Player.hpp"

namespace pandemic{

    class GeneSplicer: public Player {

        public:
            GeneSplicer(Board& b, City c): Player(b, c) {};
            Player& discover_cure(Color c) override;
    };
    
}