#include "Tile.hpp"

Tile::Tile(const string& name, int position)
    : name(name), position(position) {}

const string& Tile::getName() const {return name;}
int Tile::getPosition() const {return position;}