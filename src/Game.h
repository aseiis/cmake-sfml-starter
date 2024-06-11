#pragma once

#include <cstdint>
#include <iostream>
#include <format>
#include <chrono>

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    void mainLoop();
    void updateFps();
    void clean();

    uint64_t windowWidth = 1920;
    uint64_t windowHeight = 1080;
    sf::RenderWindow gameWindow;

    uint64_t fps;
    std::chrono::system_clock::time_point fpsLastTimestamp;

    // UI
    sf::Font defFont;

    sf::Text fpsLabel;

private:
    uint64_t currentFrameCount;
};