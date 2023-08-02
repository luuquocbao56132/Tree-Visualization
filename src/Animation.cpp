#include <Animation.hpp>

Animation::Animation(std::vector<std::function <void(int,int)>> a, std::vector<std::function <void(int)>> b, 
        std::vector <std::function <void(std::string)>> c){
    void2para = a;
    void1para = b;
    voidString = c;
}

void Animation::go(){
    for (auto i : void2para)i(0,0);
    for (auto i : void1para)i(0);
    for (auto i : voidString)i("");
}