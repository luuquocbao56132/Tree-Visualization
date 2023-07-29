#include <World.hpp>

World::World(): menu(){   
    // set the button size and character size
    sf::Vector2f buttonSize(120.f, 65.f);
    unsigned int characterSize = 30;
    
    // calculate the button positions
    // liveData = nullptr;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // // Draw the buttons
    // liveData->draw(window, sf::RenderStates::Default);
    // if (liveData)target.draw(*liveData);
    //     else target.draw(menu);
    target.draw(menu);
}

void World::HoverCheck(sf::Vector2f mousePos){
    // if (liveData)liveData->checkHover(mousePos);
    //     else 
    menu.HoverCheck(mousePos);
}

void World::checkPress(sf::Vector2f mousePos){
    // if (liveData)liveData->checkPress(mousePos); else {
    int t = menu.checkPress(mousePos);
    // switch (t) {
    //     case 1:
    //         liveData = std::make_shared <HashTable> ();
    //         break;
    // }
    }
// }