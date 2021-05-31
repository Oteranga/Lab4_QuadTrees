
#include "classes/QuadTree.h"

void generate_new_image(string image_bin, char* file_name, pair<int,int> dimensions){
    fstream file_bin;
    FILE* file_new;
    file_bin.open(file_name,ios::binary|ios::in|ios::app);
    if(!file_bin)
        exit(EXIT_FAILURE); 
    file_new = fopen(file_name, "w");
    int height = dimensions.second;
    int width = dimensions.first;
    int image[height][width];
    fprintf(file_new,"P2\n");
    fprintf(file_new,"%d %d\n",width,height);
    fprintf(file_new,"255\n");
    Node temp;
    int line=0;
    //file_bin.read(reinterpret_cast<char*>(&temp),sizeof(Node));
    while(file_bin.read(reinterpret_cast<char*>(&temp),sizeof(Node))){
    //while(!file_bin.eof()){
        //file_bin.seekg(line*sizeof(Node));
        //file_bin.read((char*)&temp,sizeof(Node));
        for(int i = temp.quadrant.xmin; i < temp.quadrant.xmax; ++i){
            for (int j = temp.quadrant.ymin; j < temp.quadrant.ymax; ++j){
                image[i][j] = temp.key;
            }
        }
        line++;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            fprintf(file_new, "%d\n", image[i][j]);
        }
    }
    file_bin.close();
    fclose(file_new);
}

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

    string in_file = "img/dragon.pgm";
    string out_file = "img/dragon_bin";
    char new_image_file[] = "img/dragon_new.pgm";

    Quad_tree tree;
    tree.read_image(in_file);
    tree.write_image(out_file);
    generate_new_image(out_file,new_image_file,tree.get_dimensions());
    return 0;
}