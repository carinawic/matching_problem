// basic file operations
#include <iostream>
#include <fstream>
using namespace std;

const int maxEdges = 10000;

int main () {
    ofstream myfile;
    myfile.open ("generatedGraph.txt");
    myfile << maxEdges+1 << "\n";
    myfile << 1 << " " << 2 << "\n";
    myfile << maxEdges << "\n";

    for(int i=0;i<maxEdges;i++){
        myfile << 1 << " " << i+2 << " " << 1 << "\n";
    }

    myfile.close();
    return 0;
}