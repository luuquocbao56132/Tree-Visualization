#include <DynArrow.hpp>

DynArrow::DynArrow(){}

DynArrow::DynArrow(sf::Vector2f Home, sf::Vector2f target):
    m_home(Home),
    m_target(target)
{
    m_length = ResourceManager::dist2Node(Home, target);
    m_body.setFillColor(sf::Color::Black);
    m_body.setSize(sf::Vector2f(m_length,3.f));
    m_angle = ResourceManager::rad2Node(Home, target);
    setAngle(); setPosition();

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

void DynArrow::setPosition(){
    m_body.setPosition(m_home);
    m_particle.setPosition(m_home);
    m_length = ResourceManager::dist2Node(m_home, m_target);
    m_angle = ResourceManager::rad2Node(m_home, m_target);
    setAngle(); setLength();
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


