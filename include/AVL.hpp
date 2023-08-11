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
    void initGraph(int);
    void checkBalance(std::shared_ptr <Node> );
    void checkBalanceInt(int);
    int getBalance(std::shared_ptr <Node>);
    void leftRotate(int, int );
    void rightRotate(int, int );
    std::shared_ptr <Node> newNode(int, std::shared_ptr <Node>);
    void resetNode(std::shared_ptr <Node> );
    int getHeight(std::shared_ptr <Node> );
    void getList(std::shared_ptr <Node>);
    void balancePosition();
    void setVerticalPosition(std::shared_ptr <Node>, int);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void insert(int);
    void remove(int);
    void search(int);
    void checkFunction() override;
    void checkFunctionFast() override;
    void checkPress(sf::Vector2f ) override;
    void fromfile();

    Graph graph, firstGraph;
    std::vector< std::pair < int, std::shared_ptr <Node> > > listNode;
};

#endif // AVL_hpp