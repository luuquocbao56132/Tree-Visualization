#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;
bool isThemeChange = 1;

Game::Game(): mWindow(sf::VideoMode(1700,900), "Data Visualization", sf::Style::Default, sf::ContextSettings(0, 0, 16)), mWorld{}{
    mWindow.setFramerateLimit(110);
}

void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::milliseconds(8);
    mWorld.updateTheme();
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

void Game::runBreak(){
    while (mWindow.isOpen()){
        processEventsBreak();
        render(4); 
        break; 
    }
}

void Game::processEventsBreak(){
    sf::Event event;

    while (mWindow.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::processEvents(){
    sf::Event event;
    if (isThemeChange == 0) mWorld.updateTheme(), isThemeChange = 1;
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
        // std::cout << "event" << '\n';
    }
}

void Game::update(sf::Time TimePerFrame){
    
}

void Game::render(){
    mWindow.clear(sf::Color(238,238,238));
    if (!mWorld.liveData->mainGraph.listNode.empty() && mWorld.liveData->mainGraph.listNode[0]->getRad() != CircleRad){
        sf::Clock clock;
        float timeSinceLastUpdate = 0; clock.restart();
        // std::cout << "radius first: " << mWorld.liveData->mainGraph.listNode[0]->getRad() << '\n'; Sleep(3000);
        for (int stt = 2; stt <= numFrame; ++stt){
            for (int i = 0; i < mWorld.liveData->mainGraph.listNode.size(); ++i)
                mWorld.liveData->mainGraph.listNode[i]->changeSizeNode(-CircleRad / numFrame);
            if (mWorld.liveData->mainGraph.newNode)
                mWorld.liveData->mainGraph.newNode->changeSizeNode(-CircleRad / numFrame);
            // std::cout << "radius last: " << mWorld.liveData->mainGraph.listNode[0]->getRad() << '\n';
            // std::cout << "stt " << stt << "\n";
            gameGlobal->runBreak();
        }
        for (int i = 0; i < mWorld.liveData->mainGraph.listNode.size(); ++i)
            mWorld.liveData->mainGraph.listNode[i]->changeSizeNode(mWorld.liveData->mainGraph.listNode[i]->getRad() - CircleRad);
        mWorld.liveData->mainGraph.setNode();
    }
    mWindow.draw(mWorld);
    mWindow.display();
}

void Game::render(int x){
    mWindow.clear(sf::Color(238,238,238));
    mWindow.draw(mWorld);
    mWindow.display();
}