#ifndef Theme_hpp
#define Theme_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>

class Theme: public sf::Drawable, public sf::Transformable {
    public:
        Button themeBut;
        sf::Texture backGroundTexture;
        sf::Sprite backGroundSprite;

        Theme();
        void draw(sf::RenderTarget& , sf::RenderStates ) const;
        void HoverCheck(sf::Vector2f );
        bool checkPress(sf::Vector2f );
};

#endif // Theme_Hpp