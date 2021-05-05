#pragma once
#include <map>
#include <iostream>
#include "City.hpp"
#include "Color.hpp"
using namespace std;

namespace pandemic
{
    class Board
    {

    private:
    //int num;
    
    public:
        // constructor
        Board();
        int& operator[](City c);
        void remove_cures();
        friend ostream& operator<<(ostream& os,Board& b);
        bool is_clean();
    };
}