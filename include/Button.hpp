#ifndef Button_hpp
#define Button_hpp

#include <BaseHeader.hpp>

class InputBox;

class Button : public sf::Drawable, public sf::Transformable {
public:
    Button();
    Button(const sf::Vector2f& , const sf::Vector2f& ,
           const std::string& , const sf::Font& , unsigned int , int);

    void setFillColor(const sf::Color& ); 
    void setColor(); 

    void setOutlineColor(const sf::Color& );

    void setOutlineThickness(float );

    void setPosition(const sf::Vector2f& );

    void setSize(const sf::Vector2f& ); 

    sf::Vector2f getSize() const ;

    bool isHovered() const ;

    void hover();

    void unhover();

    sf::FloatRect getGlobalBounds() const ;

    void createMinButton(std::initializer_list<std::string> , std::initializer_list<int> );

// private:
    void centerOrigin(const sf::Vector2f& );

    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

    void checkHover(sf::Vector2f);

    bool checkPress(sf::Vector2f);

    sf::Vector2f m_size;
    sf::RectangleShape m_rect;
    sf::Text m_text;
    std::vector < std::shared_ptr<Button> > minButton;
    std::vector < std::shared_ptr<InputBox> > inputButton;
    int isInput;
    bool m_isHovered, onInput;
};

#endif //Button_hpp