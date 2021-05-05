#include "Board.hpp"
using namespace std;
using namespace pandemic;

int x =0;

namespace pandemic
{
    // constructor
    Board::Board(){};
    int& Board::operator[](pandemic::City c)
    {
        return x;
    }
    void Board::remove_cures(){};
    ostream& operator<<(ostream& os, pandemic::Board& b) { return os; };
    bool Board::is_clean() { return true; };
}