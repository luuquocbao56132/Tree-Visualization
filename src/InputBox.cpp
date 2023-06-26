#include <InputBox.hpp>

InputBox::InputBox (sf::Vector2f position, sf::Vector2f size, std::string textLeft, bool isGo): 
    cursorOn(0), valueLimit(std::make_shared <int> (maxValue))
{
    m_box.setFillColor(sf::Color::Black);
    m_box.setOutlineColor(sf::Color::White);
    m_box.setOutlineThickness(2.f);
    m_box.setSize(size);
    m_box.setPosition(position);

        // Set up the text
    m_text.setFont(ResourceManager::getFont());
    m_text.setCharacterSize(19);
    m_text.setFillColor(backgroundColor);
    m_text.setPosition(position);
    
    m_textLeft.setFont(ResourceManager::getFont());
    m_textLeft.setCharacterSize(19);
    m_textLeft.setFillColor(sf::Color::Yellow);
    m_textLeft.setString(textLeft);
    m_textLeft.setStyle(sf::Text::Bold);
    m_textLeft.setPosition(sf::Vector2f(position.x - 35, position.y));

        // Set up the cursor shape
    m_cursor.setFillColor(backgroundColor);
    m_cursor.setSize(sf::Vector2f(1.f, 19));

    charLength = 10;
    std::cout << "charLength: " << charLength;

    if (isGo){
        Go = std::make_shared <Button> (sf::Vector2f(position.x + size.x + 20, position.y), sf::Vector2f(60,40),
                                                "Go", ResourceManager::getFont(), 19, 0);
        Go->setFillColor(sf::Color::Yellow);
        Go->m_text.setFillColor(sf::Color::Black);
    }                    
        else Go = nullptr;
}

int InputBox::getValue(){return m_value;}

void InputBox::setValue(int x){m_value = x;}

sf::FloatRect InputBox::getGlobalBounds() const {
    return getTransform().transformRect(m_box.getGlobalBounds());
}

void InputBox::checkPress(sf::Vector2f mousePos){
    if (!getGlobalBounds().contains(mousePos)){
        m_cursor.setPosition(m_text.getPosition());
        m_cursorPos = 0; cursorOn = 0; return;
    }
    float x = std::max(0.f,mousePos.x - m_text.getPosition().x - 5);
    int index = x / charLength + ((int)x % charLength ? 1 : 0);
    if (index > m_text.getString().getSize())index = m_text.getString().getSize();
    m_cursor.setPosition(m_text.getPosition().x + index * charLength,
                            m_cursor.getPosition().y);
    m_cursorPos = index; cursorOn = 1;
}

void InputBox::handleEvent(const sf::Event& event){
    if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9){
        if (m_cursorPos < 2){
            if (m_value > 9)return;
            std::string t = m_text.getString();
            int intInput = event.key.code - sf::Keyboard::Num0;
            t.insert(m_cursorPos, std::to_string(intInput));
            if (t.size() > 2 || ResourceManager::StringtoInt(t) > *valueLimit)return;
            m_text.setString(t);
            m_value = ResourceManager::StringtoInt(t);
            m_cursorPos++; m_cursor.setPosition(m_cursor.getPosition() + sf::Vector2f(charLength,0));
        }
    } else if (event.key.code == sf::Keyboard::Backspace) {
        if (m_cursorPos > 0) {
            std::string t = m_text.getString();
            t.erase(t.begin() + m_cursorPos - 1);
            m_value = ResourceManager::StringtoInt(t);
            m_text.setString(t);
            m_cursorPos--; m_cursor.setPosition(m_cursor.getPosition() - sf::Vector2f(charLength,0));
        }
    }   
}

void InputBox::resetValue(){
    m_value = ResourceManager::random(1,*valueLimit);
    m_text.setString(std::to_string(m_value));
}

void InputBox::setValueLimit(std::shared_ptr <int> x){valueLimit = x;}

void InputBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_box);
    if (Go != nullptr)Go->draw(target, states);
    target.draw(m_text);
    target.draw(m_textLeft);
    target.draw(m_cursor);
}