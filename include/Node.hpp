#ifndef Node_hpp
#define Node_hpp

#include <BaseHeader.hpp>
#include <DynArrow.hpp>

class Node;

class Node : public sf::Drawable, public sf::Transformable{
public:
    Node();
    Node(float radius, const std::string& , const sf::Font& , float , const sf::Color& , const sf::Vector2f& , bool);
    Node(float radius, const std::string& , const sf::Font& , float , const sf::Color& , const sf::Vector2f& , bool, int);

    void setColor(const sf::Color& );

    void setText(const std::string& );
    void setTextBot(std::string );
    void setTextTop(std::string );

    void setArrow();
    void setNodeColor(sf::Color );
    void setOutlineColor(sf::Color );
    void setTextColor(sf::Color );

    void setSearching(float);
    void setDel(float);
    void removeSearching(float);
    void setFound(float);
    void removeFound(float);

    void setDirectionColor(const sf::Color& , unsigned int );

    void setPosition(sf::Vector2f );

    void setPartialColor(float , int);

    void rotateNextArrow(float ,int );

    void changeSizeArrow(float, int);

    void changeSizeNode(float);

    float getLengthArrow(int);

    float getRad();

    sf::Vector2f getNodePosition();

    std::string getString();

    int getValue();

    void changeText(Direction, std::string );

    void setHeight(int );
    int getHeight();

    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

    std::vector < std::pair < std::shared_ptr <Node>, DynArrow > > childNode;
    std::shared_ptr <Node> prevNode;

    sf::Text m_text_directions[4];
    void updateCircle();
    void setCircle(bool);
    int numArrow, H;
private:
    bool typeNode;
    sf::CircleShape m_circle;
    sf::RectangleShape m_rectangle;
    sf::Color m_color;
    sf::Vector2f m_position;
    sf::Text m_text;
    float m_radius;
};

#endif // Node_hpp