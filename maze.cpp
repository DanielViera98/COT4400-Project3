#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <list>

using namespace std;


class vertex{
    public:
        void addContents(string newContent) {contents = newContent;};
        string getContents() {return contents;};
        void addConnection(pair<char, int> connection) {
            connections->push_back(connection);
            numConnections++;
        };
        int getNumConnections() {return numConnections;};
        pair<char, int> getConnection(int i) {return connections->at(i);};
        void printConnections() {
            for (int i = 0; i < connections->size(); i++)
                cout << connections->at(i).first << " " << connections->at(i).second << " ";
        };
        void makeFinish() {finish = true;};
        bool isFinish() {return finish;};
        void makeVisited() {visited = true;};
        bool isVisited() {return visited;};
    private:
        bool visited = false;
        bool finish = false;
        string contents = " ";
        vector<pair<char, int>> connections[1];
        int numConnections = 0;

};
void addEdge(vector<vertex> graph[], int location1, int location2, char direction, char oppositeDir, ofstream& pairs);
void BFS(vector<vertex> graph[], vertex node, string path, string *final_path);
int main(){
    //Open file
    ifstream maze;
    maze.open("tiny-maze.txt");
    if (maze.is_open())
        cout << "Success" << endl;
    else
        cout << "Problem opening input" << endl;

    ofstream pairs;
    pairs.open("pairs.txt");

    //Get starter info including size of graph, start index, and finish index
    int levels, rows, columns;
    maze >> levels >> rows >> columns;
    int temp1, temp2, temp3;
    int finish, start = -1;
    maze >> temp1 >> temp2 >> temp3;
    start = temp1 * columns * rows + temp2 * columns + temp3;
    maze >> temp1 >> temp2 >> temp3;
    finish = temp1 * columns * rows + temp2 * columns + temp3;


    cout << levels << " levels, " << rows << " rows, " << columns << " columns " << endl;
    cout << "Start = " << start << endl;
    cout << "Finish = " << finish << endl;

    //6 bit directional, North, East, South, West, Up, Down. 1 means connection, 0 means none
    int graphSize = rows * columns * levels;
    vector<vertex> graph[graphSize];
    string vertexContents;
    for (int i = 0; i < graphSize; i++){
        maze >> vertexContents;
        vertex V;
        graph->push_back(V);
        graph->at(i).addContents(vertexContents);
        string test = graph->at(i).getContents();
        cout << test;
        cout << graph->at(i).getContents() << " ";
        if (vertexContents.at(0) == '1')    /*if spider can move north, connect with northern vertex*/
            addEdge(graph, i, i-columns, 'N', 'S', pairs);
        if (vertexContents.at(3) == '1')    /*if spider can move west, connect with western vertex*/
            addEdge(graph, i, i-1, 'W', 'E', pairs);
        if (vertexContents.at(5) == '1')    /*if spider can move down, connect with lower vertex*/
            addEdge(graph, i, i-columns*rows, 'D', 'U', pairs);
    }
    graph->at(finish).makeFinish();
    cout << endl << "DISPLAY CONTENTS" << endl;
    //display contents of graph
    
    for (int i = 0; i < graphSize; i++){
        if (i % 3 == 0) cout << endl;
        if (i % 9 == 0) cout << endl;
        cout << graph->at(i).getContents() << " ";
        graph->at(i).printConnections();
    }

    
    string final_path;
    string path = "";
    BFS(graph, graph->at(start), path, &final_path);
    cout << endl << "PATH TO GOAL: " << final_path << endl;
    return 0;
}

void addEdge(vector<vertex> graph[], int location1, int location2, char direction, char oppositeDir, ofstream& pairs){
    cout << "(Connecting " << graph->at(location1).getContents() << " " << graph->at(location2).getContents() << ")" << endl;
    pairs << graph->at(location1).getContents() << " " << graph->at(location2).getContents() << " " << direction << "-" << oppositeDir << endl;
    pair<char, int> newConnection;
    newConnection.first = direction;
    newConnection.second = location2;
    graph->at(location1).addConnection(newConnection);

    newConnection.first = oppositeDir;
    newConnection.second = location1;
    graph->at(location2).addConnection(newConnection);
}

void BFS(vector<vertex> graph[], vertex node, string path, string *final_path){
    node.makeVisited();
    if (node.isFinish()){
        *final_path = path;
    }
    else{
        for (int i = 0; i < node.getNumConnections(); i++){
            if (graph->at(node.getConnection(i).second).isVisited() == 0){
                node.makeVisited();
                graph->at(node.getConnection(i).second).makeVisited();
                path = path + node.getConnection(i).first + " ";
                BFS(graph, graph->at(node.getConnection(i).second), path, final_path);
                path.pop_back();
                path.pop_back();
            }
        }
    }
}
