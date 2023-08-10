#include <Node.hpp>

Node::Node(){}

Node::Node(float radius, const std::string& text, const sf::Font& font, float text_size, const sf::Color& color, const sf::Vector2f& position, bool type, int numChild) :
    m_radius(radius),
    m_color(color),
    m_position(position),
    m_text(text, font, text_size),
    H(1), typeNode(type),
    m_text_directions {sf::Text("", font, text_size), sf::Text("",font,text_size), sf::Text("",font,text_size), sf::Text("",font,text_size)}
{
        // Set the position and color of the circle shape
    if (typeNode){
        m_circle.setRadius(radius);
        m_circle.setOrigin(sf::Vector2f(radius,radius));
        m_circle.setPosition(position);
        m_circle.setOutlineColor(sf::Color::Black);
        m_circle.setOutlineThickness(3.f);
        m_circle.setFillColor(color);
    } else {
        m_rectangle.setSize(sf::Vector2f(radius*2,radius*2));
        m_rectangle.setOrigin(sf::Vector2f(radius,radius));
        m_rectangle.setPosition(position);
        m_rectangle.setOutlineColor(sf::Color::Black);
        m_rectangle.setOutlineThickness(3.f);
        m_rectangle.setFillColor(color);
    }

      // Set the position and color of the text
    m_text.setFillColor(sf::Color::Black);
    setText(text);

    m_text_directions[TOP].setString("");
    m_text_directions[TOP].setOrigin(m_text_directions[TOP].getLocalBounds().width / 2.f, m_text_directions[TOP].getLocalBounds().height);
    m_text_directions[TOP].setPosition(sf::Vector2f(position.x, position.y - radius - text_size));
    setDirectionColor(sf::Color::Black,TOP);
    // east text
    m_text_directions[RIGHT].setString("");
    m_text_directions[RIGHT].setPosition(sf::Vector2f(position.x + radius + text_size, position.y));
    // south text
    m_text_directions[BOT].setString("");
    m_text_directions[BOT].setStyle(sf::Text::Bold);
    m_text_directions[BOT].setOrigin(m_text_directions[BOT].getLocalBounds().width / 2.f, m_text_directions[BOT].getLocalBounds().height);
    m_text_directions[BOT].setPosition(sf::Vector2f(position.x, position.y + radius + text_size));
    setDirectionColor(sf::Color(255, 0, 123),BOT);
    // west text
    m_text_directions[LEFT].setString("");
    m_text_directions[LEFT].setOrigin(m_text_directions[LEFT].getLocalBounds().width / 2.f, m_text_directions[LEFT].getLocalBounds().height);
    m_text_directions[LEFT].setPosition(sf::Vector2f(position.x - radius - text_size, position.y));

    childNode.resize(numChild);
    // nextArrow = DynArrow(60, sf::Color::Black, sf::Vector2f(position.x + radius + 3, position.y), 0.f);
}

Node::Node(float radius, const std::string& text, const sf::Font& font, float text_size, const sf::Color& color, const sf::Vector2f& position, bool type) :
    m_radius(radius),
    m_color(color),
    m_position(position),
    m_text(text, font, text_size),
    H(1), typeNode(type),
    m_text_directions {sf::Text("", font, text_size), sf::Text("",font,text_size), sf::Text("",font,text_size), sf::Text("",font,text_size)}
{
        // Set the position and color of the circle shape
    if (typeNode){
        m_circle.setRadius(radius);
        m_circle.setOrigin(sf::Vector2f(radius,radius));
        m_circle.setPosition(position);
        m_circle.setOutlineColor(sf::Color::Black);
        m_circle.setOutlineThickness(3.f);
        m_circle.setFillColor(color);
    } else {
        m_rectangle.setSize(sf::Vector2f(radius*2,radius*2));
        m_rectangle.setOrigin(sf::Vector2f(radius,radius));
        m_rectangle.setPosition(position);
        m_rectangle.setOutlineColor(sf::Color::Black);
        m_rectangle.setOutlineThickness(3.f);
        m_rectangle.setFillColor(color);
    }

      // Set the position and color of the text
    m_text.setFillColor(sf::Color::Black);
    setText(text);

    m_text_directions[TOP].setString("");
    m_text_directions[TOP].setOrigin(m_text_directions[TOP].getLocalBounds().width / 2.f, m_text_directions[TOP].getLocalBounds().height);
    m_text_directions[TOP].setPosition(sf::Vector2f(position.x, position.y - radius - text_size));
    setDirectionColor(sf::Color::Black,TOP);
    // east text
    m_text_directions[RIGHT].setString("");
    m_text_directions[RIGHT].setPosition(sf::Vector2f(position.x + radius + text_size, position.y));
    // south text
    m_text_directions[BOT].setString("");
    m_text_directions[BOT].setStyle(sf::Text::Bold);
    m_text_directions[BOT].setOrigin(m_text_directions[BOT].getLocalBounds().width / 2.f, m_text_directions[BOT].getLocalBounds().height);
    m_text_directions[BOT].setPosition(sf::Vector2f(position.x, position.y + radius + text_size));
    setDirectionColor(sf::Color(255, 0, 123),BOT);
    // west text
    m_text_directions[LEFT].setString("");
    m_text_directions[LEFT].setOrigin(m_text_directions[LEFT].getLocalBounds().width / 2.f, m_text_directions[LEFT].getLocalBounds().height);
    m_text_directions[LEFT].setPosition(sf::Vector2f(position.x - radius - text_size, position.y));

    // nextArrow = DynArrow(60, sf::Color::Black, sf::Vector2f(position.x + radius + 3, position.y), 0.f);
}

void Node::setColor(const sf::Color& color){
    m_color = color;
    if (typeNode)m_circle.setFillColor(color);
        else m_rectangle.setFillColor(color);
    for (auto i : childNode)i.second.setColor(color);
}

void Node::setNodeColor(sf::Color color){
    m_color = color;
    if (typeNode)m_circle.setFillColor(color);
        else m_rectangle.setFillColor(color);
}

void Node::setOutlineColor(sf::Color color){
    if (typeNode)m_circle.setOutlineColor(color);
        else m_rectangle.setOutlineColor(color);
}

void Node::setTextColor(sf::Color color){
    m_text.setFillColor(color);
}

float Node::getRad(){
    return (typeNode == 1 ? m_circle.getRadius() : m_rectangle.getSize().x/2);
}

float dist2Node(sf::Vector2f x, sf::Vector2f y){
    float height = x.y - y.y, width = x.x - y.x;
    return sqrt(height*height + width*width) - CircleRad*2;
}

float rad2Node(sf::Vector2f x, sf::Vector2f y){
    float height = y.y - x.y, width = y.x - x.x;
    float angle = atan2(1,1 / (height / width)) * 180 / M_PI;
    if (angle < 0)angle += 180;
    if (height < 0)angle += 180; 
    return angle;
}

void Node::changeSizeNode(float rad){
    float rate = (m_radius-rad) / m_radius;
    sf::Vector2f position = (typeNode == 1 ? m_circle.getPosition() : m_rectangle.getPosition());
    // std::cout << " (m_radius-rad) / m_radius: " << rate << '\n';
    m_radius -= rad;
    
    if (typeNode){
        m_circle.setRadius(m_radius);
        m_circle.setOrigin(sf::Vector2f(m_radius, m_radius));
        m_circle.setPosition(position);
    } else {
        m_rectangle.setSize(sf::Vector2f(m_radius*2, m_radius*2));
        m_rectangle.setOrigin(sf::Vector2f(m_radius, m_radius));
        m_rectangle.setPosition(position);
    }

    // m_text.setCharacterSize(std::min(std::ceil(m_text.getCharacterSize()*rate), textSize));
    m_text.setCharacterSize(m_radius/CircleRad * textSize);
    m_text.setPosition(position);
    for (int i = 0; i < 4; ++i)m_text_directions[i].setCharacterSize(std::min(std::ceil(m_text_directions[i].getCharacterSize()*rate), textSize));
    
    for (auto i : childNode)i.second.minimizeArrow(i.second.getLength() - i.second.getLength()*rate); 
}

void Node::setPosition(sf::Vector2f position){
    // std::cout << "position: " <<position.x << ' ' << position.y << '\n';
    m_position = position;
    if (typeNode)m_circle.setPosition(position);
        else m_rectangle.setPosition(position);
    m_text_directions[TOP].setPosition(sf::Vector2f(position.x, position.y - CircleRad - textSize));
    m_text_directions[RIGHT].setPosition(sf::Vector2f(position.x + CircleRad + textSize, position.y));
    m_text_directions[BOT].setPosition(sf::Vector2f(position.x, position.y + CircleRad + textSize));
    m_text_directions[LEFT].setPosition(sf::Vector2f(position.x - CircleRad - textSize, position.y));
    for (auto i : childNode)i.second = DynArrow(60, sf::Color::Black, sf::Vector2f(position.x + CircleRad + 3, position.y), 0.f);
    //prevArrow.setRotation(180);
    m_text.setPosition(m_position);
}

void Node::setArrow(){
    for (int i = 0; i < childNode.size(); ++i)
    if (childNode[i].first != nullptr){
        float length = dist2Node(getNodePosition(), childNode[i].first->getNodePosition());
        rotateNextArrow(rad2Node(getNodePosition(), childNode[i].first->getNodePosition()), i);
        childNode[i].second.minimizeArrow(childNode[i].second.getLength() - length);
    }
}

void Node::changeText(Direction i, std::string text){
    m_text_directions[i].setString(text);
}

void Node::setText(const std::string& text){
    m_text.setString(text);
    m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height);
    m_text.setPosition(m_position);
}

void Node::setTextBot(std::string text){
    m_text_directions[BOT].setString(text);
    m_text_directions[BOT].setOrigin(m_text_directions[BOT].getLocalBounds().width / 2.f, m_text_directions[BOT].getLocalBounds().height);
    m_text_directions[BOT].setPosition(sf::Vector2f(m_position.x, m_position.y + m_radius + textSize));
}
void Node::setTextTop(std::string text){
    m_text_directions[TOP].setString(text);
    m_text_directions[TOP].setOrigin(m_text_directions[TOP].getLocalBounds().width / 2.f, m_text_directions[TOP].getLocalBounds().height);
    m_text_directions[TOP].setPosition(sf::Vector2f(m_position.x, m_position.y - m_radius - textSize));
}

void Node::setDirectionColor(const sf::Color& color, unsigned int direction){
    m_text_directions[direction].setFillColor(color);
}

void Node::setPartialColor(float ratio, int id){
    childNode[id].second.setPartialColor(ratio);
}

void Node::setSearching(float ratio){
    setOutlineColor(ResourceManager::changeColor(sf::Color::Black, SearchingNodeColor, ratio));
    setNodeColor(ResourceManager::changeColor(FirstNodeColor, SearchingNodeColor, ratio));
    setTextColor(ResourceManager::changeColor(textColorStart, textColorEnd, ratio));
    // if (vtx && typeGraph != Graph)setArrowColor(vtx-1, ratio);
}

void Node::removeSearching(float ratio){
    setNodeColor(ResourceManager::changeColor(SearchingNodeColor, FirstNodeColor, ratio));
    setTextColor(ResourceManager::changeColor(textColorEnd, SearchingNodeColor, ratio));
}

void Node::setFound(float ratio){
    setOutlineColor(ResourceManager::changeColor(SearchingNodeColor, FoundNodeColor, ratio));
    setNodeColor(ResourceManager::changeColor(SearchingNodeColor, FoundNodeColor, ratio));
    setTextColor(ResourceManager::changeColor(textColorEnd, textColorEnd, ratio));
}

void Node::removeFound(float ratio){
    setOutlineColor(FoundNodeColor);
    setNodeColor(backgroundColor);
    setTextColor(FoundNodeColor);
    // gameGlobal->runBreak();
}

void Node::rotateNextArrow(float degrees, int id){
    childNode[id].second.setRotation(degrees);
    float dx = 0, dy = 0;
    if (childNode[id].first != nullptr)
        if (childNode[id].first->prevNode != nullptr){
            dx = 6*std::sin(degrees * M_PI / 180);
            dy = -6*std::cos(degrees * M_PI / 180);
        } 
    childNode[id].second.setPosition(sf::Vector2f(m_position.x + m_radius * std::cos(degrees * M_PI / 180.f) + dx, m_position.y + m_radius * std::sin(degrees * M_PI / 180.f) + dy));
}

void Node::changeSizeArrow(float length, int id){
    childNode[id].second.minimizeArrow(length);
}

float Node::getLengthArrow(int id){
    return childNode[id].second.getLength();
}

sf::Vector2f Node::getNodePosition(){
    if (typeNode)return m_circle.getPosition();
    return m_rectangle.getPosition();
}

int Node::getValue(){
    return ResourceManager::StringtoInt(m_text.getString());
}

std::string Node::getString(){
    return m_text.getString();
}

void Node::setHeight(int k){H = k;}
int Node::getHeight(){return H;}
    
void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    if (typeNode)target.draw(m_circle, states);
        target.draw(m_rectangle, states);
    target.draw(m_text, states);
    for (const auto& text : m_text_directions)
    {
        target.draw(text, states);
    }
    for (auto i : childNode){
        if (i.first)target.draw(*i.first, states);
    }
}
       
