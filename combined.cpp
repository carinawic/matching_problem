/**
 * Exempel på in- och utdatahantering för maxflödeslabben i kursen
 * ADK.
 *
 * Använder iostreams i C++.
 * Anmärkning: scanf/printf-rutinerna från C-exemplet går att använda
 * även i C++ och är ofta märkbart snabbare än cin/cout som det här
 * programmet använder.
 *
 * Author: Per Austrin
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

class FlowSolver{
    public: int globalintname;
};

int x, y;

int* readBipartiteGraph() {
  int e;
  int graph[600004]; // maybe bigger?
  int graphPointer = 0;

  // Läs antal hörn och kanter
  cin >> x >> y >> e;

  // Skriv ut flödesgrafen.
  int s =  x+y+1;
  int t =  x+y+2;
  //cout << x+y+2 << "\n" << s << " " << t << "\n" << e+x+y << "\n";
  
  graph[graphPointer] = x+y+2;
  graphPointer ++;
  graph[graphPointer] = s;
  graphPointer ++;
  graph[graphPointer] = t;
  graphPointer ++;
  graph[graphPointer] = e+x+y;
  graphPointer ++;


  // Läs in kanterna
  for (int i = 0; i < e; ++i) {
    int a, b;
    cin >> a >> b;

    // Skriv ut kant. x-y
    // cout << a << " " << b << " " << 1 << "\n";
    graph[graphPointer] = a;
    graphPointer ++;
    graph[graphPointer] = b;
    graphPointer ++;
    graph[graphPointer] = 1;
    graphPointer ++;
  }

  // Skriv ut kanterna s-x
  for (int i = 1; i < x+1; ++i) {
    // cout << s << " " << i << " " << 1 << "\n";
    graph[graphPointer] = s;
    graphPointer ++;
    graph[graphPointer] = i;
    graphPointer ++;
    graph[graphPointer] = 1;
    graphPointer ++;
  }

  // Skriv ut kanterna y-t
  for (int i = 1; i < y+1; ++i) {
    // cout << i+x << " " << t << " " << 1 << "\n";
    graph[graphPointer] = i+x;
    graphPointer ++;
    graph[graphPointer] = t;
    graphPointer ++;
    graph[graphPointer] = 1;
    graphPointer ++;
  }

  // Var noggrann med att flusha utdata när flödesgrafen skrivits ut!
  // cout.flush();

  // Debugutskrift
  // cerr << "Skickade iväg flödesgrafen\n";

  return graph;
}


void readMaxFlowSolution() {
  int v, e, s, t, f;

  // Läs in antal hörn, kanter, källa, sänka, och totalt flöde
  // (Antal hörn, källa och sänka borde vara samma som vi i grafen vi
  // skickade iväg)
  cin >> v >> s >> t >> f >> e;

  // Skriv ut x, x och flödete (maximala matchning).
  cout << x << " " << y << "\n" << f << "\n";

  for (int i = 0; i < e; ++i) {
    int u, v, f;
    // Flöde f från u till v
    cin >> u >> v >> f;

    if ((u != s) && (v != t)) {
      // Skriv ut kant x-y.
      cout << u << " " << v << "\n";
    }
  }
}


int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  int *graph = readBipartiteGraph();


  FlowSolver myFlowSolver;

  myFlowSolver.globalintname = 10;

  readMaxFlowSolution();

  // debugutskrift
  cerr << "Bipred avslutar\n";
  return 0;
}
