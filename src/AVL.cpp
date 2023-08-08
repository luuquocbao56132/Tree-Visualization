#include <AVL.hpp>

AVL::AVL(): DataTypes(), graph(){
    initGraph();
    firstGraph = graph;
}

std::shared_ptr <Node> AVL::newNode(int k, std::shared_ptr <Node> t){
    std::shared_ptr nod = std::make_shared <Node> (19.f, std::to_string(k), ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(0,0),CIRCLE,2);
    nod->prevNode = t;
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

void AVL::insertNode(int k){
    std::shared_ptr <Node> t = graph.pHead, preNode = nullptr;
    while (true){
        if (t == nullptr){t = newNode(k, preNode); break;}
        if (k < t->getValue())preNode = t, t = t->childNode[0].first;
        if (k >= t->getValue())preNode = t, t = t->childNode[1].first;
        t->setHeight(1 + std::max(t->childNode[0].first->getHeight(), t->childNode[1].first->getHeight()));
    }
    while (t != nullptr){
        t->setHeight(1 + std::max(t->childNode[0].first->getHeight(), t->childNode[1].first->getHeight()));
        int balance = getBalance(t);
        std::shared_ptr <Node> leftChild = t->childNode[0].first, rightChild = t->childNode[1].first;
        if (balance > 1 && getBalance(leftChild) > 0){
            t = rightRotate(t);
        } else if (balance < -1 && getBalance(rightChild) < 0){
            t = leftRotate(t);
        } else if (balance > 1 && getBalance(leftChild) < 0){
            t->childNode[0].first = leftRotate(leftChild);
            t = rightRotate(t);
        } else if (balance < -1 && getBalance(rightChild) > 0){
            t->childNode[1].first = rightRotate(rightChild);
            t = leftRotate(t);
        } 
        t = t->prevNode;
    }
}

void AVL::initGraph(){
    int n = ResourceManager::random(5, 12);
    for(int i = 1; i <= n; ++i){
        int k = ResourceManager::random(1, 999);
        insertNode(k);
    }
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
