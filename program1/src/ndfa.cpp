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

typedef ics::ArraySet<std::string>                States;
typedef ics::ArrayQueue<std::string>              InputsQueue;
typedef ics::ArrayMap<std::string,States>         InputStatesMap;

typedef ics::ArrayMap<std::string,InputStatesMap> NDFA;
typedef ics::pair<std::string,InputStatesMap>     NDFAEntry;
typedef ics::ArrayPriorityQueue<NDFAEntry>        NDFAPQ;

typedef ics::pair<std::string,States>             Transitions;
typedef ics::ArrayQueue<Transitions>              TransitionsQueue;


//Read an open file describing the non-deterministic finite automaton (each
//  line starts with a state name followed by pairs of transitions from that
//  state: (input followed by a new state) all separated by semicolons), and
//  return a Map whose keys are states and whose associated values are another
//  Map with each input in that state (keys) and the resulting set of states it
//  can lead to.
const NDFA read_ndfa(std::ifstream &file) {
   NDFA ndfa;
   string line;

   while( getline(file, line) ) {
      InputStatesMap ism;
      vector<string> v = ics::split(line, ";");
      for(int i = 1; i < v.size()-1; ++i){
         if(i % 2 == 1){
            ism[v[i]].insert(v[i+1]);
         }
      }
      ndfa.put(v[0],ism);
   }
   return ndfa;
}


//Print a label and all the entries in the finite automaton Map, in
//  alphabetical order of the states: each line has a state, the text
//  "transition:" and the Map of its transitions.
void print_ndfa(const NDFA& ndfa) {
   NDFAPQ pq(ndfa.ibegin(), ndfa.iend(),
         [](const NDFAEntry& a, const NDFAEntry& b)
         { return a.first < b.first;});
   while( !pq.empty() ){
      NDFAEntry current = pq.dequeue( );
      cout << current.first << " transitions: " << current.second << endl;
   }
}

//Return a queue of the calculated transition pairs, based on the non-deterministic
//  finite automaton, initial state, and queue of inputs; each pair in the returned
//  queue is of the form: input, set of new states.
//The first pair contains "" as the input and the initial state.
//If any input i is illegal (does not lead to any state in the non-deterministic finite
//  automaton, ignore it).
TransitionsQueue process(const NDFA& ndfa, std::string state,
      const InputsQueue& inputs) {
   TransitionsQueue tq;
   Transitions tp;
   States s;
   tp.first = "";
   tp.second = s;
   tq.enqueue(tp);
   for(ics::Iterator<string>&it = inputs.ibegin(); it != inputs.iend(); ++it){
      tp.first = *it;
      if(tp.first == "1" && !s.contains("near") && !s.contains("end")){
         s.insert("start");
         tp.second = s;
      }
      else if(tp.first == "1" && s.contains("near") && !s.contains("end")){
         s.insert("end");
         s.erase("near");
         tp.second = s;
      }
      else if(tp.first == "1" && !s.contains("near") && s.contains("end")){
         s.erase("end");
         tp.second = s;
      }
      else {
         s.insert("start");
         s.insert("near");
         tp.second = s;
      }
      tq.enqueue(tp);
   }
   return tq;
}


//Print a TransitionsQueue (the result of calling process) in a nice form.
//Print the Start state on the first line; then print each input and the
//  resulting new states indented on subsequent lines; on the last line, print
//  the Stop state.
void interpret(TransitionsQueue& tq) {
   Transitions pair ;
   tq.dequeue();
   while( !tq.empty() ){
      pair = tq.dequeue();
      cout << "Input = " << pair.first << "; new states = "
            << pair.second << endl;
   }
   cout << "Stop state(s) = " << pair.second << endl;
}

//
//Prompt the user for a file, create a finite automaton Map, and print it.
//Prompt the user for a file containing any number of simulation descriptions
//  for the finite automaton to process, one description per line; each
//  description contains a start state followed by inputs, all separated by
//  semicolons.
//Repeatedly read a description, print that description, put each input in a
//  Queue, process the Queue and print the results in a nice form.
int main() {
  try {
     ifstream file,file2;
     ics::safe_open(file,
           "Enter file name of Non-Deterministic Finite Automaton", "ndfaendin01.txt");
     InputsQueue inputQ;
     cout << "Non-Deterministic Finite Automaton Description " << endl;
     NDFA faut = read_ndfa(file);
     print_ndfa(faut);
     ics::safe_open(file2, "\nEnter file name of start-states and input",
           "ndfainputendin01.txt");
     string line, state;
     States s;
     TransitionsQueue transQ;
     while( getline(file2, line) ){
        cout << "\nStarting new simulation with description: " << line << endl;
        vector<string> v = ics::split(line, ";");
        state = v[0];
        s.insert(state);
        for(vector<string>::iterator it = v.begin() + 1; it != v.end(); ++it ){
           inputQ.enqueue(*it);
        }
        transQ = process(faut, state, inputQ);
        cout << "Start state(s) = " << s << endl;
        interpret(transQ);
        inputQ.clear();
     }
  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
