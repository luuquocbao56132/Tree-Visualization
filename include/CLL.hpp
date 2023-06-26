#ifndef CLL_hpp
#define CLL_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>
#include <Graph.hpp>

class CLL: public DataTypes{
public:
    CLL();
    CLL(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    void LetsSearch(int );
    void LetsInsert(int, int);
    void LetsRemove(int);
    void LetsUpdate(int, int);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void getFromFile();
    void checkPress(sf::Vector2f ) override;
    // bool isTurn;
};

#endif // CLL_hpp