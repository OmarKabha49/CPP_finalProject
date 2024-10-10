
#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>
#include "Tile.hpp"

using namespace std;

class Board {
private:
    vector<Tile*> tiles;

public:
    Board();
    void addTile(Tile* tile);
    Tile* getTile(int position) const;

};



#endif //BOARD_HPP
