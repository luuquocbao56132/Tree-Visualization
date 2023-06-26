#include <CircleArrow.hpp>

CircleArrow::CircleArrow(){}
//bottom position (x,400)
CircleArrow::CircleArrow(bool st):state(st){
    leftArr = DynArrow(28,sf::Color::Black,sf::Vector2f(10,250),0);
    right.setFillColor(sf::Color::Black);
    left.setFillColor(sf::Color::Black);
    right.setSize(sf::Vector2f(3.f,(400 - 250)-CircleRad-2));
    left.setSize(sf::Vector2f(3.f,(400 - 250)-CircleRad-2));

    bottom.setFillColor(sf::Color::Black);
    setPosition(sf::Vector2f(30,250), sf::Vector2f(1000, 250));
}

void CircleArrow::setPosition(sf::Vector2f l, sf::Vector2f r){
    leftArr.setPosition(sf::Vector2f(l.x-CircleRad-28,l.y));
    left.setSize(sf::Vector2f(3,400-l.y));
    left.setPosition(sf::Vector2f(l.x-CircleRad-28,l.y));

    right.setSize(sf::Vector2f(3,(400-r.y)-CircleRad-2));
    right.setPosition(sf::Vector2f(r.x,r.y+CircleRad+2));

    bottom.setSize(sf::Vector2f(r.x - l.x + CircleRad + 33, 3));
    bottom.setPosition(sf::Vector2f(l.x-CircleRad-30,400));
}

void CircleArrow::setState(bool t){state = t;}

bool CircleArrow::getState(){return state;}

void CircleArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(left); target.draw(bottom); target.draw(right);
    target.draw(leftArr);
}