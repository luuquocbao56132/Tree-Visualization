#ifndef InputBox_hpp
#define InputBox_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>

class InputBox: public sf::Drawable, public sf::Transformable{
public: 
    InputBox();
    InputBox(sf::Vector2f , sf::Vector2f, std::string, bool);
    InputBox(sf::Vector2f , sf::Vector2f, std::string, bool, bool);
    void setValue(int);
    int getValue();
    std::string getString();
    void resetValue();
    void setValueLimit(std::shared_ptr <int> );
    
    bool cursorOn, isCharacter;
    sf::FloatRect getGlobalBounds() const;
    void checkPress(sf::Vector2f );
    void handleEvent(const sf::Event& );
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
    std::shared_ptr<Button> Go;
private:
    sf::RectangleShape m_box;
    sf::Text m_text;
    sf::Text m_textLeft;
    sf::RectangleShape m_cursor;
    int m_value, m_cursorPos, charLength;
    std::shared_ptr<int> valueLimit;
};

#endif // InputBox_hpp