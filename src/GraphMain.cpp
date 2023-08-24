#include <GraphMain.hpp>

GraphMain::GraphMain(): DataTypes() {
    for (int i = 1; i <= 3; ++i){
        auto x = BaseButton[i];
        BaseButton[i]->inputButton.clear();
    }
    BaseButton[1]->inputButton.push_back(std::make_shared <InputBox>(
                sf::Vector2f(BaseButton[1]->getPosition().x + BaseButton[1]->getSize().x + 45, 
                            BaseButton[1]->getPosition().y), 
                        inputButtonSize, "n = ", 0));
    BaseButton[1]->inputButton[0]->setValueLimit(std::make_shared <int> (20));
    BaseButton[1]->inputButton.push_back(std::make_shared <InputBox>(
        sf::Vector2f(BaseButton[1]->getPosition().x + BaseButton[1]->getSize().x + inputButtonSize.x + 85, 
                    BaseButton[1]->getPosition().y), 
                inputButtonSize, "m = ", 1));
    BaseButton[1]->inputButton[1]->setValueLimit(std::make_shared <int> (60));

    int i, ii = 300;
    i = 2;
    auto x = BaseButton[i];
    *x = *std::make_shared <Button>(buttonPosition + sf::Vector2f(buttonPosition.x + i*ii + 100, buttonRange.y),
                    buttonSize + sf::Vector2f(50,0), "Connected Components", ResourceManager::getFont(), 20,0);

    i = 3;
    x = BaseButton[i];
    *x = *std::make_shared <Button>(buttonPosition + sf::Vector2f(buttonPosition.x + i*ii + 100, buttonRange.y),
                    buttonSize, "MST", ResourceManager::getFont(), 20,0);

    i = 4;
    x = BaseButton[i];
    x->m_text.setString("Dijktra");
    x->inputButton[0]->setValueLimit(std::make_shared <int> (20));
        
    n = ResourceManager::random(3,20);
    // n = 4;
    initGraph(n, ResourceManager::random(0,3*n));
}

void GraphMain::resetGraph(){
    for (int i = 1; i <= n; ++i){
        listNode[i].setDefault();
        for (int j = i+1; j <= n; ++j)if (a[i][j]){
            listArrow[i][j].setColor(sf::Color::Black);
        }
        listNode[i].setTextBot("");
    }
}

sf::Vector2f GraphMain::frep(int u, int v){
    float crep = 800;
    sf::Vector2f uPos = listNode[u].getNodePosition(), vPos = listNode[v].getNodePosition();
    float len = sqrt(((uPos.x - vPos.x) * (uPos.x - vPos.x) + (uPos.y - vPos.y) * (uPos.y - vPos.y)));
    return crep / (len*len) * ((uPos - vPos) / len);
}

sf::Vector2f GraphMain::fspring(int u, int v){
    float cspring = 2;
    sf::Vector2f uPos = listNode[u].getNodePosition(), vPos = listNode[v].getNodePosition();
    float len = sqrt(((uPos.x - vPos.x) * (uPos.x - vPos.x) + (uPos.y - vPos.y) * (uPos.y - vPos.y)));
    return cspring * log(len / 250.f) * ((vPos - uPos) / len);
}

sf::Vector2f GraphMain::fattr(int u, int v){
    return fspring(u,v) - frep(u,v);
}

void GraphMain::createGraph(){
    sf::Vector2f F[100];
    float MaxLen = 10000;

    float gamma = 0.9999;
    for (int ii = 1; ii <= 5000 && MaxLen > 0.001; ++ii){
        MaxLen = 0;
        for (int u = 1; u <= n; ++u){
            F[u] = sf::Vector2f(0,0);
            // std::cout << "u: " << u << " coordinate: " << listNode[u].getNodePosition().x << " " << listNode[u].getNodePosition().y << '\n';
            for (int v = 1; v <= n; ++v)if (v != u){
                F[u] += frep(u,v);
                // std::cout << "v: " << v << " frep: " << frep(u,v).x << "  "<< frep(u,v).y << " ";
                if (a[u][v])F[u] += fattr(u,v);
                // ?, std::cout << "fattr: " << fattr(u,v).x << " " << fattr(u,v).y << " ";
                // std::cout << "abc: " << F[u].x << " " << F[u].y << " " << u << "  "<< v << "\n";
            }
            MaxLen = std::max(MaxLen, sqrt(F[u].x * F[u].x + F[u].y * F[u].y));
            // std::cout << F[u].x << " " << F[u].y << '\n';
            // std::cout << '\n';
        }
        // std::cout << "MaxLen: " << MaxLen << '\n';

        for (int u = 1; u <= n; ++u){
            sf::Vector2f res = listNode[u].getNodePosition() + F[u] * gamma;
            res.x = std::max(res.x, 100.f);
            res.y = std::max(res.y, 150.f);
            res.x = std::min(res.x, 1800.f);
            res.y = std::min(res.y, 500.f);
            listNode[u].setPosition(res);
        }
        gamma *= 0.9999;
    }

    for (int u = 1; u <= n; ++u)
        listNode[u].changePosition(listNode[u].getNodePosition());
    for (int u = 1; u <= n; ++u) for (int v = u + 1; v <= n; ++v) if (a[u][v]){
        listArrow[u][v] = DynArrow(listNode[u].getNodePosition(), listNode[v].getNodePosition());
    }
}

void GraphMain::initGraph(int _n, int m){
    n = _n; 
    for (int i = 1; i <= n; ++i)for (int j = 1; j <= n; ++j)a[i][j] = 0;
    int sq = sqrt(n)+1, cnt = 0;
    for (int i = 1; i <= n; ++i){
        sf::Vector2f pos = sf::Vector2f(100 + 220 * ((i-1) % sq), 150 + 100 * i / sq);
        pos = sf::Vector2f(ResourceManager::random(150,1800), ResourceManager::random(150, 500));
        listNode[i] = Node(19.f, std::to_string(i), ResourceManager::getFont(), 
                        textSize, backgroundColor, pos, CIRCLE, 0);
        listNode[i].setPosition(listNode[i].m_position);
    }

    while (m--){
        while (true){
            int u = ResourceManager::random(1,n), v = ResourceManager::random(1,n);
            if (u == v || a[u][v])continue;
            a[u][v] = a[v][u] = ResourceManager::random(1,99);
            break;
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            std::cout << a[i][j] << " ";
        std::cout << "\n";
    } 
    createGraph();

    for (int u = 1; u <= n; ++u) for (int v = u + 1; v <= n; ++v) if (a[u][v]){
        listArrow[u][v] = DynArrow(listNode[u].getNodePosition(), listNode[v].getNodePosition());
    }

    for (int i = 1; i <= n; ++i)std::cout << "pos " << i << ": " << listNode[i].getNodePosition().x << " " << listNode[i].getNodePosition().y << '\n';
}

void GraphMain::checkFunction(){
    DataTypes::checkFunction();
}

void GraphMain::checkFunctionFast(){
    DataTypes::checkFunctionFast();
}

void GraphMain::MST(){

}

void GraphMain::Dijktra(int s){
    resetGraph();
    for (int i = 1; i <= n; ++i)d[i] = 1e9;
    d[s] = 0;
    std::priority_queue <std::pair <int,int> > pq;
    pq.push(std::make_pair(0,s));
    while (!pq.empty()){
        int u = pq.top().second, du = -pq.top().first;
        pq.pop();
        if (du != d[u])continue;
        listNode[u].setTextBot(std::to_string(d[u]));
        listNode[u].setFound(1);
        for (int v = 1; v <= n; ++v)if (a[u][v]){
            if (d[v] > d[u] + a[u][v]){
                d[v] = d[u] + a[u][v];
                pq.push(std::make_pair(-d[v], v));
                // listArrow[u][v].setColor(sf::Color::Yellow);
            }
        }
    }
}

void GraphMain::dfs(int u, sf::Color color){
    listNode[u].setNodeColor(color);
    listNode[u].setOutlineColor(color);
    for (int v = 1; v <= n; ++v)if (a[u][v] && !d[v]){
        d[v] = d[u];
        dfs(v, color);
    }
}

void GraphMain::Component(){
    resetGraph();
    for (int i = 1; i <= n; ++i)d[i] = 0;
    int cnt = 0;
    for (int i = 1; i <= n; ++i)if (!d[i]){
        ++cnt; d[i] = cnt;
        dfs(i, sf::Color(ResourceManager::random(0,255), ResourceManager::random(0,255), ResourceManager::random(0,255)));
    }
    for (int i = 1; i <= n; ++i)listNode[i].setTextBot(std::to_string(d[i]));
}

void GraphMain::fromfile(){
    
}

void GraphMain::checkPress(sf::Vector2f mousePos){
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
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0])
                    for (int j = 0; j < inputBox.size(); ++j) {
                        if (inputBox[j] == res->inputButton[j]){
                            inputBox[j]->checkPress(mousePos);
                            if (j == 1 && inputBox[j]->Go->checkPress(mousePos) && 
                            inputBox[j-1]->getValue()*3 >= inputBox[j]->getValue()){
                                initGraph(inputBox[j-1]->getValue(), inputBox[j]->getValue());
                            }
                        } else break;
                    }
                break;
            case INSERT:
                Component();
                break;
            case REMOVE:
                MST();
                break;
            case SEARCH:
                if (res->checkPress(mousePos)){
                    inputBox = res->inputButton; 
                    for (auto i : inputBox)i->resetValue();
                }
                if (!inputBox.empty() && inputBox[0] == res->inputButton[0]){
                    inputBox[0]->checkPress(mousePos);
                    if (inputBox[0]->Go->checkPress(mousePos))Dijktra(inputBox[0]->getValue());
                }
                break;
        }
    }
}

void GraphMain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    DataTypes::draw(target, states);
    for (int i = 1; i <= n; ++i) for (int j = i+1; j <= n; ++j) if (a[i][j])
        target.draw(listArrow[i][j]);
    for (int i = 1; i <= n; ++i){
        target.draw(listNode[i]);
    }
}