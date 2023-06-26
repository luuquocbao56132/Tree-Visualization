#include <CLL.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

CLL::CLL():DataTypes(CIRCULARLINKEDLIST)
        {

            std::shared_ptr<Button> Create (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*1),
                            buttonSize, "Create", ResourceManager::getFont(), 20,0));
            std::shared_ptr<Button> Search (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*2),
                            buttonSize, "Search", ResourceManager::getFont(), 20,1));
            std::shared_ptr<Button> Insert (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*3),
                            buttonSize, "Insert", ResourceManager::getFont(), 20,0));
            std::shared_ptr<Button> Remove (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*4),
                            buttonSize, "Remove", ResourceManager::getFont(), 20,0));
            std::shared_ptr<Button> Update (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*5),
                            buttonSize, "Update", ResourceManager::getFont(), 20,2));

            //BaseButton.push_back(std::make_shared<Button>(Create));
            BaseButton.push_back(Create);
            BaseButton.push_back(Search);
            BaseButton.push_back(Insert);
            BaseButton.push_back(Remove);
            BaseButton.push_back(Update);

            Search->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Search->getPosition().x + Search->getSize().x + 40, 
                                                                            Search->getPosition().y), 
                                                                        inputButtonSize,"v = ",1));

            Create->createMinButton({"Empty","Random","Random Fixed Size","Custom"},
                                    {0,0,1,1});
            Create->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                        sf::Vector2f(Create->minButton[2]->getPosition().x + 55, 
                            Create->minButton[2]->getPosition().y + Create->minButton[2]->getSize().y + 5), 
                        inputButtonSize,"n = ",1));
            Create->minButton[2]->inputButton[0]->setValueLimit(std::make_shared <int> (maxSize));
            
            Insert->createMinButton({"i = 0 (Head), specify v = ","i = N (After tail), specify v = ", "i in {1..N-1} and v = "},
                                    {1,1,2});
                for (int i = 0; i <= 1; ++i){
                    Insert->minButton[i]->inputButton.push_back(std::make_shared <InputBox>(
                            sf::Vector2f(Insert->minButton[i]->getPosition().x + 55, 
                                Insert->minButton[i]->getPosition().y + Insert->minButton[i]->getSize().y + 5), 
                            inputButtonSize,"v = ",1));
                }
            Insert->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Insert->minButton[2]->getPosition().x + 20, 
                            Insert->minButton[2]->getPosition().y + Insert->minButton[2]->getSize().y + 5), 
                        inputButtonSize, "i = ", 0));
            Insert->minButton[2]->inputButton[0]->setValueLimit(mainGraph.n);
            Insert->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Insert->minButton[2]->getPosition().x + Insert->minButton[2]->getSize().x / 2 + 25, 
                            Insert->minButton[2]->getPosition().y + Insert->minButton[2]->getSize().y + 5), 
                        inputButtonSize, "v = ", 1));

            Remove->createMinButton({"i = 0 (Head)", "i = N-1 (tail)", "i in {1..N-1}"},
                                    {0,0,1});
            Remove->minButton[2]->inputButton.push_back(std::make_shared <InputBox>(
                        sf::Vector2f(Remove->minButton[2]->getPosition().x + 35, 
                            Remove->minButton[2]->getPosition().y + Remove->minButton[2]->getSize().y + 5), 
                        inputButtonSize,"i = ",1));
            Remove->minButton[2]->inputButton[0]->setValueLimit(mainGraph.n);

            Update->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Update->getPosition().x + Update->getSize().x + 45, 
                            Update->getPosition().y), 
                        inputButtonSize, "i = ", 0));
            Update->inputButton[0]->setValueLimit(mainGraph.n);
            Update->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(Update->getPosition().x + Update->getSize().x + inputButtonSize.x + 85, 
                            Update->getPosition().y), 
                        inputButtonSize, "v = ", 1));
            // isTurn = 0;
            //setTheme();
            firstGraph = mainGraph;
        }

void CLL::LetsSearch(int X){
    mainGraph = firstGraph; mainGraph.resetStep();
    mainGraph.highlight.addImage("./Image/"+theme+"LL_Search.png"); mainGraph.highlight.setHL(1);
    if (mainGraph.getSize() == 0){
        mainGraph.highlight.setLine(1);
        return;
    }

    // std::cout << "List rad of search graph: \n";
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    int flag = 100;
    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.setSearchingNode(0, stt/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.highlight.setLine(2);
    mainGraph.saveStep();
    if (mainGraph.getValue(0) == X){
        mainGraph.highlight.setLine(6);
        mainGraph.saveStep();
        return;
    }

    for (int vtx = 1; vtx < mainGraph.getSize(); ++vtx){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(vtx-1, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.highlight.setLine(3);
        mainGraph.saveStep();

        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.highlight.setLine(4);
        mainGraph.saveStep();

        if (mainGraph.getValue(vtx) == X){
            flag = vtx; 
            mainGraph.highlight.setLine(6);
            mainGraph.saveStep();
            return;
        }
    }

    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.removeSearchingNode(mainGraph.getSize()-1, stt/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.highlight.setLine(5); mainGraph.saveStep();
}

void CLL::LetsInsert(int vtx, int value){
    mainGraph = firstGraph; mainGraph.resetStep();
    if (mainGraph.getSize() == maxSize)return;
    if (vtx == 0)mainGraph.highlight.addImage("./Image/"+theme+"CLL_Insert0.png"); else 
    if (vtx == mainGraph.getSize())mainGraph.highlight.addImage("./Image/"+theme+"CLL_InsertN.png"); else
        mainGraph.highlight.addImage("./Image/"+theme+"LL_InsertMid.png"); 
    mainGraph.highlight.setHL(1);
    
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
    
    if (vtx != mainGraph.getSize() && vtx){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(0, stt/numFrame);
            gameGlobal->runBreak();
        } 
        mainGraph.highlight.setLine(1);
        mainGraph.saveStep();
        for (int i = 1; i < vtx; ++i){
            for (int stt = 1; stt <= numFrame; ++stt){
                mainGraph.removeSearchingNode(i-1, stt/numFrame);
                gameGlobal->runBreak();
            }
            mainGraph.highlight.setLine(2);
            mainGraph.saveStep();

            for (int stt = 1; stt <= numFrame; ++stt){
                mainGraph.setSearchingNode(i, stt/numFrame);
                gameGlobal->runBreak();
            } 
            mainGraph.highlight.setLine(3);
            mainGraph.saveStep();
        }
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setFoundNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        } 
        mainGraph.highlight.setLine(4);
        mainGraph.saveStep();
    }
    if (vtx == mainGraph.getSize())mainGraph.listNode[vtx-1]->setCircle(0);
    mainGraph.makeNewNode(vtx, value);
    firstGraph = mainGraph;
}

void CLL::LetsRemove(int vtx){
    mainGraph = firstGraph; mainGraph.resetStep(); mainGraph.highlight.setHL(1);
    if (vtx == 0)mainGraph.highlight.addImage("./Image/"+theme+"CLL_Remove0.png"); else 
    if (vtx == mainGraph.getSize()-1)mainGraph.highlight.addImage("./Image/"+theme+"LL_RemoveMid.png"); else
        mainGraph.highlight.addImage("./Image/"+theme+"LL_RemoveMid.png"); 
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
    if (vtx){
        mainGraph.highlight.setLine(2);
        mainGraph.saveStep();
    }

    for (int i = 1; i < vtx; ++i){
        mainGraph.highlight.setLine(3);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i-1, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        mainGraph.highlight.setLine(4);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        } 
        mainGraph.saveStep();
    }
    mainGraph.removeNode(vtx);
    firstGraph = mainGraph;
}

void CLL::LetsUpdate(int vt, int value){
    mainGraph = firstGraph; mainGraph.resetStep();
    mainGraph.highlight.addImage("./Image/"+theme+"LL_Update.png"); mainGraph.highlight.setHL(1);

    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.setSearchingNode(0, stt/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.highlight.setLine(1);
    mainGraph.saveStep();

    for (int vtx = 1; vtx <= vt; ++vtx){
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(vtx-1, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.highlight.setLine(2);
        mainGraph.saveStep();

        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.highlight.setLine(3);
        mainGraph.saveStep();
    }
    
    mainGraph.setValue(vt, value); 
    mainGraph.highlight.setLine(4);
    mainGraph.saveStep();
    gameGlobal->runBreak();
    firstGraph = mainGraph;
}

void CLL::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    target.draw(mainGraph);
}

void CLL::getFromFile(){
    std::ifstream file("customInput.txt"); // open the file
    std::string line;
    if (file.is_open()) { // check if the file is successfuCLLy opened
        while (std::getline(file, line)) { // read the file line by line
            std::cout << line << '\n'; // print each line to the console
        }
        file.close(); // close the file
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


void CLL::checkPress(sf::Vector2f mousePos){
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
            case SEARCH:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))LetsSearch(inputBox[0]->getValue());
                }
                break;
            case INSERT:
                for (int i = 0; i < 3; ++i){
                    if (res->minButton[i]->checkPress(mousePos)){
                        if (!firstGraph.getSize() && i == 2)continue;
                        inputBox = res->minButton[i]->inputButton;
                        for (auto ii : inputBox) ii->resetValue();
                        // std::cout << "InputBox: " << inputBox.size();
                    } 
                    if (!inputBox.empty())
                        for (int j = 0; j < inputBox.size(); ++j) {
                            if (inputBox[j] == res->minButton[i]->inputButton[j]){
                                inputBox[j]->checkPress(mousePos);
                                if (i < 2 && inputBox[j]->Go->checkPress(mousePos)){
                                    if (firstGraph.getSize() == maxSize || firstGraph.checkSameNum(inputBox[j]->getValue()))break;
                                    if (i == 0)LetsInsert(0,inputBox[j]->getValue()), inputBox.clear();
                                    if (i == 1)LetsInsert(firstGraph.getSize(),inputBox[j]->getValue()), inputBox.clear();
                                }
                                if (i == 2 && j == 1 && inputBox[j]->Go->checkPress(mousePos) && firstGraph.getSize() < maxSize && firstGraph.getSize() && !firstGraph.checkSameNum(inputBox[j]->getValue()))
                                    LetsInsert(inputBox[j-1]->getValue(),inputBox[j]->getValue()), inputBox.clear();
                            } else break;
                        }
                }
                break;
            case REMOVE:
                if (res->minButton[0]->checkPress(mousePos))LetsRemove(0), inputBox.clear();
                if (res->minButton[1]->checkPress(mousePos))LetsRemove(firstGraph.getSize()-1), inputBox.clear();
                if (res->minButton[2]->checkPress(mousePos) && firstGraph.getSize() > 2){
                    inputBox = res->minButton[2]->inputButton;  
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->minButton[2]->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos) && inputBox[0]->getValue() > 0 && inputBox[0]->getValue() < firstGraph.getSize())
                        LetsRemove(inputBox[0]->getValue()), inputBox.clear();
                }
                break;
            case UPDATE:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0])
                    for (int j = 0; j < inputBox.size(); ++j) {
                        if (inputBox[j] == res->inputButton[j]){
                            inputBox[j]->checkPress(mousePos);
                            if (j == 1 && inputBox[j]->Go->checkPress(mousePos) && 
                                inputBox[j-1]->getValue() >= 0 && 
                                inputBox[j-1]->getValue() < firstGraph.getSize() &&
                                !firstGraph.checkSameNum(inputBox[j]->getValue()))
                                LetsUpdate(inputBox[j-1]->getValue(), inputBox[j]->getValue()), inputBox.clear();
                        } else break;
                    }
                break;
        }
    }
}
                    