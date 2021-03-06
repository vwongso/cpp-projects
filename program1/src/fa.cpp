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

typedef ics::ArrayQueue<std::string>             InputsQueue;
typedef ics::ArrayMap<std::string,std::string>   InputStateMap;

typedef ics::ArrayMap<std::string,InputStateMap> FA;
typedef ics::pair<std::string,InputStateMap>     FAEntry;
typedef ics::ArrayPriorityQueue<FAEntry>         FAPQ;

typedef ics::pair<std::string,std::string>       Transition;
typedef ics::ArrayQueue<Transition>              TransitionQueue;


//Read an open file describing the finite automaton (each line starts with
//  a state name followed by pairs of transitions from that state: (input
//  followed by new state) all separated by semicolons), and return a Map
//  whose keys are states and whose associated values are another Map with
//  each input in that state (keys) and the resulting state it leads to.
const FA read_fa(std::ifstream &file) {
   FA fa;
   string line;

   while( getline(file, line) ) {
      InputStateMap ism;
      vector<string> v = ics::split(line, ";");
      string fa_key = v[0];
      string key, val;
      for(vector<string>::iterator it = v.begin()+1 ; it != v.end(); ++it ){
         auto pos = it - v.begin();
         if(pos % 2 == 1) key = *it;
         else {
            val = *it;
            ism.put(key, val);
         }
      }
      fa.put(fa_key, ism);
   }
   return fa;
}


//Print a label and all the entries in the finite automaton Map, in
//  alphabetical order of the states: each line has a state, the text
//  "transition:" and the Map of its transitions.
void print_fa(const FA& fa) {
   FAPQ pq(fa.ibegin(), fa.iend(), [](const FAEntry& a, const FAEntry& b){ return a.first < b.first;} );

      while( !pq.empty() ){
         FAEntry current = pq.dequeue( );
         cout << current.first << " transitions: " << current.second << endl;
      }
}

//Return a queue of the calculated transition pairs, based on the finite
//  automaton, initial state, and queue of inputs; each pair in the returned
//  queue is of the form: input, new state.
//The first pair contains "" as the input and the initial state.
//If any input i is illegal (does not lead to a state in the finite
//  automaton, then the last pair in the returned queue is i,"None".
TransitionQueue process(const FA& fa, std::string state, const InputsQueue& inputs) {
   TransitionQueue transq;
   Transition trans_pair;
   string s;
   string currentState = state;
   trans_pair.first = "";
   trans_pair.second = currentState;
   transq.enqueue(trans_pair);

   for(ics::Iterator<string>&it = inputs.ibegin() ; it!=inputs.iend() ; ++it){
      trans_pair.first = *it;
      if( trans_pair.first != "1" && trans_pair.first != "0"){
         trans_pair.second = "None";
         transq.enqueue(trans_pair);
         break;
      }
      else if( trans_pair.first == "1" && currentState == "odd" ){
         currentState = "even";
         trans_pair.second = currentState;
      }
      else if(trans_pair.first == "1"  && currentState == "even" ){
         currentState = "odd";
         trans_pair.second = currentState;
      }
      transq.enqueue(trans_pair);
   }
   return transq;
}


//Print a TransitionQueue (the result of calling process) in a nice form.
//Print the Start state on the first line; then print each input and the
//  resulting new state (or "illegal input: terminated", if the state is
//  "None") indented on subsequent lines; on the last line, print the Stop
//  state (which might be "None").
void interpret(TransitionQueue& tq) {
   //or TransitionQueue or TransitionQueue&&
   ics::pair<string, string> pair ;
   tq.dequeue();
   while( !tq.empty() ){
      pair = tq.dequeue( );
      cout << "Input = " << pair.first << "; new state = " ;
      if( pair.second == "None")
         cout << "illegal input: terminated " << endl;
      else cout << pair.second << endl;
   }
   cout << "Stop state = " << pair.second << endl;
}

//Prompt the user for a file, create a finite automaton Map, and print it.
//Prompt the user for a file containing any number of simulation descriptions
//  for the finite automaton to process, one description per line; each
//  description contains a start state followed by inputs, all separated by
//  semicolons.
//Repeatedly read a description, print that description, put each input in a
//  Queue, process the Queue and print the results in a nice form.
int main() {
   try {
      ifstream file;
      ics::safe_open(file, "File Name", "faparity.txt");
      FA faut, faut2;
      InputsQueue inputQ;
      cout << "\nFinite Automaton " << endl;
      faut = read_fa(file);
      print_fa(faut);
      ifstream file2;
      ics::safe_open(file2, "\nEnter file with start state and input " , "fainputparity.txt");
      string line, state;
      TransitionQueue transQ;
      while( getline(file2, line) ){
         cout << "\nStarting new simulation with description: " << line << endl;
         vector<string> v = ics::split(line, ";");
         state = v[0];
         for(vector<string>::iterator it = v.begin() + 1 ; it != v.end(); ++it ){
            inputQ.enqueue(*it);
         }
             transQ = process(faut, state, inputQ);
             cout << "Start state = " << state << endl;
             interpret(transQ);
             inputQ.clear();
      }
   } catch (ics::IcsError& e) {
       std::cout << e.what() << std::endl;
   }
     return 0;
}
