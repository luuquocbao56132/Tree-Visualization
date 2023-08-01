#ifndef Array_hpp
#define Array_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>
#include <Highlight.hpp>

class Game;

class Array: public sf::Transformable, public sf::Drawable {
public:
    Array();
    Array(int);
    Array& operator=(Array& other);
    void init(int, std::vector <std::string> );
    void init(int );
    void init();
    void setNode();
    bool checkSameNum(int );
    int randomNodeValue();
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;

    void delValue(int );
    void setNodeColor(int, sf::Color);
    void setArrowColor(int, float);

    void setSearchingNode(int, float);
    void setDelNode(int, float);
    void removeSearchingNode(int, float);
    void setFoundNode(int, float);
    void removeFoundNode(int, float);

    void insertValue(int);
    void search(int);
    int getValue(int );
    int getNumValue();
    void setValue(int,int);
    int getSize();
    void setSize(int);

    void resetStep();
    void getStep(int );
    void saveStep();

    int typeArray, numArrow, nowStep;
    int n, numValue;
    std::vector <std::shared_ptr <Node>> listNode;
    std::vector < std::vector <std::shared_ptr<Node> > > stepNode, stepListNew;
    std::vector < std::shared_ptr <Node> > stepNewNode, listNew;
    std::vector <int> stepString, stepIsListNew;
    Highlight highlight;
    std::shared_ptr <Node> newNode;
    int leftBound, numberNow, isListNew;
    std::set <int> setNumber;
};

#endif //Array_hpp