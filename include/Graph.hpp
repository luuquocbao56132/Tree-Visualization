#ifndef Graph_hpp
#define Graph_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>
#include <Highlight.hpp>

class Game;

class Graph: public sf::Transformable, public sf::Drawable {
public:
    Graph();
    Graph(int);
    Graph& operator=(Graph& other);
    void init(int, LinkedList <std::string> );
    void init(int );
    void init();
    void setNode();
    bool checkSameNum(int );
    int randomNodeValue();
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

    void removeNode(int );
    void setNodeColor(int, sf::Color);
    void setArrowColor(int, float);

    void setSearchingNode(int, float);
    void setDelNode(int, float);
    void removeSearchingNode(int, float);
    void setFoundNode(int, float);
    void removeFoundNode(int, float);

    void makeNewNode(int, int);
    int getValue(int );
    void setValue(int,int);
    int getSize();
    void setSize(int);

    void resetStep();
    void getStep(int );
    void saveStep();

    int typeGraph, numArrow, nowStep;
    std::shared_ptr <int> n;
    LinkedList <std::shared_ptr <Node>> listNode;
    LinkedList < LinkedList <std::shared_ptr<Node> > > stepNode, stepListNew;
    LinkedList < std::shared_ptr <Node> > stepNewNode, listNew;
    LinkedList <int> stepString, stepIsListNew;
    Highlight highlight;
    std::shared_ptr <Node> newNode;
    int leftBound, numberNow, isListNew;
    std::set <int> setNumber;
};

#endif //Graph_hpp