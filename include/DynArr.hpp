#ifndef DynArr_hpp
#define DynArr_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>
#include <Graph.hpp>

class DynArr: public DataTypes{
public:
    DynArr();
    DynArr(const sf::Vector2f& , const sf::Vector2f& ,
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
    int newNode;
    LinkedList <std::shared_ptr <Node> > listNew;
    // bool isTurn;
};

#endif // DynArr_hpp