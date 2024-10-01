// #include "Property.hpp"
// #include "Player.hpp"
//
// Property::Property(const string& name, int position, int price, int baseRent)
//     : Tile(name, position), price(price), baseRent(baseRent), owner(nullptr) {}
//
// // void Property::onLand(Player* player) {
// //     if (owner && owner != player) {
// //         int rent = calculateRent();
// //         player->payRent(rent, owner);
// //     }
// // }
//
// void Property::buy(Player* player) {
//     if (!owner && player->getBalance() >= price) {
//         player->decreaseBalance(price);
//         setOwner(player);
//     }
// }
//
// int Property::calculateRent() const {
//     return baseRent;
// }
//
// Player* Property::getOwner() const {
//     return owner;
// }
//
// void Property::setOwner(Player* player) {
//     owner = player;
// }
//
// int Property::getPrice() const {return this->price;}
