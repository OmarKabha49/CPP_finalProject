

#ifndef STREET_HPP
#define STREET_HPP
#include <string>
#include "Tile.hpp"
#include "Player.hpp"
class Player;
using namespace std;
class Street : public Tile{

private:

    Player* owner = nullptr;
    int houses = 0;
    bool hotel = false;
    int price;
    int baseRent;
    int housePrice;
    int hotelPrice;

public:
    Street(const string& Color,int position, int price, int baseRent, int housePrice, int hotelPrice);

    int getRent() const;
    void setOwner(Player* newOwner);
    Player* getOwner() const;
    bool canBuildHouse(const Player* player) const;
    bool buildHouse();
    bool buildHotel();
    const string& getColor() const;
    int getPrice() const;
    int getHouses() const;
    bool getHotel() const;
    int getHousePrice() const;
    int getHotelPrice() const;

    void onLand(Player *player) override;

};



#endif //STREET_HPP
