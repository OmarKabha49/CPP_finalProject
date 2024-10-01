#include "SpecialTile.hpp"

#include <iostream>

#include "Player.hpp"

SpecialTile::SpecialTile(const std::string& name, int position, SpecialType type)
    : Tile(name, position), type(type) {}

void SpecialTile::onLand(Player* player) {

    switch (type) {
        case SpecialType::GO:
            player->increaseBalance(200); // Passing Go
        break;
        case SpecialType::JAIL:
            player->goToJail();
            cout << player->getName() << " in jail" << endl;

        break;
        case SpecialType::GO_TO_JAIL:
            player->move(10); // Move to Jail directly
            player->goToJail();
            cout << player->getName() << " in jail" << endl;
        break;
        case SpecialType::INCOME_TAX:
            player->decreaseBalance(200); // Pay Income Tax
            cout << player->getName() << " paid : 200" << endl;
        break;
        case SpecialType::LUXURY_TAX:
            player->decreaseBalance(100); // Pay Luxury Tax
            cout << player->getName() << " paid : 100" << endl;
        break;
        default:
            break;
    }
}