#ifndef HashTable_hpp
#define HashTable_hpp

#include <BaseHeader.hpp>
#include <Button.hpp>
#include <DataTypes.hpp>
#include <Array.hpp>
#include <Theme.hpp>

class HashTable: public DataTypes {
public:
    HashTable();
    // HashTable(const sf::Vector2f& , const sf::Vector2f& ,
    //     const std::string& , const sf::Font& , unsigned int );
    // void LetsSearch(int);
    // void LetsInsert(int);
    // void LetsRemove(int);
    void draw(sf::RenderTarget& , sf::RenderStates ) const override;
    void insert(int);
    void remove(int);
    void search(int);
    void fromfile();
    void checkFunction() override;
    // void getFromFile();
    void checkPress(sf::Vector2f ) override;

    std::queue <Animation> funcQueue;
    Array graph;
};

#endif /* HashTable_hpp */