#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <list>

using namespace std;

/*
class AdjList{
    int levels, rows, columns;
    list<int> *adjLists;

    public:
        AdjList(int v);
        void addEdge(int src, int dest);
    struct node*;
};*/

class vertex{
    bool visited = false;
    int value = -1;
};

int main(){
    ifstream maze;
    maze.open("tiny-maze.txt");
    if (maze.is_open())
        cout << "Success" << endl;
    else
        cout << "Problem opening input" << endl;

    int levels, rows, columns;
    maze >> levels >> rows >> columns;
    tuple <int, int, int> start, end;
    int temp1, temp2, temp3;
    maze >> temp1 >> temp2 >> temp3;
    start = make_tuple(temp1, temp2, temp3);
    maze >> temp1 >> temp2 >> temp3;
    end = make_tuple(temp1, temp2, temp3);

    cout << levels << " levels, " << rows << " rows, " << columns << " columns " << endl;
    cout << "Start Values: " << get<0>(start) << " " << get<1>(start) << " " << get<2>(start) << endl;
    cout << "Start Values: " << get<0>(end) << " " << get<1>(end) << " " << get<2>(end) << endl;

    //6 bit directional, North, East, South, West, Up, Down. 1 means connection, 0 means none
    vector<string> graph;
    string vertexContents;
    for (int i = 0; i < rows * columns * levels; i++){
        maze >> vertexContents;
        graph.push_back(vertexContents);
        cout << vertexContents<< " ";
    }
    cout << endl;
    //display contents of graph
    /*
    for (int i = 0; i < levels * rows * columns; i++){
        if (i % 3 == 0) cout << endl;
        if (i % 9 == 0) cout << endl;
        cout << graph.at(i) << " ";
    }
    */


    return 0;
}

void addEdge(vector<int> adj[], int vertex1, int vertex2){
    adj[vertex1].push_back(vertex2);
    adj[vertex2].push_back(vertex1);
}