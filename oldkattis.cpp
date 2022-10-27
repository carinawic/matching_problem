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

const int numParalellEdges = 10;
int capacities[2002][2002][numParalellEdges];
int flows[2002][2002];
int restcapacities[2002][2002];

void readFlowGraph() {
  cin >> v >> s >> t >> e;

  
  for(int i=0;i<v+1;i++){
    vert.push_back({{}});
  }

  for (int i = 0; i < e; ++i) {
    int a, b, c;
    cin >> a >> b >> c;

    vert[a].neighbours.push_back(b);
    
    capacities[a][b][0] += c;
    restcapacities[a][b] += c;
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


    int r = 2147483647; //inf is not std in kattis old version
    for (int i = 1; i < path.size(); i++) {
      r = std::min(r, restcapacities[path[i]][path[i-1]]);
    }
    
    maxFlow += r;

    for (int i = 1; i < path.size(); i++) {
      int u = path[i];
      int v = path[i-1];

      flows[u][v] = flows[u][v]+r;
      flows[v][u] = -flows[u][v];

      restcapacities[u][v] = capacities[u][v][0] - flows[u][v];
      restcapacities[v][u] = capacities[v][u][0] - flows[v][u];
    }

    path.clear();
  }
}


void writeFlowGraphSolution() {

  int answerdgeNumbers[40000]; // TODO change back
  int pekareInAns = 0;

  cout << v << "\n" << s << " " << t << " " << maxFlow << "\n";
  int flowingEdges = 0;
  for (int a = 1; a < v+1; a++) {
    for (int i = 0; i < vert[a].neighbours.size(); i++) {
      int b = vert[a].neighbours[i];
      if (flows[a][b] > 0) {
        flows[a][b] = 0;
        if(capacities[a][b][2] != 0){
          for(int j = 1; j < numParalellEdges; j++){
            
            if(capacities[a][b][j] == 0){
              break;
            }else{
              //cout << "found edge between " << a << " and " << b << " with cap " << capacities[a][b][j] << "\n";
              
              answerdgeNumbers[pekareInAns] = a;
              pekareInAns++;
              answerdgeNumbers[pekareInAns] = b;
              pekareInAns++;
              answerdgeNumbers[pekareInAns] = capacities[a][b][j];
              pekareInAns++;
              

              flowingEdges++;
            }
          }
        }else{
          flowingEdges++;

          //cout << "found edge between " << a << " and " << b << " with cap " << capacities[a][b][0] << "\n";
          
          answerdgeNumbers[pekareInAns] = a;
          pekareInAns++;
          answerdgeNumbers[pekareInAns] = b;
          pekareInAns++;
          answerdgeNumbers[pekareInAns] = capacities[a][b][0];
          pekareInAns++;
              
          
        }
        
      }
    }
  }

  cout << flowingEdges << "\n";
  for(int i=0;i<pekareInAns;i+=3){

    cout << answerdgeNumbers[i] << " " << answerdgeNumbers[i+1] << " " << answerdgeNumbers[i+2] << "\n";

  }
}



int main(void) {
  std::ios::sync_with_stdio(false);
  cin.tie(0);


  readFlowGraph();

  solveFlowProblem();

  writeFlowGraphSolution();


  cout.flush();

  return 0;
}
