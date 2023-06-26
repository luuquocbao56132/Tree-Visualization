#ifndef StaArr_hpp
#define StaArr_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>
#include <Graph.hpp>

class StaArr: public DataTypes{
public:
    StaArr();
    StaArr(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    void LetsCreate(int );
    void LetsSearch(int );
    void LetsInsert(int, int);
    void LetsRemove(int);
    void LetsUpdate(int, int);
    void LetsAccess(int);
    void resetAll() override;
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void getFromFile();
    void checkPress(sf::Vector2f ) override;
    int number;
    // bool isTurn;
};

#endif // StaArr_hpp