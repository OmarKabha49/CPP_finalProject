#include "Street.hpp"
#include <iostream>

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

int Street::getHousePrice() {
    return housePrice;
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

void Street::onLand(Player *player) {
    if(getOwner() == nullptr) {
        while (true) {
            cout << player->getName() << ", do you want to buy the " <<
                getColor() << " street at position " << getPosition() << " it cost : " << getPrice() << " (y/n):";

            char choice;
            cin >> choice;
            if(choice == 'y' || choice == 'Y') {
                if(player->getBalance() < this->price) {
                    cout << "you dont have enoght money" << endl;
                    break;
                }
                player->buyStreet(this);
                break;
            }
            else if(choice == 'n' ||  choice == 'N') {
                break;
            }
            else{cout << "Invalid input. Please enter  y/Y or n/N" << endl;}
        }

    }

    else if(getOwner() != player) {
        int rent = getRent();
        player->decreaseBalance(rent);
        cout<<player->getName()<< " paid : " << rent << " to " << getOwner()->getName() << endl;
        getOwner()->increaseBalance(rent);
    }
}
