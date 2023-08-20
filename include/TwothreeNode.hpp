#ifndef TwothreeNode_hpp
#define TwothreeNode_hpp

#include <BaseHeader.hpp>
#include <DynArrow.hpp>

class TwothreeNode;

class TwothreeNode : public sf::Drawable, public sf::Transformable{
public:
    TwothreeNode();
    TwothreeNode(std::vector <std::string>, const sf::Vector2f& );

    void setColor(const sf::Color& );
    void setNodeColor(sf::Color );
    void setOutlineColor(sf::Color );
    void setTextColor(sf::Color );

    void setSearching(float);
    void setDel(float);
    void setDefault();
    void removeSearching(float);
    void setFound(float);
    void removeFound(float);

    void setDirectionColor(const sf::Color& , unsigned int );

    void setPosition(sf::Vector2f );
    void setTextPosition(sf::Vector2f );
    void changePosition(sf::Vector2f);
    bool checkPosition();
    void checkPositionFast();
    bool checkArrow();
    void checkArrowFast();
    void setPosSpeed(sf::Vector2f, sf::Vector2f);

    void setPartialColor(float , int);

    void addNew(std::string );

    float getLengthArrow(int);

    float getRad();

    sf::Vector2f getNodePosition() const;

    std::string getString() const;

    int getValue() const;

    void changeText(Direction, std::string );

    void setHeight(int );
    int getHeight();

    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

    std::vector < std::pair < std::shared_ptr <TwothreeNode>, DynArrow > > childNode;
    std::shared_ptr <TwothreeNode> prevNode;

    sf::Vector2f positionSpeed, m_position;
    int numArrow, H;

    sf::RectangleShape m_rectangle;
    std::vector <sf::Text> listValue;
    float m_size;
};

#endif // TwothreeNode_hpp