
#include "classes/QuadTree.h"

int main(){
    /* //EJEMPLO 1
    Quad_tree tree(Point{100, 100});
    tree.insert(Point{50, 50}, 20);
    tree.insert(Point{20, 50}, 20);
    tree.insert(Point{40, 50}, 20);
    tree.insert(Point{50, 30}, 20);
    tree.insert(Point{50, 10}, 20);
    tree.insert(Point{50, 90}, 20); */

    /* //EJEMPLO 2 
    Quad_tree tree(Quadrant{0,127,0,127});
    tree.insert(Point{40, 45}, 20);
    tree.insert(Point{15, 70}, 20);
    tree.insert(Point{70, 10}, 20);
    tree.insert(Point{69, 50}, 20);
    tree.insert(Point{55, 80}, 20);
    tree.insert(Point{80, 90}, 20); */

    /* string in_file = "img/dragon.pgm";
    string out_file = "img/dragon_bin";
    char new_image_file[] = "img/dragon_new.pgm";

    Quad_tree tree;
    tree.read_image(in_file);
    tree.write_image(out_file); */
    //tree.generate_new_image(out_file,new_image_file);
    return 0;
}