#include <DataTypes.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;
extern int typeTheme;
extern bool isThemeChange;
extern std::string theme;

DataTypes::DataTypes(){};

DataTypes::DataTypes(int graphType):
        buttonSize(sf::Vector2f(90.f, 50.f)), buttonSpacing(sf::Vector2f(0.f, 5.f)),
        buttonPosition(sf::Vector2f(10.f, 500.f)), buttonRange(buttonSize + buttonSpacing),
        buttonState(-1),
        mainGraph(graphType), typeGraph(graphType){     

            upSpeed = Button(sf::Vector2f(980,10), sf::Vector2f(buttonSize.y/2,buttonSize.y/2), 
                            "U", ResourceManager::getFont(), 15, 0);
            downSpeed = Button(sf::Vector2f(980,10+buttonSize.y/2), sf::Vector2f(buttonSize.y/2,buttonSize.y/2), 
                            "D", ResourceManager::getFont(), 15, 0);
            timeText = sf::Text(std::to_string((int)xtime) + "x", ResourceManager::getFont(), 25);
            timeText.setPosition(sf::Vector2f(upSpeed.getPosition().x - 50,buttonSize.y/2-10));
            timeText.setFillColor(TextColor[typeTheme]);

            previousButton = Button(sf::Vector2f(1050,15), sf::Vector2f(85,50),"Previous", ResourceManager::getFont(), 19, 0);
            nextButton = Button(sf::Vector2f(1150,15), sf::Vector2f(85,50),"Next", ResourceManager::getFont(), 19, 0);

            themeButton =  Button(sf::Vector2f(1250,15), sf::Vector2f(85,50),"Theme", ResourceManager::getFont(), 19, 0);
            backGroundTexture.loadFromFile("./Image/"+theme+"background.png");
            backGroundSprite.setTexture(backGroundTexture);

            graphSquare.setSize(sf::Vector2f(1600,400));
            graphSquare.setPosition(sf::Vector2f(50,100));
            graphSquare.setFillColor(backgroundColor);
            
            newNode = nullptr; isThemChange = 0;
        }

void DataTypes::resetAll(){
    buttonState = -1;
    xtime = 1.f; numFrame = 60;
    inputBox.clear();
    Graph newGraph = Graph(typeGraph);
    mainGraph = newGraph;
    // std::cout << "size node of mainGraph: \n";
    // for (int i = 0; i < mainGraph.listNode.size(); ++i)
    //     std::cout << mainGraph.listNode[i]->getRad() << " "; std::cout << '\n';
    
    firstGraph = mainGraph;
    for (int i = 0; i < firstGraph.listNode.size(); ++i)
        firstGraph.listNode[i]->changeSizeNode(firstGraph.listNode[i]->getRad() - CircleRad);
    timeText = sf::Text(std::to_string((int)xtime) + "x", ResourceManager::getFont(), 25);
    timeText.setPosition(sf::Vector2f(upSpeed.getPosition().x - 50,buttonSize.y/2-10));
    timeText.setFillColor(TextColor[typeTheme]);
    numFrame = 1.f/xtime * 60;
    // for (int i = 0; i < firstGraph.listNode.size(); ++i)
    //     std::cout << firstGraph.listNode[i]->getValue() << " "; std::cout << '\n';
}

void DataTypes::setTheme(){
    backGroundTexture.loadFromFile("./Image/"+theme+"background.png");
    std::string res = mainGraph.highlight.url;
    res.erase(0,8);
    if (res[0] == '1')res.erase(res.begin());
    mainGraph.highlight.addImage("./Image/"+theme+res);

    timeText.setFillColor(TextColor[typeTheme]);
    upSpeed.setColor(); downSpeed.setColor(); themeButton.setColor();
    previousButton.setColor(); nextButton.setColor();
    for (int i = 0; i < BaseButton.size(); ++i){
        BaseButton[i]->setColor();
        if (!BaseButton[i]->minButton.empty())
            for (int j = 0; j < BaseButton[i]->minButton.size(); ++j)
                BaseButton[i]->minButton[j]->setColor();
    }
    if (!functionButton.empty())for (int i = 0; i < functionButton.size(); ++i)functionButton[i]->setColor();
    // gameGlobal->runBreak();
}

void DataTypes::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    // if (!isTurn)return;
    target.draw(backGroundSprite); 
    target.draw(graphSquare);
    target.draw(timeText);
    target.draw(upSpeed); target.draw(downSpeed);
    target.draw(previousButton); target.draw(nextButton);
    target.draw(themeButton);
    for (auto res : BaseButton)target.draw(*res);
    if (buttonState != -1){
        for (auto res : (BaseButton[buttonState]->minButton))target.draw(*res);
    }
    for (auto i : inputBox)target.draw(*i);
}

void DataTypes::checkHover(sf::Vector2f mousePos){
    upSpeed.checkHover(mousePos);
    downSpeed.checkHover(mousePos);
    previousButton.checkHover(mousePos);
    nextButton.checkHover(mousePos);
    themeButton.checkHover(mousePos);
    for (auto res : BaseButton)res->checkHover(mousePos);
    if (buttonState != -1)
        for (auto res : (BaseButton[buttonState]->minButton))res->checkHover(mousePos);
}

void DataTypes::checkPress(sf::Vector2f mousePos){
    //if (LL_button.checkPress(mousePos))isTurn = 1;
    for (int i = 0; i < BaseButton.size(); ++i)if (BaseButton[i]->checkPress(mousePos))
        buttonState = i, inputBox.clear(); 
    if (upSpeed.checkPress(mousePos))xtime = std::min(xtime + 1, 10.f), timeText.setString(std::to_string((int)xtime)+"x");
    if (downSpeed.checkPress(mousePos))xtime = std::max(xtime - 1, 1.f), timeText.setString(std::to_string((int)xtime) + "x");
    if (previousButton.checkPress(mousePos))mainGraph.getStep(-1);
    if (nextButton.checkPress(mousePos))mainGraph.getStep(1);
    if (themeButton.checkPress(mousePos)){
        isThemeChange = 0;
        if (theme == ""){theme = "1"; typeTheme = 1;}
            else {theme = ""; typeTheme = 0;}
        setTheme();
    }
    numFrame = 1.f/xtime * 60;
}

void DataTypes::checkKeyInput(sf::Event& event){
    for (auto i : inputBox)if (i->cursorOn)i->handleEvent(event);
}
