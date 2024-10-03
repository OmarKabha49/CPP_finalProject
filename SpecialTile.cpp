#include "SpecialTile.hpp"

#include "Game.hpp"
#include "Player.hpp"
#include "Logger.hpp" // Include Logger to use logging functionality

SpecialTile::SpecialTile(const std::string& name, int position, SpecialType type)
    : Tile(name, position), type(type) {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
}

void SpecialTile::onLand(Player* player) {

    switch (type) {
        case SpecialType::GO:
            player->increaseBalance(200); // Passing Go
            Logger::log(player->getName() + " passed GO and received $200.");
            break;

        case SpecialType::JAIL:
            player->goToJail();
            Logger::log(player->getName() + " is sent to jail.");
            break;

        case SpecialType::GO_TO_JAIL:
            player->move(10); // Move to Jail directly
            player->goToJail();
            Logger::log(player->getName() + " landed on 'Go to Jail' and is sent to jail.");
            break;

        case SpecialType::INCOME_TAX:
            player->decreaseBalance(200); // Pay Income Tax
            Logger::log(player->getName() + " paid $200 in Income Tax.");
            break;

        case SpecialType::LUXURY_TAX:
            player->decreaseBalance(100); // Pay Luxury Tax
            Logger::log(player->getName() + " paid $100 in Luxury Tax.");
            break;

         case SpecialType::CHANCE: {
            // Draw a random chance card
            int card = rand() % 16; // Random number between 0 and 15
            Logger::log(player->getName() + " drew a Chance card!");

            switch (card) {
                case 0:
                    player->move(0); // Advance to Go
                    player->increaseBalance(200);
                    Logger::log("Advance to Go (Collect $200)");
                    Game::getInstance()->updateCurrentPlayer();
                    break;

                case 1:
                    player->increaseBalance(50);
                    Logger::log("Bank pays you dividend of $50");
                    break;

                case 2:
                    player->move(player->getPosition() - 3); // Go back 3 spaces
                    Logger::log("Go back 3 spaces");
                    Game::getInstance()->updateCurrentPlayer();
                    break;

                case 3:
                    player->move(10); // Go directly to Jail
                    player->goToJail();
                    Logger::log("Go directly to Jail – do not pass Go, do not collect $200");
                    Game::getInstance()->updateCurrentPlayer();
                    break;

                case 4:
                    Logger::log("Make general repairs on all your property – For each house pay $25 – For each hotel $100");
                    player->repairProperties(25,100);
                    break;

                case 5:
                    player->decreaseBalance(15);
                    Logger::log("Pay poor tax of $15");
                    break;

                case 6:
                    player->move(5); // Move to Reading Railroad
                    if (player->getPosition() > 5) player->increaseBalance(200); // Passing Go
                    Logger::log("Take a trip to Reading Railroad – If you pass Go collect $200");
                    Game::getInstance()->updateCurrentPlayer();
                    break;

                case 7:
                    player->move(39); // Move to Boardwalk
                    Logger::log("Take a walk on the Boardwalk , Advance token to Boardwalk");
                    Game::getInstance()->updateCurrentPlayer();
                    break;

                case 8:
                    // Pay each player $50
                    Logger::log("You have been elected Chairman of the Board , Pay each player $50");
                    for (Player& otherPlayer : Game::getInstance()->getPlayers()) {
                        if (&otherPlayer != player) {
                            player->decreaseBalance(50);
                            otherPlayer.increaseBalance(50);
                        }
                    }
                    break;

                case 9:
                    player->increaseBalance(150);
                    Logger::log("Your building loan matures , Collect $150");
                    break;

                case 10:
                    player->increasGetOutOfJailFreeCard();
                    Logger::log("Get out of Jail Free , This card may be kept until needed or traded");
                    break;

                case 11:
                    player->move(24); // Move to Illinois Ave
                    if (player->getPosition() > 24) player->increaseBalance(200); // Passing Go
                    Logger::log("Advance to Illinois Ave. – If you pass Go, collect $200");
                    Game::getInstance()->updateCurrentPlayer();
                    break;

                case 12:
                    player->move(11); // Move to St. Charles Place
                    if (player->getPosition() > 11 ) player->increaseBalance(200); // Passing Go
                    Logger::log("Advance to St. Charles Place – If you pass Go, collect $200");
                    break;

                case 13:
                    Logger::log("You are assessed for street repairs – $40 per house, $115 per hotel");
                    player->repairProperties(40, 115);
                    break;

                case 14: {
                    // Move to nearest Utility
                    int nearestUtility = (player->getPosition() >= 12 && player->getPosition() < 28) ? 28 : 12;
                    player->move(nearestUtility);
                    Logger::log("Advance to nearest Utility");
                    Game::getInstance()->updateCurrentPlayer();
                    break;
                }

                case 15: {
                    // Move to nearest Railroad
                    int nearestRailroad = (player->getPosition() >= 35 || player->getPosition() < 5) ? 5 :
                        (player->getPosition() < 15) ? 15 :
                        (player->getPosition() < 25) ? 25 : 35;
                    player->move(nearestRailroad);
                    Logger::log("Advance to nearest Railroad");
                    Game::getInstance()->updateCurrentPlayer();
                    break;
                }

                default:
                    break;
            }
        }
        break;


        default:
            break;
    }
}
