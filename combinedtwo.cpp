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


using std::cin;
using std::cout;
using std::cerr;
using namespace std;

struct vertex{
  std::vector<int> neighbours;
};

int v = 0, s, t, e;
int maxFlow = 0;

std::vector<vertex> vert;

int capacities[2002][2002]; // 9223372036854775807
int flows[2002][2002];
int restcapacities[2002][2002];


int x, y, bipE;

void readFlowGraph() {


  
  // Läs antal hörn och kanter
  cin >> x >> y >> bipE;
    
  // Skriv ut flödesgrafen.
  s = x+y+1;
  t = x+y+2;

  // cout << x+y+2 << "\n" << s << " " << t << "\n" << bipE+x+y << "\n";
  // cout      v              s           t              e
  //cin >> v >> s >> t >> e;
  
  v = t;
  e = bipE+x+y;

  for(int i=0;i<v+1;i++){
    vert.push_back({{}});
  }

  

  for (int i = 0; i < bipE; i++) { // edges x -> y
    int a, b;
    int c = 1;
    cin >> a >> b; //>> c;
    

    vert[a].neighbours.push_back(b);
    vert[b].neighbours.push_back(a);

    capacities[a][b] = c;
    restcapacities[a][b] = c;
  }
    
  // kanterna s-x
  for (int i = 1; i < x+1; i++) {

    vert[s].neighbours.push_back(i);
    vert[i].neighbours.push_back(s);

    capacities[s][i] = 1;
    restcapacities[s][i] = 1;

  }

  // kanterna y-t
  for (int i = 1; i < y+1; i++) {
    vert[i+x].neighbours.push_back(t);
    vert[t].neighbours.push_back(i+x);

    capacities[i+x][t] = 1;
    restcapacities[i+x][t] = 1;

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
    
    // cout << "path is: \n" << std::flush;
    // for(int i=0;i<path.size();i++){
    //     cout << path[i] << " " << std::flush;
    // }
    // cout << "\n" << std::flush;


    int r = 2000000; //inf is not std in kattis old version
    
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
    

  // Skriv ut x, x och flödete (maximala matchning).
  cout << x << " " << y << "\n" << maxFlow << "\n" << std::flush;

  int flowingEdges = 0;
  
  int answer[30000];
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
  // cout << flowingEdges << "\n" << std::flush;
  for (int i = 0; i < answerPekare; i+=3) {
    if ((answer[i] != s) && (answer[i+1] != t)) {
      // Skriv ut kant x-y.
      cout << answer[i] << " " << answer[i+1] << "\n" << std::flush;
    }
    
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
