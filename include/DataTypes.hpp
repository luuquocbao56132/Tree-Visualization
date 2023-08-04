#ifndef DataTypes_hpp
#define DataTypes_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <InputBox.hpp>
// #include <Graph.hpp>
#include <Theme.hpp>
#include <Node.hpp>
#include <Animation.hpp>

class DataTypes: public sf::Drawable, public sf::Transformable{
public:
    DataTypes();
    DataTypes(int);
    virtual void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkHover(sf::Vector2f);
    void checkKeyInput(sf::Event& );
    void setTheme();
    void clearQueue();
    virtual void checkFunction();
    virtual void checkPress(sf::Vector2f);
    // virtual void resetAll();
    std::vector <std::shared_ptr<Button>> BaseButton, functionButton;
    std::vector <std::shared_ptr<InputBox>> inputBox;
    std::shared_ptr <Node> newNode;
    std::queue <Animation> funcQueue;
    Button upSpeed, downSpeed, previousButton, nextButton, MenuButton;
    Theme themeSet;
    sf::RectangleShape graphSquare;
    sf::Text timeText;
    // InputBox inpBox;
    int buttonState, typeGraph;
    bool isThemChange;
    // Graph firstGraph, mainGraph;
    //Graph xyz
    sf::Vector2f buttonSize, buttonSpacing, buttonPosition, buttonRange;
};

#endif // DataTypes_hpp