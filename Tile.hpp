#ifndef TILE_HPP
#define TILE_HPP
#include <string>

using namespace std;
class Player;
class Tile {

private:
    string name;
    int position;

public:
    Tile(const string& name,int position);
    virtual ~Tile() = default;

    virtual void onLand(Player* player) = 0;

    int getPosition() const;
    const string& getName() const;

};



#endif //TILE_HPP
