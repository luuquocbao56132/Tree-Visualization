#include <Highlight.hpp>

Highlight::Highlight(){
    highlightShape.setPosition(sf::Vector2f(1100,720));
    highlightShape.setSize(sf::Vector2f(700,40));
    highlightShape.setOutlineThickness(2.f);
    highlightShape.setOutlineColor(sf::Color::Black);

    highlightText = sf::Text("", ResourceManager::getFont(), 22);
    highlightText.setFillColor(sf::Color::Black);
    highlightText.setPosition(sf::Vector2f(1105,720));
    setTheme();
}

void Highlight::setLine(std::string x){
    highlightText.setString(x);
}

void Highlight::setTheme(){
    highlightShape.setFillColor(ButtonColor[typeTheme]);
    highlightShape.setOutlineColor(ButtonColor[typeTheme]);
    highlightText.setFillColor(TextColor[typeTheme]);
}

void Highlight::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(highlightShape, states);
    target.draw(highlightText, states);
}