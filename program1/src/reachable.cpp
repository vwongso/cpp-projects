//Dinorah Carrion Rodriguez   ID#35657319
//Valencia Wongso             ID#80147413
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"

using namespace std;


typedef ics::ArraySet<std::string>           NodeSet;
typedef ics::pair<std::string,NodeSet>       GraphEntry;
typedef ics::ArrayPriorityQueue<GraphEntry>  GraphPQ;
typedef ics::ArrayMap<std::string,NodeSet>   Graph;


//Read an open file of edges (node names separated by semicolons, with an
//  edge going from the first node name to the second node name) and return a
//  Graph (Map) of each node name associated with the Set of all node names to
//  which there is an edge from the key node name.
Graph read_graph(std::ifstream &file) {
   string line;
   Graph g;

      while( getline( file, line ) ){
         vector<string> v = ics::split(line, ";");
         string key = v[0];

         g[key].insert( v[1] );

      }
    return g;
}

//Print a label and all the entries in the Graph, in alphabetical order.
//Use a "->" to separate the key node name from the Set of node names to
//  which it has an edge.
void print_graph(const Graph& graph) {
   GraphPQ pq(graph.ibegin(),graph.iend(), [](const GraphEntry& a, const GraphEntry&b){ return a.first < b.first;});
   cout << "\nGraph: source -> {destination} edges " << endl;
   for(GraphEntry e : pq)
      std::cout << e.first << " -> " << e.second << endl;
}


//Return the Set of node names reaching in the Graph starting at the
//  specified (start) node.
//Use a local Set and a Queue to respectively store the reachable nodes and
//  the nodes that are being explored.
NodeSet reachable(const Graph& graph, std::string start) {
   NodeSet set;
   ics::ArrayQueue<string> q;
   q.enqueue(start);
   string currentNode;

   while( !q.empty() ){
      set.insert( ( currentNode = q.dequeue() ) );

      if( graph.has_key( currentNode ) ){
         for(ics::Iterator<string>& i = graph[currentNode].ibegin() ; i != graph[currentNode].iend() ; ++i){
            if( set.insert(*i) == 1 )
               q.enqueue(*i);
         }
      }
   }
   return set;
}

//Prompt the user for a file, create a graph from its edges, print the graph,
//  and then repeatedly (until the user enters "quit") prompt the user for a
//  starting node name and then either print an error (if that the node name
//  is not a source node in the graph) or print the Set of node names
//  reachable from it using the edges in the Graph.
int main() {
  try {
     string node;
     Graph g;
     NodeSet set;
     std::ifstream file;
     ics::safe_open(file, "Enter graph file name", "graph1.txt");
     print_graph( (g = read_graph(file) ) );
     while( (node = ics::prompt_string("\nEnter starting node (enter quit to quit)") ) != "quit"  ){
        if(g.has_key(node)){
           set = g[node];
           cout <<"Reachable from node name " << node << " = " << reachable(g,node)  << endl;
        }
        else
        cout << node << " is not a source node name in the graph" << endl;
     }
  } catch (ics::IcsError& e) {
    cout << e.what() << endl;
  }

  return 0;
}
