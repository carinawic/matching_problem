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
#include <map>
#include <tuple>

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

// short capacities[10004][10004]; // 9223372036854775807
// short flows[10004][10004];
// short restcapacities[10004][10004];

map<tuple<short, short>, short> capacities;
map<tuple<short, short>, short> flows;
map<tuple<short, short>, short> restcapacities;
// capacities.insert(pair<tuple <short, short>, short> (make_tuple(10, 15), 3));

short x, y, bipE;

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

    
    capacities.insert(pair<tuple <short, short>, short> (make_tuple(a, b), c));
    capacities.insert(pair<tuple <short, short>, short> (make_tuple(b, a), 0));

    restcapacities.insert(pair<tuple <short, short>, short> (make_tuple(a, b), c));
    restcapacities.insert(pair<tuple <short, short>, short> (make_tuple(b, a), 0));

    flows.insert(pair<tuple <short, short>, short> (make_tuple(a, b), 0));
    flows.insert(pair<tuple <short, short>, short> (make_tuple(b, a), 0));
    
  }
    
  // kanterna s-x
  for (int i = 1; i < x+1; i++) {

    vert[s].neighbours.push_back(i);
    vert[i].neighbours.push_back(s);

    capacities.insert(pair<tuple <short, short>, short> (make_tuple(s, i), 1));
    capacities.insert(pair<tuple <short, short>, short> (make_tuple(i, s), 0));

    restcapacities.insert(pair<tuple <short, short>, short> (make_tuple(s, i), 1));
    restcapacities.insert(pair<tuple <short, short>, short> (make_tuple(i, s), 0));

    flows.insert(pair<tuple <short, short>, short> (make_tuple(s, i), 0));
    flows.insert(pair<tuple <short, short>, short> (make_tuple(i, s), 0));
    

  }

  // kanterna y-t
  for (int i = 1; i < y+1; i++) {
    vert[i+x].neighbours.push_back(t);
    vert[t].neighbours.push_back(i+x);

    capacities.insert(pair<tuple <short, short>, short> (make_tuple(i+x, t), 1));
    capacities.insert(pair<tuple <short, short>, short> (make_tuple(t, i+x), 0));

    restcapacities.insert(pair<tuple <short, short>, short> (make_tuple(i+x, t), 1));
    restcapacities.insert(pair<tuple <short, short>, short> (make_tuple(t, i+x), 0));
    
    flows.insert(pair<tuple <short, short>, short> (make_tuple(i+x, t), 0));
    flows.insert(pair<tuple <short, short>, short> (make_tuple(t, i+x), 0));
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
          if (restcapacities.at(make_tuple(node, neighbour)) > 0) {
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


    // short r = 32766; //inf is not std in kattis old version
    
    // for (int i = 1; i < path.size(); i++) {
    //   r = std::min(r, restcapacities[path[i]][path[i-1]]);
    // }
    
    // cout << "maxflow is: " << maxFlow << "\n";
    // cout << "r is: " << r << "\n";
    maxFlow += 1;
    

    for (int i = 1; i < path.size(); i++) {
      int u = path[i];
      int v = path[i-1];
    
      flows[make_tuple(u,v)] = flows.at(make_tuple(u,v)) + 1;
      flows[make_tuple(v,u)] = -flows.at(make_tuple(u,v));
      
      restcapacities[make_tuple(u,v)] = capacities.at(make_tuple(u,v)) - flows.at(make_tuple(u,v));
      restcapacities[make_tuple(v,u)] = capacities.at(make_tuple(v,u)) - flows.at(make_tuple(v,u));

    }

    path.clear();
  }
}

void writeFlowGraphSolution() {
    
  // Skriv ut x, x och flödete (maximala matchning).
  cout << x << " " << y << "\n" << maxFlow << "\n" << std::flush;

  for (int a = 1; a < v+1; a++) {
    for (int i = 0; i < vert[a].neighbours.size(); i++) {
      int b = vert[a].neighbours[i];
      if (flows.at(make_tuple(a,b)) > 0) {
        flows[make_tuple(a,b)] = 0;

        if ((a != s) && (b != t)) {
            // Skriv ut kant x-y.
            cout << a << " " << b << "\n" << std::flush;
        }
      }
    }
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
