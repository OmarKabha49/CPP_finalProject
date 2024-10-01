#include "Board.hpp"
#include "Property.hpp"
#include "SpecialTile.hpp"
#include "Street.hpp"


Board::Board() {

    // Special Tiles
    addTile(new SpecialTile("Go", 0, SpecialType::GO));

    // Brown Group
    addTile(new Street("Brown", 1, 60, 2, 50, 300));   // Mediterranean Avenue
    addTile(new SpecialTile("Community Chest", 2, SpecialType::COMMUNITY_CHEST));
    addTile(new Street("Brown", 3, 60, 4, 50, 300));   // Baltic Avenue
    addTile(new SpecialTile("Income Tax", 4, SpecialType::INCOME_TAX));

    // Train Tiles
    addTile(new Train("Reading Railroad", 5, 200));

    // Light Blue Group
    addTile(new Street("LightBlue", 6, 100, 6, 50, 300));  // Oriental Avenue
    addTile(new SpecialTile("Chance", 7, SpecialType::CHANCE));
    addTile(new Street("LightBlue", 8, 100, 6, 50, 300));  // Vermont Avenue
    addTile(new Street("LightBlue", 9, 120, 8, 50, 300));  // Connecticut Avenue

    // Special Tile - Jail
    addTile(new SpecialTile("Jail", 10, SpecialType::JAIL));

    // Pink Group
    addTile(new Street("Pink", 11, 140, 10, 100, 500));  // St. Charles Place

    // Utility Tile
    addTile(new Utility("Electric Company", 12, 150));

    addTile(new Street("Pink", 13, 140, 10, 100, 500));  // States Avenue
    addTile(new Street("Pink", 14, 160, 12, 100, 500));  // Virginia Avenue

    // Train Tiles
    addTile(new Train("Pennsylvania Railroad", 15, 200));

    // Orange Group
    addTile(new Street("Orange", 16, 180, 14, 100, 500)); // St. James Place
    addTile(new SpecialTile("Community Chest", 17, SpecialType::COMMUNITY_CHEST));
    addTile(new Street("Orange", 18, 180, 14, 100, 500)); // Tennessee Avenue
    addTile(new Street("Orange", 19, 200, 16, 100, 500)); // New York Avenue

    // Special Tile - Free Parking
    addTile(new SpecialTile("Free Parking", 20, SpecialType::FREE_PARKING));

    // Red Group
    addTile(new Street("Red", 21, 220, 18, 150, 750)); // Kentucky Avenue
    addTile(new SpecialTile("Chance", 22, SpecialType::CHANCE));
    addTile(new Street("Red", 23, 220, 18, 150, 750)); // Indiana Avenue
    addTile(new Street("Red", 24, 240, 20, 150, 750)); // Illinois Avenue

    // Train Tiles
    addTile(new Train("B. & O. Railroad", 25, 200));

    // Yellow Group
    addTile(new Street("Yellow", 26, 260, 22, 150, 750)); // Atlantic Avenue
    addTile(new Street("Yellow", 27, 260, 22, 150, 750)); // Ventnor Avenue

    // Utility Tile
    addTile(new Utility("Water Works", 28, 150));

    addTile(new Street("Yellow", 29, 280, 24, 150, 750)); // Marvin Gardens

    // Special Tile - Go to Jail
    addTile(new SpecialTile("Go to Jail", 30, SpecialType::GO_TO_JAIL));

    // Green Group
    addTile(new Street("Green", 31, 300, 26, 200, 900)); // Pacific Avenue
    addTile(new Street("Green", 32, 300, 26, 200, 900)); // North Carolina Avenue
    addTile(new SpecialTile("Community Chest", 33, SpecialType::COMMUNITY_CHEST));
    addTile(new Street("Green", 34, 320, 28, 200, 900)); // Pennsylvania Avenue

    // Train Tiles
    addTile(new Train("Short Line", 35, 200));

    addTile(new SpecialTile("Chance", 36, SpecialType::CHANCE));

    // Dark Blue Group
    addTile(new Street("DarkBlue", 37, 350, 35, 200, 1000)); // Park Place
    addTile(new SpecialTile("Luxury Tax", 38, SpecialType::LUXURY_TAX));
    addTile(new Street("DarkBlue", 39, 400, 50, 200, 1000)); // Boardwalk


}

void Board::addTile(Tile* tile) {
    tiles.push_back(tile);
}

Tile* Board::getTile(int position) const {
    if (position < tiles.size()) {
        return tiles[position];
    }
    return nullptr;
}