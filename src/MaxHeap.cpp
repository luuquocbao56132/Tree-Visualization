#include <MaxHeap.hpp>

sf::Vector2f getPosI(int i){
    int pos = i - (1 << lg2[i]);
    float x = 120.f + 1650.f / (1 << lg2[i]) / 2 +  1650.f / (1 << lg2[i]) * pos;
    float y = 130 + 70 * lg2[i];
    return sf::Vector2f(x,y);
}

void MaxHeap::resetNode(){
    for (int j = 1; j <= numValue; ++j){
        std::shared_ptr <Node> res = listNode[j];
        Node t = *res;
        *res = Node(19, t.getString(), ResourceManager::getFont(), textSize, backgroundColor, getPosI(j), CIRCLE, 0);
        for (int i = 0; i <= 1; ++i)if (j*2+i <= numValue){
            std::shared_ptr <Node> tmp = listNode[j*2+i];
            if (!i)listArrow[j].first = DynArrow(res->m_position, tmp->m_position);
                else listArrow[j].second = DynArrow(res->m_position, tmp->m_position);
        }
        for (int i = 0; i < 4; ++i)
            res->m_text_directions[i].setString(t.m_text_directions[i].getString());
        res->setTextBot(std::to_string(j));
    }
}

MaxHeap::MaxHeap(): DataTypes(), numValue(0){
    BaseButton[1]->inputButton[0]->setValueLimit(std::make_shared <int> (63));
    BaseButton.back()->inputButton.clear();
    initGraph(ResourceManager::random(5, 50));
    clearQueue();
    resetNode();
    balancePosition();
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "")},{}));
    checkFunctionFast();
}

void MaxHeap::initGraph(int n){
    // std::vector <int> t = {30,29,28,27,26};
    // for (int i : t)insert(i);
    listNode.clear(); listArrow.clear(); numValue = 0;
    listArrow.push_back({DynArrow(getPosI(1), getPosI(1)), DynArrow(getPosI(1),getPosI(1))});
    for (int i = 1; i <= 300; ++i){
        listNode.push_back(nullptr);
        listArrow.push_back({DynArrow(getPosI(i), getPosI(i)), DynArrow(getPosI(i),getPosI(i))});
    }
    // std::cout << "sizelist " << listNode.size() << '\n'; Sleep(2000);
    for(int i = 1; i <= n; ++i){
        int k = ResourceManager::random(1, 99);
        insert(k);
        balancePosition();
        checkFunctionFast(); 
    }
}

bool MaxHeap::checkPosition(){
    bool res = 0;
    for (int i = 1; i <= numValue; ++i){
        res |= listNode[i]->checkPosition();
    }
    return res;
}

bool MaxHeap::checkArrow(){
    bool res = 0;
    for (int i = 1; i <= numValue; ++i){
        res |= listArrow[i].first.checkPosition() | listArrow[i].second.checkPosition();
    }
    return res;
}

void MaxHeap::checkPositionFast(){
    for (int i = 1; i <= numValue; ++i){
        listNode[i]->checkPositionFast();
    }
}

void MaxHeap::checkArrowFast(){
    for (int i = 1; i <= numValue; ++i){
        listArrow[i].first.checkPositionFast(); listArrow[i].second.checkPositionFast();
    }
}

void MaxHeap::checkFunction(){
    DataTypes::checkFunction();
    if (checkPosition()){
        checkArrow(); 
        return;
    } 
    // std::cout << 1234567 << '\n';
    if (checkArrow())return;
    if (funcQueue.empty())return;
    // std::cout << funcQueue.size() << '\n';
    Animation ani = funcQueue.front();
    funcQueue.pop();
    ani.go();
}

void MaxHeap::checkFunctionFast(){
    DataTypes::checkFunctionFast();
    checkPositionFast();
    checkArrowFast();
    while (!funcQueue.empty()){
        Animation ani = funcQueue.front();
        funcQueue.pop();
        ani.go();
    }
    checkPositionFast();
}

void MaxHeap::balancePosition(){
    for (int i = 1; i <= numValue; ++i){
        std::shared_ptr <Node> x = listNode[i];
        // std::cout << x->getValue() << '\n';
        x->changePosition(getPosI(i));
        x->setTextBot(std::to_string(i));
    }
}

std::shared_ptr <Node> MaxHeap::newNode(int k){
    std::shared_ptr <Node> nod = std::make_shared <Node> (19.f, std::to_string(k), ResourceManager::getFont(), 
                        textSize, backgroundColor, getPosI(numValue), CIRCLE, 0);
    nod->changeSizeNode(CircleRad);
    nod->setTextBot(std::to_string(numValue));
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Node::setSearching, nod, i/60.f)},{},{},{}));
    funcQueue.push(Animation({std::bind(&Node::changeSizeNode, nod, nod->getRad()-CircleRad)},{},{},{}));
    // std::cout << "newNode: " << nod->prevNode << " " << t << '\n';
    return nod;
}

void MaxHeap::runUp(int idx, int cas){
    std::shared_ptr <Node> t = listNode[idx];
    std::shared_ptr <Node> preNode = listNode[idx/2];
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Push the value up to the top")},{}));

    if (idx == 1 || t->getValue() <= preNode->getValue()){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::removeSearching, listNode[idx], i/60.f)},{},{},{}));
        if (cas){
            for (int i = 1; i <= 60; ++i){
                auto funcDel = [this, i]{
                    listNode[1]->changeSizeNode(CircleRad/60.f);
                };
                funcQueue.push(Animation({},{},{},{funcDel}));
            }

            auto funcDel = [this]{
                if (numValue & 1)listArrow[numValue / 2].second.setTail(getPosI(numValue/2));
                        else listArrow[numValue / 2].first.setTail(getPosI(numValue/2));
                --numValue; listNode[1] = listNode[numValue+1]; listNode[numValue+1] = nullptr;
                balancePosition();
            };
            funcQueue.push(Animation({},{},{},{funcDel}));

            auto funcc = [this]{
                for (int i = 1; i <= 60; ++i)
                    funcQueue.push(Animation({std::bind(&Node::setSearching, listNode[1], i/60.f)},{},{},{}));
                runDown(1);
            };
            funcQueue.push(Animation({},{},{},{funcc}));
        }
        funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Done")},{}));
        return;
    }

    funcQueue.push(Animation({std::bind(&Node::setSearching, preNode, 1.f)},{},{},{}));
    for (int i = 1; i <= 60; ++i){
        auto funcLambda = [this, preNode, idx, i](){
            if (idx % 2 == 0)listArrow[idx / 2].first.setPartialColor(1-i/60.f);
                else listArrow[idx / 2].second.setPartialColor(1-i/60.f);
            preNode->removeSearching(i/60.f);
        };
        funcQueue.push(Animation({},{},{},{funcLambda}));
    }

    auto funcLambda = [idx,this]{
        std::swap(listNode[idx], listNode[idx/2]);
        listNode[idx]->setTextBot(std::to_string(idx));
        listNode[idx/2]->setTextBot(std::to_string(idx/2));
        balancePosition();
    };
    funcQueue.push(Animation({},{},{},{funcLambda}));

    for (int i = 1; i <= 60; ++i){
        auto funcLambda2 = [idx,this]{
            listNode[idx]->setNodeColor(FirstNodeColor);
            listNode[idx]->setOutlineColor(sf::Color::Black);
            listNode[idx]->setTextColor(textColorStart);
        };
        funcQueue.push(Animation({},{},{},{funcLambda2}));
    }

    auto funcLambda2 = [this, idx, cas]{
        runUp(idx/2,cas);
    };
    funcQueue.push(Animation({},{},{},{funcLambda2}));
}

void MaxHeap::runDown(int idx){
    std::shared_ptr <Node> t = listNode[idx];
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Reconstruct heap")},{}));

    int tt, leftValue = 0, rightValue = 0;
    if (idx*2 <= numValue)leftValue = listNode[idx*2]->getValue();
    if (idx*2+1 <= numValue)rightValue = listNode[idx*2+1]->getValue();
    if (leftValue > rightValue)tt = 0; else tt = 1;

    std::shared_ptr <Node> preNode = listNode[idx*2 + tt];

    if (preNode == nullptr || t->getValue() >= preNode->getValue()){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Node::removeSearching, listNode[idx], i/60.f)},{},{},{}));
        auto funcLambda2 = [idx,this]{
            listNode[idx]->setNodeColor(FirstNodeColor);
            listNode[idx]->setOutlineColor(sf::Color::Black);
            listNode[idx]->setTextColor(textColorStart);
        };
        funcQueue.push(Animation({},{},{},{funcLambda2}));
        funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Done")},{}));
        return;
    }

    funcQueue.push(Animation({std::bind(&Node::setSearching, preNode, 1.f)},{},{},{}));
    for (int i = 1; i <= 60; ++i){
        auto funcLambda = [this, preNode, tt, idx, i](){
            if (tt == 0)listArrow[idx].first.setPartialColor(i/60.f);
                else listArrow[idx].second.setPartialColor(i/60.f);
            preNode->removeSearching(i/60.f);
        };
        funcQueue.push(Animation({},{},{},{funcLambda}));
    }

    auto funcLambda = [idx,this,tt]{
        std::swap(listNode[idx], listNode[idx*2 + tt]);
        listNode[idx]->setTextBot(std::to_string(idx));
        listNode[idx*2 + tt]->setTextBot(std::to_string(idx*2 + tt));
        balancePosition();
    };
    funcQueue.push(Animation({},{},{},{funcLambda}));

    for (int i = 1; i <= 60; ++i){
        auto funcLambda2 = [idx,this]{
            listNode[idx]->setNodeColor(FirstNodeColor);
            listNode[idx]->setOutlineColor(sf::Color::Black);
            listNode[idx]->setTextColor(textColorStart);
        };
        funcQueue.push(Animation({},{},{},{funcLambda2}));
    }

    auto funcLambda2 = [this, idx, tt]{
        runDown(idx*2 + tt);
    };
    funcQueue.push(Animation({},{},{},{funcLambda2}));
}
 
void MaxHeap::insert(int k){
    clearQueue(); resetNode(); balancePosition(); checkFunctionFast(); 
    std::cout << " k = " << k << '\n';
    ++numValue; listNode[numValue] = newNode(k);
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Make new node at last leaf")},{}));
    if (numValue > 1){
        int idx = numValue / 2;
        if (numValue % 2){
            auto funcL = [this, idx](){
                listArrow[idx].second.setTail(getPosI(numValue));
            };
            funcQueue.push(Animation({},{},{},{funcL}));
        } else {
            auto funcL = [this, idx](){
                listArrow[idx].first.setTail(getPosI(numValue));
            };
            funcQueue.push(Animation({},{},{},{funcL}));
        }
    }
    int t = numValue;
    
    // for (int i = 1; i <= 60; ++i)
    //     funcQueue.push(Animation({std::bind(&Node::setSearching, listNode[t], i/60.f)},{},{},{}));

    auto funcLambda = [this](){
        runUp(numValue,0);
    };
    funcQueue.push(Animation({},{},{},{funcLambda}));
}

void MaxHeap::fromfile(){
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
    listNode.clear(); listArrow.clear(); numValue = 0;
    listArrow.push_back({DynArrow(getPosI(1), getPosI(1)), DynArrow(getPosI(1),getPosI(1))});
    for (int i = 1; i <= 300; ++i){
        listNode.push_back(nullptr);
        listArrow.push_back({DynArrow(getPosI(i), getPosI(i)), DynArrow(getPosI(i),getPosI(i))});
    }
    for(std::string i : list){
        insert(ResourceManager::StringtoInt(i));
        checkFunctionFast(); 
    }
    clearQueue();
    resetNode();
    balancePosition();
    checkFunctionFast();
}

void MaxHeap::getTop(){
    clearQueue(); resetNode(); balancePosition(); checkFunctionFast(); 
    if (numValue == 0)return;
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "return Top")},{}));
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Node::setSearching, listNode[1], i/60.f)},{},{},{}));
}

void MaxHeap::remove(int vtx){
    clearQueue(); resetNode(); balancePosition(); checkFunctionFast(); 
    if (numValue == 0 || vtx > numValue)return;
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Make value of node bigger than the max")},{}));
    listNode[vtx]->setText(std::to_string(listNode[1]->getValue() + 1));

    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Node::setSearching, listNode[vtx], i/60.f)},{},{},{}));

    auto funcLambda = [this,vtx](){
        runUp(vtx,1);
    };
    funcQueue.push(Animation({},{},{},{funcLambda}));
}

void MaxHeap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    DataTypes::draw(target, states);
    for (int i = 1; i <= numValue; ++i){
        if (listNode[i*2] != nullptr)target.draw(listArrow[i].first);
        if (listNode[i*2+1] != nullptr)target.draw(listArrow[i].second);
    }
    for (int i = 1; i <= numValue; ++i){
        target.draw(*listNode[i]);
    }
}

void MaxHeap::checkPress(sf::Vector2f mousePos){
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
                        clearQueue();
                        resetNode();
                        balancePosition();
                        checkFunctionFast();
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
                getTop();
                break;
        }
    }
}
