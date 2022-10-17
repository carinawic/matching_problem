/*
*
*
*
*/

#include <iostream>
#include <vector>
#include <queue>

struct vertex{
  std::vector<int> neighbours;
};


using std::cin;
using std::cout;
using std::cerr;

int v = 0, s, t, e;
vertex * vert;

int capacities[2000][2000];
int flows[2000][2000];
int restcapacities[2000][2000];


void readFlowGraph() {
  // Läs antal hörn och kanter
  cin >> v >> s >> t >> e;
  vert = new vertex[v];

  // Läs in kanterna
  for (int i = 0; i < e; ++i) {
    int a, b, c;
    cin >> a >> b >> c;

    // add to neighbor list
    vert[a].neighbours.push_back(b);

    // fill matrices
    // add edge from a to b with capacity c, flow 0, and restcapacity c

    capacities[a][b] = c; // capacities[b][a] = ?;
    //flows[a][b] = 0; already initialized
    restcapacities[a][b] = c;

  }


  // Debugutskrift
  cerr << "Läst in flödesgrafen\n";
}

int printGraph() {

    for (int i=0;i<v;i++){
        for (int j=0;j<vert[i].neighbours.size();j++){
            int nodeNum = vert[i].neighbours[j];
            std::cout << "vector " << i << " has neighbours " << vert[i].neighbours[j] << std::endl;
        }
        std::cout << std::endl ;
    }
    // delete vertex
    return 0;
}

void solveFlowProblem() {

/*
c[u,v] är kapaciteten från u till v, f[u,v] är flödet, cf[u,v] är restkapaciteten.

for varje kant (u,v) i grafen do
    f[u,v]:=0; f[v,u]:=0
    cf[u,v]:=c[u,v]; cf[v,u]:=c[v,u]
while det finns en stig p från s till t i restflödesgrafen do
    r:=min(cf[u,v]: (u,v) ingår i p)
    for varje kant (u,v) i p do
         f[u,v]:=f[u,v]+r; f[v,u]:= -f[u,v]
         cf[u,v]:=c[u,v] - f[u,v]; cf[v,u]:=c[v,u] - f[v,u]

*/
  std::queue<int> toVisitQueue;
  std::vector<int> visited(v+1);

  toVisitQueue.push(s);
  visited[s] = 1;
  int node = -1;

  while (!toVisitQueue.empty()) {
    // BFS
    node = toVisitQueue.front();
    toVisitQueue.pop();
    cout << "Visting node: " << node << "\n";

    for (int i=0;i<vert[node].neighbours.size();i++) {
      int neighbour = vert[node].neighbours[i];
      if (!visited[neighbour]) {
        visited[neighbour] = 1;
        toVisitQueue.push(neighbour);
      }
    }

  }


}


void writeFlowGraphSolution() {
  cout << v;
}



int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);


  readFlowGraph();

  printGraph();

  solveFlowProblem();

  //writeFlowGraphSolution();


  // debugutskrift
  cerr << "Avslutar\n";
  return 0;
}
