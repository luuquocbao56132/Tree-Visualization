#include <HashTable.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

void HashTable::resetNode(){
    for (int i = 0; i < graph.getSize(); ++i){
        Node t = *graph.listNode[i];
        graph.listNode[i] = std::make_shared <Node> (19.f, t.getString(), ResourceManager::getFont(), 
                                    textSize, backgroundColor,t.getNodePosition(),ARRAY,0);
        // graph.listNode[i]->setPosition();
        graph.listNode[i]->setTextBot(std::to_string(i));
    }
}

HashTable::HashTable(): DataTypes(), graph(){
    BaseButton[1]->inputButton[0]->setValueLimit(std::make_shared <int> (72));
    firstGraph = graph;
}

void HashTable::checkPress(sf::Vector2f mousePos){
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
                        graph.init(inputBox[0]->getValue());
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

void HashTable::checkFunction(){
    DataTypes::checkFunction();
    if (funcQueue.empty())return;
    // std::cout << funcQueue.size() << '\n';
    Animation ani = funcQueue.front();
    funcQueue.pop();
    ani.go();
}

void HashTable::checkFunctionFast(){
    DataTypes::checkFunctionFast();
    while (!funcQueue.empty()){
    // std::cout << funcQueue.size() << '\n';
        Animation ani = funcQueue.front();
        funcQueue.pop();
        ani.go();
    }
}

void HashTable::fromfile(){
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

void HashTable::insert(int x){
    clearQueue(); resetNode();
    if (graph.getNumValue() == graph.getSize()-1){
        return;
    }
    
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Find empty node from (value mod n)")},{}));
    int j = x % graph.getSize(), first = (j - 1 < 0 ? j = graph.getSize()-1 : j - 1);
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{},{},{}));
    
    while (graph.listNode[j]->getString() != "" && !graph.isDel(j) && j != first){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        ++j; if (j == graph.getSize())j = 0;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{}, {},{}));
    }

    if (j == first){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        return;
    }
    
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Found node")},{}));
    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setFoundNode, &graph, j, i/60.f)}, {},
                                    {std::bind(&Node::setText, graph.listNode[j], std::to_string(x))},{}));
    funcQueue.push(Animation({}, {}, {}, {[this,j](){
        ++graph.numValue; graph.unDel(j);
    }}));
    // for (int i = 0; i < graph.getSize(); ++i)std::cout << graph.listNode[i]->getString() << ' '; std::cout << '\n';
    // for (int i = 0; i < firstGraph.getSize(); ++i)std::cout << firstGraph.listNode[i]->getString() << ' '; std::cout << '\n';
}

void HashTable::remove(int x){
    clearQueue(); resetNode(); 
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Search node to remove, start from (value mod n)")},{}));

    int j = x % graph.getSize(), first = (j - 1 < 0 ? j = graph.getSize()-1 : j - 1);
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{},{},{}));
    while ((graph.isDel(j) || graph.listNode[j]->getString() != "") && graph.listNode[j]->getString() != std::to_string(x) && j != first){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        ++j; if (j == graph.getSize())j = 0;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{}, {},{}));
    }

    if (graph.listNode[j]->getString() == "" || j == first){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Doesn't have this value")},{}));
        return;
    }

    funcQueue.push(Animation({}, {}, {std::bind(&Highlight::setLine, &highlight, "Delete value, mark this node to DEL")}, {std::bind(&Node::setText, graph.listNode[j], "Del"), [this, j](){
        --graph.numValue; graph.setDel(j);
    }}));

    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setFoundNode, &graph, j, i/60.f)}, {},{},{}));
}

void HashTable::search(int x){
    clearQueue(); resetNode();

    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Searching node, start from (value mod n)")},{}));
    int j = x % graph.getSize(), first = (j - 1 < 0 ? j = graph.getSize()-1 : j - 1);
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{},{},{}));
    while ((graph.isDel(j) || graph.listNode[j]->getString() != "") && graph.listNode[j]->getString() != std::to_string(x) && j != first){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        ++j; if (j == graph.getSize())j = 0;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{}, {},{}));
    }

    if (graph.listNode[j]->getString() == "" || j == first){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Doesn't have this value")},{}));
        return;
    }
    funcQueue.push(Animation({},{},{std::bind(&Highlight::setLine, &highlight, "Found node")},{}));
    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setFoundNode, &graph, j, i/60.f)}, {},{},{}));
}

void HashTable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    target.draw(graph);
}