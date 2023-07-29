#include <Menu.hpp>

Menu::Menu(): themeSet(){
    bHash = Button(sf::Vector2f(800.f, 420.f), sf::Vector2f(125.f, 60.f), "Hash Table", ResourceManager::getFont(), 20, 0);
    bAVL = Button(sf::Vector2f(800.f, 520.f), sf::Vector2f(125.f, 60.f), "AVL Tree", ResourceManager::getFont(), 20, 0);
    b234 = Button(sf::Vector2f(800.f, 620.f), sf::Vector2f(125.f, 60.f), "234 Tree", ResourceManager::getFont(), 20, 0);
    bMinHeap = Button(sf::Vector2f(975.f, 420.f), sf::Vector2f(125.f, 60.f), "Min Heap", ResourceManager::getFont(), 20, 0);
    bMaxHeap = Button(sf::Vector2f(975.f, 520.f), sf::Vector2f(125.f, 60.f), "Max Heap", ResourceManager::getFont(), 20, 0);
    bTrie = Button(sf::Vector2f(975.f, 620.f), sf::Vector2f(125.f, 60.f), "Trie", ResourceManager::getFont(), 20, 0);
    bGraph = Button(sf::Vector2f(890.f, 720.f), sf::Vector2f(125.f, 60.f), "Graph", ResourceManager::getFont(), 20, 0);
}

void Menu::setTheme(){
   bHash.setColor();
   bTrie.setColor();
   b234.setColor();
   bMinHeap.setColor();
   bMaxHeap.setColor();
   bGraph.setColor();
   bAVL.setColor();
}

int Menu::checkPress(sf::Vector2f mousePos){
    if (bHash.checkPress(mousePos)){
        return 1;
    }
    if (bAVL.checkPress(mousePos)){
        return 2;
    }
    if (b234.checkPress(mousePos)){
        return 3;
    }
    if (bGraph.checkPress(mousePos)){
        return 4;
    }
    if (bTrie.checkPress(mousePos)){
        return 5;
    }
    if (bMaxHeap.checkPress(mousePos)){
        return 6;
    }
    if (bMinHeap.checkPress(mousePos)){
        return 7;
    }
    if (themeSet.checkPress(mousePos))setTheme();
    return 0;
}

void Menu::HoverCheck(sf::Vector2f mousePos){
    themeSet.HoverCheck(mousePos);
    bHash.checkHover(mousePos);
    bAVL.checkHover(mousePos);
    b234.checkHover(mousePos);
    bTrie.checkHover(mousePos);
    bGraph.checkHover(mousePos);
    bMaxHeap.checkHover(mousePos);
    bMinHeap.checkHover(mousePos);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(themeSet);
    target.draw(bHash);
    target.draw(bAVL);
    target.draw(b234);
    target.draw(bMinHeap);
    target.draw(bMaxHeap);
    target.draw(bTrie);
    target.draw(bGraph);
}