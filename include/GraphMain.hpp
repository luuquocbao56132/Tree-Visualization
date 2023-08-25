#ifndef GraphMain_hpp
#define GraphMain_hpp

#include <BaseHeader.hpp>
#include <Node.hpp>
#include <DataTypes.hpp>  
#include <Graph.hpp>
#include <Theme.hpp>  

class GraphMain: public DataTypes {
public:
    GraphMain();
    void initGraph(int, int);
    void resetGraph();
    void dijktraFind(int);
    void findMST();
    void dsu();
    void dfs(int, sf::Color);
    void createGraph();
    sf::Vector2f frep(int, int);
    sf::Vector2f fspring(int, int);
    sf::Vector2f fattr(int, int);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void checkFunction() override;
    void checkFunctionFast() override;
    void MST();
    void Dijktra(int);
    void Component();
    void checkPress(sf::Vector2f ) override;
    void fromfile();

    int a[100][100], n, d[100];
    std::vector <std::pair <int,int> > listEdge;
    Node listNode[100];
    std::pair <DynArrow,sf::Text> listArrow[100][100];
};

#endif // GraphMain_hpp