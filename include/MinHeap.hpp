#ifndef MinHeap_hpp
#define MinHeap_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>
#include <DataTypes.hpp>  
#include <Theme.hpp>  

class MinHeap: public DataTypes {
public:
    MinHeap();
    void initGraph(int);
    std::shared_ptr <Node> newNode(int);
    sf::Vector2f getPosI(int );
    void resetNode();
    void balancePosition();
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void insert(int);
    void remove(int);
    void getTop();
    void runUp(int,int);
    void runDown(int);
    void checkFunction() override;
    void checkFunctionFast() override;
    bool checkPosition();
    bool checkArrow();
    void checkPositionFast();
    void checkArrowFast();
    void checkPress(sf::Vector2f ) override;
    void fromfile();

    int numValue;
    std::vector < std::shared_ptr <Node> > listNode;
    std::vector < std::pair <DynArrow, DynArrow> > listArrow;
};

#endif // MinHeap_hpp