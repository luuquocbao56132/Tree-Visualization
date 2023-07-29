#include <Theme.hpp>

Theme::Theme(){
    themeBut = Button(sf::Vector2f(1700,20), sf::Vector2f(120,65),"Theme", ResourceManager::getFont(), 25, 0);
    backGroundTexture.loadFromFile("./Image/"+theme+"background.png");
    backGroundSprite.setTexture(backGroundTexture);
}

void Theme::draw(sf::RenderTarget& target, sf::RenderStates states) const{  
    target.draw(backGroundSprite);
    target.draw(themeBut);
}

void Theme::HoverCheck(sf::Vector2f mousePos){
    themeBut.checkHover(mousePos);
}

bool Theme::checkPress(sf::Vector2f mousePos){
    if (themeBut.checkPress(mousePos)){
        isThemeChange = 0;
        if (theme == ""){theme = "1"; typeTheme = 1;}
            else {theme = ""; typeTheme = 0;}
        backGroundTexture.loadFromFile("./Image/"+theme+"background.png");
        themeBut.setColor();
        return 1;
    }
    return 0;
}