#include <DataTypes.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;
extern int typeTheme;
extern bool isThemeChange;
extern std::string theme;

DataTypes::DataTypes():
        buttonSize(sf::Vector2f(90.f, 50.f)), buttonSpacing(sf::Vector2f(0.f, 5.f)),
        buttonPosition(sf::Vector2f(10.f, 780.f)), buttonRange(buttonSize + buttonSpacing),
        buttonState(-1), highlight(){     
            highlight.setLine("");
            MenuButton = Button(sf::Vector2f(10,10), sf::Vector2f(100,50), "Menu", ResourceManager::getFont(), 19, 0);
            caseSpeedButton = Button(sf::Vector2f(120,10), sf::Vector2f(100,50), "Case Speed", ResourceManager::getFont(), 19, 0);
            // upSpeed = Button(sf::Vector2f(980,10), sf::Vector2f(buttonSize.y/2,buttonSize.y/2), 
            //                 "U", ResourceManager::getFont(), 15, 0);
            // downSpeed = Button(sf::Vector2f(980,10+buttonSize.y/2), sf::Vector2f(buttonSize.y/2,buttonSize.y/2), 
            //                 "D", ResourceManager::getFont(), 15, 0);
            // timeText = sf::Text(std::to_string((int)xtime) + "x", ResourceManager::getFont(), 25);
            // timeText.setPosition(sf::Vector2f(upSpeed.getPosition().x - 50,buttonSize.y/2-10));
            // timeText.setFillColor(TextColor[typeTheme]);

            int i = 280;
            std::shared_ptr<Button> FromFile (new Button(buttonPosition + sf::Vector2f(buttonPosition.x + 0*i, buttonRange.y),
                            buttonSize + sf::Vector2f(100,0), "Insert from file", ResourceManager::getFont(), 20,0));
            std::shared_ptr<Button> Random (new Button(buttonPosition + sf::Vector2f(buttonPosition.x + 1*i - 100, buttonRange.y),
                            buttonSize, "Random", ResourceManager::getFont(), 20,1));
            std::shared_ptr<Button> Insert (new Button(buttonPosition + sf::Vector2f(buttonPosition.x + 2*i - 100, buttonRange.y),
                            buttonSize, "Insert", ResourceManager::getFont(), 20,1));
            std::shared_ptr<Button> Remove (new Button(buttonPosition + sf::Vector2f(buttonPosition.x + 3*i - 100, buttonRange.y),
                            buttonSize, "Remove", ResourceManager::getFont(), 20,1));
            std::shared_ptr<Button> Search (new Button(buttonPosition + sf::Vector2f(buttonPosition.x + 4*i - 100, buttonRange.y),
                            buttonSize, "Search", ResourceManager::getFont(), 20,1));

            //BaseButton.push_back(std::make_shared<Button>(Create));
            BaseButton.push_back(FromFile);
            BaseButton.push_back(Random);
            BaseButton.push_back(Insert);
            BaseButton.push_back(Remove);
            BaseButton.push_back(Search);

            Search->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Search->getPosition().x + Search->getSize().x + 40, 
                                                                            Search->getPosition().y), 
                                                                        inputButtonSize,"x = ",1));
            Search->inputButton[0]->setValueLimit(std::make_shared <int> (99));

            Random->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Random->getPosition().x + Random->getSize().x + 40, 
                                                                            Random->getPosition().y), 
                                                                        inputButtonSize,"n = ",1));
            Random->inputButton[0]->setValueLimit(std::make_shared <int> (60));             

            Insert->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Insert->getPosition().x + Insert->getSize().x + 40, 
                                                                            Search->getPosition().y), 
                                                                        inputButtonSize,"x = ",1));
            Insert->inputButton[0]->setValueLimit(std::make_shared <int> (99));

            Remove->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Remove->getPosition().x + Remove->getSize().x + 40, 
                                                                            Search->getPosition().y), 
                                                                        inputButtonSize,"x = ",1));
            Remove->inputButton[0]->setValueLimit(std::make_shared <int> (99));                                                                        


            // previousButton = Button(sf::Vector2f(1050,15), sf::Vector2f(85,50),"Previous", ResourceManager::getFont(), 19, 0);
            // nextButton = Button(sf::Vector2f(1150,15), sf::Vector2f(85,50),"Next", ResourceManager::getFont(), 19, 0);

            graphSquare.setSize(sf::Vector2f(1800,600));
            graphSquare.setPosition(sf::Vector2f(50,100));
            graphSquare.setFillColor(backgroundColor);
            
            // newNode = nullptr; isThemChange = 0;
        }
void DataTypes::checkFunction(){}
void DataTypes::checkFunctionFast(){}

void DataTypes::clearQueue(){
    while (!funcQueue.empty())funcQueue.pop();
}

void DataTypes::setTheme(){
    highlight.setTheme();
    MenuButton.setColor();
    caseSpeedButton.setColor();
    timeText.setFillColor(TextColor[typeTheme]);
    // upSpeed.setColor(); downSpeed.setColor();
    // previousButton.setColor(); nextButton.setColor();
    for (int i = 0; i < BaseButton.size(); ++i){
        BaseButton[i]->setColor();
        if (!BaseButton[i]->minButton.empty())
            for (int j = 0; j < BaseButton[i]->minButton.size(); ++j)
                BaseButton[i]->minButton[j]->setColor();
    }
    if (!functionButton.empty())for (int i = 0; i < functionButton.size(); ++i)functionButton[i]->setColor();
    // // gameGlobal->runBreak();
}

void DataTypes::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    // if (!isTurn)return;
    target.draw(MenuButton);
    target.draw(caseSpeedButton);
    target.draw(graphSquare);
    target.draw(timeText);
    target.draw(highlight);
    // target.draw(upSpeed); target.draw(downSpeed); 
    // target.draw(previousButton); target.draw(nextButton);
    for (auto res : BaseButton)target.draw(*res);
    if (buttonState != -1){
        for (auto res : (BaseButton[buttonState]->minButton))target.draw(*res);
    }
    for (auto i : inputBox)target.draw(*i);
}

void DataTypes::checkHover(sf::Vector2f mousePos){
    MenuButton.checkHover(mousePos);
    caseSpeedButton.checkHover(mousePos);
    // upSpeed.checkHover(mousePos);
    // downSpeed.checkHover(mousePos);
    // previousButton.checkHover(mousePos);
    // nextButton.checkHover(mousePos);
    for (auto res : BaseButton)res->checkHover(mousePos);
    if (buttonState != -1)
        for (auto res : (BaseButton[buttonState]->minButton))res->checkHover(mousePos);
}

void DataTypes::checkPress(sf::Vector2f mousePos){
    //if (LL_button.checkPress(mousePos))isTurn = 1;
    if (MenuButton.checkPress(mousePos))clearQueue(), gameGlobal->mWorld.MenuState = 1, gameGlobal->mWorld.menu.setTheme();
    if (caseSpeedButton.checkPress(mousePos))caseSpeed = !caseSpeed;
    for (int i = 0; i < BaseButton.size(); ++i)if (BaseButton[i]->checkPress(mousePos))
        buttonState = i, inputBox.clear(); 
    // if (upSpeed.checkPress(mousePos))xtime = std::min(xtime + 1, 10.f), timeText.setString(std::to_string((int)xtime)+"x");
    // if (downSpeed.checkPress(mousePos))xtime = std::max(xtime - 1, 1.f), timeText.setString(std::to_string((int)xtime) + "x");
    // if (previousButton.checkPress(mousePos))mainGraph.getStep(-1);
    // if (nextButton.checkPress(mousePos))mainGraph.getStep(1);
    // if (themeSet.checkPress(mousePos)) setTheme();
    numFrame = 1.f/xtime * 60;
}

void DataTypes::checkKeyInput(sf::Event& event){
    for (auto i : inputBox)if (i->cursorOn)i->handleEvent(event);
}
