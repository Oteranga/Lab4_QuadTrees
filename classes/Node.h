#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Point{
    int x = -1; //Also considered first point
    int y = -1; //Also considered second point
};

struct Quadrant{
    int xmin;
    int xmax;
    int ymin;
    int ymax;
};

struct Node{
    Point point;
    int key = -1;
    Quadrant quadrant;
    Node* children[4] = {nullptr};
    Node(Point _point, int value, Quadrant _quadrant) : point(_point), key(value), quadrant(_quadrant){}

    Node(Point _point, int value): point(_point), key(value){}

    Node(Quadrant _quadrant): quadrant(_quadrant){}

    Node(){}

    bool empty_point(){ return (this->point.x == -1 && this->point.y == -1 && key == -1); }

    bool no_children(){
        return (children[0] == nullptr && children[1] == nullptr && children[2] == nullptr && children[3] == nullptr);
    }
};