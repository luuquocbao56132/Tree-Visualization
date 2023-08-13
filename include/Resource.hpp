#ifndef Resource_hpp
#define Resource_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <BaseHeader.hpp>
class ResourceManager {
public:
    static sf::Font& getFont();
    static int random(int, int);
    static int StringtoInt(std::string);
    static sf::Color changeColor(sf::Color , sf::Color , float );
    static sf::Vector2f changePosition(sf::Vector2f, sf::Vector2f, float);
    static float rad2Node(sf::Vector2f, sf::Vector2f);
    static float dist2Node(sf::Vector2f, sf::Vector2f);
    //     static void changeXtime(float);
//     static float getXtime();
// private:
//     static float xtime = 1;
};

#endif //Resource_hpp