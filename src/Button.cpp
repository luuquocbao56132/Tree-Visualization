#include <Button.hpp>
#include <BaseHeader.hpp>

extern int typeTheme;
extern std::string theme;

Button::Button(){};

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
           const std::string& text, const sf::Font& font, unsigned int characterSize, int numInput):
    m_size(size),
    m_rect(size),
    m_text(text, font, characterSize),
    m_isHovered(false),
    onInput(1)
{
    // m_rect.setFillColor(sf::Color::White);
    // m_rect.setOutlineThickness(2.f);
    // m_rect.setOutlineColor(sf::Color::Black);
    // m_text.setFillColor(sf::Color::Black);

    // std::cout << "TextColor: " << (int)TextColor[typeTheme].r << '\n';
    // m_rect.setFillColor(ButtonColor[typeTheme]);
    m_rect.setOutlineThickness(2.f);
    // m_rect.setOutlineColor(TextColor[typeTheme]);
    // m_text.setFillColor(TextColor[typeTheme]);
    setColor();
    
    setPosition(position);
    isInput = numInput;
}

void Button::centerOrigin(const sf::Vector2f& pos) {
        m_rect.setOrigin(pos);
        m_text.setOrigin(pos);
        //if (m_rect.getOrigin() == m_text.getOrigin())std::cout << 1;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_rect, states);
    target.draw(m_text, states);    
}

void Button::setColor(){
    setFillColor(ButtonColor[typeTheme]);
    setOutlineColor(TextColor[typeTheme]);
    m_text.setFillColor(TextColor[typeTheme]);
}

void Button::setFillColor(const sf::Color& color) {
    m_rect.setFillColor(color);
}

void Button::setOutlineColor(const sf::Color& color) {
    m_rect.setOutlineColor(color);
}

void Button::setOutlineThickness(float thickness) {
    m_rect.setOutlineThickness(thickness);
}

void Button::setPosition(const sf::Vector2f& pos) {
    sf::Transformable::setPosition(pos);
    m_rect.setPosition(pos);
    m_text.setPosition(pos);
    centerOrigin(pos);
}

void Button::setSize(const sf::Vector2f& size) {
    m_size = size;
    m_rect.setSize(m_size);
    //centerOrigin(pos);
}

sf::Vector2f Button::getSize() const {
    return m_size;
}

bool Button::isHovered() const {
    return m_isHovered;
}

void Button::hover() {
    m_isHovered = true;
    m_rect.setFillColor(HoverColor[typeTheme]);
}

void Button::unhover() {
    m_isHovered = false;
    m_rect.setFillColor(ButtonColor[typeTheme]);
}

sf::FloatRect Button::getGlobalBounds() const {
    return getTransform().transformRect(m_rect.getGlobalBounds());
}

void Button::createMinButton(std::initializer_list<std::string> names, std::initializer_list<int> numInputs){
    LinkedList <std::string> Name(names);
    LinkedList <int> numInput(numInputs);

    sf::Vector2f prevPos = getPosition();
    sf::Vector2f prevSize = getSize();

    // Calculate the position and size of the new button
    sf::Vector2f newPos(prevPos.x + prevSize.x + 10.f, prevPos.y);
    sf::Vector2f newSize(prevSize.x, prevSize.y);
    for (int i = 0; i < Name.size(); ++i) {
        std::shared_ptr<Button> newButton (new Button(newPos, newSize, Name[i], ResourceManager::getFont(), 16, numInput[i]));
        newButton -> setSize(sf::Vector2f(newButton->m_text.getGlobalBounds().width,newButton->getSize().y));
        minButton.push_back(newButton);
        // std::cout << newPos.x << '\n';

        prevPos = newButton->getPosition();
        prevSize = newButton->getSize();

        newPos = sf::Vector2f(prevPos.x + prevSize.x + 10.f, prevPos.y);
        newSize = sf::Vector2f(prevSize.x, prevSize.y);
    }
    //std::cout<<minButton.size();
}

void Button::checkHover(sf::Vector2f mousePos){
    if (getGlobalBounds().contains(mousePos))hover(); 
        else unhover();
}

bool Button::checkPress(sf::Vector2f mousePos){
    if (getGlobalBounds().contains(mousePos))return 1; 
        else return 0;
}