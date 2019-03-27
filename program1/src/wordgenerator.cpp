//Dinorah Carrion Rodriguez   ID#35657319
//Valencia Wongso             ID#80147413
//We certify that we worked cooperatively on this programming
//  assignment, according to the rules for pair programming
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>                           //I used std::numeric_limits<int>::max()
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_set.hpp"
#include "array_map.hpp"
using namespace std;

typedef ics::ArrayQueue<std::string>         WordQueue;
typedef ics::ArraySet<std::string>           FollowSet;
typedef ics::pair<WordQueue,FollowSet>       CorpusEntry;
typedef ics::ArrayPriorityQueue<CorpusEntry> CorpusPQ;
typedef ics::ArrayMap<WordQueue,FollowSet>   Corpus;


//Return a random word in the words set (use in produce_text)
std::string random_in_set(const FollowSet& words) {
  int index = ics::rand_range(1, words.size());
  int i = 0;
  for (std::string s : words)
    if (++i == index)
      return s;
  return "?";
}

//Read an open file of lines of words (separated by spaces) and return a
//  Corpus (Map) of each sequence (Queue) of os (Order-Statistic) words
//  associated with the Set of all words that follow them somewhere in the
//  file.
//You may assume the first line contains at least Order-Statistic words.
Corpus read_corpus(int os, std::ifstream &file) {
   string word, key, line, everything;
   FollowSet follow;
   WordQueue wordQ;
   Corpus map;

   string all;


   while( getline(file,line) ){
      all+=line;
      all+= ' ';
   }
   cout << all << endl;
   everything = all;
   vector<string> v = ics::split(all, " ");
   size_t posFound;
   for(int i = 0; i < v.size(); ++i){

      if(wordQ.size() < os){
            wordQ.enqueue(v[i]);
            key += v[i];
      }

      if(wordQ.size() == os){

         for(int j = 0; j < all.size(); ++j ){
          int index = 0;
          cout << "j1 " << j << endl;
          posFound = everything.find(key);
           index = posFound+1;
          index += os*2;
          follow.insert( everything.substr( index, 1 ));
           cout << "follow  " << follow << endl;
           cout << "index = " << index << endl;

           j = index;
           everything = everything.substr(j+1, (all.size() - j) );
           cout << "everything " << everything << endl;
           cout << "j " << j << endl;

         }

          map.put(wordQ, follow);
          key = key.substr(0, key.size());
          wordQ.dequeue();
          --i;

      }
   }


   return map;
}


//Print "Corpus" and all entries in the Corpus, in lexical alphabetical order
//  (with the minimum and maximum set sizes at the end).
//Use a "can be followed by any of" to separate the key word from the Set of words
//  that can follow it.

//One queue is lexically greater than another, if its first value is smaller; or if
//  its first value is the same and its second value is smaller; or if its first
//  and second values are the same and its third value is smaller...
//If any of its values is less than the corresponding value in the other queue,
//  the first queue is not greater.
//Note that the queues sizes are the same: each stores Order-Statistic words
//Important: Use iterators for examining the queue values: DO NOT CALL DEQUEUE.

bool queue_gt(const CorpusEntry& a, const CorpusEntry& b) {
   WordQueue q1, q2;
   q1 = a.first;
   q2 = b.first;

   for(ics::Iterator<string> &it = q1.ibegin() ; it != q1.iend(); ){
      for(ics::Iterator<string> &t = q2.ibegin() ; t != q2.iend(); ){
         if( *it == *t ){
            ++it;
            ++t;
         }
         else return (*it < *t);
      }
   }

   return true;
}


//Print "Corpus" and all entries in the Corpus, in lexical alphabetical order
//  (with the minimum and maximum set sizes at the end).
//Use a "can be followed by any of" to separate the key word from the Set of words
//  that can follow it.

void print_corpus(const Corpus& corpus) {
  int min = 0;
  int max = 0;
  CorpusPQ pq(corpus.ibegin(), corpus.iend(), queue_gt);
  cout << "Corpus"<< endl;
  for(auto qs: pq){
    if(qs.second.size() < min )
       min = qs.second.size();
    if(qs.second.size() >= max )
       max = qs.second.size();
     cout << qs.first << "->" << qs.second << endl;
  }
  cout << "min/max = " << min << "/" << max << endl;
}


//Return a Queue of words, starting with those in start and including count more
//  randomly selected words using corpus to decide which word comes next.
//If there is no word that follows the previous ones, put "None" into the queue
//  and return immediately this list (whose size is <= start.size() + count).
WordQueue produce_text(const Corpus& corpus, const WordQueue& start, int count) {
   WordQueue generated_words, current_nwords;
   generated_words.enqueue(start.peek());
   current_nwords.enqueue(start.peek());


   for(ics::Iterator<string>& key = start.ibegin( ) ; key!=start.iend() ; ++key ){
      //corpus[*key];
   }
}

//Prompt the user for (a) the order statistic and (b) the file storing the text.
//Read the text as a Corpus and print it appropriately.
//Prompt the user for order statistic words from the text.
//Prompt the user for number of random words to generate
//Call the functions above to solve the problem, and print the appropriate information
int main() {
  try {
   int order;
   cout << "Enter the order statistic: "  << endl;
   cin >> order;
   ifstream file;
   ics::safe_open(file, "File Name", "wginput1.txt");
   print_corpus(read_corpus(order,file));

 } catch (ics::IcsError& e) {
   cout << e.what() << endl;
  }

 return 0;
}
