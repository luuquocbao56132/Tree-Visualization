#include <DynArrow.hpp>

DynArrow::DynArrow(){}

DynArrow::DynArrow(float length, sf::Color color, sf::Vector2f position, float angle):
    m_length(length),
    m_color(color),
    m_position(position),
    m_angle(angle)
{
    m_body.setFillColor(color);
    m_body.setSize(sf::Vector2f(length,3.f));

    m_head.setPointCount(3);
    m_head.setFillColor(color);
    m_head.setPoint(0, sf::Vector2f(length, 1.5));
    m_head.setPoint(1, sf::Vector2f(length-12, -4.5));
    m_head.setPoint(2, sf::Vector2f(length-12, 7.5));
    m_head.setOrigin(length-12.f, 1.5f);

    m_particle.setFillColor(sf::Color::Yellow);
    m_particle.setSize(sf::Vector2f(0.f,3.f));
    setPosition(position); 
}

void DynArrow::setColor(const sf::Color& color){
    m_color = color;
    m_body.setFillColor(color);
}

void DynArrow::setRotation(float degrees){
    m_body.setRotation(degrees);
    m_head.setRotation(degrees);
    m_particle.setRotation(degrees);
    m_angle = degrees;
}

void DynArrow::setPosition(sf::Vector2f position){
    m_body.setPosition(position);
    m_particle.setPosition(position);
}

void DynArrow::setPartialColor(float ratio){
    float length = m_length * ratio;
    m_particle.setSize(sf::Vector2f(length, 3.f));
}

void DynArrow::minimizeArrow(float length){
    // std::cout << "m_length: " << m_length << " length: " << length << '\n'; 
    float ratio_particle;
    if (abs(m_length) < EPS)ratio_particle = 0; 
        else ratio_particle = m_particle.getSize().x / m_length;
    m_length = length;
    // m_length = std::max(m_length,1.f);
    // std::cout << "mlength: " << m_length << '\n';

    sf::Vector2f res = m_body.getPosition();
    m_body.setSize(sf::Vector2f(m_length,3.f));
    if (m_particle.getSize().x > 0)m_particle.setSize(sf::Vector2f(m_length * ratio_particle, 3.f));
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
    if (m_particle.getSize().y > 0)target.draw(m_particle, states);
}


