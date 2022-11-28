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

/*class vertex{
    bool visited = false;
    int value = -1;
};*/
void addEdge(vector<vector<string>> adj[], vector<string> vertex1, vector<string> vertex2, int location1, int location2);
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
    vector<vector<string>> graph;
    vector<string> vertex;
    string vertexContents;
    for (int i = 0; i < rows * columns * levels; i++){
        maze >> vertexContents;
        vertex.push_back(vertexContents);
        graph.push_back(vertex);
        cout << graph.back().at(0) << " ";
        if (vertexContents.at(0) == '1')    /*if spider can move north, connect with northern vertex*/
            addEdge(&graph, graph.back(), graph.at(i-columns), i, i-columns);
        if (vertexContents.at(3) == '1')    /*if spider can move west, connect with western vertex*/
            addEdge(&graph, graph.back(), graph.at(i-1), i, i-1);
        if (vertexContents.at(5) == '1')    /*if spider can move down, connect with lower vertex*/
            addEdge(&graph, graph.back(), graph.at(i-columns*rows), i, i-columns*rows);
        vertex.clear();
    }
    cout << endl;
    //display contents of graph
    
    for (int i = 0; i < levels * rows * columns; i++){
        if (i % 3 == 0) cout << endl;
        if (i % 9 == 0) cout << endl;
        cout << graph.at(i).at(0) << " ";
    }
    


    return 0;
}

void addEdge(vector<vector<string>> adj[], vector<string> vertex1, vector<string> vertex2,
 int location1, int location2){
    cout << "(Connecting " << vertex1.at(0) << " to " << vertex2.at(0) << ")" << endl;
    vertex1.push_back(vertex2.at(0));
    vertex2.push_back(vertex1.at(0));
    cout << "Finished 1, v1.0 = " << vertex1.at(0) << " & v1.1 = " << vertex1.at(1);
    cout << ", v2.0 = " << vertex2.at(0) << " & v2.1 = " << vertex2.at(1) << endl;

    cout << adj->size() << "long, " << location1 << " " << location2 << endl;
    if (location1 < 0 || location2 < 0){
        cout << "size 0" << endl;
        return;
    }
    if (location1 >= adj->size()){
        cout << "Resize" << endl;
        adj->resize(location1+1);
    }
    adj[location1].push_back(vertex2);
    cout << "Finished 1" << endl;
    adj[location2].emplace_back(vertex1);
    cout << "Finished 2" << endl;
}