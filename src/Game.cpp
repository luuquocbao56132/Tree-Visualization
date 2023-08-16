#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;
bool isThemeChange = 1;

Game::Game(): mWindow(sf::VideoMode(1900,900), "Data Visualization", sf::Style::Default, sf::ContextSettings(0, 0, 16)), mWorld(){
    mWindow.setFramerateLimit(120);
}

void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1.f/60.f);
    while (mWindow.isOpen()){
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        update(TimePerFrame);
        render();
    }
}

void Game::processEvents(){
    sf::Event event;
    while (mWindow.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow)); 
                    mWorld.checkPress(mousePos);
                } 
                break;
            case sf::Event::MouseMoved:
                sf::Vector2f mousePos = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
                mWorld.HoverCheck(mousePos);
                break;
        }
        if (event.type == sf::Event::KeyPressed){
            mWorld.liveData->checkKeyInput(event);
        }
    }
}

void Game::update(sf::Time TimePerFrame){
    if (!mWorld.MenuState){
        if (caseSpeed)mWorld.liveData->checkFunction();
            else mWorld.liveData->checkFunctionFast();
    } else mWorld.liveData = nullptr;
}

void Game::render(){
    mWindow.clear(sf::Color(238,238,238));
    mWindow.draw(mWorld);
    mWindow.display();
}