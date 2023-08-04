#include <Animation.hpp>

Animation::Animation(std::vector<std::function <void(int,int)>> a, std::vector<std::function <void(int)>> b, 
        std::vector <std::function <void(std::string)>> c, std::vector <std::function <void()>> d){
    void2para = a;
    void1para = b;
    voidString = c;
    void0para = d;
}

void Animation::go(){
    for (auto i : void2para)i(0,0);
    for (auto i : void1para)i(0);
    for (auto i : voidString)i("");
    for (auto i : void0para)i();
}