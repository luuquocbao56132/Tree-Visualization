#include <World.hpp>

World::World(): menu(), MenuState(1), themeSet(){   
    // set the button size and character size
    sf::Vector2f buttonSize(120.f, 65.f);
    unsigned int characterSize = 30;
    
    // calculate the button positions
    liveData = nullptr;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // // Draw the buttons
    // liveData->draw(window, sf::RenderStates::Default);
    target.draw(themeSet);
    if (liveData)target.draw(*liveData);
        else target.draw(menu);
}

void World::HoverCheck(sf::Vector2f mousePos){
    themeSet.HoverCheck(mousePos);
    if (liveData)liveData->checkHover(mousePos);
        else menu.HoverCheck(mousePos);
}

void World::checkPress(sf::Vector2f mousePos){
    if (themeSet.checkPress(mousePos)){
        if (liveData)liveData->setTheme();
            else menu.setTheme();
    }
    if (liveData)liveData->checkPress(mousePos); else {
    int t = menu.checkPress(mousePos);
    switch (t) {
        case 1:
            MenuState = 0;
            liveData = std::make_shared <HashTable> ();
            break;
        case 2:
            MenuState = 0;
            liveData = std::make_shared <AVL> ();
            break;
        case 3:
            MenuState = 0;
            liveData = std::make_shared <Twothree> ();
            break;
        case 4:
            MenuState = 0;
            liveData = std::make_shared <GraphMain> ();
            break;
        case 5:
            MenuState = 0;
            liveData = std::make_shared <Trie> ();
            break;
        case 6:
            MenuState = 0;
            liveData = std::make_shared <MaxHeap> ();
            break;
        case 7:
            MenuState = 0;
            liveData = std::make_shared <MinHeap> ();
            break;
    }
    }
    if (liveData)std::cout << "liveData\n";
}