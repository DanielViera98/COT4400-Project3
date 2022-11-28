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
        void addConnection(pair<char, int> connection) {connections->push_back(connection);};
        void printConnections() {
            for (int i = 0; i < connections->size(); i++)
                cout << connections->at(i).first << " " << connections->at(i).second << " ";
        };
    private:
        bool visited = false;
        bool finish = false;
        string contents = " ";
        vector<pair<char, int>> connections[1];

};
void addEdge(vector<vertex> graph[], int location1, int location2, char direction, char oppositeDir);
int main(){
    ifstream maze;
    maze.open("tiny-maze.txt");
    if (maze.is_open())
        cout << "Success" << endl;
    else
        cout << "Problem opening input" << endl;

    int levels, rows, columns;
    maze >> levels >> rows >> columns;
//    tuple <int, int, int> start, end;
    int temp1, temp2, temp3;
    int finish, start = -1;
    maze >> temp1 >> temp2 >> temp3;
//    start = make_tuple(temp1, temp2, temp3);
    start = temp1 * columns * rows + temp2 * columns + temp3;
    maze >> temp1 >> temp2 >> temp3;
//    end = make_tuple(temp1, temp2, temp3);
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
            addEdge(graph, i, i-columns, 'N', 'S');
        if (vertexContents.at(3) == '1')    /*if spider can move west, connect with western vertex*/
            addEdge(graph, i, i-1, 'W', 'E');
        if (vertexContents.at(5) == '1')    /*if spider can move down, connect with lower vertex*/
            addEdge(graph, i, i-columns*rows, 'D', 'U');
    }

    cout << endl << "DISPLAY CONTENTS" << endl;
    //display contents of graph
    
    for (int i = 0; i < graphSize; i++){
        if (i % 3 == 0) cout << endl;
        if (i % 9 == 0) cout << endl;
        cout << graph->at(i).getContents() << " ";
        graph->at(i).printConnections();
    }
    


    return 0;
}

void addEdge(vector<vertex> graph[], int location1, int location2, char direction, char oppositeDir){
    cout << "(Connecting " << graph->at(location1).getContents() << " to " << graph->at(location2).getContents() << ")" << endl;
    pair<char, int> newConnection;
    newConnection.first = direction;
    newConnection.second = location2;
    graph->at(location1).addConnection(newConnection);

    newConnection.first = oppositeDir;
    newConnection.second = location1;
    graph->at(location2).addConnection(newConnection);
}

