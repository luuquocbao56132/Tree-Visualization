#include <Game.hpp>
#include <BaseHeader.hpp>

float xtime = 1.f;
float numFrame = 60.f;
int typeTheme = ResourceManager::random(0,1);
std::string theme = (typeTheme == 0 ? "" : "1");
std::shared_ptr <Game> gameGlobal = std::make_shared<Game>();

int main() {
    srand(time(NULL));
    std::cout << "Typetheme: " << typeTheme << " " << theme << '\n';
    // gameGlobal = std::make_shared <Game> ();
    std::cout << "Game pointer: " << gameGlobal << '\n';
    // gameGlobal = game;
    // std::cout << "Game pointer: " << game << " " << gameGlobal << '\n';
    gameGlobal->run();

    return 0;
}
