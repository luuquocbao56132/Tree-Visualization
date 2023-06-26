#ifndef Game_hpp
#define Game_hpp

// #include <BaseHeader.hpp>
#include <SFML/Graphics.hpp>
#include <World.hpp>

class Game{
    sf::RenderWindow mWindow;
    World mWorld;

    void processEvents();
    void processEventsBreak();
    void update(sf::Time);

    public:
    Game();
    void render();
    void render(int );
    void run();
    void runBreak();
};

#endif //Game_hpp