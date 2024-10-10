#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Street.hpp"
#include "Tile.hpp"
#include "Train.hpp"
#include "Utility.hpp" // Include the Utility header

using namespace sf;
using namespace std;

class Street; // Forward declaration of Street

class Player {
private:
    string playerName;
    int balance; // The player's current money balance.
    vector<Street*> streets; // Streets owned by the player.
    vector<Train*> trains;   // Trains owned by the player.
    vector<Utility*> utilities;  // Utilities owned by the player.
    bool inJail; // Flag to indicate if the player is in jail.
    int jailTurns; // Number of turns the player has been in jail
    int getOutOfJailFreeCards; // Number of "Get Out of Jail Free" cards the player has.
    int position;
    int doubleRollCount;
    int housesNum;
    int hotelsNum;
    CircleShape playerToken;
    CircleShape ownershipMarker;
    unordered_map<Street*, CircleShape> _streets;
    unordered_map<Utility*, CircleShape> _utilityies;
    unordered_map<Train*, CircleShape> _trains;
    int loanAmount;         // Amount of loan taken
    int goPassCount;        // Number of times the player has passed "Go" since taking a loan
    bool hasLoan;           // Whether the player currently has a loan


public:
    Player(string name);

    // Getters
    const string& getName() const;
    int getBalance() const;
    const vector<Street*>& getStreets() const; // Get the streets owned by the player
    const vector<Train*>& getTrains() const;   // Get the trains owned by the player
    const vector<Utility*>& getUtilities() const;  // Get the utilities owned by the player
    int GetOutOfJailFreeCards() const;
    int getPosition() const;
    const CircleShape& getPlayerToken() const;

    // Other Methods
    void setName(const string& newName);
    void decreaseBalance(int amount);
    void increaseBalance(int amount);
    void goToJail();
    bool payRent(int amount, Player* owner);
    void buyStreet(Street* street);
    void buyTrain(Train* train);
    void buyUtility(Utility* utility);
    void move(int steps);
    void setPosition(float x, float y);
    void setPlayerToken(const CircleShape& token);
    void releaseFromJail();
    void incrementTurnsInJail();
    int getTurnsInJail() const;
    bool isInJail() const;
    Vector2f getTileScreenPosition(int tilePosition) const;
    void drawOwnerships(RenderWindow& window) const;
    void removePlayerToken();

    bool buildHouse(Street* street);
    bool canBuildHouseOnGroup(const string& colorGroup) const;
    bool ownsAllTheStreetsInSameColor(const string& colorGroup) const;

    bool canBuildHotelOnGroup(Street* street) const;
    bool buildHotel(Street* street);


    void resetDoubleRollCount();
    void incrementDoubleRollCount();
    int getDoubleRollCount() const;
    bool useGetOutOfJailFreeCard();

    int getHousesNum();
    int getHotelesNum();

    void repairProperties(int perHouse, int perHotel);
    void increasGetOutOfJailFreeCard();

    void takeLoan(int amount);
    bool repayLoan();

    void passGo();  // To increment goPassCount and check loan repayment
    void transferPropertiesToPlayer(Player* newOwner);

    unordered_map<Street*, CircleShape> _getStreets();
    bool operator==(const Player* other) const {
        return this->playerName == other->playerName;
    }
    bool operator!=(const Player* other) const {
        return !(*this == other);
    }
};

#endif // PLAYER_HPP
