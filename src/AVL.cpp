#include <AVL.hpp>

void resetSize(std::shared_ptr <Node> x){
    x->changeSizeNode(x->getRad()-CircleRad);
}

AVL::AVL(): DataTypes(), graph(){
    initGraph();
    clearQueue();
    // resetSize(graph.pHead);
    firstGraph = graph;
}

void AVL::initGraph(){
    int n = ResourceManager::random(5, 12);
    for(int i = 1; i <= n; ++i){
        int k = ResourceManager::random(1, 99);
        std::cout << "pHead: " << graph.pHead << " k: " << k << '\n';
        insert(k);
    }
}

void AVL::checkFunction(){
    DataTypes::checkFunction();
    if (funcQueue.empty())return;
    // std::cout << funcQueue.size() << '\n';
    Animation ani = funcQueue.front();
    funcQueue.pop();
    ani.go();
}

int AVL::getBalance(std::shared_ptr <Node> t){
    if (t == nullptr)return 0;
    return t->childNode[0].first->getHeight() - t->childNode[1].first->getHeight();
}

std::shared_ptr <Node> AVL::leftRotate(std::shared_ptr <Node> x){
    std::shared_ptr <Node> y = x->childNode[1].first;
    std::shared_ptr <Node> T2 = y->childNode[0].first;
    y->childNode[0].first = x;
    x->childNode[1].first = T2;
    if (T2 != nullptr)T2->prevNode = x; 
    y->prevNode = x->prevNode; x->prevNode = y;
    x->setHeight(1 + std::max(x->childNode[0].first->getHeight(), x->childNode[1].first->getHeight()));
    y->setHeight(1 + std::max(y->childNode[0].first->getHeight(), y->childNode[1].first->getHeight()));
    return y;
}

std::shared_ptr <Node> AVL::rightRotate(std::shared_ptr <Node> x){
    std::shared_ptr <Node> y = x->childNode[0].first;
    std::shared_ptr <Node> T2 = y->childNode[1].first;
    y->childNode[1].first = x;
    x->childNode[0].first = T2;
    if (T2 != nullptr)T2->prevNode = x;
    y->prevNode = x->prevNode; x->prevNode = y;
    x->setHeight(1 + std::max(x->childNode[0].first->getHeight(), x->childNode[1].first->getHeight()));
    y->setHeight(1 + std::max(y->childNode[0].first->getHeight(), y->childNode[1].first->getHeight()));
    return y;
}

void AVL::getList(std::shared_ptr <Node> x){
    if (x == nullptr)return;
    listNode.push_back({x->getValue(),x});
    getList(x->childNode[0].first);
    getList(x->childNode[1].first);
}

void AVL::setVerticalPosition(std::shared_ptr <Node> t, int k){
    if (t == nullptr)return;
    t->setPosition(sf::Vector2f(0.f, k));
    setVerticalPosition(t->childNode[0].first, k + 40);
    setVerticalPosition(t->childNode[1].first, k + 40);
}

void AVL::balancePosition(){
    setVerticalPosition(graph.pHead, 200);
    graph.pHead->setPosition(sf::Vector2f(0.f, 200));
    listNode.clear();
    getList(graph.pHead);
    std::sort(listNode.begin(), listNode.end());
    for (int i = 0; i < listNode.size(); ++i){
        float k = listNode[i].second->getNodePosition().y;
        // std::cout << k << '\n';
        listNode[i].second->setPosition(sf::Vector2f(120 + 50*i, k));
    }
    listNode.clear();
}

Node AVL::newNode(int k, std::shared_ptr <Node> t){
    Node nod = Node(19.f, std::to_string(k), ResourceManager::getFont(), 
                        textSize, backgroundColor,sf::Vector2f(0,0),CIRCLE,2);
    funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, CircleRad)},{},{},{}));
    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, -CircleRad/60.f)},{},{},{}));
    funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, nod.getRad()-CircleRad)},{},{},{}));
    nod.prevNode = t;
    return nod;
}

void AVL::insert(int k){
    clearQueue();

    std::shared_ptr <Node> t = graph.pHead, preNode = nullptr;
    int idx = 0;
    while (true){
        if (t == nullptr){
            if (graph.pHead == nullptr) graph.pHead = std::make_shared <Node> (newNode(k, preNode)); 
                else t = std::make_shared <Node> (newNode(k, preNode)), preNode->childNode[idx].first = t; 
            // auto insertNode = [this, k, &preNode, &t, &idx]() {
            //     if (graph.pHead == nullptr) {
            //         graph.pHead = std::make_shared<Node>(newNode(k, preNode));
            //     } else {
            //         t = std::make_shared<Node>(newNode(k, preNode));
            //         preNode->childNode[idx].first = t;
            //     }
            // };

            // funcQueue.push(Animation({}, {}, {}, {insertNode}));
            std::cout << t << " " << preNode << '\n';
            break;
        }
        std::cout << t->getValue() << '\n';
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
        if (k < t->getValue()){
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, t, i/60.f)},{},{},{}));
            preNode = t; t = t->childNode[0].first; idx = 0;
        } else 
        if (k > t->getValue()){
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::removeSearching, t, i/60.f)},{},{},{}));
            preNode = t; t = t->childNode[1].first; idx = 1;
        } else break;
        for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&Node::setSearching, t, i/60.f)},{},{},{}));
    }
    // while (t != nullptr){
    //     t->setHeight(1 + std::max(t->childNode[0].first->getHeight(), t->childNode[1].first->getHeight()));
    //     int balance = getBalance(t);
    //     std::shared_ptr <Node> leftChild = t->childNode[0].first, rightChild = t->childNode[1].first;
    //     if (balance > 1 && getBalance(leftChild) > 0){
    //         t = rightRotate(t);
    //     } else if (balance < -1 && getBalance(rightChild) < 0){
    //         t = leftRotate(t);
    //     } else if (balance > 1 && getBalance(leftChild) < 0){
    //         t->childNode[0].first = leftRotate(leftChild);
    //         t = rightRotate(t);
    //     } else if (balance < -1 && getBalance(rightChild) > 0){
    //         t->childNode[1].first = rightRotate(rightChild);
    //         t = leftRotate(t);
    //     } 
    //     t = t->prevNode;
    // }
    balancePosition();
    // firstGraph = graph;
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
    clearQueue();
    graph.init(list.size(), list); firstGraph = graph;
}

void AVL::search(int k){

}

void AVL::remove(int k){

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
                        graph.init();
                        firstGraph = graph;
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
