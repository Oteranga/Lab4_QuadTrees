#include "Node.h"
#include <fstream>
#include <sstream>

class Quad_tree{
    private:
        Node* root;
        Quadrant quadrant;
        int number_nodes;
        bool insert(Node* _root, Node* _new_node);
        bool split_limit(Quadrant quadrant);
        int verify_cardinality(Quadrant quadrant, Point new_node);
        bool in_range(Quadrant quadrant, Point point);
        void switch_children(Node* _root, Node* new_node);
        void write_leaf_nodes(Node* _root, ofstream& file);
    public:
        Quad_tree():number_nodes(0),root(new Node){};
        Quad_tree(Quadrant quadrant);
        void insert(Point point, int key);
        int size();
        void read_image(string file_name);
        void write_image(string file_name);
        void generate_new_image(string image_bin, char* file_name);
};

void Quad_tree::read_image(string file_name){
    int height = 0, width = 0, max_value = 0;
    fstream infile(file_name);
    stringstream ss;
    string inputLine = "";

    // First line : version
    getline(infile,inputLine);
    if(inputLine.compare("P2") != 0) cerr << "Version error" << endl;

    // Second line : comment
    getline(infile,inputLine);

    ss << infile.rdbuf();
    // Third line : size
    ss >> width >> height;
    
    //Max value in the image
    ss >> max_value;

    this->quadrant= Quadrant{0,width,0,height};

    int num;
    for(int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            ss >> num;
            insert(Point{i,j},num);
        }
    }
}

void Quad_tree::write_image(string filename){
    ofstream file;
    file.open(filename,ios::binary);
    if(!file)
        exit(EXIT_FAILURE); 
    write_leaf_nodes(this->root,file);
    file.close();
}

void Quad_tree::write_leaf_nodes(Node* _root, ofstream& file){
    if(_root->no_children()){
        if(_root->key==-1)
            return;
        else
            file.write((char*)&_root,sizeof(Node));
    } else {
        for(int i=0; i<4; i++){
            write_leaf_nodes(_root->children[i],file);
        }
    }
}

void Quad_tree::generate_new_image(string image_bin, char* file_name){
    ifstream file_bin;
    FILE* file_new;
    file_bin.open(file_name);
    file_new = fopen(file_name, "w");
    int height = root->quadrant.ymax;
    int width = root->quadrant.xmax;
    int image[height][width];
    fprintf(file_new,"P2\n");
    fprintf(file_new,"%d %d\n",width,height);
    fprintf(file_new,"255\n");
    Node* temp;
    while(!file_bin.eof()){
        file_bin.read((char*)&temp,sizeof(temp));
        for(int i = temp->quadrant.xmin; i < temp->quadrant.xmax; ++i){
            for (int j = temp->quadrant.ymin; j < temp->quadrant.ymax; ++j){
                image[i][j] = temp->key;
            }
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            fprintf(file_new, "%d\n", image[i][j]);
        }
    }
    file_bin.close();
    fclose(file_new);
}

Quad_tree::Quad_tree(Quadrant quadrant){
    this->root = new Node;
    this->root->quadrant = quadrant;
    this->quadrant = quadrant;
    this->number_nodes = 0;
}

int Quad_tree::size(){ return this->number_nodes; }

bool Quad_tree::split_limit(Quadrant quadrant){
    return (quadrant.xmax-quadrant.xmin <= 1 || quadrant.ymax - quadrant.ymin <= 1);
}

int Quad_tree::verify_cardinality(Quadrant quadrant, Point new_node){
    if(quadrant.xmin <= new_node.x && (quadrant.xmin+quadrant.xmax)/2 > new_node.x && quadrant.ymin <= new_node.y && (quadrant.ymin+quadrant.ymax)/2 > new_node.y)
        return 0;
    else if((quadrant.xmin+quadrant.xmax)/2 <= new_node.x && quadrant.xmax > new_node.x && quadrant.ymin <= new_node.y && (quadrant.ymin+quadrant.ymax)/2 > new_node.y)
        return 1;
    else if(quadrant.xmin <= new_node.x && (quadrant.xmin+quadrant.xmax)/2 > new_node.x && (quadrant.ymin+quadrant.ymax)/2 <= new_node.y && quadrant.ymax > new_node.y)
        return 2;
    else if((quadrant.xmin+quadrant.xmax)/2 <= new_node.x && quadrant.xmax > new_node.x && (quadrant.ymin+quadrant.ymax)/2 <= new_node.y && quadrant.ymax > new_node.y)
        return 3;
    return -1;
}

bool Quad_tree::in_range(Quadrant quadrant, Point point){
    return (point.x >= quadrant.xmin && point.y >= quadrant.ymin && point.x < quadrant.xmax && quadrant.ymax > point.y);
}

void Quad_tree::insert(Point point, int key){
    auto new_node = new Node(point,key);
    auto temp_root = this->root;
    number_nodes++;
    insert(temp_root, new_node);
}

void Quad_tree::switch_children(Node* _root, Node* new_node){
    switch (verify_cardinality(_root->quadrant,new_node->point)){
        case 0:
            insert(_root->children[0], new_node);
            break;
        case 1:
            insert(_root->children[1], new_node);
            break;
        case 2:
            insert(_root->children[2], new_node);
            break;
        case 3:
            insert(_root->children[3], new_node);
            break;
        default:
            break;
        }
}

bool Quad_tree::insert(Node* _root,Node* new_node){
    if(!in_range(_root->quadrant,new_node->point)) return false;
    if(!_root->no_children()){
        switch_children(_root,new_node);
    } else {
        if(_root->empty_point()){
            _root->point = new_node->point;
            _root->key = new_node->key;
            return true;
        } else{
            Quadrant r_quadrant = _root->quadrant;
            _root->children[0] = new Node(Quadrant{r_quadrant.xmin,(r_quadrant.xmin+r_quadrant.xmax)/2,r_quadrant.ymin,(r_quadrant.ymin+r_quadrant.ymax)/2});
            _root->children[1] = new Node(Quadrant{(r_quadrant.xmin+r_quadrant.xmax)/2,r_quadrant.xmax,r_quadrant.ymin,(r_quadrant.ymin+r_quadrant.ymax)/2});
            _root->children[2] = new Node(Quadrant{r_quadrant.xmin,(r_quadrant.xmin+r_quadrant.xmax)/2,(r_quadrant.ymin+r_quadrant.ymax)/2,r_quadrant.ymax});
            _root->children[3] = new Node(Quadrant{(r_quadrant.xmin+r_quadrant.xmax)/2,r_quadrant.xmax,(r_quadrant.ymin+r_quadrant.ymax)/2,r_quadrant.ymax});
            switch_children(_root,_root);
            switch_children(_root,new_node);
            _root->point = Point{-1,-1};
            _root->key = -1;
        }
    }
    return true;
}