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
    float getLength();
    float getAngle();
    sf::Vector2f m_target,m_home;
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

private:
    sf::RectangleShape m_body,m_particle;
    float m_length, m_angle;
};

#endif // Arroww_hpp