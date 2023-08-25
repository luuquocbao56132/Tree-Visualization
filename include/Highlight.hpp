#ifndef Highlight_hpp
#define Highlight_hpp

#include <BaseHeader.hpp>

class Highlight: public sf::Transformable, public sf::Drawable{
public:
    Highlight();
    void setLine(std::string);
    sf::RectangleShape highlightShape;
    sf::Text highlightText;
    void setTheme();
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
private:
    int sizeShape, line;
    bool shapeOn;
};

#endif // Highlight_hpp