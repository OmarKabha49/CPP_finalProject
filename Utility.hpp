#ifndef X_HPP
#define X_HPP

#include "Tile.hpp"

using namespace std;

class Utility  : public Tile{
private:
    Player* owner = nullptr;
    int price;
    int diceRoll;

public:
    Utility(const string& name, int postion,int price);

    int getRent(int diceRoll) const;
    Player* getOwner() const;
    int getPrice() const;
    void setOwner(Player* newPlayer);
    void onLand(Player *player) override;
    void setDiceRoll(int diceRollResult);
    int getDiceRoll() const;
};



#endif //X_HPP
