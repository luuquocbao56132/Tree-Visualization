#ifndef Animation_hpp
#define Animation_hpp

#include <BaseHeader.hpp>

class Animation {
public:
    Animation(std::vector<std::function <void(int,int)>>, std::vector<std::function <void(int)>>,
            std::vector <std::function <void(std::string)>>, std::vector <std::function <void()>>);
    void go();

    std::vector <std::function <void(int,int)> > void2para;
    std::vector <std::function <void(int)> > void1para;
    std::vector <std::function <void(std::string)> > voidString;
    std::vector <std::function <void()> > void0para;
};

#endif /* Animation_hpp */