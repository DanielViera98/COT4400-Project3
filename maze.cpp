#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class vertex{
    public:
        void addConnection(pair<char, int> connection) {
            connections->push_back(connection);
            numConnections++;
        };
        int getNumConnections() {return numConnections;};
        pair<char, int> getConnection(int i) {return connections->at(i);};
        void makeFinish() {finish = true;};
        bool isFinish() {return finish;};
        void makeVisited() {visited = true;};
        bool isVisited() {return visited;};
    private:
        bool visited = false;
        bool finish = false;
        vector<pair<char, int>> connections[1];
        int numConnections = 0;

};
void addEdge(vector<vertex> graph[], int location1, int location2, char direction, char oppositeDir);
void BFS(vector<vertex> graph[], vertex node, string path, string *final_path);
int main(){
    //Open input file
    ifstream maze;
    maze.open("itsybitsy-maze.txt");
    if (maze.is_open())
        cout << "Success" << endl;
    else
        cout << "Problem opening input" << endl;

    //open output file
    ofstream output;
    output.open("output.txt");
    if (output.is_open())
        cout << "Success" << endl;
    else
        cout << "Problem opening output" << endl;

    //Get starter info including size of graph, start index, and finish index
    int levels, rows, columns;
    maze >> levels >> rows >> columns;
    int temp1, temp2, temp3;
    int finish, start = -1;
    maze >> temp1 >> temp2 >> temp3;
    start = temp1 * columns * rows + temp2 * columns + temp3;
    maze >> temp1 >> temp2 >> temp3;
    finish = temp1 * columns * rows + temp2 * columns + temp3;

    //6 bit directional, North, East, South, West, Up, Down. 1 means connection, 0 means none
    int graphSize = rows * columns * levels;
    vector<vertex> graph[graphSize];        //create graph
    string vertexContents;
    for (int i = 0; i < graphSize; i++){        //iterate through input file
        maze >> vertexContents;
        vertex V;                               //create vertex
        graph->push_back(V);
        if (vertexContents.at(0) == '1')    /*if spider can move north, connect with northern vertex*/
            addEdge(graph, i, i-columns, 'N', 'S');
        if (vertexContents.at(3) == '1')    /*if spider can move west, connect with western vertex*/
            addEdge(graph, i, i-1, 'W', 'E');
        if (vertexContents.at(5) == '1')    /*if spider can move down, connect with lower vertex*/
            addEdge(graph, i, i-columns*rows, 'D', 'U');
    }
    //set end node to be finish
    graph->at(finish).makeFinish();
    
    //get final path, call BFS, output result to file
    string final_path;
    string path = "";
    BFS(graph, graph->at(start), path, &final_path);
    output << final_path;

    return 0;
}

//adds edge between two vertices
void addEdge(vector<vertex> graph[], int location1, int location2, char direction, char oppositeDir){
    pair<char, int> newConnection;

    //create connection from first to second vertex
    newConnection.first = direction;
    newConnection.second = location2;
    graph->at(location1).addConnection(newConnection);

    //create connection from second to first vertex
    newConnection.first = oppositeDir;
    newConnection.second = location1;
    graph->at(location2).addConnection(newConnection);
}

//Do a BFS to find the path from start to end
void BFS(vector<vertex> graph[], vertex node, string path, string *final_path){
    //if the node is the final node, change the pointer to the correct path
    if (node.isFinish()){
        *final_path = path;
    }
    else{
        //iterate through the vertex's edge list
        for (int i = 0; i < node.getNumConnections(); i++){
            //if the edge goes to a node not yet visited, call BFS on it
            if (graph->at(node.getConnection(i).second).isVisited() == 0){
                graph->at(node.getConnection(i).second).makeVisited();      //mark next node as visited
                path = path + node.getConnection(i).first + " ";            //update path with next direction
                BFS(graph, graph->at(node.getConnection(i).second), path, final_path);  //go to next node
                path.pop_back();    //removes space    
                path.pop_back();    //removes previous step
            }
        }
    }
}
