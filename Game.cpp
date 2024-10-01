#include "Game.hpp"
#include <iostream>
#include <limits>

#include "SpecialTile.hpp"


int dice1Result = 0;
int dice2Result = 0;
int numberOfClicksOnButton = 0 ;// each player can roll dice once

// Constructor without initializing the window
Game::Game() : currentPlayerIndex(0), numberOfPlayers(0), currentPlayerInputIndex(0),
               isWaitingForPlayerCount(true), isWaitingForPlayerNames(false) {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
    loadBoardTexture();  // Load board texture
    loadFont();          // Load fonts

    window.create(VideoMode(1500, 1000), "MONOPOLY");
    window.setFramerateLimit(60);  // Limit frame rate

    addButton("Roll Dice", 800, 0, 100, 50);  // Add the test button
    addDiceResult();                          // Add dice text fields
    initializeTextInputAndConsoleLog();       // Initialize text input and console log areas
}

void Game::run() {
    bool playerCountPrompted = false;  // To prevent infinite prompting

    while (window.isOpen()) {
        handleEvents();  // Handle input events (e.g., typing, mouse clicks)

        // Process the game input logic, but only show the input prompt once
        if (!playerCountPrompted && isWaitingForPlayerCount) {
            updateConsoleLog("Enter the number of players (2 to 8):");
            playerCountPrompted = true;  // Ensure this message is only displayed once
        }

        // Only call initializeGame when there's new input to process
        if (!inputBuffer.empty()) {
            initializeGame();
        }

        drawGame();  // Draw the game state in every frame
    }
}
void Game::setupScenario() {
    // Create 3 players
    Player& player1 = players[0];
    Player& player2 = players[1];
    Player& player3 = players[2];

    // Assign brown streets to player 1
    Street* brown1 = dynamic_cast<Street*>(board.getTile(1)); // Mediterranean Avenue
    Street* brown2 = dynamic_cast<Street*>(board.getTile(3)); // Baltic Avenue
    if (brown1 && brown2) {
        player1.buyStreet(brown1);
        player1.buyStreet(brown2);
    }

    // Assign pink streets to player 2
    Street* pink1 = dynamic_cast<Street*>(board.getTile(11)); // St. Charles Place
    Street* pink2 = dynamic_cast<Street*>(board.getTile(13)); // States Avenue
    Street* pink3 = dynamic_cast<Street*>(board.getTile(14)); // Virginia Avenue
    if (pink1 && pink2 && pink3) {
        player2.buyStreet(pink1);
        player2.buyStreet(pink2);
        player2.buyStreet(pink3);
    }

    // Assign light blue streets to player 3
    Street* blue1 = dynamic_cast<Street*>(board.getTile(6));  // Oriental Avenue
    Street* blue2 = dynamic_cast<Street*>(board.getTile(8));  // Vermont Avenue
    Street* blue3 = dynamic_cast<Street*>(board.getTile(9));  // Connecticut Avenue
    if (blue1 && blue2 && blue3) {
        player3.buyStreet(blue1);
        player3.buyStreet(blue2);
        player3.buyStreet(blue3);
    }

    // Log the scenario setup
    cout << player1.getName() << " owns the brown group." << endl;
    cout << player2.getName() << " owns the pink group." << endl;
    cout << player3.getName() << " owns the blue group." << endl;
}

// This is a modified initializeGame() method
// void Game::initializeGame() {
//     // Set up the game with 3 players and predefined names
//     vector<string> playerNames = {"Player 1", "Player 2", "Player 3"};
//     vector<Color> colors = {Color::Red, Color::Green, Color::Blue};
//
//     for (int i = 0; i < playerNames.size(); ++i) {
//         string playerName = playerNames[i];
//
//         // Initialize Player object
//         Player player(playerName);
//
//         // Set player's graphical token
//         CircleShape token(10.f);
//         token.setFillColor(colors[i % colors.size()]); // Assign unique color
//         token.setPosition(750.f, 750.f); // Starting position for all players
//         player.setPlayerToken(token);
//
//         players.push_back(player);
//     }
// }

void Game::initializeGame() {

    // If we're still waiting for the number of players
    if (isWaitingForPlayerCount) {
        // Only prompt once for the number of players
        if (inputBuffer.empty()) {
            updateConsoleLog("Enter the number of players (2 to 8):");
        } else {
            try {
                numberOfPlayers = stoi(inputBuffer);  // Convert inputBuffer to an integer

                if (numberOfPlayers >= 2 && numberOfPlayers <= 8) {
                    updateConsoleLog("Number of players: " + to_string(numberOfPlayers));
                    isWaitingForPlayerCount = false;  // Move to the next phase (player name input)
                    isWaitingForPlayerNames = true;   // Now waiting for player names
                    inputBuffer.clear();  // Clear the buffer for the next input
                } else {
                    updateConsoleLog("Invalid number of players. Please enter a number between 2 and 8.");
                    inputBuffer.clear();  // Clear the buffer for new input
                }
            } catch (...) {
                updateConsoleLog("Invalid input. Please enter a valid number.");
                inputBuffer.clear();  // Clear the buffer for new input
            }
        }
    }

    // If we are now waiting for player names
    if (isWaitingForPlayerNames) {
        vector<Color> colors = {Color::Red, Color::Green, Color::Blue, Color::Yellow,
                                Color::Magenta, Color::Cyan, Color(255, 69, 0), Color::Black};

        // Ask for player names one by one
        if (currentPlayerInputIndex < numberOfPlayers) {
            // Only prompt once for each player's name
            if (inputBuffer.empty()) {
                updateConsoleLog("Enter name for Player " + to_string(currentPlayerInputIndex + 1) + ":");
            } else {
                string playerName = inputBuffer;

                // Initialize Player object
                Player player(playerName);

                // Set player's graphical token
                float offset = currentPlayerInputIndex * 15;
                CircleShape token(10.f);
                token.setFillColor(colors[currentPlayerInputIndex % colors.size()]);  // Assign unique color
                token.setPosition(700.f + offset, 700.f);  // Starting position for all players
                player.setPlayerToken(token);

                players.push_back(player);  // Add the player to the players vector
                updateConsoleLog("Player " + to_string(currentPlayerInputIndex + 1) + " named " + playerName + " added.");

                currentPlayerInputIndex++;  // Move to the next player
                inputBuffer.clear();  // Clear the buffer for the next input
            }
        }

        if (currentPlayerInputIndex == numberOfPlayers) {
            updateConsoleLog("All players added. Starting the game!");
            isWaitingForPlayerNames = false;  // No longer waiting for player names
        }
    }
}

void Game::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        handleWindowClose(event);
        handleKeyPress(event);
        handleMousePress(event);
        handleTextInput(event);
    }
}

void Game::drawGame() {
    // Clear window
    window.clear(Color::White);

    // Draw board
    window.draw(monopolyBoard);

    // Draw players
    drawPlayers();

    // Draw houses
    drawHousesOnTheBoard();

    // Draw UI elements
    window.draw(button);
    window.draw(buttonText);

    window.draw(diceText1);
    window.draw(diceText2);

    if(!players.empty()) {
        drawPlayerInfo();
        drawCurrentPlayerTurn();
    }
    // Draw text input bar and input text
    window.draw(textBar);
    window.draw(inputText);

    // Draw console log
    window.draw(consoleBar);
    for (const auto& logEntry : consoleLog) {
        window.draw(logEntry);
    }

    // Display window
    window.display();
}


void Game::drawHousesOnTheBoard() {
    for(const auto& entry : housesOnTheBoard ) {
        for (const auto& house : entry.second) {
            window.draw(house);
        }
    }
}

void Game::drawPlayers() {
    // Draw players
    for (const auto& player : players) {
        window.draw(player.getPlayerToken());
        player.drawOwnerships(window);
    }
}

void Game::addButton(const string& label, float x, float y, float width, float height) {
    // Create the button shape
    button.setSize(Vector2f(width, height));
    button.setFillColor(Color::Black);
    button.setPosition(x, y);

    // Create the button text
    buttonText.setFont(font);
    buttonText.setString(label);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(Color::White);
    // Center the text on the button
    FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    buttonText.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Game::movePlayer() {
    Vector2i mousePosition = Mouse::getPosition(window);
    players[currentPlayerIndex].setPosition(
        (mousePosition.x - players[currentPlayerIndex].getPlayerToken().getRadius()),
        (mousePosition.y - players[currentPlayerIndex].getPlayerToken().getRadius())
    );
}

void Game::loadBoardTexture() {
    if (!monopolyTexture.loadFromFile("monopoly.jpg")) {
        cerr << "Error loading the Monopoly board image." << endl;
        return;
    }
    monopolyBoard.setTexture(monopolyTexture);
}

void Game::loadFont() {
    // Load the font for button text
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Error loading font." << endl;
    }
}

void Game::addDiceResult() {
    // Initialize the text for the dice results
    diceText1.setFont(font);
    diceText1.setCharacterSize(20);
    diceText1.setFillColor(Color::Black);
    diceText1.setPosition(800, 60); // Position below the button

    diceText2.setFont(font);
    diceText2.setCharacterSize(20);
    diceText2.setFillColor(Color::Black);
    diceText2.setPosition(800, 90); // Position below the first dice text
}

void Game::handleWindowClose(Event& event) {
    if (event.type == Event::Closed) {
        window.close();
    }
}

void Game::handleKeyPress(Event& event) {
    FloatRect monopolyBounds(0.f,0.f,800.f,800.f);
    Vector2i mousePosition = Mouse::getPosition(window);
    if (event.type == Event::KeyPressed &&
        monopolyBounds.contains(static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y))) {
        if (event.key.code == Keyboard::Enter) {
            handlePlayerLanding(&players[currentPlayerIndex]);
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            dice1Result = 0;
            dice2Result = 0;
            numberOfClicksOnButton = 0;
        }
        else if (event.key.code == Keyboard::Space) {
            cout << players[currentPlayerIndex].getName() << " ," << players[currentPlayerIndex].getPosition() << endl;
        }
        // Build a house with 'B'
        else if (event.key.code == Keyboard::B) {
            Vector2i mousePosition = Mouse::getPosition(window);
            handleBuildingHouse(mousePosition);
        }
    }
}

void Game::handleMousePress(Event& event) {
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2i mousePosition = Mouse::getPosition(window);
//        printMousePosition();

        FloatRect monopolyBounds(0.f,0.f,800.f,800.f);
        if (numberOfClicksOnButton == 0 && button.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            numberOfClicksOnButton += 1;
            // Button clicked
            cout << "Button clicked!" << endl;
            int dice1 = rand() % 6 + 1;
            int dice2 = rand() % 6 + 1;

            dice1Result += dice1;
            dice2Result += dice2;
            diceText1.setString("Dice 1: " + to_string(dice1));
            diceText2.setString("Dice 2: " + to_string(dice2));

            players[currentPlayerIndex].move(dice1Result + dice2Result);

        } else if (monopolyBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) ){
            // Move the current player
            movePlayer();
        }
    }
    else if(event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {

    }
}

void Game::drawPlayerInfo() {
    float baseYPosition = 820.f; // Starting Y position for player names and tokens
    float xOffset = 30.f;        // Starting X position for the first column
    float xOffsetRight = 420.f;  // X position for the second column
    float tokenSize = 20.f;
    float textYOffset = 5.f;
    int playersPerColumn = 4;    // Maximum number of players before switching to second column

    for (size_t i = 0; i < players.size(); ++i) {
        // Determine if we should switch to the second column
        float currentXOffset = (i < playersPerColumn) ? xOffset : xOffsetRight;
        float currentYPosition = baseYPosition + (i % playersPerColumn) * (tokenSize + 20.f);

        // Draw player token (a small circle)
        CircleShape playerToken(tokenSize / 2);
        playerToken.setFillColor(players[i].getPlayerToken().getFillColor());
        playerToken.setPosition(currentXOffset, currentYPosition);
        window.draw(playerToken);


        string playerInfo = players[i].getName() +
                    " | Score: " + to_string(players[i].getBalance()) +
                    " | Position: " + to_string(players[i].getPosition());

        // Draw player name
        Text playerNameText;
        playerNameText.setFont(font);
        playerNameText.setString(playerInfo);
        playerNameText.setCharacterSize(20);
        playerNameText.setFillColor(Color::Black);
        playerNameText.setPosition(currentXOffset + tokenSize + 10.f, currentYPosition + textYOffset);
        window.draw(playerNameText);
    }

}

void Game::drawCurrentPlayerTurn() {
    float rightXPosition = 800.f; // Position on the right side of the board
    float topYPosition = 200.f;    // Adjust this value to your preference

    // Draw the current player's token
    CircleShape currentPlayerToken(10.f);
    currentPlayerToken.setFillColor(players[currentPlayerIndex].getPlayerToken().getFillColor());
    currentPlayerToken.setPosition(rightXPosition, topYPosition);
    window.draw(currentPlayerToken);

    // Draw the current player's name
    Text currentPlayerNameText;
    currentPlayerNameText.setFont(font);
    currentPlayerNameText.setString("Current Turn: " + players[currentPlayerIndex].getName());
    currentPlayerNameText.setCharacterSize(15);
    currentPlayerNameText.setFillColor(Color::Black);
    currentPlayerNameText.setPosition(rightXPosition, topYPosition + 20.f);
    window.draw(currentPlayerNameText);
}

void Game::handlePlayerLanding(Player *player) {
    Tile* currTile = board.getTile(player->getPosition());


    if(dynamic_cast<Street*>(currTile)){
        currTile->onLand(player);
    }
    else if(dynamic_cast<Train*>(currTile)) {
        currTile->onLand(player);
    }
    else if(Utility* utilityTile = dynamic_cast<Utility*>(currTile)) {
        utilityTile->setDiceRoll(dice1Result + dice2Result);
        utilityTile->onLand(player);
    }
    else if(dynamic_cast<SpecialTile*>(currTile)) {
        currTile->onLand(player);
    }
}

void Game::printMousePosition() {
    // Get the mouse position relative to the window
    Vector2i mousePosition = Mouse::getPosition(window);

    // Get the board's position and size (assuming board is centered in the window)
    FloatRect boardBounds = monopolyBoard.getGlobalBounds();

    // Check if the mouse is within the board's boundaries
    if (boardBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        // Mouse is on the board, print its position
        cout << "X=" << mousePosition.x << " Y=" << mousePosition.y << endl;
    }
}

void Game::handleBuildingHouse(Vector2i mousePosition) {
    int position;
    cout << "choose the street position : ";
    cin >> position;
    Tile* tile = board.getTile(position);
    if(dynamic_cast<Street*>(tile)) {
        Street* street = dynamic_cast<Street*>(tile);
        Player currPlayer = players[currentPlayerIndex];
        if(currPlayer.buildHouse(street)) {
            // Convert mouse position to the window coordinates
            Vector2f mousePositionFloat(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

            // Create a small square to represent the house
            RectangleShape houseShape(Vector2f(10.f, 10.f)); // 15x15 square
            houseShape.setFillColor(players[currentPlayerIndex].getPlayerToken().getFillColor()); // Use the player's token color
            houseShape.setPosition(mousePositionFloat);

            housesOnTheBoard[players[currentPlayerIndex].getName()].push_back(houseShape);


            // Output the action for confirmation
            cout << "House built at (" << mousePositionFloat.x << ", " << mousePositionFloat.y << ") by " << players[currentPlayerIndex].getName() << endl;
        }

    }
}

void Game::initializeTextInputAndConsoleLog() {
    // Initialize text input bar
    textBar.setSize(Vector2f(600, 50));  // Adjust size
    textBar.setFillColor(Color::Black);
    textBar.setPosition(850, 850);  // Place below the game board

    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(Color::White);
    inputText.setPosition(860, 860);  // Inside the textBar

    // Initialize console log area
    consoleBar.setSize(Vector2f(600, 300));  // Adjust width and height
    consoleBar.setFillColor(Color(100, 100, 100));  // Dark gray for console background
    consoleBar.setPosition(850, 500);  // Placed at the side of the board
}

void Game::handleTextInput(Event &event) {
    static string tempInputBuffer = "";  // Persisted across calls, not reset each time
    bool isTextEntered = false;

    FloatRect textBarBounds = textBar.getGlobalBounds();
    Vector2i mousePosition = Mouse::getPosition(window);

    // Handle text input for the text bar
    if (event.type == Event::TextEntered &&
        textBarBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {

        if (event.text.unicode == '\b' && !tempInputBuffer.empty()) {
            // Handle backspace
            tempInputBuffer.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
            // Append normal text
            tempInputBuffer += static_cast<char>(event.text.unicode);
        }
        // Update the displayed text with the current input buffer
        inputText.setString(tempInputBuffer);
        }

    // Handle the Enter key to process the input
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter
        && textBarBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
        isTextEntered = true;
        }

    // Once Enter is pressed, process the input
    if (isTextEntered) {
        inputBuffer = tempInputBuffer;  // Move the accumulated buffer into inputBuffer
        processInput(inputBuffer);  // Process the input
        tempInputBuffer.clear();  // Clear the temporary buffer for the next input
        inputText.setString("");  // Clear the displayed text
    }
}


void Game::updateConsoleLog(const string &message) {
    // If the number of log messages exceeds the limit, remove the first (oldest) entry
    if (consoleLog.size() >= maxConsoleLogLines) {
        // Remove the first (oldest) log entry
        consoleLog.erase(consoleLog.begin());

        // Shift all remaining entries upwards
        for (size_t i = 0; i < consoleLog.size(); ++i) {
            consoleLog[i].setPosition(860, 510 + i * 22);  // Adjust y-position for each log entry
        }
    }

    // Create a new log entry
    Text logEntry;
    logEntry.setFont(font);  // Assuming 'font' is loaded
    logEntry.setCharacterSize(20);
    logEntry.setFillColor(Color::White);
    logEntry.setString(message);

    // Set the position of the new log entry based on the number of existing entries
    logEntry.setPosition(860, 510 + consoleLog.size() * 22);  // Adjust y-position per message

    // Add the new log entry to the consoleLog
    consoleLog.push_back(logEntry);
}


void Game::processInput(const string &input) {
    if (waitingForInput && inputCallback) {
        inputCallback(input);
        waitingForInput = false;
    } else {
        updateConsoleLog(input);  // Normal console input processing
    }
}

void Game::waitForInput(function<void(const string &)> callback) {
    waitingForInput = true;
    inputCallback = callback;
}
