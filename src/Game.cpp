#include "Game.h"

Game::Game() : gameWindow(sf::VideoMode(windowWidth, windowHeight), "SFML Project")
{
    // Setting up game window
    gameWindow.setFramerateLimit(144);

    // FPS tracking variables init
    fps = 0;
    currentFrameCount = 0;
    fpsLastTimestamp = std::chrono::system_clock::now();

    // UI
    if (!defFont.loadFromFile("../assets/fonts/vera.ttf")) {
        std::cout << "ERROR: Couldn't load default font!";
    }
    fpsLabel.setFont(defFont);
    fpsLabel.setCharacterSize(12);
}

void Game::mainLoop()
{
    while (gameWindow.isOpen())
    {
        for (auto event = sf::Event{}; gameWindow.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                gameWindow.close();
            }
        }

        updateFps();

        gameWindow.clear();

        fpsLabel.setString(std::format("FPS: {}", fps));
        gameWindow.draw(fpsLabel);

        gameWindow.display();
    }
}

void Game::updateFps()
{
    std::chrono::system_clock::time_point currentTimestamp = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedSeconds = currentTimestamp - fpsLastTimestamp;
    currentFrameCount++;

    if (elapsedSeconds.count() >= 1.0f)
    {
        fps = currentFrameCount / elapsedSeconds.count();
        fpsLastTimestamp = currentTimestamp;
        currentFrameCount = 0;
    }
}