#include <DynArr.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

DynArr::DynArr():DataTypes(ARRAY)
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
            std::shared_ptr<Button> Access (new Button(buttonPosition + sf::Vector2f(buttonPosition.x, buttonRange.y*6),
                            buttonSize, "Access", ResourceManager::getFont(), 20,1));

            //BaseButton.push_back(std::make_shared<Button>(Create));
            BaseButton.push_back(Create);
            BaseButton.push_back(Search);
            BaseButton.push_back(Insert);
            BaseButton.push_back(Remove);
            BaseButton.push_back(Update);
            BaseButton.push_back(Access);

            Search->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Search->getPosition().x + Search->getSize().x + 40, 
                                                                            Search->getPosition().y), 
                                                                        inputButtonSize,"v = ",1));
            Access->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(Access->getPosition().x + Access->getSize().x + 40, 
                                                                            Access->getPosition().y), 
                                                                        inputButtonSize,"i = ",1));
            Access->inputButton[0]->setValueLimit(mainGraph.n);

            Create->createMinButton({"Empty (Allocate)","Random","Random Fixed Size","Custom"},
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
            LetsCreate(-1); //setTheme();
            firstGraph = mainGraph;
        }

void DynArr::resetAll(){
    DataTypes::resetAll();
}
    
void DynArr::LetsCreate(int t){
    if (t == -1)mainGraph.init(); else mainGraph.init(t);
}

void DynArr::LetsSearch(int X){
    mainGraph = firstGraph; mainGraph.resetStep(); mainGraph.isListNew = 0;
    mainGraph.highlight.addImage("./Image/"+theme+"Arr_Search.png"); mainGraph.highlight.setHL(1);
    if (mainGraph.getSize() == 0){
        mainGraph.highlight.setLine(1);
        return;
    }

    // std::cout << "List rad of search graph: \n";
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    int flag = 100;

    for (int vtx = 0; vtx < mainGraph.getSize(); ++vtx){
        mainGraph.highlight.setLine(2);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        mainGraph.highlight.setLine(3);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(vtx, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        if (mainGraph.getValue(vtx) == X){
            flag = vtx; 
            mainGraph.highlight.setLine(4);
            for (int stt = 1; stt <= numFrame; ++stt){
                mainGraph.setFoundNode(vtx, stt/numFrame);
                gameGlobal->runBreak();
            }
            mainGraph.saveStep();
            return;
        }
    }

    mainGraph.highlight.setLine(5); mainGraph.saveStep();
}

void DynArr::LetsInsert(int vtx, int value){
    mainGraph = firstGraph;
    std::cout << vtx << " " << mainGraph.getSize() << '\n';
    if (mainGraph.getSize() == maxSize)return;
    if (vtx > mainGraph.getSize())return;

    mainGraph.resetStep(); mainGraph.isListNew = 0;
    mainGraph.highlight.addImage("./Image/"+theme+"DynArr_Insert.png"); mainGraph.highlight.setHL(1);
    
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    int leftBound = 850 - (100*(mainGraph.getSize()+1) - arrowLength ) / 2;
    mainGraph.isListNew = 1; mainGraph.listNew.clear();
    for (int i = 0; i <= mainGraph.getSize(); ++i){
        mainGraph.listNew.push_back(std::make_shared <Node> (19.f, "", ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(leftBound + 10 + 100*i, 350.f),typeGraph));
    }
    for (int i = 0; i <= mainGraph.getSize(); ++i)
        mainGraph.listNew[i]->setTextTop(std::to_string(i)),
        mainGraph.listNew[i]->changeSizeNode(CircleRad / numFrame * (numFrame-1));
    mainGraph.listNew[vtx]->setNodeColor(BlurNodeColor);

    mainGraph.highlight.setLine(1);
    for (int stt = 2; stt <= numFrame; ++stt)
        for (int i = 0; i <= mainGraph.getSize(); ++i)mainGraph.listNew[i]->changeSizeNode(-CircleRad/numFrame);
    mainGraph.saveStep();
    
    for (int i = 0; i < vtx; ++i){
        mainGraph.highlight.setLine(2);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        mainGraph.highlight.setLine(3);
        mainGraph.listNew[i]->setText(std::to_string(mainGraph.getValue(i)));
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i, stt/numFrame);
            mainGraph.listNew[i]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, FoundNodeColor, stt/numFrame));
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();
    }

    for (int i = vtx; i < mainGraph.getSize(); ++i){
        mainGraph.highlight.setLine(4);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        mainGraph.highlight.setLine(5);
        mainGraph.listNew[i+1]->setText(std::to_string(mainGraph.getValue(i)));
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i, stt/numFrame);
            mainGraph.listNew[i+1]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, FoundNodeColor, stt/numFrame));
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();
    }

    mainGraph.highlight.setLine(6);
    for (int stt = 1; stt <= numFrame; ++stt){
        for (int i = 0; i < mainGraph.getSize(); ++i)
            mainGraph.listNode[i]->changeSizeNode(CircleRad/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.listNode = mainGraph.listNew;
    *mainGraph.n = mainGraph.listNew.size(); mainGraph.isListNew = 0;
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
    gameGlobal->runBreak();
    mainGraph.saveStep();

    mainGraph.highlight.setLine(7);
    LinkedList <sf::Vector2f> startPos;
    for (int i = 0; i < mainGraph.listNew.size(); ++i)startPos.push_back(mainGraph.listNew[i]->getNodePosition());
    mainGraph.listNode[vtx]->setText("");
    for (int stt = 1; stt <= numFrame; ++stt){
        for (int i = 0; i < mainGraph.listNew.size(); ++i){
            mainGraph.listNode[i]->setPosition(ResourceManager::changePosition(startPos[i], sf::Vector2f(startPos[i].x, 250), stt/numFrame));
            if (i != vtx){
                mainGraph.listNode[i]->setNodeColor(ResourceManager::changeColor(FoundNodeColor, FirstNodeColor, stt/numFrame));
                mainGraph.listNode[i]->setTextColor(ResourceManager::changeColor(sf::Color::White, sf::Color::Black, stt/numFrame));
            } else {
                mainGraph.listNew[vtx]->setNodeColor(ResourceManager::changeColor(BlurNodeColor, FirstNodeColor, stt/numFrame));
                mainGraph.listNew[vtx]->setOutlineColor(ResourceManager::changeColor(BlurNodeColor, sf::Color::Black, stt/numFrame));
                // mainGraph.listNew[vtx]->setTextColor(ResourceManager::changeColor(sf::Color::Black, sf::Color::White, stt/numFrame));
            }
        }

        gameGlobal->runBreak();
    }
    mainGraph.saveStep();

    mainGraph.highlight.setLine(8);
    mainGraph.setValue(vtx, value);
    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.listNew[vtx]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, FoundNodeColor, stt/numFrame));
        mainGraph.listNew[vtx]->setOutlineColor(ResourceManager::changeColor(FirstNodeColor, FoundNodeColor, stt/numFrame));
        mainGraph.listNew[vtx]->setTextColor(ResourceManager::changeColor(sf::Color::Black, sf::Color::White, stt/numFrame));
        gameGlobal->runBreak();
    }
    mainGraph.saveStep();

    firstGraph = mainGraph;
}

void DynArr::LetsRemove(int vtx){
    mainGraph = firstGraph;
    if (vtx >= mainGraph.getSize())return;
    mainGraph.resetStep(); mainGraph.isListNew = 0;
    mainGraph.highlight.addImage("./Image/"+theme+"DynArr_Remove.png"); mainGraph.highlight.setHL(1);

    if (mainGraph.getSize() == 0){
        mainGraph.highlight.setLine(1);
        gameGlobal->runBreak();
        mainGraph.saveStep();
        return;
    }

    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    int leftBound = 850 - (100*(mainGraph.getSize()-1) - arrowLength ) / 2;
    mainGraph.isListNew = 1; mainGraph.listNew.clear();
    for (int i = 0; i < mainGraph.getSize()-1; ++i){
        mainGraph.listNew.push_back(std::make_shared <Node> (19.f, "", ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(leftBound + 10 + 100*i, 350.f),typeGraph));
    }
    for (int i = 0; i < mainGraph.listNew.size(); ++i)
        mainGraph.listNew[i]->setTextTop(std::to_string(i)),
        mainGraph.listNew[i]->changeSizeNode(CircleRad / numFrame * (numFrame-1));

    mainGraph.highlight.setLine(2);
    for (int stt = 2; stt <= numFrame; ++stt)
        for (int i = 0; i < mainGraph.listNew.size(); ++i)mainGraph.listNew[i]->changeSizeNode(-CircleRad/numFrame);
    mainGraph.saveStep();
    
    for (int i = 0; i < vtx; ++i){
        mainGraph.highlight.setLine(3);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        mainGraph.highlight.setLine(4);
        mainGraph.listNew[i]->setText(std::to_string(mainGraph.getValue(i)));
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i, stt/numFrame);
            mainGraph.listNew[i]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, FoundNodeColor, stt/numFrame));
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();
    }

    for (int i = vtx+1; i < mainGraph.getSize(); ++i){
        mainGraph.highlight.setLine(5);
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.setSearchingNode(i, stt/numFrame);
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();

        mainGraph.highlight.setLine(6);
        mainGraph.listNew[i-1]->setText(std::to_string(mainGraph.getValue(i)));
        for (int stt = 1; stt <= numFrame; ++stt){
            mainGraph.removeSearchingNode(i, stt/numFrame);
            mainGraph.listNew[i-1]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, FoundNodeColor, stt/numFrame));
            mainGraph.listNew[i-1]->setTextColor(ResourceManager::changeColor(sf::Color::Black, sf::Color::White, stt/numFrame));
            gameGlobal->runBreak();
        }
        mainGraph.saveStep();
    }

    mainGraph.highlight.setLine(7);
    for (int stt = 1; stt <= numFrame; ++stt){
        for (int i = 0; i < mainGraph.getSize(); ++i)
            mainGraph.listNode[i]->changeSizeNode(CircleRad/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.listNode = mainGraph.listNew;
    *mainGraph.n = mainGraph.listNew.size(); mainGraph.isListNew = 0;
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);
    gameGlobal->runBreak();
    mainGraph.saveStep();

    mainGraph.highlight.setLine(8);
    LinkedList <sf::Vector2f> startPos;
    for (int i = 0; i < mainGraph.listNew.size(); ++i)startPos.push_back(mainGraph.listNew[i]->getNodePosition());
    for (int stt = 1; stt <= numFrame; ++stt){
        for (int i = 0; i < mainGraph.listNew.size(); ++i){
            mainGraph.listNode[i]->setPosition(ResourceManager::changePosition(startPos[i], sf::Vector2f(startPos[i].x, 250), stt/numFrame));
            mainGraph.listNode[i]->setNodeColor(ResourceManager::changeColor(FoundNodeColor, FirstNodeColor, stt/numFrame));
            mainGraph.listNode[i]->setTextColor(ResourceManager::changeColor(sf::Color::White, sf::Color::Black, stt/numFrame));
        }
        gameGlobal->runBreak();
    }
    mainGraph.saveStep();

    firstGraph = mainGraph;
}

void DynArr::LetsUpdate(int vt, int value){
    mainGraph = firstGraph; mainGraph.resetStep(); mainGraph.isListNew = 0;
    mainGraph.highlight.addImage("./Image/"+theme+"Arr_Update.png"); mainGraph.highlight.setHL(1);

    // std::cout << "List rad of search graph: \n";
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    mainGraph.setValue(vt, value); 
    mainGraph.highlight.setLine(1);
    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.setSearchingNode(vt, stt/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.saveStep();
    gameGlobal->runBreak();
    firstGraph = mainGraph;
}

void DynArr::LetsAccess(int vt){
    mainGraph = firstGraph;
    if (vt >= mainGraph.getSize())return;
    mainGraph.resetStep(); mainGraph.isListNew = 0;
    mainGraph.highlight.addImage("./Image/"+theme+"Arr_Access.png"); mainGraph.highlight.setHL(1);

    // std::cout << "List rad of search graph: \n";
    for (int i = 0; i < mainGraph.getSize(); ++i)
        mainGraph.listNode[i]->changeSizeNode(mainGraph.listNode[i]->getRad() - CircleRad);

    mainGraph.highlight.setLine(1);
    for (int stt = 1; stt <= numFrame; ++stt){
        mainGraph.setSearchingNode(vt, stt/numFrame);
        gameGlobal->runBreak();
    }
    mainGraph.saveStep();
    gameGlobal->runBreak();
    firstGraph = mainGraph;
}

void DynArr::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    target.draw(mainGraph);
}

void DynArr::getFromFile(){
    std::ifstream file("customInput.txt"); // open the file
    std::string line;
    if (file.is_open()) { // check if the file is successfuDynArry opened
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

void DynArr::checkPress(sf::Vector2f mousePos){
    DataTypes::checkPress(mousePos);
    if (DataTypes::buttonState != -1){
        auto res = BaseButton[buttonState];
        switch (buttonState){
            case CREATE:
                if (res->minButton[0]->checkPress(mousePos))LetsCreate(0), inputBox.clear(), firstGraph = mainGraph;
                if (res->minButton[1]->checkPress(mousePos))LetsCreate(-1), inputBox.clear(), firstGraph = mainGraph;
                if (res->minButton[2]->checkPress(mousePos)){
                    inputBox = res->minButton[2]->inputButton;  
                    for (auto i : inputBox)i->resetValue();
                }
                if (res->minButton[3]->checkPress(mousePos))getFromFile();
                if (!inputBox.empty() && inputBox[0] == res->minButton[2]->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))
                        LetsCreate(inputBox[0]->getValue()), inputBox.clear(), firstGraph = mainGraph;
                }
                break;
            case SEARCH:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))LetsSearch(inputBox[0]->getValue()), inputBox.clear();
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
                                    if (firstGraph.checkSameNum(inputBox[j]->getValue()))break;
                                    if (i == 0)LetsInsert(0,inputBox[j]->getValue()), inputBox.clear();
                                    if (i == 1)LetsInsert(firstGraph.getSize(),inputBox[j]->getValue()), inputBox.clear();
                                }
                                if (i == 2 && j == 1 && inputBox[j]->Go->checkPress(mousePos) && !firstGraph.checkSameNum(inputBox[j]->getValue()))
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
                            if (j == 1 && inputBox[j]->Go->checkPress(mousePos)){
                                if (inputBox[j-1]->getValue() >= 0 && 
                                    inputBox[j-1]->getValue() < firstGraph.getSize() &&
                                    !firstGraph.checkSameNum(inputBox[j]->getValue()))
                                        LetsUpdate(inputBox[j-1]->getValue(), inputBox[j]->getValue());
                                inputBox.clear();
                            }
                        } else break;
                    }
                break;
            case ACCESS:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos) && inputBox[0]->getValue() < firstGraph.getSize())
                        LetsAccess(inputBox[0]->getValue()), inputBox.clear();
                }
                break;
        }
    }
}
                    