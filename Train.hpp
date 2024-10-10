
#ifndef TRAIN_HPP
#define TRAIN_HPP
#include "Tile.hpp"


class Train : public Tile {
private:
    Player* owner = nullptr;
    int price;

public:
    Train(const string& name, int position, int price);

    int getRent() const;
    void setOwner(Player* newPlayer);
    Player* getOwner() const;
    int getPrice() const;
    void onLand(Player *player) override;
};



#endif //TRAIN_HPP
