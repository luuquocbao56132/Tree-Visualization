#ifndef World_hpp
#define World_hpp

#include <BaseHeader.hpp>
#include <DataTypes.hpp>
#include <Button.hpp>
#include <set>
#include <vector>
#include <LL.hpp>
#include <DLL.hpp>
#include <CLL.hpp>
#include <DynArr.hpp>
#include <StaArr.hpp>
#include <Queue.hpp>
#include <Stack.hpp>

class World: public sf::Drawable, private sf::NonCopyable {
public:
    std::shared_ptr <DataTypes> liveData;

    Button bLL,bDLL,bCLL,bDynArr,bStaArr,bStack,bQueue;

public:
    World();
    void updateTheme();
    void HoverCheck(sf::Vector2f);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkPress(sf::Vector2f);
};

#endif //World_hpp