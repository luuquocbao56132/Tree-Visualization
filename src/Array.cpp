#include <Array.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

Array::Array(){
    n = ResourceManager::random(40,72);
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
    init(ResourceManager::random(40,72));
}

void Array::init(int x){
    std::vector <std::string> s;
    int k = ResourceManager::random(0,x-1);
    for (int i = 0; i <= k; ++i)s.push_back(std::to_string(randomNodeValue()));
    init(x,s);
}

void Array::init(int x, std::vector <std::string> s){
    n = x; listNode.clear(); numValue = s.size(); 
    if (!n)return;

    for (int i = 0; i < x; ++i){
        listNode.push_back(std::make_shared <Node> (19.f, "", ResourceManager::getFont(), 
                                    textSize, backgroundColor,sf::Vector2f(0.f, 0.f),ARRAY,0));

        listNode[i]->setTextBot(std::to_string(i));
    }        
    for (int i = 0; i < s.size(); ++i){
        int j = ResourceManager::StringtoInt(s[i]) % n;
        while (listNode[j]->getString() != ""){
            ++j; if (j == n)j = 0;
        }
        listNode[j]->setText(s[i]);
    }

    int cnt = 0;
    for (int j = 0; j < n / 12; ++j)
        for (int i = 0; i < 12; ++i){
            listNode[cnt]->setPosition(sf::Vector2f(120 + 150*i, 150.f + 100*j));
            ++cnt;
        }
    if (cnt < n-1)for (int i = 0; cnt < n; ++i){
        listNode[cnt]->setPosition(sf::Vector2f(120 + 150*i, 150.f + 100*(n/12)));
        ++cnt;
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

void Array::setSearchingNode(int vtx, float ratio){
    listNode[vtx]->setSearching(ratio);
}

void Array::removeSearchingNode(int vtx, float ratio){
    listNode[vtx]->removeSearching(ratio);
}

void Array::setFoundNode(int vtx, float ratio){
    listNode[vtx]->setFound(ratio);
}

void Array::removeFoundNode(int vtx, float ratio){
    listNode[vtx]->removeFound(ratio);
}

void Array::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // std::cout << stepImageSprite.getTexture()->getSize().x << '\n';
    // target.draw(highlight);
    if (listNode.empty())return;
    for (int i = 0; i < n; ++i)target.draw(*listNode[i]);
}