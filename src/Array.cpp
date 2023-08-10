#include <Array.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

Array::Array(){
    n = 40;
    init(n);
}

Array& Array::operator=(Array& other) {
    if (this != &other) { 
        this->init(other.getSize());
        for (int i = 0; i < other.getSize(); ++i)
            this->listNode[i]->setText(other.listNode[i]->getString());
        this->numValue = other.numValue;
        // std::cout << this->getSize() << '\n';
        // for (int i = 0; i < this->getSize(); ++i)std::cout << this->listNode[i]->getValue() << ' '; std::cout << '\n';
    }
    return *this;
}

void Array::init(){
    init(ResourceManager::random(2,7));
}

void Array::init(int x){
    std::vector <std::string> s;
    int k = ResourceManager::random(0,x-1);
    for (int i = 0; i < k; ++i)s.push_back(std::to_string(randomNodeValue()));
    init(x,s);
}

void Array::init(int x, std::vector <std::string> s){
    x = 40;
    n = x; listNode.clear(); newNode = nullptr; isListNew = 0; nowStep = -1; numValue = s.size();
    resetStep(); 
    highlight.addImage("./Image/" + theme + "Blank.png"); highlight.setHL(0);
    if (!n)return;

    leftBound = 850 - (100*(n) - arrowLength ) / 2;

    for (int i = 0; i < x; ++i){
        listNode.push_back(std::make_shared <Node> (19.f, "", ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(leftBound + 10 + 100*i, 250.f),ARRAY));

        listNode[i]->setTextBot(std::to_string(i));
    }        
    for (int i = 0; i < s.size(); ++i){
        int j = ResourceManager::StringtoInt(s[i]) % 40;
        while (listNode[j]->getString() != ""){
            ++j; if (j == 40)j = 0;
        }
        listNode[j]->setText(s[i]);
    }

    for (int i = 0; i < 10; ++i){
        listNode[i]->setPosition(sf::Vector2f(120 + 150*i, 150.f));
        listNode[10+i]->setPosition(sf::Vector2f(120 + 150*i, 250.f));
        listNode[20+i]->setPosition(sf::Vector2f(120 + 150*i, 350.f));
        listNode[30+i]->setPosition(sf::Vector2f(120 + 150*i, 450.f));
    }

    // std::cout << 3 << '\n';
    // for (int i = 0; i < s.size(); ++i)listNode[i]->changeSizeNode(CircleRad / numFrame * (numFrame-1));
}

void Array::setValue(int vtx, int value){
    if (vtx >= getSize())return;
    setNumber.erase(listNode[vtx]->getValue());
    listNode[vtx]->setText(std::to_string(value));
    setNumber.insert(value);
}

void Array::setSize(int nn){n = nn;}

int Array::randomNodeValue(){
    int t = ResourceManager::random(1,maxValue);
    return t;
}

int Array::getSize(){
    return n;
}

int Array::getNumValue(){
    return numValue;
}

void Array::setNodeColor(int vtx, sf::Color color){
    listNode[vtx]->setNodeColor(color);
}

int Array::getValue(int vtx){return listNode[vtx]->getValue();}

void Array::delValue(int vtx){
    int j = vtx % getSize();
    while (listNode[j]->getString() != "" && listNode[j]->getValue() != vtx){
        ++j; if (j == getSize())j = 0;
    }
    if (listNode[j]->getString() == "")return;
    listNode[j]->setText("");
    --numValue;
}

void Array::search(int value){
    int j = value % getSize();
    while (listNode[j]->getString() != "" && listNode[j]->getValue() != value){
        ++j; if (j == getSize())j = 0;
    }
    if (listNode[j]->getString() == "")return;
    listNode[j]->setNodeColor(SearchingNodeColor);
}

void Array::resetStep(){
    stepNode.clear(); stepString.clear(); nowStep = -1; stepNewNode.clear();
    stepIsListNew.clear(); stepListNew.clear();
}

void Array::getStep(int dx){
    if (stepNode.empty())return;
    if (nowStep + dx >= stepNode.size() || nowStep + dx < 0)return;
    nowStep += dx;
    
    listNode.resize(stepNode[nowStep].size()); 
    n = listNode.size();
    listNode = stepNode[nowStep];
    newNode = stepNewNode[nowStep];
    highlight.setLine(stepString[nowStep]); highlight.setHL(1);

    for (int i = 0; i < listNode.size(); ++i){
        listNode[i]->setArrow();
    }

    isListNew = stepIsListNew[nowStep];
    listNew = stepListNew[nowStep];
    // if (newNode)newNode->setArrow();
}

// void Array::saveStep(){
//     std::vector <std::shared_ptr <Node> > res;

//     if (newNode == nullptr)stepNewNode.push_back(nullptr);
//         else stepNewNode.push_back(std::make_shared <Node> (*newNode));
//     for (int i = 0; i < getSize(); ++i)res.push_back(std::make_shared <Node> (*listNode[i]));

//     for (int i = 0; i < getSize(); ++i){
//         if (i > 0 && listNode[i]->prevNode == listNode[i-1])
//             res[i]->prevNode = res[i-1];
//         if (i < getSize()-1 && listNode[i]->nextNode == listNode[i+1])
//             res[i]->nextNode = res[i+1];
        
//         if (listNode[i]->nextNode == newNode) 
//             res[i]->nextNode = stepNewNode[stepNewNode.size()-1];
//         if (listNode[i]->prevNode == newNode) 
//             res[i]->prevNode = stepNewNode[stepNewNode.size()-1];

//         if (newNode){
//             if (newNode->prevNode == listNode[i])
//                 stepNewNode[stepNewNode.size()-1]->prevNode = res[i];
//             if (newNode->nextNode == listNode[i])
//                 stepNewNode[stepNewNode.size()-1]->nextNode = res[i]; 
//         }
//     }

//     stepNode.push_back(res); ++nowStep;
//     stepString.push_back(highlight.getLine()+1);

//     stepIsListNew.push_back(isListNew);
//     res.clear();
//     if (isListNew){
//         for (int i = 0; i < listNew.size(); ++i)
//             res.push_back(std::make_shared <Node> (*listNew[i]));
//     } stepListNew.push_back(res);
//     // std::cout << stepNode.size() << '\n';
// }

void Array::setSearchingNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(ResourceManager::changeColor(sf::Color::Black, SearchingNodeColor, ratio));
    listNode[vtx]->setNodeColor(ResourceManager::changeColor(FirstNodeColor, SearchingNodeColor, ratio));
    listNode[vtx]->setTextColor(ResourceManager::changeColor(textColorStart, textColorEnd, ratio));
}

void Array::removeSearchingNode(int vtx, float ratio){
    listNode[vtx]->setNodeColor(ResourceManager::changeColor(SearchingNodeColor, FirstNodeColor, ratio));
    listNode[vtx]->setTextColor(ResourceManager::changeColor(textColorEnd, SearchingNodeColor, ratio));
}

void Array::setFoundNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(ResourceManager::changeColor(SearchingNodeColor, FoundNodeColor, ratio));
    listNode[vtx]->setNodeColor(ResourceManager::changeColor(SearchingNodeColor, FoundNodeColor, ratio));
    listNode[vtx]->setTextColor(ResourceManager::changeColor(textColorEnd, textColorEnd, ratio));
}

void Array::removeFoundNode(int vtx, float ratio){
    listNode[vtx]->setOutlineColor(FoundNodeColor);
    listNode[vtx]->setNodeColor(backgroundColor);
    listNode[vtx]->setTextColor(FoundNodeColor);
    // gameGlobal->runBreak();
}

void Array::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // std::cout << stepImageSprite.getTexture()->getSize().x << '\n';
    target.draw(highlight);
    if (isListNew)for (int i = 0; i < listNew.size(); ++i)target.draw(*listNew[i]);
    if (newNode != nullptr)target.draw(*newNode);
    if (listNode.empty())return;
    for (int i = 0; i < n; ++i)target.draw(*listNode[i]);
}