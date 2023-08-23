#ifndef Menu_hpp
#define Menu_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <Theme.hpp>

class Menu : public sf::Drawable, public sf::Transformable {
public:
    Menu();
    Button bHash, bAVL, b234, bMinHeap, bMaxHeap, bTrie, bGraph;

    void setTheme();
    int checkPress(sf::Vector2f);
    void HoverCheck(sf::Vector2f);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
};

#endif /* Menu_hpp */