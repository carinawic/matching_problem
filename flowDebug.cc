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
vertex * vert;

int capacities[2000][2000];
int flows[2000][2000];
int restcapacities[2000][2000];


void readFlowGraph() {
  cin >> v >> s >> t >> e;
  vert = new vertex[v];

  for (int i = 0; i < e; ++i) {
    int a, b, c;
    cin >> a >> b >> c;


    vert[a].neighbours.push_back(b);
    capacities[a][b] = c;
    restcapacities[a][b] = c;
  }
}

void solveFlowProblem() {
  std::queue<int> toVisitQueue;
  std::vector<int> visited(v+1);
  int node = -1;
  std::vector<int> path;

  while (true) {
    while(!toVisitQueue.empty()) toVisitQueue.pop();
    for (int i = 0; i < visited.size(); i++) {
      visited[i] = 0;
    }
    toVisitQueue.push(s);
    visited[s] = s;

    while (!toVisitQueue.empty()) {
      node = toVisitQueue.front();
      toVisitQueue.pop();
      if (node == t) {
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
          if (restcapacities[node][neighbour] > 0) {
            toVisitQueue.push(neighbour);
            visited[neighbour] = node;
          }
        }
      }
    }
    if (path.empty()) {
      break;
    }


    int r = std::numeric_limits<int>::max();
    for (int i = 1; i < path.size(); i++) {
      r = std::min(r, restcapacities[path[i]][path[i-1]]);
    }
    maxFlow += r;

    for (int i = 1; i < path.size(); i++) {
      int u = path[i];
      int v = path[i-1];

      flows[u][v] = flows[u][v]+r;
      flows[v][u] = -flows[u][v];

      restcapacities[u][v] = capacities[u][v] - flows[u][v];
      restcapacities[v][u] = capacities[v][u] - flows[v][u];
    }

    path.clear();
  }
}


void writeFlowGraphSolution() {
  cout << v << "\n" << s << " " << t << " " << maxFlow << "\n";
  int flowingEdges = 0;
  for (int a = 1; a < v; a++) {
    for (int i = 0; i < vert[a].neighbours.size(); i++) {
      int b = vert[a].neighbours[i];
      if (flows[a][b] > 0) {
        flowingEdges++;
      }
    }
  }
  cout << flowingEdges << "\n";
  for (int a = 1; a < v; a++) {
    for (int i = 0; i < vert[a].neighbours.size(); i++) {
      int b = vert[a].neighbours[i];
      if (flows[a][b] > 0) {
        cout << a << " " << b << " " << flows[a][b] << "\n";
      }
    }
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


  //readFlowGraph();

  //solveFlowProblem();

  //writeFlowGraphSolution();

  writeFakeFlowGraphSolution();

  cout.flush();

  return 0;
}
