#ifndef DynArrow_hpp
#define DynArrow_hpp

#include <BaseHeader.hpp>

class DynArrow: public sf::Drawable, public sf::Transformable{
public:
    DynArrow ();
    DynArrow(float, sf::Color , sf::Vector2f , float );
    void setColor(const sf::Color& );
    void setRotation(float );
    void setPosition(sf::Vector2f);
    void setPartialColor(float );
    void minimizeArrow(float );
    float getLength();
    float getAngle();
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

private:
    sf::RectangleShape m_body,m_particle;
    sf::ConvexShape m_head;
    float m_length;
    sf::Color m_color;
    sf::Vector2f m_position;
    float m_angle;
};

#endif // Arroww_hpp