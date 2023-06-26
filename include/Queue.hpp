#ifndef Queue_hpp
#define Queue_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>
#include <Graph.hpp>

class Queue: public DataTypes{
public:
    Queue();
    Queue(const sf::Vector2f& , const sf::Vector2f& ,
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

#endif // Queue_hpp