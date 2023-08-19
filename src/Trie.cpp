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

Trie::Trie(): DataTypes(), graph(), leftLimitBound(50){
    for (int i = 2; i <= 4; ++i){
        auto x = BaseButton[i];
        BaseButton[i]->inputButton.clear();
        x->inputButton.push_back(std::make_shared <InputBox> (sf::Vector2f(x->getPosition().x + x->getSize().x + 40, 
                                                                            x->getPosition().y), 
                                                                        inputButtonSize,"x = ",1,1));
    }
    initGraph(ResourceManager::random(5, 50));
    clearQueue();
    resetNode(graph.pHead);
    balancePosition(graph.pHead, 0, leftLimitBound);
    checkFunctionFast();
}

void Trie::initGraph(int n){
    // std::vector <int> t = {30,29,28,27,26};
    // for (int i : t)insert(i);
    graph.pHead = std::make_shared <Node> (19.f, "Head", ResourceManager::getFont(), 
                        textSize, backgroundColor,sf::Vector2f(1900/2,135),CIRCLE,0);
    graph.pHead->setHeight(0);
    for(int i = 1; i <= n; ++i){
        int length = ResourceManager::random(1, 9);
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
    for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::setSearching, nod, i/60.f)},{},{},{}));
    funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, nod->getRad()-CircleRad)},{},{},{}));
    nod->prevNode = t;
    nod->setHeight(0);
    // std::cout << "newNode: " << nod->prevNode << " " << t << '\n';
    return nod;
}

void Trie::insertNode(std::string k, std::shared_ptr <Node> nod){
    if (k == ""){
        auto funcLambda = [this,nod](){
            nod->setHeight(1);
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::setFound, nod, i/60.f)},{},{},{}));
        };
        funcQueue.push(Animation({},{},{},{funcLambda}));
        return;
    }
    std::string x = k.substr(0,1); bool flag = 0;
    // std::cout << k << " x12: " << x  << '\n'; Sleep(1000);
    k.erase(0,1);
    for (int i = 0; i < nod->childNode.size(); ++i)
        if (nod->childNode[i].first != nullptr && nod->childNode[i].first->getString() == x){
            for (int j = 1; j <= 60; ++j)
                funcQueue.push(Animation({std::bind(&DynArrow::setPartialColor, nod->childNode[i].second, j/60.f),
                                        std::bind(&Node::setSearching, nod, j/60.f)},{},{},{}));
            flag = 1; nod = nod->childNode[i].first; break;
        }
    if (!flag){
        auto neww = newNode(x, nod);
        // std::cout << neww->getString() << '\n'; Sleep(500);
        nod->childNode.push_back({neww, DynArrow(nod->m_position, nod->m_position)});
        balancePosition(graph.pHead, 0, leftLimitBound); 
        nod->childNode.back().second = DynArrow(nod->m_position, nod->m_position);
        funcQueue.push(Animation({std::bind(&DynArrow::setTail, nod->childNode.back().second, nod->childNode.back().first->m_position)},{},{},{}));
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&DynArrow::setPartialColor, nod->childNode.back().second, i/60.f),
                                    std::bind(&Node::setSearching, neww, i/60.f)},{},{},{}));
        nod = neww;
    }
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Node::removeSearching, nod, i/60.f)},{},{},{}));
    auto funcQ = [this, k, nod](){
        insertNode(k, nod);
    };
    funcQueue.push(Animation({},{},{},{funcQ}));
}
 
void Trie::insert(std::string k){
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

void Trie::fromfile(){
    std::ifstream file("customInput.txt"); // open the file
    std::string line;
    if (file.is_open()) { // check if the file is successfully opened
        while (std::getline(file, line)) { // read the file line by line
            std::cout << line << '\n'; // print each line to the console
        }
        file.close(); // close the file
    }
    else {
        std::cerr << "Unable to open file\n";
    }

    std::string c;
    std::vector <std::string> list;
    for (int i = 0; i < line.size(); ++i){
        if (line[i] >= '0' && line[i] <= '9')c += line[i]; else
        if (line[i] == ';' || line[i] == ','){
            if (c.empty())return;
            while (c[0] == '0')c.erase(0);
            if (c.size() > 3)return;
            if (c.size() == 0)c = "0";
            list.push_back(c); c = "";
        } else return;
    }

    clearQueue(); graph.pHead = nullptr;
    for(std::string i : list){
        insert(i);
        checkFunctionFast(); 
    }
    clearQueue();
    resetNode(graph.pHead);
    balancePosition(graph.pHead,0, leftLimitBound);
    checkFunctionFast();
}

void Trie::search(std::string k){
    clearQueue(); resetNode(graph.pHead); balancePosition(graph.pHead,0, leftLimitBound); checkFunctionFast(); 
    std::cout << "pHead: " << (graph.pHead == nullptr ? 0 : graph.pHead->getValue()) << " k = " << k << '\n';
    std::shared_ptr <Node> t = graph.pHead, preNode = nullptr;
    int idx = 0;
}

void Trie::remove(std::string k){
    clearQueue(); resetNode(graph.pHead); balancePosition(graph.pHead,0, leftLimitBound); checkFunctionFast(); 
    std::cout << "pHead: " << (graph.pHead == nullptr ? 0 : graph.pHead->getValue()) << " k = " << k << '\n';
    std::shared_ptr <Node> t = graph.pHead, preNode = nullptr;
    
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
