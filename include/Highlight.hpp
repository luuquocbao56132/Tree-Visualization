#ifndef Highlight_hpp
#define Highlight_hpp

#include <BaseHeader.hpp>

class Highlight: public sf::Transformable, public sf::Drawable{
public:
    Highlight();
    void addImage(std::string);
    void setLine(int);
    int getLine();
    void setHL(bool);
    sf::RectangleShape hlShape;
    sf::Texture stepImage;
    sf::Sprite stepImageSprite;
    std::string url;
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
private:
    int sizeShape, line;
    bool shapeOn;
};

#endif // Highlight_hpp