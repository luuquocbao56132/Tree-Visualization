#ifndef DynArrow_hpp
#define DynArrow_hpp

#include <BaseHeader.hpp>

class DynArrow: public sf::Drawable, public sf::Transformable{
public:
    DynArrow ();
    DynArrow(sf::Vector2f, sf::Vector2f );
    void setColor(const sf::Color& );
    void setPartialColor(float );
    void setLength();
    void setAngle();
    void setPosition();
    void setHome(sf::Vector2f);
    void setTail(sf::Vector2f);
    void checkPositionFastHome();
    bool checkPositionHome();
    void checkPositionFastTail();
    bool checkPositionTail();
    void checkPositionFast();
    bool checkPosition();
    float getLength();
    float getAngle();
    sf::Vector2f m_tail1, m_tail2, m_home1, m_home2;
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

private:
    sf::RectangleShape m_body,m_particle;
    float m_length, m_angle;
};

#endif // Arroww_hpp