#include "Utility.hpp"
#include "Player.hpp"
#include <iostream>

Utility::Utility(const string &name, int position, int price) :
Tile(name, position), price(price)
{}

int Utility::getRent(int diceRoll) const {
    if (owner == nullptr) return 0;
    return diceRoll * 10;
}

Player * Utility::getOwner() const {
    return owner;
}

int Utility::getPrice() const {
    return price;
}

void Utility::setOwner(Player *newPlayer) {
    owner = newPlayer;
}

void Utility::onLand(Player *player) {
    if (getOwner() == nullptr) {
        while (true) {
            cout << player->getName() << ", do you want to buy the " <<
                getName() << " utility at position, " << getPosition() << " it cost : " << getPrice() <<  " (y/n): ";

            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                if (player->getBalance() < this->price) {
                    cout << "You don't have enough money." << endl;
                    break;
                }
                player->buyUtility(this);
                break;
            }
            else if (choice == 'n' || choice == 'N') {
                break;
            }
            else {
                cout << "Invalid input. Please enter y/Y or n/N" << endl;
            }
        }
    } else if (getOwner() != player) {
        int rent = getRent(getDiceRoll());
        player->decreaseBalance(rent);
        cout<<player->getName()<< " paid : " << rent << " to " << getOwner()->getName() << endl;
        getOwner()->increaseBalance(rent);
    }
}

void Utility::setDiceRoll(int diceRollResult) {
    diceRoll = diceRollResult;
}

int Utility::getDiceRoll() const {
    return diceRoll;
}
