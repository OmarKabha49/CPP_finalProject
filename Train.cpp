
#include "Train.hpp"

#include <iostream>

#include "Player.hpp"

Train::Train(const string &name, int position, int price)
: Tile(name, position), price(price){}

int Train::getRent() const {
    if(owner == nullptr) return 0;

    int numberOfStationsOwned = 0;
    for(Train* train : owner->getTrains()) {
        if(train != nullptr) {
            numberOfStationsOwned++;
        }
    }

    switch (numberOfStationsOwned) {
        case 1: return 50;
        case 2: return 100;
        case 3: return 150;
        case 4: return 200;
        default: return 0;
    }
}

void Train::setOwner(Player *newPlayer) {
    owner = newPlayer;
}

Player* Train::getOwner() const {
    return owner;
}

int Train::getPrice() const {
    return price;
}

void Train::onLand(Player *player) {
    if(getOwner() == nullptr) {
        while (true) {
            cout << player->getName() << ", do you want to buy the " <<
                getName() << " at position " << getPosition() << " it cost : " << getPrice() << " (y/n):";

            char choice;
            cin >> choice;

            if(choice == 'y' || choice == 'Y') {
                if(player->getBalance() < this->price) {
                    cout << "you dont have enoght money" << endl;
                    break;
                }
                player->buyTrain(this);
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
