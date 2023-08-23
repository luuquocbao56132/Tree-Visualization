#ifndef Twothree_hpp
#define Twothree_hpp

#include <BaseHeader.hpp>
// #include <Node.hpp>
#include <TwothreeNode.hpp>
#include <DataTypes.hpp>  
#include <Graph.hpp>
#include <Theme.hpp>  

class Twothree: public DataTypes {
public:
    Twothree();
    void initGraph(int);
    std::shared_ptr <TwothreeNode> newNode(std::vector <std::string> , std::shared_ptr <TwothreeNode>, sf::Vector2f);
    void resetNode(std::shared_ptr <TwothreeNode> );
    int getHeight(std::shared_ptr <TwothreeNode> );
    void sortNode(std::shared_ptr <TwothreeNode> );
    int balancePosition(std::shared_ptr <TwothreeNode> , int , int );
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    bool checkPosition(std::shared_ptr <TwothreeNode> );
    bool checkArrow(std::shared_ptr <TwothreeNode> );
    void checkPositionFast(std::shared_ptr <TwothreeNode> );
    void checkArrowFast(std::shared_ptr <TwothreeNode> );
    std::shared_ptr <TwothreeNode> checkAlone(std::shared_ptr <TwothreeNode> );
    void insertNode(std::shared_ptr <TwothreeNode> , std::shared_ptr <TwothreeNode> , int , int, bool);
    void removingNode(std::shared_ptr <TwothreeNode>, int);
    void continueRemove(std::shared_ptr <TwothreeNode>, int);
    void insert(int);
    void remove(int);
    void search(int);
    void checkFunction() override;
    void checkFunctionFast() override;
    void checkPress(sf::Vector2f ) override;
    void fromfile();

    std::vector <int> listInsert;
    std::vector< std::pair < int, std::shared_ptr <TwothreeNode> > > listNode;
    std::shared_ptr <TwothreeNode> root;
};

#endif // Twothree_hpp