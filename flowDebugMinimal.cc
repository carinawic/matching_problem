/*
*
*
*
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct vertex{
  std::vector<int> neighbours;
};


using std::cin;
using std::cout;
using std::cerr;

int v = 0, s, t, e;
int maxFlow = 0;

std::vector<vertex> vert;

int capacities[2000][2000];
int flows[2000][2000];
int restcapacities[2000][2000];


void readFlowGraph() {
  cin >> v >> s >> t >> e;
  
  for(int i=0;i<v;i++){
    vert.push_back({{}});
  }

  for (int i = 0; i < e; ++i) {
    int a, b, c;
    cin >> a >> b >> c;

    vert[0].neighbours.push_back(b); // "at" syntax

    capacities[a][b] = c;
    restcapacities[a][b] = c;
  }
}

void writeFakeFlowGraphSolution() {
  cout << 2 << "\n";
  cout << 1 << " " << 2 << " " << 10 << "\n";
  cout << 1 << "\n";
  cout << 1 << " " << 2 << " " << 10 << "\n";

}



int main(void) {
  std::ios::sync_with_stdio(false);
  cin.tie(0);


  readFlowGraph();

  //solveFlowProblem();

  //writeFlowGraphSolution();

  writeFakeFlowGraphSolution();

  cout.flush();

  return 0;
}
