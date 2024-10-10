#include "Street.hpp"
#include <iostream>

#include "Game.hpp"
#include "Logger.hpp"

Street::Street(const string &Color, int position, int price, int baseRent,int housePrice, int hotelPrice)
    : Tile(Color, position), price(price), baseRent(baseRent), housePrice(housePrice), hotelPrice(hotelPrice) {

}

const string &Street::getColor() const {
    return getName();
}

int Street::getRent() const {
    if(hotel) {
        return baseRent * 5;
    }
    return baseRent * (1 << houses);
}

void Street::setOwner(Player* newOwner) {
    owner = newOwner;

}

Player* Street::getOwner() const {
    return owner;
}
int Street::getPrice() const {
    return price;
}

int Street::getHouses() const {
    return houses;
}

bool Street::getHotel() const {
    return hotel;
}


int Street::getHousePrice() const{
    return housePrice;
}

int Street::getHotelPrice() const{
    return hotelPrice;
}

bool Street::canBuildHouse(const Player * player) const {
    if (owner != player) return false;
    // Check if the player owns all streets in the color group (handled outside)
    if (houses < 4 && !hotel) {
        return true;
    }
    return false;
}

bool Street::buildHouse() {
    if (houses < 4) {
        houses++;
        return true;
    }
    return false;
}

bool Street::buildHotel() {
    if (houses == 4 && !hotel) {
        hotel = true;
        return true;
    }
    return false;
}

void Street::onLand(Player* player) {
    if(this->owner == nullptr) {
        string outPut = player->getName() + ", do you want to buy " + getName() + " for $" + to_string(getPrice()) + "? (y/n)";

        function<void(const string&)> promptPlayer;

        promptPlayer = [this, player](const string& input) {
            Logger::log(input);
            char choice = tolower(input[1]);
            if (choice == 'y') {
                if (player->getBalance() < this->price) {
                    Logger::log("You don't have enough money to buy this property.");
                } else {
                    player->buyStreet(this);
                    Logger::log(player->getName() + " bought " + getName() + " for $" + to_string(getPrice()) + ".");
                }
            } else if (choice == 'n') {
                Logger::log(player->getName() + " decided not to buy " + getName() + ".");

            }
            else {
                Logger::log("Invalid input. Please enter 'y' or 'n'.");
                onLand(player);
            }
        };
        Game::getInstance()->waitForInput(promptPlayer,outPut);
    }
    else if(owner != player){
        int rent = getRent();
        player->payRent(rent, owner);
    }
    else {
        Logger::log(player->getName() + " landed on their own property.");
    }
}
