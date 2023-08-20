#include <TwothreeNode.hpp>

TwothreeNode::TwothreeNode(){}

TwothreeNode::TwothreeNode(std::vector <std::string> text, const sf::Vector2f& position) :
    m_size(40),
    m_position(position),
    positionSpeed(sf::Vector2f(0,0))
{
    m_rectangle.setSize(sf::Vector2f(m_size*text.size(),m_size));
    m_rectangle.setOrigin(sf::Vector2f(m_rectangle.getSize().x/2,m_size/2));
    m_rectangle.setPosition(position);
    m_rectangle.setOutlineColor(sf::Color::Black);
    m_rectangle.setOutlineThickness(3.f);
    m_rectangle.setFillColor(FirstNodeColor);

      // Set the position and color of the text
    for (auto i : text){
        sf::Text m_text = sf::Text(i, ResourceManager::getFont(), textSize);
        m_text.setFillColor(sf::Color::Black);
        m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height);
        listValue.push_back(m_text);
    }
    setTextPosition(position);
}

void TwothreeNode::setColor(const sf::Color& color){
    m_rectangle.setFillColor(color);
    for (auto i : childNode)i.second.setColor(color);
}

void TwothreeNode::setNodeColor(sf::Color color){
    m_rectangle.setFillColor(color);
}

void TwothreeNode::setOutlineColor(sf::Color color){
    m_rectangle.setOutlineColor(color);
}

void TwothreeNode::setTextColor(sf::Color color){
    for (auto i : listValue)i.setFillColor(color);
}

float TwothreeNode::getRad(){
    return m_rectangle.getSize().x;
}

void TwothreeNode::addNew(std::string val){
    sf::Text m_text = sf::Text(val, ResourceManager::getFont(), textSize);
    m_text.setFillColor(sf::Color::Black);
    m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height);
    listValue.push_back(m_text);

    m_rectangle.setSize(sf::Vector2f(m_rectangle.getSize().x + m_size, m_rectangle.getSize().y));
    m_rectangle.setOrigin(sf::Vector2f(m_rectangle.getSize().x / 2, m_rectangle.getSize().y / 2));
    setPosition(m_rectangle.getPosition());
}

void TwothreeNode::setPosSpeed(sf::Vector2f x, sf::Vector2f y){
    positionSpeed = sf::Vector2f((y.x - x.x) / numFrame, (y.y - x.y) / numFrame);
}

bool TwothreeNode::checkPosition(){
    bool kq = 0;
    sf::Vector2f speed = (m_position - getNodePosition()) * 0.1f;
    if (std::max(abs(m_position.x - getNodePosition().x), abs(m_position.y - getNodePosition().y)) > EPS)
        setPosition(getNodePosition() + speed), kq = 1;
    // std::cout << getValue() << " " << kq << " " << abs(m_position.x - getNodePosition().x) << " " << abs(m_position.y - getNodePosition().y) << '\n';
    for(int i = 0; i < childNode.size(); ++i) if (childNode[i].first != nullptr){
        kq |= childNode[i].first -> checkPosition();
    }
    return kq;  
}

bool TwothreeNode::checkArrow(){
    bool kq = 0;
    for(int i = 0; i < childNode.size(); ++i) if (childNode[i].first != nullptr){
        kq |= childNode[i].second.checkPosition();
        kq |= childNode[i].first -> checkArrow();
    }
    return kq;  
}

void TwothreeNode::checkPositionFast(){
    setPosition(m_position);
    for(int i = 0; i < childNode.size(); ++i) if (childNode[i].first != nullptr){
        childNode[i].first -> checkPositionFast();
    }
}

void TwothreeNode::checkArrowFast(){
    for(int i = 0; i < childNode.size(); ++i) if (childNode[i].first != nullptr){
        childNode[i].second.checkPositionFast();
        childNode[i].first -> checkArrowFast();
    }
}

void TwothreeNode::changePosition(sf::Vector2f position){
    m_position = position;
}

void TwothreeNode::setTextPosition(sf::Vector2f position){
    position.x -= m_rectangle.getSize().x / 2;
    float node_pos = m_size / 2;
    for (int i = 0; i < listValue.size(); ++i){
        listValue[i].setOrigin(listValue[i].getLocalBounds().width / 2.f, listValue[i].getLocalBounds().height);
        listValue[i].setPosition(sf::Vector2f(position.x + node_pos + m_size*i, position.y));
    }
}

void TwothreeNode::setPosition(sf::Vector2f position){
    // std::cout << "position: " <<position.x << ' ' << position.y << '\n';
    m_rectangle.setPosition(position);
    // for (auto i : childNode)i.second = DynArrow(60, sf::Color::Black, sf::Vector2f(position.x + CircleRad + 3, position.y), 0.f);
    setTextPosition(position);
}

void TwothreeNode::setPartialColor(float ratio, int id){
    childNode[id].second.setPartialColor(ratio);
}

void TwothreeNode::setSearching(float ratio){
    setOutlineColor(ResourceManager::changeColor(sf::Color::Black, SearchingNodeColor, ratio));
    setNodeColor(ResourceManager::changeColor(FirstNodeColor, SearchingNodeColor, ratio));
    setTextColor(ResourceManager::changeColor(textColorStart, textColorEnd, ratio));
    // if (vtx && typeGraph != Graph)setArrowColor(vtx-1, ratio);
}

void TwothreeNode::removeSearching(float ratio){
    setNodeColor(ResourceManager::changeColor(SearchingNodeColor, FirstNodeColor, ratio));
    setTextColor(ResourceManager::changeColor(textColorEnd, SearchingNodeColor, ratio));
}

void TwothreeNode::setFound(float ratio){
    setOutlineColor(ResourceManager::changeColor(SearchingNodeColor, FoundNodeColor, ratio));
    setNodeColor(ResourceManager::changeColor(SearchingNodeColor, FoundNodeColor, ratio));
    setTextColor(ResourceManager::changeColor(textColorEnd, textColorEnd, ratio));
}

void TwothreeNode::removeFound(float ratio){
    setOutlineColor(FoundNodeColor);
    setNodeColor(backgroundColor);
    setTextColor(FoundNodeColor);
    // gameGlobal->runBreak();
}

void TwothreeNode::setDefault(){
    setOutlineColor(sf::Color::Black);
    setNodeColor(FirstNodeColor);
    setTextColor(textColorStart);
}

float TwothreeNode::getLengthArrow(int id){
    return childNode[id].second.getLength();
}

sf::Vector2f TwothreeNode::getNodePosition() const {
    return m_rectangle.getPosition();
}

void TwothreeNode::setHeight(int k){H = k;}
int TwothreeNode::getHeight(){return H;}
    
void TwothreeNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    for (auto i : childNode)if (i.first){
        if (std::min(abs(i.first->getNodePosition().x), abs(i.first->getNodePosition().y)) > 10 &&
            std::min(abs(getNodePosition().x), abs(getNodePosition().y)) > 10)
            target.draw(i.second, states);
    }

    for (auto i : childNode)if (i.first){
        target.draw(*i.first, states);
    }

    target.draw(m_rectangle, states);
    for (auto i : listValue)target.draw(i, states);
}
       
