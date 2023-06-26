#ifndef BaseHeader_hpp
#define BaseHeader_hpp

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <Resource.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include <string>
#include <array>
#include <string.h>
#include <set>
#include <fstream>
#include <windows.h>
#include <memory>

enum Direction{
        TOP,
        RIGHT,
        BOT,
        LEFT
    };

enum Function{
    CREATE,
    SEARCH,
    PEEK = SEARCH,
    INSERT,
    PUSH = INSERT,
    REMOVE,
    POP = REMOVE,
    UPDATE,
    CLEAR = UPDATE,
    ACCESS
};

enum AroundNode{
    Prev,
    Next
};

enum TypeGraph{
    ARRAY,
    LINKEDLIST,
    DOUBLYLINKEDLIST,
    CIRCULARLINKEDLIST
};

static float CircleRad = 19;
static float nodeDistance = 60;
static float textSize = 19;
static sf::Color TextColor[2] = {sf::Color(40, 42, 54), sf::Color(237, 242, 245)};
static sf::Color ButtonColor[2] = {sf::Color(255,255,255), sf::Color(48, 59, 89)};
static sf::Color HoverColor[2] = {sf::Color(124, 152, 231), sf::Color(25, 38, 74)};
static sf::Color textColorStart = sf::Color::Black;
static sf::Color textColorEnd = sf::Color::White;
static sf::Color backgroundColor(238,238,238);
static sf::Color endStateColor(255, 138, 39);
static sf::Color FirstNodeColor(238, 238, 238);
static sf::Color SearchingNodeColor(255, 138, 39);
static sf::Color FoundNodeColor(46, 187, 209);
static sf::Color NewNodeColor(82, 188, 105);
static sf::Color DelNodeColor(217, 81, 60);
static sf::Color BlurNodeColor(62,62,62);
static sf::Vector2f inputButtonSize = sf::Vector2f(60,50);
static int maxValue = 99;
static int maxSize = 15;
static float timeLength = 1000;
static float arrowLength = 60;
static float nodeRadius = 19;
static float TimePerFrame = 1/60;
extern std::string theme;
extern int typeTheme;
extern bool isThemeChange;
extern float numFrame;
extern float xtime;

template<typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr)
            : data(d), next(n) {}
    };
    Node* head;
public:
    class Iterator {
    public:
        Iterator(Node* node) : node(node) {}
        bool operator!=(const Iterator& other) const { return node != other.node; }
        Iterator& operator++() { node = node->next; return *this; }
        T& operator*() const { return node->data; }
    private:
        Node* node;
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
    LinkedList() : head(nullptr) {}
    
    // Constructor that takes an initializer list
    LinkedList(std::initializer_list<T> init) : head(nullptr) {
        for (auto elem : init) {
            push_back(elem);
        }
    }
    
    ~LinkedList() {
        clear();
    }
    
    LinkedList(const LinkedList& other) : head(nullptr) {
        Node** curr = &head;
        for (Node* temp = other.head; temp; temp = temp->next) {
            *curr = new Node(temp->data);
            curr = &((*curr)->next);
        }
    }
    
    LinkedList& operator=(const LinkedList& other) {
        LinkedList temp(other);
        std::swap(head, temp.head);
        return *this;
    }
    
    void push_back(const T& value) {
        if (!head) {
            head = new Node(value);
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new Node(value);
        }
    }
    
    void pop_back() {
        if (!head) {
            return;
        } else if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }
    
    T& operator[](std::size_t index) {
        Node* temp = head;
        for (std::size_t i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    
    const T& operator[](std::size_t index) const {
        Node* temp = head;
        for (std::size_t i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }
    
    std::size_t size() const {
        std::size_t count = 0;
        for (Node* temp = head; temp; temp = temp->next) {
            count++;
        }
        return count;
    }
    
    // Implementation of the clear() method
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Implementation of the empty() method
    bool empty() const {
        return head == nullptr;
    }

    void resize(std::size_t newSize, const T& value = T()) {
    if (newSize == 0) {
        clear();
        return;
    }
    if (newSize < size()) {
        Node* temp = head;
        for (std::size_t i = 0; i < newSize - 1; i++) {
            temp = temp->next;
        }
        Node* del = temp->next;
        temp->next = nullptr;
        while (del) {
            Node* next = del->next;
            delete del;
            del = next;
        }
    } else if (newSize > size()) {
        std::size_t numToAdd = newSize - size();
        Node* temp = head;
        if (!temp) {
            head = new Node(value);
            numToAdd--;
            temp = head;
        } else {
            while (temp->next) {
                temp = temp->next;
            }
        }
        for (std::size_t i = 0; i < numToAdd; i++) {
            temp->next = new Node(value);
            temp = temp->next;
        }
    }
}

};


//static float M_PI = 3.14159;
// #include "Game.hpp"
class Game;
// static std::shared_ptr <Game> gameGlobal = std::make_shared<Game>();;

#endif // BaseHeader_hpp