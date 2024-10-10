#include "Logger.hpp"
#include "Game.hpp"

void Logger::log(const string& message) {
    Game::getInstance()->updateConsoleLog(message);
}