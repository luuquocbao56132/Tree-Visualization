#include <HashTable.hpp>
#include <Game.hpp>

extern std::shared_ptr <Game> gameGlobal;

HashTable::HashTable(): DataTypes(), graph(){
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

void HashTable::checkFunction(){
    DataTypes::checkFunction();
    if (funcQueue.empty())return;
    // std::cout << funcQueue.size() << '\n';
    Animation ani = funcQueue.front();
    funcQueue.pop();
    ani.go();
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
    graph = firstGraph;
    if (graph.getNumValue() == graph.getSize()-1){
        return;
    }
    clearQueue(); 
    
    int j = x % graph.getSize();
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{},{},{}));
    
    while (graph.listNode[j]->getString() != ""){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        ++j; if (j == graph.getSize())j = 0;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{}, {},{}));
    }
    
    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setFoundNode, &graph, j, i/60.f)}, {},
                                    {std::bind(&Node::setText, graph.listNode[j], std::to_string(x))},{}));
    funcQueue.push(Animation({}, {}, {}, {[&](){
        ++graph.numValue; firstGraph = graph;
    }}));
}

void HashTable::remove(int x){
    graph = firstGraph; clearQueue(); 

    int j = x % graph.getSize();
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{},{},{}));

    while (graph.listNode[j]->getString() != "" && graph.listNode[j]->getString() != std::to_string(x)){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        ++j; if (j == graph.getSize())j = 0;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{}, {},{}));
    }

    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setFoundNode, &graph, j, i/60.f)}, {},{},{}));

    std::cout << graph.numValue << '\n';

    if (graph.listNode[j]->getString() == "")return;

    funcQueue.push(Animation({}, {}, {}, {std::bind(&Node::setText, graph.listNode[j], ""), [&](){
        --graph.numValue; 
        firstGraph = graph;
    }}));
}

void HashTable::search(int x){
    graph = firstGraph; clearQueue();

    int j = x % graph.getSize();
    for (int i = 1; i <= 60; ++i)
        funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{},{},{}));
    while (graph.listNode[j]->getString() != ""){
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::removeSearchingNode, &graph, j, i/60.f)},{},{},{}));
        ++j; if (j == graph.getSize())j = 0;
        for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setSearchingNode, &graph, j, i/60.f)},{}, {},{}));
    }
    for (int i = 1; i <= 60; ++i)
            funcQueue.push(Animation({std::bind(&Array::setFoundNode, &graph, j, i/60.f)}, {},{},{}));
}

void HashTable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    target.draw(graph);
}