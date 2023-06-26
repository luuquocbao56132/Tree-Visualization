#include <DLL.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

DLL::DLL():DataTypes(DOUBLYLINKEDLIST)
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

void DLL::LetsSearch(int X){
    mainGraph = firstGraph; mainGraph.resetStep();
    mainGraph.highlight.addImage("./Image/"+theme+"DLL_Search.png"); mainGraph.highlight.setHL(1);
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

void DLL::LetsInsert(int vtx, int value){
    mainGraph = firstGraph; mainGraph.resetStep();
    if (mainGraph.getSize() == maxSize)return;
    if (vtx == 0)mainGraph.highlight.addImage("./Image/"+theme+"DLL_Insert0.png"); else 
    if (vtx == mainGraph.getSize())mainGraph.highlight.addImage("./Image/"+theme+"DLL_InsertN.png"); else
        mainGraph.highlight.addImage("./Image/"+theme+"DLL_InsertMid.png"); 
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
    mainGraph.makeNewNode(vtx, value);
    firstGraph = mainGraph;
}

void DLL::LetsRemove(int vtx){
    mainGraph = firstGraph; mainGraph.resetStep(); mainGraph.highlight.setHL(1);
    if (vtx == 0)mainGraph.highlight.addImage("./Image/"+theme+"DLL_Remove0.png"); else 
    if (vtx == mainGraph.getSize()-1)mainGraph.highlight.addImage("./Image/"+theme+"DLL_RemoveN.png"); else
        mainGraph.highlight.addImage("./Image/"+theme+"DLL_RemoveMid.png"); 
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
    if (mainGraph.getSize() == 0){
        mainGraph.highlight.setLine(1);
        return;
    }

    if (vtx == mainGraph.getSize()-1){
        mainGraph.highlight.setLine(2);
        mainGraph.listNode[vtx]->setTextBot("tmp");
        for (int i = 1; i <= numFrame; ++i){
            mainGraph.setDelNode(vtx,i/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        mainGraph.highlight.setLine(3);
        if (vtx)mainGraph.listNode[vtx-1]->setTextBot("tail");
        mainGraph.saveStep(); Sleep(1000*(numFrame/110));

        mainGraph.highlight.setLine(4);
        if (vtx){
            std::shared_ptr <Node> res = std::make_shared <Node> (CircleRad, std::to_string(vtx), ResourceManager::getFont(), 
                                    textSize, NewNodeColor,sf::Vector2f(mainGraph.listNode[vtx]->getNodePosition()),1);
            mainGraph.listNode[vtx-1]->nextNode = res;
            for (int i = 1; i <= numFrame; ++i){
                res->setPosition(ResourceManager::changePosition(mainGraph.listNode[vtx]->getNodePosition(), mainGraph.listNode[vtx-1]->getNodePosition(), i/numFrame));
                mainGraph.listNode[vtx-1]->setArrow();
                gameGlobal->runBreak();
            }
        }
        mainGraph.saveStep();
        
        mainGraph.highlight.setLine(5);
        int nn = mainGraph.getSize() - 1;
        int hieu = abs(mainGraph.leftBound - (850 - (100*nn - arrowLength ) / 2));
        mainGraph.leftBound = 850 - (100*nn - arrowLength ) / 2;
        LinkedList <sf::Vector2f> startPos, endPos;
        for (int i = 0; i < vtx; ++i){
            startPos.push_back(mainGraph.listNode[i]->getNodePosition());
            endPos.push_back(sf::Vector2f(mainGraph.listNode[i]->getNodePosition().x + hieu, mainGraph.listNode[i]->getNodePosition().y));
        }
        for (int i = vtx+1; i < mainGraph.getSize(); ++i){
            startPos.push_back(mainGraph.listNode[i]->getNodePosition());
            endPos.push_back(sf::Vector2f(mainGraph.listNode[i]->getNodePosition().x - hieu, mainGraph.listNode[i]->getNodePosition().y));
        }

        mainGraph.newNode = mainGraph.listNode[vtx];
        for (int i = vtx; i < nn; ++i)mainGraph.listNode[i] = mainGraph.listNode[i+1]; mainGraph.listNode[nn] = nullptr;
        mainGraph.setSize(mainGraph.getSize()-1); mainGraph.setNode();
        for (int i = 1; i < numFrame; ++i){
            for (int j = 0; j < mainGraph.getSize(); ++j)
                mainGraph.listNode[j]->setPosition(ResourceManager::changePosition(startPos[j], endPos[j], ((float)i)/numFrame));
            mainGraph.newNode->changeSizeNode(CircleRad/numFrame);        
            mainGraph.setNode();
            gameGlobal->runBreak();
        }
        mainGraph.setNumber.erase(mainGraph.newNode->getValue());
        mainGraph.newNode = nullptr;
        gameGlobal->runBreak();
        mainGraph.saveStep();
    } else {

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
    if (!vtx)mainGraph.highlight.setLine(5), mainGraph.saveStep();
    }
    firstGraph = mainGraph;
}

void DLL::LetsUpdate(int vt, int value){
    mainGraph = firstGraph; mainGraph.resetStep();
    mainGraph.highlight.addImage("./Image/"+theme+"DLL_Update.png"); mainGraph.highlight.setHL(1);

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

void DLL::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    target.draw(mainGraph);
}

void DLL::getFromFile(){
    std::ifstream file("customInput.txt"); // open the file
    std::string line;
    if (file.is_open()) { // check if the file is successfuDLLy opened
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


void DLL::checkPress(sf::Vector2f mousePos){
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
                    