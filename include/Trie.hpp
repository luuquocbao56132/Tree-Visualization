#ifndef Trie_hpp
#define Trie_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>
#include <DataTypes.hpp>  
#include <Graph.hpp>
#include <Theme.hpp>  

class Trie: public DataTypes {
public:
    Trie();
    void initGraph(int);
    std::shared_ptr <Node> newNode(std::string, std::shared_ptr <Node>);
    void resetNode(std::shared_ptr <Node> );
    int getHeight(std::shared_ptr <Node> );
    void sortNode(std::shared_ptr <Node> );
    int balancePosition(std::shared_ptr <Node>, int, int);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    bool checkPosition(std::shared_ptr <Node> );
    bool checkArrow(std::shared_ptr <Node> );
    void checkPositionFast(std::shared_ptr <Node> );
    void checkArrowFast(std::shared_ptr <Node> );
    void insertNode(std::string, std::shared_ptr <Node>);
    void insert(std::string);
    void remove(std::string);
    void search(std::string);
    void checkFunction() override;
    void checkFunctionFast() override;
    void checkPress(sf::Vector2f ) override;
    void fromfile();

    int leftLimitBound;
    Graph graph, firstGraph;
    std::vector< std::pair < int, std::shared_ptr <Node> > > listNode;
};

#endif // Trie_hpp