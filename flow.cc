/*
*
*
*
*/

#include <iostream>
#include <vector>

struct vertex{
    int data;
    std::vector<int> neighbours;
};

/*
swap : 1-2

1 <-> 2

edge.leftflow = 0
edge.rightflow = 4
edge.cap = 9
edge.leftvertex = 1
edge.rightvertex = 2

to

1 -> 3
2 -> 1
2 <- 1
*/


using std::cin;
using std::cout;
using std::cerr;

int v = 0, s, t, e;

void readFlowGraph() {
  // Läs antal hörn och kanter
  cin >> v >> s >> t >> e;

  // Läs in kanterna
  for (int i = 0; i < e; ++i) {
    int a, b, c;
    cin >> a >> b >> c;


  }

  // Debugutskrift
  cerr << "Läst in flödesgrafen\n";
}

int setup() {
  vertex * vert = new vertex[v];

    for (int i=0;i<v;i++){
        vert[i].data = i*i;
    }

    for (int i=0;i<v;i++){
        vert[i].neighbours.push_back((i+1) % 5);
        vert[i].neighbours.push_back((i+2) % 5);
    }

    for (int i=0;i<v;i++){
         std::cout << "vector " << i << " has value " << vert[i].data << std::endl;
        for (int j=0;j<vert[i].neighbours.size();j++){
            int nodeNum = vert[i].neighbours[j];
            std::cout << "vector " << i << " has neighbours " << vert[i].neighbours[j] << " with data " << vert[nodeNum].data << std::endl;
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


}


void writeFlowGraphSolution() {
}



int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);


  readFlowGraph();

  setup();

  //solveFlowProblem();

  //writeFlowGraphSolution();

  // debugutskrift
  cerr << "Avslutar\n";
  return 0;
}
