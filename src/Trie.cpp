#include <Trie.hpp>

void Trie::resetNode(std::shared_ptr <Node> res){
    if (res == nullptr)return;
    // std::cout << res->getString() << '\n';
    Node t = *res;
    *res = Node(19, t.getString(), ResourceManager::getFont(), textSize, backgroundColor, t.m_position, CIRCLE, t.childNode.size());
    for (int i = 0; i < (int)t.childNode.size(); ++i){
        res->childNode[i].first = t.childNode[i].first;
        if (res->childNode[i].first != nullptr)
            res->childNode[i].second = DynArrow(res->m_position, res->childNode[i].first->m_position);
    }
    res->prevNode = t.prevNode;
    res->setHeight(t.getHeight());
    if (res->getHeight() == 1)res->setFound(1);
    for (int i = 0; i < res->childNode.size(); ++i)
        resetNode(res->childNode[i].first);
}

Trie::Trie(): DataTypes(), graph(), leftLimitBound(60){
    for (int i = 2; i <= 4; ++i){
        auto x = BaseButton[i];
        BaseButton[i]->inputButton.clear();
        BaseButton[i]->setPosition(BaseButton[i]->getPosition() + sf::Vector2f(100*(i-2), 0));
        x->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(x->getPosition().x + x->getSize().x + 40, 
                                                                            x->getPosition().y), 
                                                                        sf::Vector2f(inputButtonSize.x*2,inputButtonSize.y),"x = ",1,1));
    }
    BaseButton[1]->inputButton[0]->setValueLimit(std::make_shared <int> (10));
    initGraph(ResourceManager::random(5, 10));
    clearQueue();
    resetNode(graph.pHead);
    balancePosition(graph.pHead, 0, leftLimitBound);
    checkFunctionFast();
}

void Trie::initGraph(int n){
    // std::vector <int> t = {30,29,28,27,26};
    // for (int i : t)insert(i);
    graph.pHead = std::make_shared <Node> (17.f, "", ResourceManager::getFont(), 
                        textSize, backgroundColor,sf::Vector2f(1900/2,135),CIRCLE,0);
    graph.pHead->setHeight(0);
    for(int i = 1; i <= n; ++i){
        int length = ResourceManager::random(1, 8);
        std::string s = "";
        for (int j = 1; j <= length; ++j)
            s += (char)ResourceManager::random((int)('A'), (int)('Z'));
        insert(s);
        balancePosition(graph.pHead, 0, leftLimitBound);
        checkFunctionFast(); 
    }
}

bool Trie::checkPosition(std::shared_ptr <Node> n){
    if (n == nullptr)return 0;
    return n->checkPosition();
}

bool Trie::checkArrow(std::shared_ptr <Node> n){
    if (n == nullptr)return 0;
    return n->checkArrow();
}

void Trie::checkPositionFast(std::shared_ptr <Node> n){
    if (n == nullptr)return;
    n->checkPositionFast();
}

void Trie::checkArrowFast(std::shared_ptr <Node> n){
    if (n == nullptr)return;
    n->checkArrowFast();
}

void Trie::checkFunction(){
    DataTypes::checkFunction();
    if (checkPosition(graph.pHead)){
        checkArrow(graph.pHead); 
        return;
    } 
    // std::cout << 1234567 << '\n';
    if (checkArrow(graph.pHead))return;
    if (funcQueue.empty())return;
    // std::cout << funcQueue.size() << '\n';
    Animation ani = funcQueue.front();
    funcQueue.pop();
    ani.go();
}

void Trie::checkFunctionFast(){
    DataTypes::checkFunctionFast();
    checkPositionFast(graph.pHead);
    checkArrowFast(graph.pHead);
    while (!funcQueue.empty()){
        Animation ani = funcQueue.front();
        funcQueue.pop();
        ani.go();
    }
    checkPositionFast(graph.pHead);
}

int Trie::getHeight(std::shared_ptr <Node> t){
    if (t == nullptr)return 0;
    return t->getHeight();
}

bool cmp(std::pair < std::shared_ptr <Node>, DynArrow > a, std::pair < std::shared_ptr <Node>, DynArrow > b){
    return a.first->getString() < b.first->getString();
}

void Trie::sortNode(std::shared_ptr <Node> t){
    if (t == nullptr)return;
    if (!t->childNode.empty()) {
        // std::cout << t->getString() << '\n';
        std::sort(t->childNode.begin(), t->childNode.end(),cmp);
    }
}

int Trie::balancePosition(std::shared_ptr <Node> nod, int height, int widthSum){
    int width = 0;
    sortNode(nod);
    // 
    for (int i = 0; i < nod->childNode.size(); ++i){
        width += balancePosition(nod->childNode[i].first, height+1, widthSum + width);
        nod->childNode[i].second.setTail(nod->childNode[i].first->m_position);
    }
    if (width == 0)width = 50;
    nod->changePosition(sf::Vector2f(widthSum + width/2, 130.f + 60*height));
    for (int i = 0; i < nod->childNode.size(); ++i){
        nod->childNode[i].second.setHome(nod->m_position);
    }
    return width;
}

std::shared_ptr <Node> Trie::newNode(std::string k, std::shared_ptr <Node> t){
    std::shared_ptr <Node> nod = std::make_shared <Node> (19.f, k, ResourceManager::getFont(), 
                        textSize, backgroundColor,(t == nullptr ? sf::Vector2f(0,0) : t->getNodePosition()),
                        CIRCLE,0);
    nod->changeSizeNode(CircleRad);
    // for (int i = 1; i <= 60; ++i)
    //             funcQueue.push(Animation({std::bind(&Node::setSearching, nod, i/60.f)},{},{},{}));
    funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, nod->getRad()-CircleRad)},{},{},{}));
    nod->prevNode = t;
    nod->setHeight(0);
    // std::cout << "newNode: " << nod->prevNode << " " << t << '\n';
    return nod;
}

void Trie::insertNode(std::string k, std::shared_ptr <Node> nod){
    for (int j = 1; j <= 60; ++j)
        funcQueue.push(Animation({std::bind(&Node::setSearching, nod, j/60.f)},{},{},{}));
    if (k == ""){
        auto funcLambda = [this,nod](){
            nod->setHeight(1);
            funcQueue.push(Animation({},{},{},{std::bind(&Node::setDefault, nod)}));
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::setFound, nod, i/60.f)},{},{},{}));
        };
        funcQueue.push(Animation({},{},{},{funcLambda}));
        return;
    }
    std::string x = k.substr(0,1); k.erase(0,1); bool flag = 0;
    // std::cout << k << " x12: " << x  << '\n'; Sleep(1000);
    for (int i = 0; i < nod->childNode.size(); ++i)
        if (nod->childNode[i].first != nullptr && nod->childNode[i].first->getString() == x){
            for (int j = 1; j <= 60; ++j)
                funcQueue.push(Animation({std::bind(&DynArrow::setPartialColor, nod->childNode[i].second, j/60.f),
                                        std::bind(&Node::removeSearching, nod, j/60.f)},{},{},{}));
            flag = 1; nod = nod->childNode[i].first; break;
        }
    if (!flag){
        auto neww = newNode(x, nod);
        // std::cout << neww->getString() << '\n'; Sleep(500);
        nod->childNode.push_back({neww, DynArrow(nod->m_position, nod->m_position)});
        auto setPositionLambda = [this]() {
            balancePosition(graph.pHead, 0, leftLimitBound); 
        };
        funcQueue.push(Animation({},{},{},{setPositionLambda}));
        funcQueue.push(Animation({std::bind(&DynArrow::setTail, nod->childNode.back().second, nod->childNode.back().first->m_position)},{},{},{}));
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&DynArrow::setPartialColor, nod->childNode.back().second, i/60.f),
                                    std::bind(&Node::removeSearching, nod, i/60.f)},{},{},{}));
        nod = neww;
    }
    auto funcQ = [this, k, nod](){
        insertNode(k, nod);
    };
    funcQueue.push(Animation({},{},{},{funcQ}));
}
 
void Trie::insert(std::string k){
    checkFunctionFast(); 
    if (k == "")return;
    clearQueue(); 
    resetNode(graph.pHead); 
    balancePosition(graph.pHead, 0, leftLimitBound); 
    checkFunctionFast(); 
    std::cout << " k = " << k << '\n';
    int idx = 0;
    auto funcQ = [this, k](){
        insertNode(k, graph.pHead);
    };
    funcQueue.push(Animation({},{},{},{funcQ}));
}

void clearChild(std::shared_ptr <Node> nod){
    if (nod == nullptr)return;
    for (int i = 0; i < nod->childNode.size(); ++i)
        clearChild(nod->childNode[i].first);
    nod->childNode.clear();
}

void Trie::fromfile(){
    std::ifstream file("customInput.txt"); // open the file
    std::vector <std::string> lineVector;
    std::string line;
    if (file.is_open()) { // check if the file is successfully opened
        while (std::getline(file, line)) { // read the file line by line
            std::cout << line << '\n'; // print each line to the console
            for (int i = 0; i < (int)line.size(); ++i)
                if (line[i] == ' ' || line[i] == '\t' || line[i] == ';')line.erase(i,1), --i;
            lineVector.push_back(line);
        }
        file.close(); // close the file
    }
    else {
        std::cerr << "Unable to open file\n";
    }

    clearQueue(); clearChild(graph.pHead);
    for (std::string i : lineVector){
        insert(i);
        checkFunctionFast(); 
    }
    clearQueue();
    resetNode(graph.pHead);
    balancePosition(graph.pHead,0, leftLimitBound);
    checkFunctionFast();
}

void Trie::search(std::string k){
    checkFunctionFast();  clearQueue(); resetNode(graph.pHead); balancePosition(graph.pHead,0, leftLimitBound); checkFunctionFast(); 
    std::cout << " k = " << k << '\n';
    std::shared_ptr <Node> t = graph.pHead;
    
    while (k != ""){
        for (int j = 1; j <= 60; ++j)
            funcQueue.push(Animation({std::bind(&Node::setSearching, t, j/60.f)},{},{},{}));
        std::string x = k.substr(0,1); k.erase(0,1); bool flag = 0;
        for (int i = 0; i < t->childNode.size(); ++i)
            if (t->childNode[i].first->getString() == x){
                flag = 1; 
                for (int j = 1; j <= 60; ++j)
                    funcQueue.push(Animation({std::bind(&DynArrow::setPartialColor, t->childNode[i].second, j/60.f),
                                        std::bind(&Node::removeSearching, t, j/60.f)},{},{},{}));
                t = t->childNode[i].first; break;
            }
        if (flag)continue;
        for (int j = 1; j <= 60; ++j)
            funcQueue.push(Animation({std::bind(&Node::removeSearching, t, j/60.f)},{},{},{}));
        return;
    }
    if (t->getHeight() == 0){
        for (int j = 1; j <= 60; ++j)
            funcQueue.push(Animation({std::bind(&Node::removeSearching, t, j/60.f)},{},{},{}));
        return;
    }
}

void Trie::removingNode(std::shared_ptr <Node> nod){
    for (int j = 1; j <= 60; ++j)
        funcQueue.push(Animation({std::bind(&Node::setSearching, nod, j/60.f)},{},{},{}));
    if (nod == graph.pHead || nod->getHeight() == 1 || !nod->childNode.empty()){
        for (int j = 1; j <= 60; ++j)
            funcQueue.push(Animation({std::bind(&Node::removeSearching, nod, j/60.f)},{},{},{}));
        auto funcc = [this](){
            resetNode(graph.pHead);
        };
        funcQueue.push(Animation({},{},{},{funcc}));
        return;
    }

    std::cout << "removingNode: " << nod->getString() << '\n';

    auto funcLambda = [this,nod](){
        int idx = 0;
        for (int i = 0; i < (int)nod->prevNode->childNode.size(); ++i)
            if (nod->prevNode->childNode[i].first == nod){
                idx = i;
                funcQueue.push(Animation({std::bind(&DynArrow::setTail, nod->prevNode->childNode[i].second,
                                        nod->prevNode->m_position)},{},{},{}));
                break;
            }
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, CircleRad/60.f)},{},{},{}));
        auto funcc = [this,nod,idx](){           
            nod->prevNode->childNode.erase(nod->prevNode->childNode.begin() + idx);
            balancePosition(graph.pHead, 0, leftLimitBound);
            removingNode(nod->prevNode);
        };
        funcQueue.push(Animation({},{},{},{funcc}));
    };
    funcQueue.push(Animation({},{},{},{funcLambda}));
}

void Trie::remove(std::string k){
    checkFunctionFast(); clearQueue(); resetNode(graph.pHead); balancePosition(graph.pHead,0, leftLimitBound); checkFunctionFast(); 
    std::cout << " k = " << k << '\n';
    std::shared_ptr <Node> t = graph.pHead;
    
    while (k != ""){
        for (int j = 1; j <= 60; ++j)
            funcQueue.push(Animation({std::bind(&Node::setSearching, t, j/60.f)},{},{},{})); 
        std::string x = k.substr(0,1); bool flag = 0;
        for (int i = 0; i < t->childNode.size(); ++i)
            if (t->childNode[i].first->getString() == x){
                flag = 1; 
                for (int j = 1; j <= 60; ++j)
                    funcQueue.push(Animation({std::bind(&DynArrow::setPartialColor, t->childNode[i].second, j/60.f),
                                        std::bind(&Node::removeSearching, t, j/60.f)},{},{},{}));
                t = t->childNode[i].first; 
                k.erase(0,1); break;
            }
        for (int j = 1; j <= 60; ++j)
            funcQueue.push(Animation({std::bind(&Node::removeSearching, t, j/60.f)},{},{},{}));
        if (flag)continue;
        return;
    }
    funcQueue.push(Animation({std::bind(&Node::setDefault, t)},{},{},{}));
    for (int j = 1; j <= 60; ++j)
        funcQueue.push(Animation({std::bind(&Node::setSearching, t, j/60.f)},{},{},{}));

    if (t->getHeight() == 0){
        for (int j = 1; j <= 60; ++j)
            funcQueue.push(Animation({std::bind(&Node::removeSearching, t, j/60.f)},{},{},{}));
        return;
    }

    auto funcLambda = [this,t](){
        t->setHeight(0);
        funcQueue.push(Animation({},{},{},{std::bind(&Node::setDefault, t)}));
        removingNode(t);
    };
    funcQueue.push(Animation({},{},{},{funcLambda}));
}

void Trie::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    DataTypes::draw(target, states);
    target.draw(graph, states);
}

void Trie::checkPress(sf::Vector2f mousePos){
    DataTypes::checkPress(mousePos);
    if (DataTypes::buttonState != -1){
        auto res = BaseButton[buttonState];
        switch (buttonState){
            case FROMFILE:
                fromfile();
                break;
            case RANDOM:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos)){
                        clearQueue();
                        initGraph(inputBox[0]->getValue());
                        clearQueue(); resetNode(graph.pHead);
                        balancePosition(graph.pHead,0, leftLimitBound); checkFunctionFast();
                    }
                }
                break;
            case INSERT:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))insert(inputBox[0]->getString());
                }
                break;
            case REMOVE:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))remove(inputBox[0]->getString());
                }
                break;
            case SEARCH:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))search(inputBox[0]->getString());
                }
                break;
        }
    }
}
