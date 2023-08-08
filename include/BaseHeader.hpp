#ifndef BaseHeader_hpp
#define BaseHeader_hpp

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <Resource.hpp>
#include <iostream>
#include <Vector>
#include <cmath>
#include <math.h>
#include <string>
#include <array>
#include <string.h>
#include <set>
#include <fstream>
#include <functional>
#include <queue>
#include <windows.h>
#include <memory>

enum Direction{
        TOP,
        RIGHT,
        BOT,
        LEFT
    };

enum Function{
    FROMFILE,
    RANDOM,
    INSERT,
    REMOVE,
    SEARCH,
};

enum AroundNode{
    Prev,
    Next
};

enum Child{
    node,
    arrow
};

enum TypeGraph{
    ARRAY,
    CIRCLE,
    DOUBLYVector,
    CIRCULARVector
};

static float CircleRad = 19;
static float nodeDistance = 60;
static float textSize = 19;
static sf::Color TextColor[2] = {sf::Color(40, 42, 54), sf::Color(237, 242, 245)};
static sf::Color ButtonColor[2] = {sf::Color(255,255,255), sf::Color(48, 59, 89)};
static sf::Color HoverColor[2] = {sf::Color(124, 152, 231), sf::Color(25, 38, 74)};
static sf::Color textColorStart = sf::Color::Black;
static sf::Color textColorEnd = sf::Color::White;
static sf::Color backgroundColor(238,238,238);
static sf::Color endStateColor(255, 138, 39);
static sf::Color FirstNodeColor(238, 238, 238);
static sf::Color SearchingNodeColor(255, 138, 39);
static sf::Color FoundNodeColor(46, 187, 209);
static sf::Color NewNodeColor(82, 188, 105);
static sf::Color DelNodeColor(217, 81, 60);
static sf::Color BlurNodeColor(62,62,62);
static sf::Vector2f inputButtonSize = sf::Vector2f(60,50);
static int maxValue = 99;
static int maxSize = 15;
static float timeLength = 1000;
static float arrowLength = 60;
static float nodeRadius = 19;
static float TimePerFrame = 1/60;
extern std::string theme;
extern int typeTheme;
extern bool isThemeChange;
extern float numFrame;
extern float xtime;


//static float M_PI = 3.14159;
// #include "Game.hpp"
class Game;
// static std::shared_ptr <Game> gameGlobal = std::make_shared<Game>();;

#endif // BaseHeader_hpp