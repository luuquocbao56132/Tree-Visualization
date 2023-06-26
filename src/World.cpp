#include <World.hpp>

World::World(){   
    // set the button size and character size
    sf::Vector2f buttonSize(120.f, 65.f);
    unsigned int characterSize = 30;
    
    // calculate the button positions
    sf::Vector2f position(10.f, 10.f);
    bLL = Button(position, buttonSize, "Linked\nList", ResourceManager::getFont(), characterSize-3,0);
    position.x += buttonSize.x + 10; 
    bDLL = Button(position, buttonSize, "Doubly\nLinked List", ResourceManager::getFont(), characterSize-11,0);
    position.x += buttonSize.x + 10; 
    bCLL = Button(position, buttonSize, "Circular\nLinked List", ResourceManager::getFont(), characterSize-11,0);
    position.x += buttonSize.x + 10; 
    bStack = Button(position, buttonSize, "Stack", ResourceManager::getFont(), characterSize,0);
    position.x += buttonSize.x + 10; 
    bQueue = Button(position, buttonSize, "Queue", ResourceManager::getFont(), characterSize,0);
    position.x += buttonSize.x + 10; 
    bStaArr = Button(position, buttonSize, "Static\nArray", ResourceManager::getFont(), characterSize-4,0);
    position.x += buttonSize.x + 10; 
    bDynArr = Button(position, buttonSize, "Dynamic\nArray", ResourceManager::getFont(), characterSize-4,0);
    liveData = std::make_shared <LL> ();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // // Draw the buttons
    // liveData->draw(window, sf::RenderStates::Default);
    target.draw(*liveData);
    target.draw(bLL);
    target.draw(bDLL);
    target.draw(bCLL);
    target.draw(bStack);
    target.draw(bQueue);
    target.draw(bStaArr);
    target.draw(bDynArr);
}

void World::updateTheme(){
    liveData->setTheme();
    bLL.setColor();
    bDLL.setColor();
    bCLL.setColor();
    bQueue.setColor();
    bStack.setColor();
    bStaArr.setColor();
    bDynArr.setColor();
}

void World::HoverCheck(sf::Vector2f mousePos){
    bLL.checkHover(mousePos);
    bDLL.checkHover(mousePos);
    bCLL.checkHover(mousePos);
    bDynArr.checkHover(mousePos);
    bStaArr.checkHover(mousePos);
    bStack.checkHover(mousePos);
    bQueue.checkHover(mousePos);
    liveData->checkHover(mousePos);
}

void World::checkPress(sf::Vector2f mousePos){
    liveData->checkPress(mousePos);
    if (bLL.checkPress(mousePos)){
        liveData = std::make_shared <LL> ();
        updateTheme();
    }
    if (bDLL.checkPress(mousePos)){
        liveData = std::make_shared <DLL> ();
        updateTheme();
    }
    if (bCLL.checkPress(mousePos)){
        liveData = std::make_shared <CLL> ();
        updateTheme();
    }
    if (bDynArr.checkPress(mousePos)){
        liveData = std::make_shared <DynArr> ();
        updateTheme();
    }
    if (bStaArr.checkPress(mousePos)){
        liveData = std::make_shared <StaArr> ();
        updateTheme();
    }
    if (bQueue.checkPress(mousePos)){
        liveData = std::make_shared <Queue> ();
        updateTheme();
    }
    if (bStack.checkPress(mousePos)){
        liveData = std::make_shared <Stack> ();
        updateTheme();
    }
}