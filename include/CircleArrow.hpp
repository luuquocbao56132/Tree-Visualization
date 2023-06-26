#ifndef CircleArrow_hpp
#define CircleArrow_hpp

#include <BaseHeader.hpp>
#include <DynArrow.hpp>

class CircleArrow: public sf::Transformable, public sf::Drawable{
public:
    CircleArrow();
    CircleArrow(bool);
    void setState(bool);
    bool getState();
    bool state;
    void setPosition(sf::Vector2f, sf::Vector2f);
    void draw (sf::RenderTarget&, sf::RenderStates) const override;
    sf::RectangleShape right,bottom,left;
    DynArrow leftArr;
};

#endif // CircleArrow_hpp