#include <Twothree.hpp>

void Twothree::resetNode(std::shared_ptr <TwothreeNode> res){
        funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "")},{}));

    idxD = -100;
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
    BaseButton[1]->inputButton[0]->setValueLimit(std::make_shared <int> (50));
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
        
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Found position, make new node")},{}));
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

    
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Move down to insert")},{}));
    
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
    
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Searching for value")},{}));

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
        
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
        if (t->childNode.empty())break;
        for (int i = 0; i < t->listValue.size(); ++i)
            if (k < ResourceManager::StringtoInt(t->listValue[i].getString())){
                t = t->childNode[i].first;  flag = 1; break;
            }

        if (flag)continue;     
        t = t->childNode.back().first;
    }
}

std::vector <std::string> getListDel(std::vector <sf::Text> X, std::string d){
    std::vector <std::string> listVal;
    bool flg = 0;
    for (auto i : X)
        if (i.getString() != d || flg)listVal.push_back(i.getString());
            else flg = 1;
    return listVal;
}

std::vector <std::string> getListIn(std::vector <sf::Text> X, std::string d){
    std::vector <std::string> listVal;
    bool flg = 0;
    for (auto i : X)
        if (ResourceManager::StringtoInt(i.getString()) <= ResourceManager::StringtoInt(d))
            listVal.push_back(i.getString());
    listVal.push_back(d);
    for (auto i : X)
        if (ResourceManager::StringtoInt(i.getString()) > ResourceManager::StringtoInt(d))
            listVal.push_back(i.getString());
    return listVal;
}

void Twothree::removingNode(std::shared_ptr <TwothreeNode> t){
    
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Find sunccesor")},{}));
    std::cout << "removingNode: " << (std::string)t->listValue[0].getString() << '\n';
    t = checkAlone(t);
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, t, i/60.f)},{},{},{}));

    if (t->childNode.empty()){
        auto funcQ = [this,t](){
            int idxDel = 0;
            if (dirChild)idxDel = t->listValue.size() - 1;
            tDel->listValue[idxD].setString(t->listValue[idxDel].getString());
            *t = *newNode(getListDel(t->listValue, t->listValue[idxDel].getString()), t->prevNode, t->m_position);
            t->setSearching(1);
            balancePosition(root, 0, 60);
            for (int i = 1; i <= 60; ++i)
                funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
        };
        funcQueue.push(Animation({},{},{},{funcQ})); return;
    }

    auto funcQ = [this,t](){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
        if (dirChild)removingNode(t->childNode.back().first);
    };
    funcQueue.push(Animation({},{},{},{funcQ})); return;
    //Case 2
//     if (!t->childNode.empty()){
//         int idx = 0;
//         for (int i = 0; i < t->listValue.size(); ++i)
//             if (ResourceManager::StringtoInt(t->listValue[i].getString()) == val){
//                 idx = i; break;
//             }
//         //2.1
//         if (t->childNode[idx].first->listValue.size() > 1){
//             auto funcQ = [this, t, idx, val](){
//                 auto res = t->childNode[idx].first;
//                 for (int i = 1; i <= 60; ++i)
//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, res, i/60.f)},{},{},{}));
                    
//                 while (!res->childNode.empty()){
//                     for (int i = 1; i <= 60; ++i)
//                         funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, res, i/60.f)},{},{},{}));
//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setDefault, res)},{},{},{}));
//                     res = res->childNode.back().first;
//                     for (int i = 1; i <= 60; ++i)
//                         funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, res, i/60.f)},{},{},{}));
//                 }

//                 auto funcc = [this,t,idx,res](){
//                     t->listValue[idx].setString(res->listValue.back().getString());
//                 };
//                 funcQueue.push(Animation({},{},{},{funcc}));
//                 for (int i = 1; i <= 60; ++i)
//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setDefault, res)},{},{},{}));
//                 continueRemove(t->childNode[idx].first, ResourceManager::StringtoInt(res->listValue.back().getString()));
//             };
//             funcQueue.push(Animation({},{},{},{funcQ})); 
//             return;
//         } else 
//         //2.2
//         if (t->childNode[idx+1].first->listValue.size() > 1){
//             auto funcQ = [this, t, idx, val](){
//                 auto res = t->childNode[idx+1].first;
//                 for (int i = 1; i <= 60; ++i)
//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, res, i/60.f)},{},{},{}));
                    
//                 while (!res->childNode.empty()){
//                     for (int i = 1; i <= 60; ++i)
//                         funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, res, i/60.f)},{},{},{}));
//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setDefault, res)},{},{},{}));
//                     res = res->childNode[0].first;
//                     for (int i = 1; i <= 60; ++i)
//                         funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, res, i/60.f)},{},{},{}));
//                 }

//                 auto funcc = [this,t,idx,res](){
//                     t->listValue[idx].setString(res->listValue[0].getString());
//                 };
//                 funcQueue.push(Animation({},{},{},{funcc}));
//                 for (int i = 1; i <= 60; ++i)
//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setDefault, res)},{},{},{}));
//                 continueRemove(t->childNode[idx+1].first, ResourceManager::StringtoInt(res->listValue[0].getString()));
//             };
//             funcQueue.push(Animation({},{},{},{funcQ})); 
//             return;
//         } else { //2.3
//             if (t->listValue.size() == 1){
//                 auto funcQ = [this, t, idx, val](){
//                     auto left = t->childNode[0].first, right = t->childNode[1].first;
//                     *t = *newNode({left->listValue[0].getString(), t->listValue[0].getString(), right->listValue[0].getString()}, 
//                                     t->prevNode, t->m_position);

//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, t, 1)},{},{},{}));

//                     for (int i = 0; i < (int)left->childNode.size(); ++i)
//                         t->childNode.push_back({left->childNode[i].first, DynArrow(t->m_position, left->childNode[i].first->m_position)}),
//                         left->childNode[i].first->prevNode = t;

//                     for (int i = 0; i < (int)right->childNode.size(); ++i)
//                         t->childNode.push_back({right->childNode[i].first, DynArrow(t->m_position, right->childNode[i].first->m_position)}),
//                         right->childNode[i].first->prevNode = t;

//                     balancePosition(root, 0, 60);
//                     continueRemove(t, val);
//                 };
//                 funcQueue.push(Animation({},{},{},{funcQ})); 
//                 return;
//             } else {
//                 auto funcQ = [this, t, idx, val](){
//                     auto left = t->childNode[idx].first, right = t->childNode[idx+1].first;
//                     auto ListChild = t->childNode;
//                     auto res = newNode({left->listValue[0].getString(), t->listValue[idx].getString(), right->listValue[0].getString()}, 
//                                     t, (left->m_position + right->m_position) / 2.f);
            
//                     *t = *newNode(getListDel(t->listValue, std::to_string(val)), t->prevNode, t->m_position);

//                     funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, t, 1)},{},{},{}));

//                     for (int i = 0; i < idx; ++i)t->childNode.push_back(ListChild[i]);
//                     t->childNode.push_back({res, DynArrow(t->m_position, res->m_position)});
//                     for (int i = idx+2; i < ListChild.size(); ++i)t->childNode.push_back(ListChild[i]);
                    
//                     balancePosition(root, 0, 60);
//                     funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, 1)},{},{},{}));
//                     continueRemove(res, val);
//                 };
//                 funcQueue.push(Animation({},{},{},{funcQ})); 
//                 return;
//             }
//         }
//     }
}

std::shared_ptr <TwothreeNode> Twothree::checkAlone(std::shared_ptr <TwothreeNode> t){
    if (t->listValue.size() > 1)return t;

    if (t == root)return t;
    
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Node has 1 value, reconstruct")},{}));
    auto preNode = t->prevNode;
    int idx = 0, cnt = 0;
    while (preNode->childNode[idx].first != t)++idx;

    if (idx > 0){
        if (preNode->childNode[idx-1].first->listValue.size() > 1){
            std::string leftVal = preNode->childNode[idx-1].first->listValue.back().getString();
            std::string rightVal = preNode->listValue[idx-1].getString();
            auto leftChild = preNode->childNode[idx-1].first;
            std::pair <std::shared_ptr <TwothreeNode>, DynArrow> res;

            if (idx-1 == idxD && tDel == preNode)
                tDel = t, idxD = 0;
            
            auto listChild = leftChild->childNode;
            *preNode->childNode[idx-1].first = *newNode(getListDel(preNode->childNode[idx-1].first->listValue, leftVal), 
                                                        preNode, preNode->childNode[idx-1].first->m_position);
            for (int i = 0; i < (int)listChild.size()-1; ++i)leftChild->childNode.push_back(listChild[i]);
            if (!listChild.empty())res = listChild.back();

            listChild = t->childNode;
            *t = *newNode(getListIn(t->listValue, rightVal), preNode, t->m_position);
            if (!leftChild->childNode.empty())t->childNode.push_back(res);
            for (int i = 0; i < listChild.size(); ++i)t->childNode.push_back(listChild[i]);

            listChild = preNode->childNode;
            *preNode = *newNode(getListDel(preNode->listValue, rightVal), preNode->prevNode, preNode->m_position);
            *preNode = *newNode(getListIn(preNode->listValue, leftVal), preNode->prevNode, preNode->m_position);
            funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, preNode, 1)},{},{},{}));
            funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, preNode, 1)},{},{},{}));
            for (auto i : listChild)preNode->childNode.push_back(i);
            balancePosition(root, 0, 60);
            
            return t;
        }
    }

    if (idx < preNode->childNode.size()-1){
        if (preNode->childNode[idx+1].first->listValue.size() > 1){
            std::string leftVal = preNode->listValue[idx].getString();
            std::string rightVal = preNode->childNode[idx+1].first->listValue[0].getString();
            auto rightChild = preNode->childNode[idx+1].first;
            std::pair <std::shared_ptr <TwothreeNode>, DynArrow> res;

            if (idx == idxD && tDel == preNode)
                tDel = t, idxD = t->listValue.size();

            auto listChild = rightChild->childNode;
            *preNode->childNode[idx+1].first = *newNode(getListDel(preNode->childNode[idx+1].first->listValue, rightVal), 
                                                        preNode, preNode->childNode[idx+1].first->m_position);
            for (int i = 1; i < listChild.size(); ++i)rightChild->childNode.push_back(listChild[i]);
            if (!listChild.empty())res = listChild[0];

            listChild = t->childNode;
            *t = *newNode(getListIn(t->listValue, leftVal), preNode, t->m_position);
            for (int i = 0; i < listChild.size(); ++i)t->childNode.push_back(listChild[i]);
            if (!rightChild->childNode.empty())t->childNode.push_back(res);

            listChild = preNode->childNode;
            *preNode = *newNode(getListDel(preNode->listValue, leftVal), preNode->prevNode, preNode->m_position);
            *preNode = *newNode(getListIn(preNode->listValue, rightVal), preNode->prevNode, preNode->m_position);
            funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, preNode, 1)},{},{},{}));
            funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, preNode, 1)},{},{},{}));
            for (auto i : listChild)preNode->childNode.push_back(i);

            balancePosition(root, 0, 60);
            return t;
        } else {
            std::string leftVal = preNode->listValue[idx].getString();
            std::string rightVal = preNode->childNode[idx+1].first->listValue[0].getString();
            auto rightChild = preNode->childNode[idx+1].first;
            auto listChild = t->childNode;
            if (idx == idxD && tDel == preNode)
                tDel = t, idxD = t->listValue.size();
            *t = *newNode(getListIn(t->listValue, leftVal), preNode, t->m_position);
            *t = *newNode(getListIn(t->listValue, rightVal), preNode, t->m_position);
            for (auto i : listChild)t->childNode.push_back(i);
            for (auto i : rightChild->childNode){
                t->childNode.push_back(i);
                i.first->prevNode = t;
            }

            listChild = preNode->childNode;
            *preNode = *newNode(getListDel(preNode->listValue, leftVal), preNode->prevNode, preNode->m_position);
            if (preNode->listValue.size() == 0){
                if (preNode->prevNode != nullptr)
                    for (int i = 0; i < preNode->prevNode->childNode.size(); ++i)
                        if (preNode->prevNode->childNode[i].first == preNode)
                            {preNode->prevNode->childNode[i].first = t; break;}
                t->prevNode = preNode->prevNode;
                if (preNode == root)root = t;
                return t;
            }

            for (int i = 0; i <= idx; ++i)preNode->childNode.push_back(listChild[i]);
            for (int i = idx+2; i < listChild.size(); ++i)preNode->childNode.push_back(listChild[i]);
            balancePosition(root, 0, 60);
            return t;
        }
    }

    --idx; t = preNode->childNode[idx].first;
    std::string leftVal = preNode->listValue[idx].getString();
    std::string rightVal = preNode->childNode[idx+1].first->listValue[0].getString();
    auto rightChild = preNode->childNode[idx+1].first;
    auto listChild = t->childNode;
    if (idx == idxD && tDel == preNode)
        tDel = t, idxD = t->listValue.size();
    *t = *newNode(getListIn(t->listValue, leftVal), preNode, t->m_position);
    *t = *newNode(getListIn(t->listValue, rightVal), preNode, t->m_position);
    for (auto i : listChild)t->childNode.push_back(i);
    for (auto i : rightChild->childNode){
        t->childNode.push_back(i);
        i.first->prevNode = t;
    }

    listChild = preNode->childNode;
    *preNode = *newNode(getListDel(preNode->listValue, leftVal), preNode->prevNode, preNode->m_position);
    if (preNode->listValue.size() == 0){
        if (preNode->prevNode != nullptr)
            for (int i = 0; i < preNode->prevNode->childNode.size(); ++i)
                if (preNode->prevNode->childNode[i].first == preNode)
                    {preNode->prevNode->childNode[i].first = t; break;}
        t->prevNode = preNode->prevNode;
        if (preNode == root)root = t;
        return t;
    }

    for (int i = 0; i <= idx; ++i)preNode->childNode.push_back(listChild[i]);
    for (int i = idx+2; i < listChild.size(); ++i)preNode->childNode.push_back(listChild[i]);
    balancePosition(root, 0, 60);
    return t;
}

void Twothree::continueRemove(std::shared_ptr <TwothreeNode> t, int k){
    std::shared_ptr <TwothreeNode> preNode = t->prevNode;
    bool flag = 0;
    if (t == nullptr)return;

    t = checkAlone(t);
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&TwothreeNode::setSearching, t, i/60.f)},{},{},{}));
    
    for (int i = 0; i < t->listValue.size(); ++i){
        if (k == ResourceManager::StringtoInt(t->listValue[i].getString())){
            if (!t->childNode.empty()){
                auto func = [this,t, k, i](){
                    idxD = i; dirChild = 1; tDel = t;
                    removingNode(t->childNode[i].first);
                };
                funcQueue.push(Animation({},{},{},{func})); return;
            } else {
                auto funcQ = [this, t, k](){
                    *t = *newNode(getListDel(t->listValue, std::to_string(k)), t->prevNode, t->m_position);
                    t->setSearching(1);
                    balancePosition(root, 0, 60);
                    for (int i = 1; i <= 60; ++i)
                        funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
                };
                funcQueue.push(Animation({},{},{},{funcQ})); 
                return;
            }
        }
    }
    
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&TwothreeNode::removeSearching, t, i/60.f)},{},{},{}));
    if (t->childNode.empty()){
        
        funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Dont have node")},{}));
        return;
    }

    for (int i = 0; i < t->listValue.size(); ++i)
        if (k < ResourceManager::StringtoInt(t->listValue[i].getString())){
            t = t->childNode[i].first; 
            auto funcc = [this,t, k](){
                continueRemove(t, k);
            };
            funcQueue.push(Animation({},{},{},{funcc})); return;
        }
 
    t = t->childNode.back().first;
    auto funcc = [this,t, k](){
        continueRemove(t, k);
    };
    funcQueue.push(Animation({},{},{},{funcc})); return;
}

void Twothree::remove(int k){
    checkFunctionFast(); clearQueue(); resetNode(root); balancePosition(root, 0, 60); checkFunctionFast(); 
    std::cout << " k = " << k << '\n';
    std::shared_ptr <TwothreeNode> t = root, preNode = nullptr;
    if (t == nullptr)return;
    
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Move down to find node")},{}));

    auto func = [this,t, k](){
        continueRemove(t, k);
    };
    funcQueue.push(Animation({},{},{},{func}));
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
