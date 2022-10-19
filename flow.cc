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
int maxFlow = 0;
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
  std::queue<int> toVisitQueue;
  std::vector<int> visited(v+1);
  int node = -1;
  std::vector<int> path;

  while (true) {
    // BFS, hitta stig
    while(!toVisitQueue.empty()) toVisitQueue.pop();
    for (int i = 0; i < visited.size(); i++) {
      visited[i] = 0;
    }
    toVisitQueue.push(s);
    visited[s] = s;

    while (!toVisitQueue.empty()) {
      node = toVisitQueue.front();
      toVisitQueue.pop();
      cout << "Visting node: " << node << "\n";
      if (node == t) {
        // bygger vi ihop stigen
        int parent = t;
        while (true) {
          path.push_back(parent);
          parent = visited[parent];
          if (parent == s) {
            path.push_back(parent);
            break;
          }
        }
        break;
      }
      for (int i=0;i<vert[node].neighbours.size();i++) {
        int neighbour = vert[node].neighbours[i];
        if (!visited[neighbour]) {
          cout << "Node " << neighbour << " was not visited. \n";
          if (restcapacities[node][neighbour] > 0) {
            // Finns det plats att flöda?
            cout << "Capacity ok. \n";
            toVisitQueue.push(neighbour);
            visited[neighbour] = node; 
          }
        }
      }
    }
    if (path.empty()) {
      // Ingen stig från s till t.
      break;
    }
    // hittat stig från s till t.
    for (int i = 0; i < path.size(); i++) {
      cout << path[i] << ", ";
    }

    int r = std::numeric_limits<int>::max(); // Flaskhalsen.
    for (int i = 1; i < path.size(); i++) {
      r = std::min(r, restcapacities[path[i]][path[i-1]]);
    }
    maxFlow += r;
    cout << "\n" << "r: " << r << " " << "maxFlow is now: " << maxFlow << "\n";

    for (int i = 1; i < path.size(); i++) {
      int u = path[i];
      int v = path[i-1];

      flows[u][v] = flows[u][v]+r;
      flows[v][u] = -flows[u][v];

      restcapacities[u][v] = capacities[u][v] - flows[u][v];
      restcapacities[v][u] = capacities[v][u] - flows[v][u];
    }

    // Töm stigen.
    path.clear();
  }
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
}


void writeFlowGraphSolution() {
  cout << "Print solution! \n";
  cout << v << "\n" << s << " " << t << " " << maxFlow << "\n";

}



int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);


  readFlowGraph();

  printGraph();

  solveFlowProblem();

  writeFlowGraphSolution();


  // debugutskrift
  cerr << "Avslutar\n";
  return 0;
}
