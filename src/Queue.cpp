#include <Queue.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

Queue::Queue():DataTypes(LINKEDLIST)
        {

            std::shared_ptr<Button> Create (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*1),
                            buttonSize, "Create", ResourceManager::getFont(), 20,0));
            std::shared_ptr<Button> Peek (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*2),
                            buttonSize, "Peek", ResourceManager::getFont(), 20,0));
            std::shared_ptr<Button> Push (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*3),
                            buttonSize, "Push", ResourceManager::getFont(), 20,1));
            std::shared_ptr<Button> Pop (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*4),
                            buttonSize, "Pop", ResourceManager::getFont(), 20,0));
            std::shared_ptr<Button> Clear (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*5),
                            buttonSize, "Clear", ResourceManager::getFont(), 20,2));

            //BaseButton.push_back(std::make_shared<Button>(Create));
            BaseButton.push_back(Create);
            BaseButton.push_back(Peek);
            BaseButton.push_back(Push);
            BaseButton.push_back(Pop);
            BaseButton.push_back(Clear);

            Create->createMinButton({"Empty","Random","Random Fixed Size","Custom"},
                                    {0,0,1,1});
            Create->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                        sf::Vector2f(Create->minButton[2]->getPosition().x + 55, 
                            Create->minButton[2]->getPosition().y + Create->minButton[2]->getSize().y + 5), 
                        inputButtonSize,"n = ",1));
            Create->minButton[2]->inputButton[0]->setValueLimit(std::make_shared <int> (maxSize));
            //std::cout << BaseButton[0]->minButton.size();
            Peek->createMinButton({"Front","Back"},{0,0});

            Push->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Push->getPosition().x + Push->getSize().x + 40, 
                                                                            Push->getPosition().y), 
                                                                        inputButtonSize,"v = ",1));
            //setTheme();
            firstGraph = mainGraph;
        }

void Queue::LetsPeek(int t){
    mainGraph = firstGraph; mainGraph.resetStep();
    std::string s;
    if (t) t = mainGraph.getSize()-1, s = "./Image/"+theme+"Q_PeekB.png";
        else s = "./Image/"+theme+"Q_PeekF.png";
    mainGraph.highlight.addImage(s); mainGraph.highlight.setHL(1);
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
    if (mainGraph.getSize() == 0){
        mainGraph.highlight.setLine(1);
        return;
    }

    mainGraph.highlight.setLine(2);
    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.setSearchingNode(t, stt/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.saveStep();
}

void Queue::LetsPush(int value){
    mainGraph = firstGraph; mainGraph.resetStep();
    mainGraph.highlight.addImage("./Image/"+theme+"Q_Push.png"); mainGraph.highlight.setHL(1);
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    mainGraph.makeNewNode(mainGraph.getSize(), value);
    firstGraph = mainGraph;
}

void Queue::LetsPop(){
    mainGraph = firstGraph; mainGraph.resetStep();
    mainGraph.highlight.addImage("./Image/"+theme+"Q_Pop.png"); mainGraph.highlight.setHL(1);
    if (mainGraph.getSize() == 0){
        mainGraph.highlight.setLine(1);
        return;
    }
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
    
    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.setSearchingNode(0, stt/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.removeNode(0);
    firstGraph = mainGraph;
}

void Queue::LetsClear(){
    mainGraph = firstGraph; mainGraph.resetStep();
    mainGraph.highlight.addImage("./Image/"+theme+"Q_Clear.png"); mainGraph.highlight.setHL(1);
    if (!mainGraph.getSize())return;
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    while (mainGraph.getSize()){
        mainGraph.highlight.setLine(1); Sleep(1000*(numFrame/110));
        mainGraph.saveStep();
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(0, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.removeNode(0);
    }
    firstGraph = mainGraph;
}

void Queue::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    target.draw(mainGraph);
}

void Queue::getFromFile(){
    std::ifstream file("customInput.txt");
    std::string line;
    if (file.is_open()) { 
        while (std::getline(file, line)) { 
            std::cout << line << '\n'; 
        }
        file.close(); 
    }
    else {
        std::cerr << "Unable to open file\n";
    }

    std::string c;
    LinkedList <std::string> list;
    for (int i = 0; i < line.size(); ++i){
        if (line[i] >= '0' && line[i] <= '9')c += line[i]; else
        if (line[i] == ';'){
            if (c.empty())return;
            while (c[0] == '0')c.erase(0);
            if (c.size() > 2)return;
            if (c.size() == 0)c = "0";
            list.push_back(c); c = "";
        } else return;
    }
    std::set <int> sameNum;
    for (int i = 0; i < list.size(); ++i)
        if (sameNum.find(ResourceManager::StringtoInt(list[i])) != sameNum.end())return;
    mainGraph.setNumber = sameNum;
    mainGraph.init(list.size(), list);
    firstGraph = mainGraph;
}

void Queue::checkPress(sf::Vector2f mousePos){
    DataTypes::checkPress(mousePos);
    if (DataTypes::buttonState != -1){
        auto res = BaseButton[buttonState];
        switch (buttonState){
            case CREATE:
                if (res->minButton[0]->checkPress(mousePos))mainGraph.init(0), inputBox.clear(), firstGraph = mainGraph;
                if (res->minButton[1]->checkPress(mousePos))mainGraph.init(), inputBox.clear(), firstGraph = mainGraph;
                if (res->minButton[2]->checkPress(mousePos)){
                    inputBox = res->minButton[2]->inputButton;  
                    for (auto i : inputBox)i->resetValue();
                }
                if (res->minButton[3]->checkPress(mousePos))getFromFile();
                if (!inputBox.empty() && inputBox[0] == res->minButton[2]->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))
                        mainGraph.init(inputBox[0]->getValue()), inputBox.clear(), firstGraph = mainGraph;
                }
                break;
            case PEEK:
                if (res->minButton[0]->checkPress(mousePos))LetsPeek(0), inputBox.clear();
                if (res->minButton[1]->checkPress(mousePos))LetsPeek(1), inputBox.clear();
                break;
            case PUSH:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos) && !firstGraph.checkSameNum(inputBox[0]->getValue()) && firstGraph.getSize() < maxSize)
                        LetsPush(inputBox[0]->getValue()), inputBox.clear();
                }
                break;
            case POP:
                if (res->checkPress(mousePos))LetsPop(), inputBox.clear();
                break;
            case CLEAR:
                if (firstGraph.getSize() == 0)break;
                if (res->checkPress(mousePos))LetsClear(), inputBox.clear();
                break;
        }
    }
}
                    