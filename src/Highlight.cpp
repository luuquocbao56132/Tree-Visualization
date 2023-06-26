#include <Highlight.hpp>

Highlight::Highlight(): sizeShape(22), shapeOn(0){
    hlShape.setFillColor(sf::Color::Transparent);
    hlShape.setPosition(sf::Vector2f(1180,641));
    hlShape.setPosition(sf::Vector2f(1180,641 + sizeShape*4));
    hlShape.setSize(sf::Vector2f(470,18));
    hlShape.setOutlineThickness(2.f);
    hlShape.setOutlineColor(sf::Color::Black);
}

void Highlight::addImage(std::string urll){
    url = urll;
    hlShape.setOutlineColor(TextColor[typeTheme]);
    stepImageSprite.setScale(1.0f, 1.0f);
    stepImage.loadFromFile(url);
    stepImageSprite.setTexture(stepImage);
    sf::IntRect textureRect(0, 0, stepImage.getSize().x, stepImage.getSize().y);
    stepImageSprite.setTextureRect(textureRect);
    sf::Vector2f pos = sf::Vector2f(1100, 550);
    stepImageSprite.setPosition(pos);
}

void Highlight::setLine(int vtx){
    --vtx; line = vtx;
    hlShape.setPosition(sf::Vector2f(1180,641 + sizeShape*vtx));
}

int Highlight::getLine(){return line;}

void Highlight::setHL(bool t){shapeOn = t;}

void Highlight::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(stepImageSprite);
    if (shapeOn)target.draw(hlShape);
}