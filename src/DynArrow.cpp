#include <DynArrow.hpp>

DynArrow::DynArrow(){}

DynArrow::DynArrow(sf::Vector2f Home, sf::Vector2f target):
    m_home1(Home),
    m_tail1(target),
    m_home2(Home),
    m_tail2(target)
{
    setPosition();
    m_body.setFillColor(sf::Color::Black);
    m_body.setSize(sf::Vector2f(m_length,3.f));
    m_particle.setFillColor(sf::Color::Yellow);
    m_particle.setSize(sf::Vector2f(0.f,3.f));
}

void DynArrow::setAngle(){
    m_body.setRotation(m_angle);
    m_particle.setRotation(m_angle);
}

void DynArrow::setLength(){
    float ratio_particle;
    if (abs(m_length) < EPS)ratio_particle = 0; 
        else ratio_particle = m_particle.getSize().x / m_length;
    m_body.setSize(sf::Vector2f(m_length,3.f));
    m_particle.setSize(sf::Vector2f(m_length*ratio_particle,3.f));
}

void DynArrow::setHome(sf::Vector2f res){
    m_home2 = res;
}

void DynArrow::setTail(sf::Vector2f res){
    m_tail2 = res;
}

void DynArrow::setPosition(){
    m_body.setPosition(m_home1);
    m_particle.setPosition(m_home1);
    m_length = ResourceManager::dist2Node(m_home1, m_tail1);
    // std::cout << "length: " << m_length << '\n';
    m_angle = ResourceManager::rad2Node(m_home1, m_tail1);
    setAngle(); setLength();
}

bool DynArrow::checkPositionHome(){
    sf::Vector2f speed = (m_home2 - m_home1) * 0.05f;
    if (std::max(abs(m_home2.x - m_home1.x), abs(m_home2.y - m_home1.y)) > EPS){
        m_home1 += speed; return 1;}
    return 0;
}

bool DynArrow::checkPositionTail(){
    sf::Vector2f speed = (m_tail2 - m_tail1) * 0.05f;
    if (std::max(abs(m_tail2.x - m_tail1.x), abs(m_tail2.y - m_tail1.y)) > EPS){
        m_tail1 += speed; return 1;}
    return 0;
}

void DynArrow::checkPositionFastHome(){
    m_home1 = m_home2;
}

void DynArrow::checkPositionFastTail(){
    m_tail1 = m_tail2;
}

void DynArrow::checkPositionFast(){
    checkPositionFastHome(); checkPositionFastTail();
    setPosition();
}

bool DynArrow::checkPosition(){
    bool kq = checkPositionHome() | checkPositionTail();
    setPosition();
    return kq;
}

void DynArrow::setColor(const sf::Color& color){
    m_body.setFillColor(color);
}

void DynArrow::setPartialColor(float ratio){
    float length = m_length * ratio;
    m_particle.setSize(sf::Vector2f(length, 3.f));
}

float DynArrow::getLength(){
    return m_length;
}

float DynArrow::getAngle(){
    return m_angle;
}

void DynArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(m_body, states);
    if (m_particle.getSize().x > 0.f)target.draw(m_particle, states);
}


