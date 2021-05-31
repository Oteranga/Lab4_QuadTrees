
#include "classes/QuadTree.h"

void generate_new_image(string image_bin, char* file_name, pair<int,int> dimensions){
    ifstream file_bin;
    FILE* file_new;
    file_bin.open(image_bin,ios::in|ios::binary);
    if(!file_bin)
        exit(EXIT_FAILURE); 
    file_new = fopen(file_name, "w");
    int height = dimensions.second;
    int width = dimensions.first;
    int image[height][width]={0};
    fprintf(file_new,"P2\n");
    fprintf(file_new,"# Comment\n");
    fprintf(file_new,"%d %d\n",width,height);
    fprintf(file_new,"255\n");
    TempNode temp;
    int line=0;
    while(!file_bin.eof()){
        file_bin.read((char*)&temp,sizeof(TempNode));
        for(int i = temp.xmin; i < temp.xmax; ++i){
            for (int j = temp.ymin; j < temp.ymax; ++j){
                image[i][j] = temp.key;
            }
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            fprintf(file_new, "%d ", image[i][j]);
        }
        fprintf(file_new,"\n");
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

    //EJEMPLO 2 
    /* Quad_tree tree(Quadrant{0,127,0,127});
    tree.insert(Point{40, 45}, 20);
    tree.insert(Point{15, 70}, 20);
    tree.insert(Point{70, 10}, 20);
    tree.insert(Point{69, 50}, 20);
    tree.insert(Point{55, 80}, 20);
    tree.insert(Point{80, 90}, 20); */

    string in_file = "img/hands.pgm";
    string out_file = "bin/hands_bin";
    char new_image_file[] = "new_img/hands_new.pgm";

    Quad_tree tree;
    tree.read_image(in_file);
    tree.write_image(out_file);
    generate_new_image(out_file,new_image_file,tree.get_dimensions());
    return 0;
}