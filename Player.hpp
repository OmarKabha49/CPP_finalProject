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
    int turnsInJail; // Number of turns the player has been in jail
    int getOutOfJailFreeCards; // Number of "Get Out of Jail Free" cards the player has.
    int position;
    CircleShape playerToken;
    unordered_map<Street*, CircleShape> _streets;
    unordered_map<Utility*, CircleShape> _utilityies;
    unordered_map<Train*, CircleShape> _trains;

public:
    Player(const string name);

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
    void decreaseBalance(int amount);
    void increaseBalance(int amount);
    void goToJail();
    void payRent(int amount, Player* owner);
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

    bool buildHouse(Street* street);
    bool canBuildHouseOnGroup(const string& colorGroup) const;
    bool ownsAllTheStreetsInSameColor(const string& colorGroup) const;

    bool operator==(Player& other) const {
        return this->playerName == other.playerName;
    }
    bool operator!=(Player& other) const {
        return !(*this == other);
    }
};

#endif // PLAYER_HPP
