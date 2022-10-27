/*
*
*
* DEBUG IDEAS:
* TODO
* optimize sizes of matrices
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
long long maxFlow = 0;

std::vector<vertex> vert;

long long capacities[2002][2002]; // 9223372036854775807
long long flows[2002][2002];
long long restcapacities[2002][2002];

void readFlowGraph() {
  cin >> v >> s >> t >> e;
  
  for(int i=0;i<v+1;i++){
    vert.push_back({{}});
  }

  for (int i = 0; i < e; i++) {
    int a, b;
    long long c;
    cin >> a >> b >> c;

    vert[a].neighbours.push_back(b);
    vert[b].neighbours.push_back(a);

    // if(capacities[a][b] > 0){
    //   while(true){
    //     cout << "found the bug!!";
    //     //cout << flows[2002][2005];
    //   }
    // }

    capacities[a][b] = c;
    //capacities[b][a] = c;
    
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


    long long r = 9223372036854775806; //inf is not std in kattis old version
    for (int i = 1; i < path.size(); i++) {
      r = std::min(r, restcapacities[path[i]][path[i-1]]);
    }
    
    // cout << "maxflow is: " << maxFlow << "\n";
    // cout << "r is: " << r << "\n";
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
  
  long long answer[30000];
  int answerPekare = 0;

  for (int a = 1; a < v+1; a++) {
    for (int i = 0; i < vert[a].neighbours.size(); i++) {
      int b = vert[a].neighbours[i];
      if (flows[a][b] > 0) {
        answer[answerPekare] = a;
        answerPekare++;
        answer[answerPekare] = b;
        answerPekare++;
        answer[answerPekare] = flows[a][b];
        answerPekare++;
        flows[a][b] = 0;
        flowingEdges++;
      }
    }
  }
  cout << flowingEdges << "\n";
  for (int i = 0; i < answerPekare; i+=3) {
    cout << answer[i] << " " << answer[i+1] << " " << answer[i+2] << "\n";
  }
  // for (int a = 1; a < v+1; a++) {
  //   for (int i = 0; i < vert[a].neighbours.size(); i++) {
  //     int b = vert[a].neighbours[i];
  //     if (flows[a][b] > 0) {
  //       cout << a << " " << b << " " << flows[a][b] << "\n";
  //     }
  //   }
  // }
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
