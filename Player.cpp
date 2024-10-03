#include "Player.hpp"

#include <iostream>

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
    : playerName(name), balance(1500), inJail(false), jailTurns(0), getOutOfJailFreeCards(0), position(0) ,doubleRollCount(0), housesNum(0), hotelNum(0){}

// Getters
const string& Player::getName() const { return playerName; }
int Player::getBalance() const { return balance; }
const vector<Street*>& Player::getStreets() const { return streets; }
const vector<Train*>& Player::getTrains() const { return trains; }
const vector<Utility*>& Player::getUtilities() const { return utilities; }

int Player::GetOutOfJailFreeCards() const { return getOutOfJailFreeCards; }
int Player::getPosition() const { return position; }
const CircleShape& Player::getPlayerToken() const { return playerToken; }

// Other Methods
void Player::decreaseBalance(int amount) { balance -= amount; }
void Player::increaseBalance(int amount) { balance += amount; }


void Player::payRent(int amount, Player* owner) {
    decreaseBalance(amount);
    owner->increaseBalance(amount);
}

void Player::buyStreet(Street* street) {
    if (street->getOwner() == nullptr && balance >= street->getPrice()) {
        decreaseBalance(street->getPrice());
        street->setOwner(this);
        //streets.push_back(street);

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
    position = (position + steps) % 40;
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
            cout << "You cannot build on this street yet.\n";
            return false;
        }

        if(street->buildHouse()) {
            decreaseBalance(street->getHousePrice());
            return true;
        }
        else {
            cout << "You can't build more houses on " << street->getColor() << " street.\n";
            return false;
        }
}

bool Player::canBuildHouseOnGroup(const string &color) const {
    if(!ownsAllTheStreetsInSameColor(color)) {
        cout << "You dont own all streets in the " << color << " groub. \n";
        return false;
    }
    int minHouses = 4;
    int maxHouses = 0;

    for(const auto & entry : _streets) {
        Street* street = entry.first;
        if(street->getColor() == color) {
            int numHouses = street->getHouses();
            minHouses =  min(minHouses,numHouses);
            maxHouses = max(maxHouses, numHouses);
        }
    }
    if(maxHouses - minHouses > 1) {
        cout << "You must build across all streets in the " << color << " groub. \n";
        return false;
    }
    return true;
}



int Player::getHousesNume(){
    for (const auto& street : streets) {
        housesNum += street->getHouses();
    }
    return housesNum;
}

int Player::getHotelesNum() {
    for (const auto& street : streets) {
        hotelNum += street->getHotel();
    }
    return hotelNum;
}

void Player::repairProperties(int perHouse, int perHotel) {
    for (int i = 0 ; i < hotelNum; i++) {
        decreaseBalance(perHotel);
    }
    for(int i = 0; i < housesNum; i++) {
        decreaseBalance(perHouse);
    }

    if(hotelNum > 0){Logger::log(getName() + " paid "+ to_string(perHotel)+ " " + to_string(hotelNum) + " times.");}
    if(housesNum > 0){Logger::log(getName() + " paid " +to_string(perHouse)+ " " +to_string(housesNum) + " times.");}
}

void Player::increasGetOutOfJailFreeCard() {
    getOutOfJailFreeCards++;
}

