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
//vertex * vert;

int capacities[2000][2000];
int flows[2000][2000];
int restcapacities[2000][2000];


void readFlowGraph() {
  cin >> v >> s >> t >> e;
  std::vector<vertex> vert(v); 
  for(int x = 0; x < v; ++x) {
    vert[x] = new vertex();
  }
  //vert = new vertex[v];

  for (int i = 0; i < e; ++i) {
    int a, b, c;
    cin >> a >> b >> c;


    vert[a].neighbours.push_back(b);
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
