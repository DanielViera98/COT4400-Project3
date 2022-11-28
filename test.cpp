#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <list>

using namespace std;

void addEdge(vector<int> testGraph[], int first, int second);
int main(){
    vector<int> testGraph[10];
    /*
    testGraph.push_back(1);
    testGraph.push_back(3);
    testGraph.push_back(2);
    */
    int first, second;
//    first = testGraph.at(0);
//    second = testGraph.at(2);
    cout << "sending to addEdge" << endl;
    addEdge(testGraph, 1, 2);
    cout << testGraph[0].size() << " " << testGraph[1].size() << " " << testGraph[2].size() << endl;
    cout << testGraph[1].at(0) << " " << testGraph[2].at(0) << endl;
    return 0;
}

void addEdge(vector<int> testGraph[], int first, int second){
    testGraph[first].push_back(second);
    testGraph[second].push_back(first);
    return;
}