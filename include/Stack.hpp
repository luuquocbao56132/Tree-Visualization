#ifndef Stack_hpp
#define Stack_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>
#include <Graph.hpp>

class Stack: public DataTypes{
public:
    Stack();
    Stack(const sf::Vector2f& , const sf::Vector2f& ,
        const std::string& , const sf::Font& , unsigned int );
    void LetsPeek(int );
    void LetsPush(int);
    void LetsPop();
    void LetsClear();
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void getFromFile();
    void checkPress(sf::Vector2f ) override;
    // bool isTurn;
};

#endif // Stack_hpp