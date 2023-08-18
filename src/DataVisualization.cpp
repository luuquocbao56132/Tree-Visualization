#include <Game.hpp>
#include <BaseHeader.hpp>

float xtime = 1.f;
float numFrame = 60.f;
bool caseSpeed = 1;
int typeTheme = ResourceManager::random(0,1), lg2[200];
std::string theme = (typeTheme == 0 ? "" : "1");
std::shared_ptr <Game> gameGlobal;

int main() {
    // freopen("log.txt", "w", stdout);
    lg2[0] = 0; lg2[1] = 0;
    for (int i = 2; i < 200; i++){
        lg2[i] = lg2[i-1] + 1;
        if ((1LL << lg2[i]) > i) lg2[i]--;
    }
    for (int i = 1; i <= 50; ++i)std::cout << lg2[i] << " "; std::cout << '\n';
    srand(time(NULL));
    std::cout << "Typetheme: " << (int)TextColor[typeTheme].r << " " << (int)TextColor[typeTheme].g << " " << (int)TextColor[typeTheme].b << '\n';
    gameGlobal = std::make_shared <Game> ();
    std::cout << "Game pointer: " << gameGlobal << '\n';
    // gameGlobal = game;
    // std::cout << "Game pointer: " << game << " " << gameGlobal << '\n';
    gameGlobal->run();

    return 0;
}
