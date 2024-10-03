
#include "Train.hpp"

#include <iostream>
#include "Logger.hpp"
#include "Game.hpp"
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
    if (this->owner == nullptr) {
        // Message to prompt the player
        string outPut = player->getName() + ", do you want to buy " + getName() +
                        " at position " + to_string(getPosition()) + " for $" +
                        to_string(getPrice()) + "? (y/n)";

        // Declare a lambda function to handle player's response
        function<void(const string&)> promptPlayer;

        // Define the lambda function for processing the input
        promptPlayer = [this, player, promptPlayer, outPut](const string& input) {
            Logger::log("Input received: " + input);

            char choice = tolower(input[1]);  // Handle first character of input

            if (choice == 'y') {
                if (player->getBalance() < this->price) {
                    Logger::log("You don't have enough money to buy this train.");
                } else {
                    player->buyTrain(this);
                    Logger::log(player->getName() + " bought " + getName() + " for $" + to_string(getPrice()) + ".");
                }
            } else if (choice == 'n') {
                Logger::log(player->getName() + " decided not to buy the " + getName() + ".");
            } else {
                Logger::log("Invalid input. Please enter 'y' or 'n'.");
                // Re-prompt without recursion
                Game::getInstance()->waitForInput(promptPlayer, outPut);
            }
        };

        // Prompt the player
        Game::getInstance()->waitForInput(promptPlayer, outPut);

    } else if (this->owner != player) {
        // Pay rent if the player lands on a train owned by another player
        int rent = getRent();
        player->decreaseBalance(rent);
        this->owner->increaseBalance(rent);
        Logger::log(player->getName() + " paid $" + to_string(rent) +
                    " to " + getOwner()->getName() + " as rent.");
    } else {
        // Player landed on their own train
        Logger::log(player->getName() + " landed on their own train.");
    }
}

