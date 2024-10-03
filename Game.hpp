#ifndef GAME_HPP
#define GAME_HPP

#include <functional>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Board.hpp"
#include "Player.hpp"
using namespace sf;
using namespace std;
class Game {
private:
    // Singleton instance
    static Game* instance;
    // Private constructor to prevent instantiation
    Game();

    RenderWindow window;
    Sprite monopolyBoard;
    Texture monopolyTexture;
    RectangleShape textBar;
    Text inputText;
    string inputBuffer;
    vector<Text> consoleLog;
    RectangleShape consoleBar;
    const int maxConsoleLogLines = 13;
    vector<Player> players;
    int currentPlayerIndex;
    RectangleShape button;
    Text buttonText;
    Font font;
    Text diceText1;
    Text diceText2;
    Board board;
    unordered_map<string , vector<RectangleShape>> housesOnTheBoard;

    int numberOfPlayers;       // Number of players in the game
    int currentPlayerInputIndex; // Tracks which player's name is being input
    bool isWaitingForPlayerCount; // True if waiting for the number of players
    bool isWaitingForPlayerNames; // True if waiting for player names
    bool waitingForInput = false;
    bool waitingForPlayerDecision;
    bool turnPrompted;
    function<void(const string&)> inputCallback;


public:
    // Static method to access the singleton instance
    static Game* getInstance();
    void run(); // Main game loop
    void initializeGame(); // Initialize players and board
    void handleEvents(); // Handle user input
    void drawGame(); // Draw the board and players
    void movePlayer(); // Move the current player based on input
    void addButton(const string& label, float x, float y, float width, float height);
    void addDiceResult();
    void handleMousePress(Event& event);
    void handleWindowClose(Event& event);
    void handleKeyPress(Event& event);
    void handleTextInput(Event& event);
    void drawPlayerInfo();
    void drawCurrentPlayerTurn();
    void printMousePosition();
    vector<Player> getPlayers();

    // Helper functions
    void loadBoardTexture(); // Load the board image
    void loadFont();

    void handlePlayerLanding(Player* player);
    void handleBuildingHouse(Vector2i mousePosition);
    void drawHousesOnTheBoard();
    void drawPlayers();
    void setupScenario();
    void updateConsoleLog(const string& message);
    void processInput(const string& input);
    void initializeTextInputAndConsoleLog();
    void waitForInput(function<void(const string&)> callback, const string& prompt);

    void handleJailTurn(Player* player);
    void updateCurrentPlayer();
};

#endif // GAME_HPP
