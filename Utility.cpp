#include "Utility.hpp"
#include "Player.hpp"
#include "Logger.hpp"
#include "Game.hpp"

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
    if (this->owner == nullptr) {
        string outPut = player->getName() + ", do you want to buy the " + getName() +
                        " utility at position " + to_string(getPosition()) + " for $" +
                        to_string(getPrice()) + "? (y/n)";

        // Declare a lambda function to handle the player's response
        function<void(const string&)> promptPlayer;

        // Define the lambda function
        promptPlayer = [this, player, promptPlayer, outPut](const string& input) {
            Logger::log("Input received: " + input);

            char choice = tolower(input[1]);  // Handle first character of input

            if (choice == 'y') {
                if (player->getBalance() < this->price) {
                    Logger::log("You don't have enough money to buy this utility.");
                } else {
                    player->buyUtility(this);
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
        int rent = getRent(getDiceRoll());  // Calculate rent based on dice roll
        player->decreaseBalance(rent);
        this->owner->increaseBalance(rent);
        Logger::log(player->getName() + " paid $" + to_string(rent) +
                    " to " + getOwner()->getName() + " as rent.");
    } else {
        // Player landed on their own utility
        Logger::log(player->getName() + " landed on their own utility.");
    }
}


void Utility::setDiceRoll(int diceRollResult) {
    diceRoll = diceRollResult;
}

int Utility::getDiceRoll() const {
    return diceRoll;
}
