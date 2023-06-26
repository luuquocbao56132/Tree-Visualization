#include <Resource.hpp>

sf::Font& ResourceManager::getFont() {
    static sf::Font font;
    static bool loaded = false;

    if (!loaded) {
        if (!font.loadFromFile("consolas.ttf")) {
            // handle error
        }

        loaded = true;
    }

    return font;
}

int ResourceManager::random(int l, int r){
    return rand()%(r-l + 1) + l;
}

int ResourceManager::StringtoInt(std::string s){
    int res = 0, t = 1;
    for (int i = s.size()-1; i >= 0; --i)res += t * (int)(s[i] - '0'), t *= 10;
    return res;
}

sf::Color ResourceManager::changeColor(sf::Color startColor, sf::Color endColor, float ratio){
    float dr = ratio*(float)((int)endColor.r - (int)startColor.r);
    float dg = ratio*(float)((int)endColor.g - (int)startColor.g);
    float db = ratio*(float)((int)endColor.b - (int)startColor.b);

    sf::Color currentColor = sf::Color((int)startColor.r + (int)dr, (int)startColor.g + (int)dg, (int)startColor.b + (int)db);
    return currentColor;
}

sf::Vector2f ResourceManager::changePosition(sf::Vector2f startPos, sf::Vector2f endPos, float ratio){
    float dx = ratio*(float)(endPos.x - startPos.x);
    float dy = ratio*(float)(endPos.y - startPos.y);

    sf::Vector2f currentPos = sf::Vector2f(startPos.x + dx, startPos.y + dy);
    return currentPos;
}
// void ResourceManager::changeXtime(float x){ResourceManager::changeXtime(x);}

// float ResourceManager::getXtime(){return xtime;}
