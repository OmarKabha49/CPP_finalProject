#include "Player.hpp"

#include <climits>
#include <iostream>

#include "Game.hpp"
#include "Logger.hpp"
#include "Street.hpp"
#include "Train.hpp"
#include "Utility.hpp"

// A map to track how many streets are in each color group
unordered_map<string, int> colorGroupStreetCount = {
    {"Brown", 2},    // Brown group has 2 streets
    {"LightBlue", 3}, // Light Blue group has 3 streets
    {"Pink", 3},     // Pink group has 3 streets
    {"Orange", 3},   // Orange group has 3 streets
    {"Red", 3},      // Red group has 3 streets
    {"Yellow", 3},   // Yellow group has 3 streets
    {"Green", 3},    // Green group has 3 streets
    {"DarkBlue", 2}  // Dark Blue group has 2 streets
};


Player::Player(const string name)
    : playerName(name), balance(1500), inJail(false), jailTurns(0), getOutOfJailFreeCards(0), position(0) ,doubleRollCount(0), housesNum(0), hotelsNum(0){}

// Getters
const string& Player::getName() const { return playerName; }
int Player::getBalance() const { return balance; }
const vector<Street*>& Player::getStreets() const { return streets; }
const vector<Train*>& Player::getTrains() const { return trains; }
const vector<Utility*>& Player::getUtilities() const { return utilities; }

int Player::GetOutOfJailFreeCards() const { return getOutOfJailFreeCards; }
int Player::getPosition() const { return position; }
const CircleShape& Player::getPlayerToken() const { return playerToken; }
void Player::setName(const string& newName) {
    playerName = newName;
}
void Player::removePlayerToken() {
    // Set the player's token position off-screen (or make it invisible)
    playerToken.setPosition(-100.f, -100.f);  // Off-screen to effectively "remove" it
}
unordered_map<Street *, CircleShape> Player::_getStreets() {
    return _streets;
}

// Other Methods
void Player::decreaseBalance(int amount) { balance -= amount; }
void Player::increaseBalance(int amount) { balance += amount; }


bool Player::payRent(int amount, Player* owner) {
    if (balance >= amount) {
        decreaseBalance(amount);
        owner->increaseBalance(amount);
        Logger::log(getName() + " paid rent of $" + std::to_string(amount) + " to " + owner->getName());
        return true;
    } else {
        Logger::log(getName() + " cannot pay rent of $" + std::to_string(amount) + ".");

        // Present options to the player: take a loan or lose the game
        string message = getName() + ", you cannot pay rent. Choose an option: (1) Take a loan, (2) Lose and give your properties to " + owner->getName();
        function<void(const string&)> rentOptions;

        rentOptions = [this, owner, amount](const string& input) {
            char choice = tolower(input[0]);
            if (choice == '1') {
                int loanAmount = amount;
                takeLoan(loanAmount);
                decreaseBalance(loanAmount);  // Pay whatever balance the player has
                owner->increaseBalance(loanAmount);  // Transfer to owner
                Logger::log(getName() + " took a loan and paid $" + to_string(loanAmount) + " to " + owner->getName());
            } else if (choice == '2') {
                Logger::log(getName() + " lost the game and transferred properties to " + owner->getName());
                transferPropertiesToPlayer(owner);
                // Handle game over for the player
            } else {
                Logger::log("Invalid input. Please choose again.");
                payRent(amount, owner);  // Re-prompt the player
            }
        };

        // Use waitForInput to prompt the player for their decision
        Game::getInstance()->waitForInput(rentOptions, message);
        return false;  // Rent is not fully paid yet
    }
}

void Player::buyStreet(Street* street) {
    if (street->getOwner() == nullptr && balance >= street->getPrice()) {
        decreaseBalance(street->getPrice());
        street->setOwner(this);
        streets.push_back(street);

        CircleShape ownershipMarker(5.f);
        ownershipMarker.setFillColor(getPlayerToken().getFillColor()); // Same color as player
        ownershipMarker.setPosition(getTileScreenPosition(street->getPosition()));
        this->_streets[street] = ownershipMarker;
    }
}

void Player::buyTrain(Train* train) {
    if (train->getOwner() == nullptr && balance >= train->getPrice()) {
        decreaseBalance(train->getPrice());
        train->setOwner(this);
        trains.push_back(train);

        CircleShape ownershipMarker(5.f);
        ownershipMarker.setFillColor(getPlayerToken().getFillColor()); // Same color as player
        ownershipMarker.setPosition(getTileScreenPosition(train->getPosition()));
        this->_trains[train] = ownershipMarker;
    }
}

void Player::buyUtility(Utility* utilityTile) {
    if (utilityTile->getOwner() == nullptr && balance >= utilityTile->getPrice()) {
        decreaseBalance(utilityTile->getPrice());
        utilityTile->setOwner(this);
        utilities.push_back(utilityTile);

        CircleShape ownershipMarker(5.f);
        ownershipMarker.setFillColor(getPlayerToken().getFillColor()); // Same color as player
        ownershipMarker.setPosition(getTileScreenPosition(utilityTile->getPosition()));
        this->_utilityies[utilityTile] = ownershipMarker;
    }
}

void Player::move(int steps) {
    if (isInJail()) {
        Logger::log("Player " + getName() + " is in jail and cannot move.");
        return; // No movement allowed when in jail
    }
    // Save the current position before moving
    int oldPosition = position;

    // Update the player's position
    position = (position + steps) % 40;  // There are 40 tiles on the board (index 0 to 39)

    // Log the player's movement
    Logger::log("Player " + getName() + " moved from position " + to_string(oldPosition) + " to position " + to_string(position));

    // Check if the player passed "Go" (position 0)
    if (position < oldPosition) {
        passGo();  // Player passed "Go", call passGo
    }
    Logger::log("Player " + getName() + " moved to position " + to_string(position));
}

void Player::setPosition(float x, float y) { playerToken.setPosition(x, y); }
void Player::setPlayerToken(const CircleShape& token) { playerToken = token; }

void Player::goToJail() {
    inJail = true;
    jailTurns = 0;
    doubleRollCount = 0; // Reset double roll count if they go to jail.
}

void Player::releaseFromJail() {
    inJail = false;
    jailTurns = 0;
}

void Player::incrementTurnsInJail() { jailTurns++; }
int Player::getTurnsInJail() const { return jailTurns; }
bool Player::isInJail() const { return inJail; }

void Player::resetDoubleRollCount() {
    doubleRollCount = 0;
}

void Player::incrementDoubleRollCount() {
    doubleRollCount++;
}

int Player::getDoubleRollCount() const {
    return doubleRollCount;
}

bool Player::useGetOutOfJailFreeCard() {
    if (getOutOfJailFreeCards > 0) {
        getOutOfJailFreeCards--;
        releaseFromJail();
        return true;
    }
    return false;
}

Vector2f Player::getTileScreenPosition(int tilePosition) const {
    switch (tilePosition) {
        case 1 : return Vector2f(633.f,695.f);
        case 3 : return Vector2f(532.f,695.f);
        case 5 : return Vector2f(399.f,695.f);
        case 6 : return Vector2f(331.f,695.f);
        case 8 : return Vector2f(200.f,695.f);
        case 9 : return Vector2f(135.f,695.f);

        case 11 : return Vector2f(105.f,661.f);
        case 12 : return Vector2f(105.f,595.f);
        case 13 : return Vector2f(105.f,532.f);
        case 14 : return Vector2f(105.f,465.f);
        case 15 : return Vector2f(105.f,399.f);
        case 16 : return Vector2f(105.f,355.f);
        case 18 : return Vector2f(105.f,206.f);
        case 19 : return Vector2f(105.f,138.f);

        case 21 : return Vector2f(138.f,106.f);
        case 23 : return Vector2f(269.f,106.f);
        case 24 : return Vector2f(335.f,106.f);
        case 25 : return Vector2f(399.f,106.f);
        case 26 : return Vector2f(466.f,106.f);
        case 27 : return Vector2f(531.f,106.f);
        case 28 : return Vector2f(597.f,106.f);
        case 29 : return Vector2f(663.f,106.f);

        case 31 : return Vector2f(694.f,139.f);
        case 32 : return Vector2f(694.f,207.f);
        case 34 : return Vector2f(694.f,333.f);
        case 35 : return Vector2f(694.f,400.f);
        case 37 : return Vector2f(694.f,527.f);
        case 39 : return Vector2f(694.f,660.f);

        default:
            return Vector2f(0.f,0.f);
    }

}

void Player::drawOwnerships(RenderWindow &window) const{
    // Draw street ownership markers
    for (const auto& entry : _streets) {
        window.draw(entry.second);
    }

    // Draw train ownership markers
    for (const auto& entry : _trains) {
        window.draw(entry.second);
    }

    // Draw utility ownership markers
    for (const auto& entry : _utilityies) {
        window.draw(entry.second);
    }
}

bool Player::ownsAllTheStreetsInSameColor(const string &color) const {
    int streetsInSameColor = 0;
    int totalStreetsInSameColor = colorGroupStreetCount[color];

    for (const auto& entry : _streets) {
        Street* street = entry.first;

        if (street->getColor() == color && this->getName() == street->getOwner()->getName()) {
                streetsInSameColor++;
        }
    }

    return streetsInSameColor == totalStreetsInSameColor;
}

bool Player::buildHouse(Street *street) {
    string color = street->getColor();
    if(!canBuildHouseOnGroup(color)) {
        Logger::log("You cannot build on this street yet.");
        return false;
    }

    if(street->buildHouse()) {
        if(balance >= street->getPrice()){
            decreaseBalance(street->getHousePrice());
            Logger::log(getName() + " built a house on " + street->getName() + " for $" + std::to_string(street->getHousePrice()) + ".");
            return true;
        }else {
            Logger::log("you dont have enough money to build a house.");
            return false;
        }

    } else {
        Logger::log("You can't build more houses on " + street->getColor() + " street.");
        return false;
    }
}

bool Player::canBuildHouseOnGroup(const string &color) const {
    // Ensure the player owns all the streets in the group
    if (!ownsAllTheStreetsInSameColor(color)) {
        Logger::log("You don't own all streets in the " + color + " group.");
        return false;
    }

    int minHouses = 4;  // Use INT_MAX to find the minimum
    int maxHouses = 0;

    // Loop through streets and find the min/max house counts
    for (const auto &entry : _streets) {
        Street* street = entry.first;
        if (street->getColor() == color) {
            int numHouses = street->getHouses();
            minHouses = min(minHouses, numHouses);
            maxHouses = max(maxHouses, numHouses);
        }
    }

    if(maxHouses - minHouses > 0) {
        if(maxHouses == 1 && minHouses == 0){return true;}
        if(maxHouses == 2 && minHouses == 1){return true;}
        if(maxHouses == 3 && minHouses == 2){return true;}
        if(maxHouses == 4 && minHouses == 3){return true;}
        Logger::log("You must build evenly across all streets in the " + color + " group.");
        return false;
    }
    return true;
}

int Player::getHousesNum(){
    for (const auto& street : streets) {
        housesNum += street->getHouses();
    }
    return housesNum;
}

int Player::getHotelesNum() {
    for (const auto& street : streets) {
        hotelsNum += street->getHotel();
    }
    return hotelsNum;
}

void Player::repairProperties(int perHouse, int perHotel) {
    for (int i = 0 ; i < hotelsNum; i++) {
        decreaseBalance(perHotel);
    }
    for(int i = 0; i < housesNum; i++) {
        decreaseBalance(perHouse);
    }

    if(hotelsNum > 0){Logger::log(getName() + " paid "+ to_string(perHotel)+ " " + to_string(hotelsNum) + " times.");}
    if(housesNum > 0){Logger::log(getName() + " paid " +to_string(perHouse)+ " " +to_string(housesNum) + " times.");}
}

void Player::increasGetOutOfJailFreeCard() {
    getOutOfJailFreeCards++;
}

bool Player::buildHotel(Street* street) {
    if (street->getHouses() == 4 && !street->getHotel()) {  // Only allow building a hotel if there are 4 houses
        decreaseBalance(street->getHotelPrice());  // Deduct the hotel price from the player's balance
        street->buildHotel();  // Update the street's status to have a hotel
        Logger::log(getName() + " built a hotel on " + street->getName() + ".");
        return true;
    }
    else if(street->getHotel()) {
        Logger::log("you can build only one Hotel at "+ street->getName());
        return false;
    }
    else{
        Logger::log("You need 4 houses on " + street->getName() + " to build a hotel.");
        return false;
    }
}

bool Player::canBuildHotelOnGroup(Street* street) const {
    string color = street->getColor();

    // Ensure the player owns all streets in the color group
    if (!ownsAllTheStreetsInSameColor(color)) {
        Logger::log("You don't own all streets in the " + color + " group.");
        return false;
    }

    // Ensure each street in the color group has exactly 4 houses
    for (const auto& entry : _streets) {
        Street* s = entry.first;
        if (s->getColor() == color && s->getHouses() < 4) {
            Logger::log("All streets in the " + color + " group must have 4 houses before building a hotel.");
            return false;
        }
    }

    return true;  // If all streets in the group have 4 houses, the player can build a hotel
}

void Player::takeLoan(int amount) {
    loanAmount = amount;
    hasLoan = true;
    goPassCount = 0;
    increaseBalance(amount);  // Give the player the loan amount
    Logger::log(getName() + " took a loan of $" + to_string(amount) + " from the bank.");
}

bool Player::repayLoan() {
    if (balance >= loanAmount) {
        decreaseBalance(loanAmount);
        hasLoan = false;
        loanAmount = 0;
        goPassCount = 0;
        Logger::log(getName() + " repaid the loan.");
        return true;
    }
    return false;
}

void Player::passGo() {
    if (hasLoan) {
        goPassCount++;
        if (goPassCount >= 3) {
            Logger::log(getName() + " has passed Go three times and must repay the loan.");
            if (!repayLoan()) {
                Logger::log(getName() + " couldn't repay the loan and is bankrupt.");
                if(!_streets.empty()){_streets.clear();}
                if(!_utilityies.empty()){_utilityies.clear();}
                if(!_trains.empty()){_trains.clear();}
            }
        }
    }
}



void Player::transferPropertiesToPlayer(Player* newOwner) {
    for (auto& streetEntry : _streets) {
        Street* street = streetEntry.first;

        for(auto shape : Game::getInstance()->getHousesOnTheBoard()[street->getOwner()->getName()]) {
            shape.setFillColor(newOwner->getPlayerToken().getFillColor());
            Game::getInstance()->getHousesOnTheBoard()[newOwner->getName()].push_back(shape);
        }

        for(auto shape : Game::getInstance()->getHotelsOnTheBoard()[street->getOwner()->getName()]) {
            shape.setFillColor(newOwner->getPlayerToken().getFillColor());
            Game::getInstance()->getHotelsOnTheBoard()[newOwner->getName()].push_back(shape);
        }
        street->setOwner(newOwner);

        CircleShape ownershipMarker(5.f);
        ownershipMarker.setFillColor(newOwner->getPlayerToken().getFillColor()); // Same color as player
        ownershipMarker.setPosition(getTileScreenPosition(street->getPosition()));
        newOwner->_streets[street] = ownershipMarker;

        Logger::log(newOwner->getName() + " now owns " + street->getName() + " with " + to_string(street->getHouses()) + " houses.");

    }
    _streets.clear();  // Remove all properties from the player

    // Transfer Trains
    for (auto& trainEntry : _trains) {
        Train* train = trainEntry.first;
        train->setOwner(newOwner);

        // Create a new ownership marker for the new owner
        CircleShape ownershipMarker(5.f);
        ownershipMarker.setFillColor(newOwner->getPlayerToken().getFillColor()); // Same color as player token
        ownershipMarker.setPosition(getTileScreenPosition(train->getPosition()));

        // Add the train to the new owner's train list with the new marker
        newOwner->_trains[train] = ownershipMarker;
    }
    _trains.clear();  // Remove all trains from the current player

    // Transfer Utilities
    for (auto& utilityEntry : _utilityies) {
        Utility* utility = utilityEntry.first;
        utility->setOwner(newOwner);

        // Create a new ownership marker for the new owner
        CircleShape ownershipMarker(5.f);
        ownershipMarker.setFillColor(newOwner->getPlayerToken().getFillColor()); // Same color as player token
        ownershipMarker.setPosition(getTileScreenPosition(utility->getPosition()));

        // Add the utility to the new owner's utility list with the new marker
        newOwner->_utilityies[utility] = ownershipMarker;
    }
    _utilityies.clear();  // Remove all utilities from the current player

    Logger::log(newOwner->getName() + " acquired all properties from " + getName());
    // removePlayerToken();
    Game::getInstance()->removePlayer(this);
}
