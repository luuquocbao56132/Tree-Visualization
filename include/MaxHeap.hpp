#ifndef MaxHeap_hpp
#define MaxHeap_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>
#include <DataTypes.hpp>  
#include <Theme.hpp>  

class MaxHeap: public DataTypes {
public:
    MaxHeap();
    void initGraph(int);
    std::shared_ptr <Node> newNode(int);
    void resetNode();
    void getList(std::shared_ptr <Node>);
    void balancePosition();
    void setVerticalPosition(std::shared_ptr <Node>, int);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void insert(int);
    void remove(int);
    void search(int);
    void runUp(int);
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

#endif // MaxHeap_hpp