#include <AVL.hpp>

void AVL::resetNode(std::shared_ptr <Node> res){
    if (res == nullptr)return;
    Node t = *res;
    *res = Node(19, t.getString(), ResourceManager::getFont(), textSize, backgroundColor, t.m_position, CIRCLE, 2);
    for (int i = 0; i < t.childNode.size(); ++i){
        res->childNode[i].first = t.childNode[i].first;
        if (res->childNode[i].first != nullptr)
            res->childNode[i].second = DynArrow(res->m_position, res->childNode[i].first->m_position);
    }
    res->prevNode = t.prevNode;
    res->setHeight(t.getHeight());
    for (int i = 0; i < 4; ++i)
        res->m_text_directions[i].setString(t.m_text_directions[i].getString());
    res->m_text_directions[BOT].setString("");
    // x->changeSizeNode(x->getRad() - CircleRad);
    // x->setDefaultColor();
    resetNode(res->childNode[0].first);
    resetNode(res->childNode[1].first);
}

AVL::AVL(): DataTypes(), graph(){
    BaseButton[1]->inputButton[0]->setValueLimit(std::make_shared <int> (60));
    initGraph(ResourceManager::random(5, 12));
    clearQueue();
    resetNode(graph.pHead);
    balancePosition();
    checkFunctionFast();
}

void AVL::initGraph(int n){
    // std::vector <int> t = {30,29,28,27,26};
    // for (int i : t)insert(i);
    graph.pHead = nullptr;
    for(int i = 1; i <= n; ++i){
        int k = ResourceManager::random(1, 99);
        insert(k);
        balancePosition();
        checkFunctionFast(); 
    }
}

bool checkPosition(std::shared_ptr <Node> n){
    if (n == nullptr)return 0;
    return n->checkPosition();
}

bool checkArrow(std::shared_ptr <Node> n){
    if (n == nullptr)return 0;
    return n->checkArrow();
}

void checkPositionFast(std::shared_ptr <Node> n){
    if (n == nullptr)return;
    n->checkPositionFast();
}

void checkArrowFast(std::shared_ptr <Node> n){
    if (n == nullptr)return;
    n->checkArrowFast();
}

void AVL::checkFunction(){
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

void AVL::checkFunctionFast(){
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

int AVL::getHeight(std::shared_ptr <Node> t){
    if (t == nullptr)return 0;
    return t->getHeight();
}

int AVL::getBalance(std::shared_ptr <Node> t){
    if (t == nullptr)return 0;
    return getHeight(t->childNode[0].first) - getHeight(t->childNode[1].first);
}

void AVL::leftRotate(int k, int cas){
    std::shared_ptr <Node> x = graph.pHead;
    while (x->getValue() != k){
        if (k < x->getValue())x = x->childNode[0].first; else
        if (k > x->getValue())x = x->childNode[1].first;
    }
    std::shared_ptr <Node> y = x->childNode[1].first;
    std::shared_ptr <Node> T2 = y->childNode[0].first;

    y->childNode[0].first = x;
    x->childNode[1].first = T2;
    y->prevNode = x->prevNode; 
    x->prevNode = y; 
    if (T2 != nullptr){
        T2->prevNode = x;
        x->childNode[1].second.setTail(T2->m_position); 
        y->childNode[0].second.setTail(x->m_position);
    } else {
        y->childNode[0].second = DynArrow(y->m_position, y->m_position);
        y->childNode[0].second.setTail(x->m_position);
    }
    if (y->prevNode != nullptr)
        for (int i = 0; i < y->prevNode->childNode.size(); ++i)
            if (y->prevNode->childNode[i].first == x)
                y->prevNode->childNode[i].first = y,
                y->prevNode->childNode[i].second.setTail(y->m_position);

    x->setHeight(1 + std::max(getHeight(x->childNode[0].first), getHeight(x->childNode[1].first)));
    y->setHeight(1 + std::max(getHeight(y->childNode[0].first), getHeight(y->childNode[1].first)));
    for (int i = 0; i < y->childNode.size(); ++i)
        if (y->childNode[i].first == graph.pHead){
            graph.pHead = y;
            break;
        }
    // funcQueue.push(Animation({},{},{},{[&](){
    //         graph.pHead->setArrow();
    //     }}));
    funcQueue.push(Animation({},{},{},{[&](){
            balancePosition();
        }}));
    if (!cas)funcQueue.push(Animation({},{std::bind(&AVL::checkBalanceInt, this, x->getValue())},{},{}));
        else funcQueue.push(Animation({std::bind(&AVL::rightRotate, this, y->prevNode->getValue(), 0)},{},{},{}));
}

void AVL::rightRotate(int k, int cas){
    std::shared_ptr <Node> x = graph.pHead;
    // std::cout << "value: " << k << '\n';
    while (x->getValue() != k){
        if (k < x->getValue())x = x->childNode[0].first; else
        if (k > x->getValue())x = x->childNode[1].first;
    }
    std::shared_ptr <Node> y = x->childNode[0].first;
    std::shared_ptr <Node> T2 = y->childNode[1].first;

    y->childNode[1].first = x;
    x->childNode[0].first = T2;
    y->prevNode = x->prevNode; 
    x->prevNode = y; 
    if (T2 != nullptr){
        T2->prevNode = x;
        x->childNode[0].second.setTail(T2->m_position);
        y->childNode[1].second.setTail(x->m_position);
    } else {
        y->childNode[1].second = DynArrow(y->m_position, y->m_position);
        y->childNode[1].second.setTail(x->m_position);
    }
    if (y->prevNode != nullptr)
        for (int i = 0; i < y->prevNode->childNode.size(); ++i)
            if (y->prevNode->childNode[i].first == x)
                y->prevNode->childNode[i].first = y,
                y->prevNode->childNode[i].second.setTail(y->m_position);

    x->setHeight(1 + std::max(getHeight(x->childNode[0].first), getHeight(x->childNode[1].first)));
    y->setHeight(1 + std::max(getHeight(y->childNode[0].first), getHeight(y->childNode[1].first)));
    for (int i = 0; i < y->childNode.size(); ++i)
        if (y->childNode[i].first == graph.pHead){
            graph.pHead = y;
            break;
        }
    // funcQueue.push(Animation({},{},{},{[&](){
    //         graph.pHead->setArrow();
    //     }}));
    funcQueue.push(Animation({},{},{},{[&](){
            balancePosition();
        }}));
    if (!cas)funcQueue.push(Animation({},{std::bind(&AVL::checkBalanceInt, this, x->getValue())},{},{}));
        else funcQueue.push(Animation({std::bind(&AVL::leftRotate, this, y->prevNode->getValue(), 0)},{},{},{}));
}

void AVL::checkBalance(std::shared_ptr <Node> t){
    if (t == nullptr)return;
    // std::cout << "balance: " << t->getValue() << '\n';
    int balance = getBalance(t);
    // std::cout << t << " " << t->getValue() << " " << balance << '\n';
    std::shared_ptr <Node> leftChild = t->childNode[0].first, rightChild = t->childNode[1].first;
    t->setTextBot("h = " + std::to_string(balance));
    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
    // std::cout << "t: " << (t == nullptr ? 0 : t->getValue()) 
    //             << " left: " << (leftChild == nullptr ? 0 : leftChild->getValue())
    //             << " right: " << (rightChild == nullptr ? 0 : rightChild->getValue()) << '\n';
    // std::cout << "leftHeight: " << (leftChild == nullptr ? 0 : getHeight(leftChild)) 
    //             << " rightHeight: " << (rightChild == nullptr ? 0 : getHeight(rightChild)) << '\n';
    auto bigFunc = [balance, this, leftChild, rightChild,t](){
                    std::cout << "balance: " << t->getValue() << " " << balance << "\n   " 
                            << (leftChild != nullptr ? leftChild->getValue() : 0) << " " << getBalance(leftChild) << "\n   " 
                            << (rightChild != nullptr ? rightChild->getValue() : 0) << " " << getBalance(rightChild) << '\n';
        if (balance > 1 && getBalance(leftChild) >= 0){
            auto setFunctionLambda = [t,this]() {
                rightRotate(t->getValue(), 0);
            };
            funcQueue.push(Animation({},{},{},{setFunctionLambda}));
            return;
        } else if (balance < -1 && getBalance(rightChild) <= 0){
            auto setFunctionLambda = [t,this]() {
                leftRotate(t->getValue(), 0);
            };
            funcQueue.push(Animation({},{},{},{setFunctionLambda}));
            return;
        } else if (balance > 1 && getBalance(leftChild) < 0){
            auto setFunctionLambda = [leftChild,this]() {
                leftRotate(leftChild->getValue(), 1);
            };
            funcQueue.push(Animation({},{},{},{setFunctionLambda}));
            return; 
        } else if (balance < -1 && getBalance(rightChild) > 0){
            auto setFunctionLambda = [rightChild,this]() {
                rightRotate(rightChild->getValue(), 1); 
            };
            funcQueue.push(Animation({},{},{},{setFunctionLambda}));
            return;
        } else {
            auto setFunctionLambda = [t,this]() {
                t->setHeight(1 + std::max(getHeight(t->childNode[0].first), getHeight(t->childNode[1].first)));
                // std::cout << "t: " << (t == nullptr ? 0 : t->getValue()) << '\n';
                for (int i = 0; i < t->childNode.size(); ++i)
                    if (t->childNode[i].first == graph.pHead){
                        graph.pHead = t;
                        break;
                    }
                for (int i = 1; i <= 60; ++i)
                        funcQueue.push(Animation({std::bind(&Node::removeSearching, t, i/60.f),
                                                std::bind(&Node::setTextBot, t, "")},
                                                {},{},{}));
                if (t->prevNode != nullptr)funcQueue.push(Animation({},{std::bind(&AVL::checkBalanceInt, this, t->prevNode->getValue())},{},{}));
            };
            funcQueue.push(Animation({},{},{},{setFunctionLambda}));
        }
    };
    funcQueue.push(Animation({},{},{},{bigFunc}));
}

void AVL::checkBalanceInt(int gt){
    std::shared_ptr <Node> t = graph.pHead;
    if (t == nullptr)return;    
    while (t->getValue() != gt){
        if (gt < t->getValue())t = t->childNode[0].first; else
        if (gt > t->getValue())t = t->childNode[1].first;
    }
    checkBalance(t);
}

void AVL::getList(std::shared_ptr <Node> x){
    if (x == nullptr)return;
    listNode.push_back({x->getValue(),x});
    getList(x->childNode[0].first);
    getList(x->childNode[1].first);
}

void AVL::setVerticalPosition(std::shared_ptr <Node> t, int k){
    if (t == nullptr)return;
    t->changePosition(sf::Vector2f(0.f, k));
    setVerticalPosition(t->childNode[0].first, k + 60);
    setVerticalPosition(t->childNode[1].first, k + 60);
}

void AVL::balancePosition(){
    setVerticalPosition(graph.pHead, 130);

    listNode.clear();
    getList(graph.pHead); 
    std::sort(listNode.begin(), listNode.end());
    float h = 1650.f / ((int)listNode.size() - 1);
    for (int i = 0; i < listNode.size(); ++i){
        float k = listNode[i].second->m_position.y;
        listNode[i].second->changePosition(sf::Vector2f(120 + h*i, k));
    }
    for (int i = 0; i < listNode.size(); ++i){
        std::shared_ptr <Node> x = listNode[i].second;
        // std::cout << x->getValue() << '\n';
        for (int j = 0; j < x->childNode.size(); ++j)
            if (x->childNode[j].first != nullptr){
                x->childNode[j].second.setTail(x->childNode[j].first->m_position);
                x->childNode[j].second.setHome(x->m_position);
                // std::cout << "pre pos: " << x->m_position.x << " " << x->m_position.y << 
                //             "  x pos: " << x->childNode[j].first->m_position.x << " " << x->childNode[j].first->m_position.y << '\n';
                // std::cout << "arrow pos" << x->childNode[j].second.m_home2.x << " " << x->childNode[j].second.m_home2.y << ' '
                //             << x->childNode[j].second.m_tail2.x << " " << x->childNode[j].second.m_tail2.y << "\n \n";
            }
    }
    listNode.clear();
}

std::shared_ptr <Node> AVL::newNode(int k, std::shared_ptr <Node> t){
    std::shared_ptr <Node> nod = std::make_shared <Node> (19.f, std::to_string(k), ResourceManager::getFont(), 
                        textSize, backgroundColor,(t == nullptr ? sf::Vector2f(0,0) : t->getNodePosition()),
                        CIRCLE,2);
    nod->changeSizeNode(CircleRad);
    for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::setSearching, nod, i/60.f)},{},{},{}));
    funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, nod->getRad()-CircleRad)},{},{},{}));
    nod->prevNode = t;
    nod->setHeight(1);
    // std::cout << "newNode: " << nod->prevNode << " " << t << '\n';
    return nod;
}

void getHeightAll(std::shared_ptr <Node> t){
    if (t == nullptr)return;
    std::cout << "t: " << t->getValue() << " height: " << t->getHeight() << '\n';
    getHeightAll(t->childNode[0].first);
    getHeightAll(t->childNode[1].first);
}
 
void AVL::insert(int k){
    clearQueue(); resetNode(graph.pHead); balancePosition(); checkFunctionFast(); 
    std::cout << "pHead: " << (graph.pHead == nullptr ? 0 : graph.pHead->getValue()) << " k = " << k << '\n';
    std::shared_ptr <Node> t = graph.pHead, preNode = nullptr;
    int idx = 0;
    while (true){
        // std::cout << "out " << t << " ";
        // if (t != nullptr)std::cout << '\n' << t->prevNode << '\n';
        if (t == nullptr){
            if (graph.pHead == nullptr) graph.pHead = newNode(k, preNode), t = graph.pHead; 
                else {
                    t = newNode(k, preNode);
                    preNode->childNode[idx].first = t;
                    preNode->childNode[idx].second = DynArrow(preNode->getNodePosition(), t->getNodePosition());
                }
            auto setPositionLambda = [t,this]() {
                balancePosition();
            };
            funcQueue.push(Animation({},{},{},{setPositionLambda}));
            break;
        }
        // std::cout << t->getValue() << '\n';
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
        if (k < t->getValue()){
            preNode = t; t = t->childNode[0].first; idx = 0;
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, preNode, i/60.f),
                                            std::bind(&DynArrow::setPartialColor, preNode->childNode[idx].second, i/60.f)},{},{},{}));
        } else 
        if (k > t->getValue()){
            preNode = t; t = t->childNode[1].first; idx = 1;
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, preNode, i/60.f),
                                            std::bind(&DynArrow::setPartialColor, preNode->childNode[idx].second, i/60.f)},{},{},{}));
        } else {
            int rr = ResourceManager::StringtoInt(t->m_text_directions[RIGHT].getString());
            if (!rr)rr = 1; ++rr; 
            funcQueue.push(Animation({std::bind(&Node::setTextRight, t, std::to_string(rr))},
                                    {},{},{})); 
            break;
        }
        // for (int i = 1; i <= 60; ++i)
        //         funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
    }
    // std::cout << 123456 << '\n';
    auto setPositionLambda = [t,this]() {
        checkBalance(t);
    };
    funcQueue.push(Animation({},{},{},{setPositionLambda}));
    // getHeightAll(graph.pHead);
    // balancePosition();
}

void AVL::fromfile(){
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
        insert(ResourceManager::StringtoInt(i));
        checkFunctionFast(); 
    }
    clearQueue();
    resetNode(graph.pHead);
    balancePosition();
    checkFunctionFast();
}

void AVL::search(int k){
    clearQueue(); resetNode(graph.pHead); balancePosition(); checkFunctionFast(); 
    std::cout << "pHead: " << (graph.pHead == nullptr ? 0 : graph.pHead->getValue()) << " k = " << k << '\n';
    std::shared_ptr <Node> t = graph.pHead, preNode = nullptr;
    int idx = 0;
    while (true){
        // std::cout << "out " << t << " ";
        // if (t != nullptr)std::cout << '\n' << t->prevNode << '\n';
        if (t == nullptr){
            break;
        }
        // std::cout << t->getValue() << '\n';
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
        if (k < t->getValue()){
            preNode = t; t = t->childNode[0].first; idx = 0;
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, preNode, i/60.f),
                                            std::bind(&DynArrow::setPartialColor, preNode->childNode[idx].second, i/60.f)},{},{},{}));
        } else 
        if (k > t->getValue()){
            preNode = t; t = t->childNode[1].first; idx = 1;
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, preNode, i/60.f),
                                            std::bind(&DynArrow::setPartialColor, preNode->childNode[idx].second, i/60.f)},{},{},{}));
        } else break;
    }
}

void AVL::remove(int k){
    clearQueue(); resetNode(graph.pHead); balancePosition(); checkFunctionFast(); 
    std::cout << "pHead: " << (graph.pHead == nullptr ? 0 : graph.pHead->getValue()) << " k = " << k << '\n';
    std::shared_ptr <Node> t = graph.pHead, preNode = nullptr;
    int idx = 0;
    while (true){
        // std::cout << "out " << t << " ";
        // if (t != nullptr)std::cout << '\n' << t->prevNode << '\n';
        if (t == nullptr)break;
        // std::cout << t->getValue() << '\n';
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
        if (k < t->getValue()){
            preNode = t; t = t->childNode[0].first; idx = 0;
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, preNode, i/60.f),
                                            std::bind(&DynArrow::setPartialColor, preNode->childNode[idx].second, i/60.f)},{},{},{}));
        } else 
        if (k > t->getValue()){
            preNode = t; t = t->childNode[1].first; idx = 1;
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, preNode, i/60.f),
                                            std::bind(&DynArrow::setPartialColor, preNode->childNode[idx].second, i/60.f)},{},{},{}));
        } else {
            int rr = ResourceManager::StringtoInt(t->m_text_directions[RIGHT].getString());
            if (rr){
                if (rr == 2)
                    funcQueue.push(Animation({std::bind(&Node::setTextRight, t, "")},
                                    {},{},{})); 
                else
                    funcQueue.push(Animation({std::bind(&Node::setTextRight, t, std::to_string(rr-1))},
                                    {},{},{})); 
            } else {
                std::shared_ptr <Node> rightMin = t->childNode[1].first, startCheckNode;
                //tim rightMin
                if (rightMin != nullptr){
                    for (int i = 1; i <= 60; ++i)
                        funcQueue.push(Animation({std::bind(&DynArrow::setPartialColor, t->childNode[1].second, i/60.f)},{},{},{}));                    
                    for (int i = 1; i <= 60; ++i)
                        funcQueue.push(Animation({std::bind(&Node::setSearching, rightMin, i/60.f)},{},{},{}));                    
                    while (rightMin->childNode[0].first != nullptr){
                        for (int i = 1; i <= 60; ++i)
                            funcQueue.push(Animation({std::bind(&Node::removeSearching, rightMin, i/60.f),
                                                std::bind(&DynArrow::setPartialColor, rightMin->childNode[0].second, i/60.f)},{},{},{}));
                        rightMin = rightMin->childNode[0].first;
                        for (int i = 1; i <= 60; ++i)
                            funcQueue.push(Animation({std::bind(&Node::setSearching, rightMin, i/60.f)},{},{},{})); 
                    }
                    startCheckNode = rightMin->prevNode;
                } else {
                    startCheckNode = t->prevNode;
                }
                //xoa node t
                for (int i = 1; i <= 60; ++i)
                    funcQueue.push(Animation({std::bind(&Node::changeSizeNode, t, CircleRad/60.f)},{},{},{}));
                //noi cac arrow
                auto setFunction = [t,rightMin,startCheckNode, this]{
                    for (int i = 0; i < t->childNode.size(); ++i)
                        if (t->childNode[i].first != nullptr){
                            t->childNode[i].second.setTail(t->m_position);
                        }
                    if (rightMin != nullptr){
                        if (rightMin->prevNode != t){ // connect parent cua node moi voi node con cua node moi
                            for (int i = 0; i < rightMin->prevNode->childNode.size(); ++i)
                                if (rightMin->prevNode->childNode[i].first == rightMin){
                                    rightMin->prevNode->childNode[i].first = rightMin->childNode[1].first;
                                    if (rightMin->childNode[1].first != nullptr)
                                        rightMin->prevNode->childNode[i].second.setTail(rightMin->childNode[1].first->m_position),
                                        rightMin->childNode[1].first->prevNode = rightMin->prevNode;
                                    else rightMin->prevNode->childNode[i].second.setTail(rightMin->prevNode->m_position);
                                    break;
                                }
                            auto setPositionLambda = [startCheckNode,this]() {
                                balancePosition();
                            };
                            funcQueue.push(Animation({},{},{},{setPositionLambda}));
                            auto setPosition2Lambda = [startCheckNode,this]() {
                                checkBalance(startCheckNode);
                            };
                            funcQueue.push(Animation({},{},{},{setPosition2Lambda}));
                        } else {
                            auto setPositionLambda = [rightMin,this]() {
                                balancePosition();
                            };
                            funcQueue.push(Animation({},{},{},{setPositionLambda}));
                            auto setPosition2Lambda = [rightMin,this]() {
                                checkBalance(rightMin);
                            };
                            funcQueue.push(Animation({},{},{},{setPosition2Lambda}));
                        }

                        if (t->prevNode != nullptr) // connect parent cua t voi node moi
                            for (int i = 0; i < t->prevNode->childNode.size(); ++i)
                                if (t->prevNode->childNode[i].first == t){
                                    t->prevNode->childNode[i].first = rightMin;
                                    t->prevNode->childNode[i].second.setTail(rightMin->m_position);
                                    break;
                        }
                        rightMin->prevNode = t->prevNode;
                        
                        //connect node con cua t thanh node con cua node moi
                        for (int i = 0; i < t->childNode.size(); ++i)if (t->childNode[i].first != rightMin){
                                if (t->childNode[i].first != nullptr){
                                    if (rightMin->childNode[i].first != nullptr)
                                        rightMin->childNode[i].second.setTail(t->childNode[i].first->m_position);
                                    else {
                                        rightMin->childNode[i].second = DynArrow(rightMin->m_position, rightMin->m_position);
                                        rightMin->childNode[i].second.setTail(t->childNode[i].first->m_position);
                                    }
                                    t->childNode[i].first->prevNode = rightMin;
                                } else {
                                    if (rightMin->childNode[i].first != nullptr)
                                        rightMin->childNode[i].second.setTail(rightMin->m_position);
                                }
                                rightMin->childNode[i].first = t->childNode[i].first;
                            }
                        if (graph.pHead == t) graph.pHead = rightMin;
                            
                    } else {
                        for (int i = 0; i < t->childNode.size(); ++i)
                            if (t->childNode[i].first != nullptr){
                                t->childNode[i].first->prevNode = t->prevNode;
                            }

                        if (t->prevNode != nullptr)
                            for (int i = 0; i < t->prevNode->childNode.size(); ++i)
                                if (t->prevNode->childNode[i].first == t){
                                    t->prevNode->childNode[i].first = t->childNode[0].first;
                                    if (t->childNode[0].first != nullptr)
                                        t->prevNode->childNode[i].second.setTail(t->childNode[0].first->m_position);
                                    else t->prevNode->childNode[i].second.setTail(t->prevNode->m_position);
                                    break;
                        }

                        if (graph.pHead == t) graph.pHead = t->childNode[0].first;

                        auto setPositionLambda = [t,this]() {
                            balancePosition();
                        };
                        funcQueue.push(Animation({},{},{},{setPositionLambda}));
                        auto setPosition2Lambda = [t,this]() {
                            checkBalance(t->prevNode);
                        };
                        funcQueue.push(Animation({},{},{},{setPosition2Lambda}));
                    }
                };
                funcQueue.push(Animation({},{},{},{setFunction}));
            }
            break;
        }
        // for (int i = 1; i <= 60; ++i)
        //         funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
    }
    // std::cout << 123456 << '\n';
}

void AVL::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    DataTypes::draw(target, states);
    target.draw(graph, states);
}

void AVL::checkPress(sf::Vector2f mousePos){
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
                        balancePosition(); checkFunctionFast();
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
