#ifndef AVL_hpp
#define AVL_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>
#include <DataTypes.hpp>  
#include <Graph.hpp>
#include <Theme.hpp>  

class AVL: public DataTypes {
public:
    AVL();
    void initGraph();
    void checkBalance();
    int getBalance(std::shared_ptr <Node>);
    std::shared_ptr <Node> leftRotate(std::shared_ptr <Node> );
    std::shared_ptr <Node> rightRotate(std::shared_ptr <Node> );
    Node newNode(int, std::shared_ptr <Node>);
    void insertNode(int);
    void getList(std::shared_ptr <Node>);
    void balancePosition();
    void setVerticalPosition(std::shared_ptr <Node>, int);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void insert(int);
    void remove(int);
    void search(int);
    void checkFunction() override;
    void checkPress(sf::Vector2f ) override;
    void fromfile();

    Graph graph, firstGraph;
    std::vector< std::pair < int, std::shared_ptr <Node> > > listNode;
};

#endif // AVL_hpp