#ifndef World_hpp
#define World_hpp

#include <BaseHeader.hpp>
#include <DataTypes.hpp>
#include <Button.hpp>
#include <set>
#include <Vector>
#include <Menu.hpp>
#include <HashTable.hpp>
#include <AVL.hpp>
#include <MaxHeap.hpp>
#include <MinHeap.hpp>
#include <Trie.hpp>
#include <Twothree.hpp>
#include <Theme.hpp>
class World: public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
    std::shared_ptr <DataTypes> liveData;
    Menu menu;
    bool MenuState;
    Theme themeSet;

    World();
    void HoverCheck(sf::Vector2f);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkPress(sf::Vector2f);
};

#endif //World_hpp