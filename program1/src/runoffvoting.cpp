//Dinorah Carrion Rodriguez   ID#35657319
//Valencia Wongso             ID#80147413
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"
using namespace std;

typedef ics::ArrayQueue<std::string>              CandidateQueue;
typedef ics::ArraySet<std::string>                CandidateSet;
typedef ics::ArrayMap<std::string,int>            CandidateTally;

typedef ics::ArrayMap<std::string,CandidateQueue> Preferences;
typedef ics::pair<std::string,CandidateQueue>     PreferencesEntry;

typedef ics::pair<std::string,int>                TallyEntry;
typedef ics::ArrayPriorityQueue<TallyEntry>       TallyEntryPQ;

//Read an open file stating voter preferences (each line is (a) a voter
//  followed by (b) all the candidates, in preference order (from most to
//  least preferred), separated by a semicolons), and return a Map of the
//  preferences as a Map whose keys are voter names and whose values are
//  a queue of candidate preferences.
Preferences read_voter_preferences(std::ifstream &file) {
   string line;
   Preferences c;

   while( getline( file, line ) ){
         vector<string> v = ics::split(line, ";");
       std::string key = v[0];
       CandidateQueue cq;
       for( int i = 1; i < v.size() ; ++i)
          cq.enqueue(v[i]);

       c.put(key,cq);
   }
   return c;
}


//Print a label and all the entries in the preferences Map, in alphabetical
//  order according to the voter.
//Use a "->" to separate the voter name from the Queue of candidate names.
void print_voter_preferences(const Preferences& preferences) {
   cout << "\nVoter Preferences " << endl;
   for( auto x : preferences){
      cout << x.first << " -> " << x.second << endl;
   }
}


//Print the message followed by all the entries in the CandidateTally, in
//   the order specified by *has_higher_priority: i is printed before j, if
//   has_higher_priority(i,j) returns true.
//Use a "->" to separate the candidate name from the number of votes they
//  received.
void print_tally(std::string message, const CandidateTally& tally,
      bool (*has_higher_priority)(const TallyEntry& i,const TallyEntry& j)) {
   cout << "\n" << message << endl;
   for(TallyEntry kv : TallyEntryPQ(tally.ibegin(),tally.iend(), has_higher_priority))
         cout << " " << kv.first << " -> " << kv.second << endl;
}


//Return the CandidateTally: a Map of candidates (as keys) and the number of
//  votes they received, based on the unchanging Preferences (read from the
//  file) and the candidates who are currently still in the election.
//Every possible candidate should appear as a key in the resulting tally.
//Each voter should tally one vote: for their highest-ranked candidate who is
//  still in the the election.
CandidateTally evaluate_ballot(const Preferences& preferences,
      const CandidateSet& candidates) {
   CandidateTally ct;
   for (auto kv : preferences) {
      for (auto i : kv.second) {
         if (candidates.contains(i)) {
            ct[i]++;
            break;
         }
      }
   }
   return ct;
}


//Return the Set of candidates who are still in the election, based on the
//  tally of votes: compute the minimum number of votes and return a Set of
//  all candidates receiving more than that minimum; if all candidates
//  receive the same number of votes, the empty Set is returned.
CandidateSet remaining_candidates(const CandidateTally& tally) {
   CandidateSet candidates;
   TallyEntryPQ pq(tally.ibegin() , tally.iend() , [](const TallyEntry&i,
         const TallyEntry&j){ return i.second < j.second ;} );
   TallyEntry prev = pq.dequeue();

   while(pq.peek().second == prev.second)
         prev = pq.dequeue();
   while(!pq.empty())
        candidates.insert(pq.dequeue().first);

   return candidates;
}


//Prompt the user for a file, create a voter preference Map, and print it.
//Determine the Set of all the candidates in the election, from this Map.
//Repeatedly evaluate the ballot based on the candidates (still) in the
//  election, printing the vote count (tally) two ways: with the candidates
//  (a) shown alphabetically increasing and (b) shown with the vote count
//  decreasing (candidates with equal vote counts are shown alphabetically
//  increasing); from this tally compute which candidates remains in the
//  election: all candidates receiving more than the minimum number of votes;
//  continue this process until there are less than 2 candidates.
//Print the final result: there may 1 candidate left, the winner, or 0, no
//  winner.
int main() {
   try {
      std::ifstream file;
      ics::safe_open(file, "Enter File Name", "votepref1.txt");
      Preferences pref;
      CandidateTally tally;
      pref = read_voter_preferences(file);
      print_voter_preferences(pref);
      CandidateSet cset;
      int stop = 0;
      for(auto kv : pref){
         while( stop != 1){
            cset.insert(kv.second.ibegin(), kv.second.iend());
            stop = 1;
         }
      }
      while(cset.size() != 1){
         tally = evaluate_ballot(pref, cset);
         cout << "\nVote count on ballot with candidates alphabetically: still in election = " << cset;
         print_tally("", tally,
               [](const TallyEntry& i, const TallyEntry &j)
               { return(i.first < j.first);});
          cset = remaining_candidates(tally);
         cout << "Vote count on ballot with candidates numerically: still in election = " << cset;
         print_tally("", tally,
               [](const TallyEntry&i, const TallyEntry &j)
               { return(i.second > j.second);});
//         }
      }
      for( auto x : cset )
      cout << "Winner is " << x;

   } catch (ics::IcsError& e) {
      std::cout << e.what() << std::endl;
   }
}
