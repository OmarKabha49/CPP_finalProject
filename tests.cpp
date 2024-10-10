// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"
// #include "Game.hpp"
// #include "Player.hpp"
// #include "Street.hpp"
// #include "Train.hpp"
// #include "Utility.hpp"
// #include <SFML/Graphics.hpp>
//
//
// // Testing Game Singleton Instance Creation
// TEST_CASE("Game Singleton Instance") {
//     Game* game1 = Game::getInstance();
//     Game* game2 = Game::getInstance();
//
//     CHECK(game1 == game2);  // Ensure both pointers point to the same instance
// }
//
// // Testing Game Initialization (without player interaction)
// TEST_CASE("Game Initialization") {
//     Game* game = Game::getInstance();
//
//     game->initializeGame1();
//     std::vector<Player> players = game->getPlayers();
//
//     // Check that 3 players were created
//     CHECK(players.size() == 3);
//
//     // Check the names of the players
//     CHECK(players[0].getName() == "Player 1");
//     CHECK(players[1].getName() == "Player 2");
//     CHECK(players[2].getName() == "Player 3");
// }
//
// // Testing setupScenario1
// TEST_CASE("Game Setup Scenario 1") {
//     Game* game = Game::getInstance();
//     game->initializeGame1();
//     game->setupScenario1();
//
//     std::vector<Player> players = game->getPlayers();
//
//     // Player 1 should own the brown group
//     CHECK(players[0].getStreets().size() == 2);
//
//     // Player 2 should own the pink group
//     CHECK(players[1].getStreets().size() == 3);
//
//     // Player 3 should own the blue group
//     CHECK(players[2].getStreets().size() == 3);
//
// }
//
//
// // Testing Dice Roll (Randomization)
// TEST_CASE("Dice Roll") {
//     int minResult = 2;
//     int maxResult = 12;
//
//     for (int i = 0; i < 100; ++i) {
//         int dice1 = rand() % 6 + 1;
//         int dice2 = rand() % 6 + 1;
//         int result = dice1 + dice2;
//
//         // Ensure dice result is between 2 and 12
//         CHECK(result >= minResult);
//         CHECK(result <= maxResult);
//     }
// }
//
// TEST_CASE("Player class basic functionality") {
//     Player player("kholyo");
//
//     REQUIRE(player.getName() == "kholyo");
//     REQUIRE(player.getBalance() == 1500);
//     REQUIRE(player.getPosition() == 0);
//     REQUIRE(player.GetOutOfJailFreeCards() == 0);
//     REQUIRE(player.getStreets().empty());
//     REQUIRE(player.getTrains().empty());
//     REQUIRE(player.getUtilities().empty());
// }
//
// TEST_CASE("Player balance operations") {
//     Player player("kholyo");
//
//     player.increaseBalance(500);
//     REQUIRE(player.getBalance() == 2000);
//
//     player.decreaseBalance(300);
//     REQUIRE(player.getBalance() == 1700);
// }
//
// TEST_CASE("Player property purchase") {
//     Player player("kholyo");
//
//     Street street("Brown", 1, 60, 2, 50, 300);
//     player.buyStreet(&street);
//
//     REQUIRE(player.getStreets().size() == 1);
//     REQUIRE(player.getStreets()[0]->getPrice() == 60);
//     REQUIRE(player.getBalance() == 1440);
// }
//
// TEST_CASE("Player jail functionality") {
//     Player player("kholyo");
//
//     REQUIRE(player.isInJail() == false);
//
//     player.goToJail();
//     REQUIRE(player.isInJail() == true);
//
//     player.releaseFromJail();
//     REQUIRE(player.isInJail() == false);
// }
//
//
