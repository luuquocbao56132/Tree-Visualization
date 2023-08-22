#include <Twothree.hpp>

void Twothree::resetNode(std::shared_ptr <TwothreeNode> res){
    if (res == nullptr)return;
    // std::cout << res->getString() << '\n';
    TwothreeNode t = *res;
    std::vector <std::string> listVal;
    for (auto i : t.listValue)listVal.push_back(i.getString());
    *res = TwothreeNode(listVal, t.m_position);
    res->childNode = t.childNode;
    res->prevNode = t.prevNode;
    for (int i = 0; i < res->childNode.size(); ++i)
        resetNode(res->childNode[i].first);
}

Twothree::Twothree(): DataTypes(){
    BaseButton[1]->inputButton[0]->setValueLimit(std::make_shared <int> (20));
    initGraph(ResourceManager::random(10, 40));
    clearQueue();
    resetNode(root);
    balancePosition(root, 0, 60);
    checkFunctionFast();
}

void Twothree::initGraph(int n){
    // std::vector <int> t = {30,29,28,27,26};
    // for (int i : t)insert(i);
    root = nullptr;
    for(int i = 1; i <= n; ++i){
        int k = ResourceManager::random(1, 99);
        insert(k);
        balancePosition(root, 0, 60);
        checkFunctionFast(); 
    }
}

bool Twothree::checkPosition(std::shared_ptr <TwothreeNode> n){
    if (n == nullptr)return 0;
    return n->checkPosition();
}

bool Twothree::checkArrow(std::shared_ptr <TwothreeNode> n){
    if (n == nullptr)return 0;
    return n->checkArrow();
}

void Twothree::checkPositionFast(std::shared_ptr <TwothreeNode> n){
    if (n == nullptr)return;
    n->checkPositionFast();
}

void Twothree::checkArrowFast(std::shared_ptr <TwothreeNode> n){
    if (n == nullptr)return;
    n->checkArrowFast();
}

void Twothree::checkFunction(){
    DataTypes::checkFunction();
    if (checkPosition(root)){
        checkArrow(root); 
        return;
    } 
    // std::cout << 1234567 << '\n';
    if (checkArrow(root))return;
    if (funcQueue.empty())return;
    // std::cout << funcQueue.size() << '\n';
    Animation ani = funcQueue.front();
    funcQueue.pop();
    ani.go();
}

void Twothree::checkFunctionFast(){
    DataTypes::checkFunctionFast();
    checkPositionFast(root);
    checkArrowFast(root);
    while (!funcQueue.empty()){
        Animation ani = funcQueue.front();
        funcQueue.pop();
        ani.go();
    }
    checkPositionFast(root);
}

int Twothree::getHeight(std::shared_ptr <TwothreeNode> t){
    if (t == nullptr)return 0;
    return t->getHeight();
}

bool cmp(std::pair < std::shared_ptr <TwothreeNode>, DynArrow > a, std::pair < std::shared_ptr <TwothreeNode>, DynArrow > b){
    return ResourceManager::StringtoInt(a.first->listValue[0].getString()) < ResourceManager::StringtoInt(b.first->listValue[0].getString());
}

void Twothree::sortNode(std::shared_ptr <TwothreeNode> t){
    if (t == nullptr)return;
    if (!t->childNode.empty()) {
        std::sort(t->childNode.begin(), t->childNode.end(), cmp);
    }
}

int Twothree::balancePosition(std::shared_ptr <TwothreeNode> nod, int height, int widthSum){
    if (nod == nullptr)return 0;
    int width = 0;
    sortNode(nod);
    
    for (int i = 0; i < nod->childNode.size(); ++i){
        width += balancePosition(nod->childNode[i].first, height+1, widthSum + width);
        nod->childNode[i].second.setTail(nod->childNode[i].first->m_position);
    }
    if (width == 0)width = nod->m_rectangle.getSize().x + 30;

    nod->changePosition(sf::Vector2f(widthSum + width/2, 130.f + 60*height));
    for (int i = 0; i < nod->childNode.size(); ++i){
        nod->childNode[i].second.setHome(nod->m_position);
    }
    return width;
}

std::shared_ptr <TwothreeNode> Twothree::newNode(std::vector <std::string> k, std::shared_ptr <TwothreeNode> t, sf::Vector2f position){
    std::shared_ptr <TwothreeNode> nod = std::make_shared <TwothreeNode> (k, position);
    nod->prevNode = t;
    // std::cout << "newNode: " << nod->prevNode << " " << t << '\n';
    return nod;
}

void Twothree::insertNode(std::shared_ptr <TwothreeNode> t, std::shared_ptr <TwothreeNode> preNode, int idx, int val, bool isSplit){
    if (t == nullptr){
        auto funcQ = [this, val](){
            std::vector <std::string> listVal;
            listVal.push_back(std::to_string(val));
            root = newNode(listVal, nullptr, sf::Vector2f(0, 0));
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&TwothreeNode::setFound, root, i/60.f)},{},{},{}));
            balancePosition(root, 0, 60);
        };
        funcQueue.push(Animation({},{},{},{funcQ})); return;
    }
    
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, t, i/60.f)},{},{},{}));
    
    if (t->listValue.size() == 3 && !isSplit){
        auto funcQ = [this, t, val, preNode, idx](){
            auto tt = t;
        if (preNode == nullptr){
            auto re = *t;
            sf::Vector2f pos = t->m_position;

            tt = newNode({re.listValue[1].getString()}, re.prevNode, pos);
            tt->childNode.push_back({newNode({re.listValue[0].getString()}, tt, pos), DynArrow(pos, pos)});
            tt->childNode.push_back({newNode({re.listValue[2].getString()}, tt, pos), DynArrow(pos, pos)});
            
            if (re.childNode.size() > 0){
                auto res = tt->childNode[0].first;
                res->childNode.push_back({re.childNode[0].first, DynArrow(res->m_position, re.childNode[0].first->m_position)});
                res->childNode.push_back({re.childNode[1].first, DynArrow(res->m_position, re.childNode[1].first->m_position)});
                for (auto i : res->childNode)i.first->prevNode = res;

                res = tt->childNode[1].first;
                res->childNode.push_back({re.childNode[2].first, DynArrow(res->m_position, re.childNode[2].first->m_position)});
                res->childNode.push_back({re.childNode[3].first, DynArrow(res->m_position, re.childNode[3].first->m_position)});
                for (auto i : res->childNode)i.first->prevNode = res;
            }
            root = tt;
        } else {
            auto re = *preNode;
            int v = ResourceManager::StringtoInt(t->listValue[1].getString());
            sf::Vector2f pos = preNode->m_position;
            std::vector <std::string> listVal; listVal.clear();
            bool flag = 0;
            
            for (auto i : preNode->listValue){
                if (!flag && ResourceManager::StringtoInt(i.getString()) > v){
                    listVal.push_back(std::to_string(v));
                    flag = 1;
                } 
                listVal.push_back(i.getString());
            }
            if (!flag)listVal.push_back(std::to_string(v));

            *preNode = *newNode(listVal, re.prevNode, re.getNodePosition());
            
            for (auto i : re.childNode){
                if (i.first == t){
                    preNode->childNode.push_back({newNode({t->listValue[0].getString()}, preNode, pos), DynArrow(pos, pos)});
                    auto res = preNode->childNode.back().first;
                    res->prevNode = preNode;
                    if (t->childNode.size() > 0){
                        res->childNode.push_back({t->childNode[0].first, DynArrow(pos, t->childNode[0].first->m_position)});
                        res->childNode.push_back({t->childNode[1].first, DynArrow(pos, t->childNode[1].first->m_position)});
                        for (auto i : res->childNode)i.first->prevNode = res;
                    }
                    
                    preNode->childNode.push_back({newNode({t->listValue[2].getString()}, preNode, pos), DynArrow(pos, pos)});
                    res = preNode->childNode.back().first;
                    res->prevNode = preNode;
                    if (t->childNode.size() > 0){
                        res->childNode.push_back({t->childNode[2].first, DynArrow(pos, t->childNode[2].first->m_position)});
                        res->childNode.push_back({t->childNode[3].first, DynArrow(pos, t->childNode[3].first->m_position)});
                        for (auto i : res->childNode)i.first->prevNode = res;
                    }
                } else preNode->childNode.push_back(i);
            }
            tt = preNode;
        }
        
        balancePosition(root, 0, 60);

        
        if (preNode != nullptr)insertNode(tt, preNode->prevNode, idx, val, 1);
            else insertNode(tt, nullptr, idx, val, 1);
        };
        funcQueue.push(Animation({},{},{},{funcQ})); 
        return;
    }
    
    if (t->childNode.empty()){
        auto funcQ = [this, t, val](){
            std::vector <std::string> listVal;
            bool flag = 0;
            for (auto i : t->listValue){
                if (!flag && ResourceManager::StringtoInt(i.getString()) > val){
                    listVal.push_back(std::to_string(val));
                    flag = 1;
                } 
                listVal.push_back(i.getString());
            }
            if (!flag)listVal.push_back(std::to_string(val));
            for (auto i : listVal)std::cout << ResourceManager::StringtoInt(i) << " "; std::cout << '\n';

            *t = *newNode(listVal, t->prevNode, t->m_position);
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&TwothreeNode::setFound, t, i/60.f)},{},{},{}));
            balancePosition(root, 0, 60);
        };
        funcQueue.push(Animation({},{},{},{funcQ})); return;
    }

    for (int i = 0; i < t->listValue.size(); ++i)
    if (val < ResourceManager::StringtoInt(t->listValue[i].getString())){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
        insertNode(t->childNode[i].first, t, i, val, 0);
        return;
    }
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
    insertNode(t->childNode.back().first, t, t->childNode.size()-1, val, 0);
}
 
void Twothree::insert(int k){
    checkFunctionFast(); clearQueue(); resetNode(root); balancePosition(root, 0, 60); checkFunctionFast(); 
    listInsert.push_back(k);
    std::cout << " k = " << k << '\n';
    std::shared_ptr <TwothreeNode> t = root, preNode = nullptr;
    
    // for (int i = 1; i <= 60; ++i)
    //     funcQueue.push(Animation({std::bind(&Node::setSearching, listNode[t], i/60.f)},{},{},{}));

    auto funcLambda = [this,k](){
        insertNode(root, nullptr, 0, k, 0);
    };
    funcQueue.push(Animation({},{},{},{funcLambda}));
}

void clearChild(std::shared_ptr <TwothreeNode> nod){
    if (nod == nullptr)return;
    for (int i = 0; i < nod->childNode.size(); ++i)
        clearChild(nod->childNode[i].first);
    nod->childNode.clear();
}

void Twothree::fromfile(){
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

    clearQueue(); root = nullptr; listInsert.clear();
    for(std::string i : list){
        insert(ResourceManager::StringtoInt(i));
        checkFunctionFast(); 
    }
    clearQueue();
    resetNode(root);
    balancePosition(root, 0, 60);
    checkFunctionFast();
}

void Twothree::search(int k){
    checkFunctionFast(); clearQueue(); resetNode(root); balancePosition(root, 0, 60); checkFunctionFast(); 
    std::cout << " k = " << k << '\n';
    std::shared_ptr <TwothreeNode> t = root, preNode = nullptr;
    bool flag = 0;
    if (t == nullptr)return;

    while (true) {
        flag = 0;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, t, i/60.f)},{},{},{}));
        
        for (int i = 0; i < t->listValue.size(); ++i){
            if (k == ResourceManager::StringtoInt(t->listValue[i].getString())){
                funcQueue.push(Animation({std::bind(&TwothreeNode::setDefault, t)},{},{},{}));
                for (int j = 1; j <= 60; ++j)
                    funcQueue.push(Animation({std::bind(&TwothreeNode::setFound, t, j/60.f)},{},{},{}));
                auto func = [this,t,i]() {
                    t->listValue[i].setFillColor(sf::Color::Yellow);
                };
                funcQueue.push(Animation({},{},{},{func}));
                flag = 1; return;
            }
        }
        
        for (int i = 0; i < t->listValue.size(); ++i)
            if (k < ResourceManager::StringtoInt(t->listValue[i].getString())){
                for (int i = 1; i <= 60; ++i)
                    funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
                t = t->childNode[i].first;  flag = 1; break;
            }

        if (flag)continue;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
        if (t->childNode.empty())break;
        t = t->childNode.back().first;
    }

    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
}

void Twothree::removingNode(std::shared_ptr <TwothreeNode> nod){
    for (int j = 1; j <= 60; ++j)
        funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, nod, j/60.f)},{},{},{}));
    
}

void Twothree::remove(int k){
    return;
}

void Twothree::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    DataTypes::draw(target, states);
    target.draw(*root, states);
}

void Twothree::checkPress(sf::Vector2f mousePos){
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
                        clearQueue(); resetNode(root);
                        balancePosition(root, 0, 60); checkFunctionFast();
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
                    if (inputBox[0]->Go->checkPress(mousePos))insert(inputBox[0]->getValue());
                }
                break;
            case REMOVE:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))remove(inputBox[0]->getValue());
                }
                break;
            case SEARCH:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))search(inputBox[0]->getValue());
                }
                break;
        }
    }
}
