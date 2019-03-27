//Valencia Wongso       Unique ID:641813

#ifndef HASH_MAP_HPP_
#define HASH_MAP_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "array_queue.hpp"   //For traversal


namespace ics {

template<class KEY,class T> class HashMap : public Map<KEY,T>	{
  public:
    typedef ics::pair<KEY,T> Entry;
    HashMap() = delete;
    HashMap(int (*ahash)(const KEY& k), double the_load_factor = 1.0);
    HashMap(int initial_bins, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
	  HashMap(const HashMap<KEY,T>& to_copy);
	  HashMap(std::initializer_list<Entry> il, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
    HashMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop, int (*ahash)(const KEY& k), double the_load_factor = 1.0);
	  virtual ~HashMap();

    virtual bool empty      () const;
    virtual int  size       () const;
    virtual bool has_key    (const KEY& key) const;
    virtual bool has_value  (const T& value) const;
    virtual std::string str () const;

    virtual T    put   (const KEY& key, const T& value);
    virtual T    erase (const KEY& key);
    virtual void clear ();

    virtual int put   (ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop);

    virtual T&       operator [] (const KEY&);
    virtual const T& operator [] (const KEY&) const;
    virtual HashMap<KEY,T>& operator = (const HashMap<KEY,T>& rhs);
    virtual bool operator == (const Map<KEY,T>& rhs) const;
    virtual bool operator != (const Map<KEY,T>& rhs) const;

    template<class KEY2,class T2>
    friend std::ostream& operator << (std::ostream& outs, const HashMap<KEY2,T2>& m);

    virtual ics::Iterator<Entry>& ibegin () const;
    virtual ics::Iterator<Entry>& iend   () const;

   private:
     class LN;

   public:
     class Iterator : public ics::Iterator<Entry> {
       public:
        //KLUDGE should be callable only in begin/end
        Iterator(HashMap<KEY,T>* iterate_over, bool begin);
        Iterator(const Iterator& i);
       virtual ~Iterator();
        virtual Entry       erase();
        virtual std::string str  () const;
        virtual const ics::Iterator<Entry>& operator ++ ();
        virtual const ics::Iterator<Entry>& operator ++ (int);
        virtual bool operator == (const ics::Iterator<Entry>& rhs) const;
        virtual bool operator != (const ics::Iterator<Entry>& rhs) const;
        virtual Entry& operator *  () const;
        virtual Entry* operator -> () const;
      private:
        ics::pair<int,LN*> current; //Bin Index/Cursor; stop: LN* == nullptr
        HashMap<KEY,T>*    ref_map;
        int                expected_mod_count;
        bool               can_erase = true;
        void advance_cursors();
    };

    virtual Iterator begin () const;
    virtual Iterator end   () const;
    //KLUDGE: define
    //virtual ics::Iterator<KEY>&  begin_key   () const;
    //virtual ics::Iterator<KEY>&  end_key     () const;
    //virtual ics::Iterator<T>&    begin_value () const;
    //virtual ics::Iterator<T>&    end_value   () const;

    private:
      class LN {
        public:
          LN ()                         : next(nullptr){}
          LN (const LN& ln)             : value(ln.value), next(ln.next){}
          LN (Entry v, LN* n = nullptr) : value(v), next(n){}

          Entry value;
          LN*   next;
      };

      LN** map      = nullptr;
      int (*hash)(const KEY& k);
      double load_factor;//used/bins <= load_factor
      int bins      = 1; //# bins available in the array
      int used      = 0; //# of key->value pairs in the hash table
      int mod_count = 0; //For sensing concurrent modification
      int   hash_compress (const KEY& key) const;
      void  ensure_load_factor(int new_used);
      LN*   find_key (int bin, const KEY& key) const;
      bool  find_value (const T& value) const;
      LN*   copy_list(LN*   l) const;
      LN**  copy_hash_table(LN** ht, int bins) const;
      void  delete_hash_table(LN**& ht, int bins);
  };





template<class KEY,class T>
HashMap<KEY,T>::HashMap(int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
  //write code here
   map = new LN*[bins];
   for( int i = 0; i < bins; i++ )
      map[i] = new LN();
}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(int initial_bins, int (*ahash)(const KEY& k), double the_load_factor) : bins(initial_bins), hash(ahash), load_factor(the_load_factor) {
  //write code here
   if(bins < 1)
      bins = 1;
   map = new LN*[bins];
   for(int i = 0; i < bins; i++)
      map[i] = new LN();
}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(const HashMap<KEY,T>& to_copy) : hash(to_copy.hash), load_factor(to_copy.load_factor), bins(to_copy.bins), used(to_copy.used) {
  //write code here
   map = copy_hash_table(to_copy.map, bins);
}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop, int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
  //write code here
   map = new LN*[bins];
   put(start,stop);
}

template<class KEY,class T>
HashMap<KEY,T>::HashMap(std::initializer_list<Entry> il,int (*ahash)(const KEY& k), double the_load_factor) : hash(ahash), load_factor(the_load_factor) {
  //write code here
   for (Entry m_entry : il)
      put(m_entry.first, m_entry.second);
}

template<class KEY,class T>
HashMap<KEY,T>::~HashMap() {
  //write code here
   delete_hash_table(map,bins);
}


template<class KEY,class T>
inline bool HashMap<KEY,T>::empty() const {
  //write code here
   return used == 0;
}

template<class KEY,class T>
int HashMap<KEY,T>::size() const {
  //write code here
   return used;
}

template<class KEY,class T>
bool HashMap<KEY,T>::has_key (const KEY& key) const {
  //write code here
   if(find_key(hash_compress(key),key) != nullptr){
      return true;
   }
   return false;

}

template<class KEY,class T>
bool HashMap<KEY,T>::has_value (const T& value) const {
  //write code here
   find_value(value);
}

template<class KEY,class T>
std::string HashMap<KEY,T>::str() const {
  //write code here
   std::ostringstream out;
   for ( int i = 0 ; i < bins ; ++i ) {
      out << std::endl << "bin[" << i << "]: ";
      for ( LN* p = map[i] ; p->next != nullptr ; p = p->next ) {
         out << "pair[" << p->value.first << "," << p->value.second << "] -> ";
      }
      out << "#";
   }
   return out.str();
}

template<class KEY,class T>
T HashMap<KEY,T>::put(const KEY& key, const T& value) {
  //write code here
   if( find_key(hash_compress(key),key) != nullptr ){
      T temp;
      temp = find_key(hash_compress(key),key)->value.second;
      find_key(hash_compress(key),key)->value.second = value;
      return temp;
   }
   else
      map[hash_compress(key)] = new LN(ics::pair<KEY,T>(key,value), map[hash_compress(key)]);

   ++used;
   ++mod_count;
}

template<class KEY,class T>
T HashMap<KEY,T>::erase(const KEY& key) {
  //write code here
   T temp;
   if(find_key(hash_compress(key),key) != nullptr){
      LN* to_delete = find_key(hash_compress(key),key)->next;
      temp = find_key(hash_compress(key),key)->value.second;
      find_key(hash_compress(key),key)->next = find_key(hash_compress(key),key)->next->next;
      delete to_delete;
      --used;
      ++mod_count;
      return temp;

   }
   else {
        std::ostringstream answer;
        answer << "HashMap::erase: key(" << key << ") not in Map";
        throw KeyError(answer.str());
   }
}

template<class KEY,class T>
void HashMap<KEY,T>::clear() {
  //write code here
   delete_hash_table(map,bins);
   bins = 1;
   map = new LN*[bins];
   map[0] = new LN();
   used = 0;
   ++mod_count;
}

template<class KEY,class T>
int HashMap<KEY,T>::put (ics::Iterator<Entry>& start, const ics::Iterator<Entry>& stop) {
  //write code here
   int count = 0;
   for (; start != stop; ++start) {
     ++count;
     put(start->first,start->second);
   }

   return count;
}

template<class KEY,class T>
T& HashMap<KEY,T>::operator [] (const KEY& key) {
  //write code here
   if (find_key(hash_compress(key),key) != nullptr)
      return find_key(hash_compress(key),key)->value.second;

   put(key,T());
   return find_key(hash_compress(key),key)->value.second;
}

template<class KEY,class T>
const T& HashMap<KEY,T>::operator [] (const KEY& key) const {
  //write code here
   if(find_key(hash_compress(key),key) != nullptr)
      return find_key(hash_compress(key),key)->value.second;

   std::ostringstream answer;
   answer << "HashMap.operator []: key(" << key << ") not in Map";
   throw KeyError(answer.str());
}

template<class KEY,class T>
bool HashMap<KEY,T>::operator == (const Map<KEY,T>& rhs) const {
  //write code here
   if (this == &rhs)
     return true;
   if (used != rhs.size())
     return false;
   for (int i = 0; i < bins; ++i){
      for (LN* p = map[i] ; p->next != nullptr ; p = p->next) {
         if (!rhs.has_key(p->value.first))
            return false;
         else if (rhs[p->value.first] != p->value.second)
            return false;
      }

   return true;
   }
}

template<class KEY,class T>
HashMap<KEY,T>& HashMap<KEY,T>::operator = (const HashMap<KEY,T>& rhs) {
  //write code here
   if (this == &rhs)
     return *this;

   used = rhs.used;
   copy_hash_table(rhs.map,rhs.bins);

   ++mod_count;
   return *this;
}

template<class KEY,class T>
bool HashMap<KEY,T>::operator != (const Map<KEY,T>& rhs) const {
  //write code here
   return !(*this == rhs);
}


template<class KEY,class T>
std::ostream& operator << (std::ostream& outs, const HashMap<KEY,T>& m) {
  //write code here
   outs << "map[";
   int first = 0;

   if (!m.empty()) {
      for ( int i = 0 ; i < m.bins ; i++ ) {
         for ( auto p = m.map[i] ; p->next != nullptr ; p = p->next ) {
            if (first == 0){
               outs << p->value.first << "->" << p->value.second;
               first = 1;
            }
            else{
               outs << "," << p->value.first << "->" << p->value.second;
            }
         }
      }
   }

   outs << "]";
   return outs;
}

//KLUDGE: memory-leak
template<class KEY,class T>
auto HashMap<KEY,T>::ibegin () const -> ics::Iterator<Entry>& {
  return *(new Iterator(const_cast<HashMap<KEY,T>*>(this),true));
}

//KLUDGE: memory-leak
template<class KEY,class T>
auto HashMap<KEY,T>::iend () const -> ics::Iterator<Entry>& {
  return *(new Iterator(const_cast<HashMap<KEY,T>*>(this),false));
}

template<class KEY,class T>
auto HashMap<KEY,T>::begin () const -> HashMap<KEY,T>::Iterator {
  return Iterator(const_cast<HashMap<KEY,T>*>(this),true);
}

template<class KEY,class T>
auto HashMap<KEY,T>::end () const -> HashMap<KEY,T>::Iterator {
  return Iterator(const_cast<HashMap<KEY,T>*>(this),false);
}

template<class KEY,class T>
int HashMap<KEY,T>::hash_compress (const KEY& key) const {
  //write code here
   int compressed = 0;
   int absKey = hash(key);

   if( hash(key) < 0 ){
      absKey = hash(key) * (-1);
   }

   compressed = absKey % bins;

   return compressed;

}

template<class KEY,class T>
void HashMap<KEY,T>::ensure_load_factor(int new_used) {
  //write code here
   if(new_used >= load_factor){
      int oldBins = bins;
      bins = 2*bins;
      LN** newMap = new LN*[bins];
      for ( int i = 0 ; i < bins ; ++i ) {
         newMap[i] = new LN();
      }
      for ( int i = 0 ; i < oldBins ; ++i ) {
         for ( LN* p = map[i] ; p->next != nullptr ; p = p->next ) {
            LN* temp = new LN();
            temp->value.first = p->value.first;
            temp->value.second = p->value.second;
            temp->next = newMap[hash_compress(p->value.first)];
            newMap[hash_compress(p->value.first)] = temp;
         }
      }
      delete_hash_table(newMap,oldBins);
   }


}

template<class KEY,class T>
typename HashMap<KEY,T>::LN* HashMap<KEY,T>::find_key (int bin, const KEY& key) const {
  //write code here
   for( LN* p = map[bin]; p->next != nullptr; p = p->next){
      if( p->value.first == key){
         return p;
      }
   }
   return nullptr;
}

template<class KEY,class T>
bool HashMap<KEY,T>::find_value (const T& value) const {
  //write code here
   for( int i = 0 ; i < bins; i++){
      for(LN* p = map[i]; p->next != nullptr; p = p->next){
         if( p->value.second == value ){
            return true;
         }
      }
   }
   return false;
}

template<class KEY,class T>
typename HashMap<KEY,T>::LN* HashMap<KEY,T>::copy_list (LN* l) const {
  //write code here
   if( l == nullptr )
      return nullptr;
   else
      return new LN(ics::pair<KEY,T>(l->value.first,l->value.second), copy_list(l->next));
}

template<class KEY,class T>
typename HashMap<KEY,T>::LN** HashMap<KEY,T>::copy_hash_table (LN** ht, int bins) const {
  //write code here
   if(ht == nullptr)
      return nullptr;
   else{
      LN** to_copy = new LN*[bins];
      for(int i = 0; i < bins; i++){
         to_copy[i] = new LN();
         to_copy[i] = copy_list(ht[i]);
      }
      return to_copy;
   }
}

template<class KEY,class T>
void HashMap<KEY,T>::delete_hash_table (LN**& ht, int bins) {
  //write code here
   for(int i = 0; i < bins; i++){
      LN* temp = ht[i];
      while ( temp != nullptr ) {
         LN* to_delete = temp;
         temp = temp->next;
         delete to_delete;
      }
   }
   delete[] ht;
}


template<class KEY,class T>
void HashMap<KEY,T>::Iterator::advance_cursors(){
  //write code here
}

template<class KEY,class T>
HashMap<KEY,T>::Iterator::Iterator(HashMap<KEY,T>* iterate_over, bool begin) : ref_map(iterate_over) {
  //write code here
   expected_mod_count = ref_map->mod_count;
   if(begin){
      current.first = 0;
      current.second = ref_map->map[0];
   }
   else{
      current.first = -1;
      current.second = nullptr;
   }

}

template<class KEY,class T>
HashMap<KEY,T>::Iterator::Iterator(const Iterator& i) :
    current(i.current), ref_map(i.ref_map), expected_mod_count(i.expected_mod_count), can_erase(i.can_erase) {}

template<class KEY,class T>
HashMap<KEY,T>::Iterator::~Iterator()
{}

template<class KEY,class T>
auto HashMap<KEY,T>::Iterator::erase() -> Entry {
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::erase");
  if (!can_erase)
    throw CannotEraseError("HashMap::Iterator::erase Iterator cursor already erased");
  if (current.second == nullptr)
    throw CannotEraseError("HashMap::Iterator::erase Iterator cursor beyond data structure");

  //write code here
//  can_erase = false;
//  Entry to_return = ref_map->map[current];
//  ref_map->erase_at(current);
//  expected_mod_count = ref_map->mod_count;
//  return to_return;
}

template<class KEY,class T>
std::string HashMap<KEY,T>::Iterator::str() const {
  std::ostringstream ans;
  ans << ref_map->str() << "(current=" << current.first << "|" <<
        current.second << ",expected_mod_count=" << expected_mod_count
        << ",can_erase=" << can_erase << ")";
  return ans.str();
}

//KLUDGE: cannot use Entry
template<class KEY,class T>
auto  HashMap<KEY,T>::Iterator::operator ++ () -> const ics::Iterator<ics::pair<KEY,T>>& {
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator ++");

  //write code here
//  if (current >= ref_map->used)
//    return *this;
//
//  Iterator* to_return = new Iterator(this->ref_map,current-1);
//  if (!can_erase)
//    can_erase = true;
//  else{
//    ++to_return->current;
//    ++current;
//  }
//
//  return *to_return;

}

//KLUDGE: creates garbage! (can return local value!)
template<class KEY,class T>
auto HashMap<KEY,T>::Iterator::operator ++ (int) -> const ics::Iterator<ics::pair<KEY,T>>&{
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator ++(int)");

  //write code here
//  if (current >= ref_map->used)
//    return *this;
//
//  Iterator* to_return = new Iterator(this->ref_map,current-1);
//  if (!can_erase)
//    can_erase = true;
//  else{
//    ++to_return->current;
//    ++current;
//  }
//
//  return *to_return;
}

template<class KEY,class T>
bool HashMap<KEY,T>::Iterator::operator == (const ics::Iterator<Entry>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HashMap::Iterator::operator ==");
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator ==");
  if (ref_map != rhsASI->ref_map)
    throw ComparingDifferentIteratorsError("HashMap::Iterator::operator ==");

  //write code here
  return current == rhsASI->current;
}


template<class KEY,class T>
bool HashMap<KEY,T>::Iterator::operator != (const ics::Iterator<Entry>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HashMap::Iterator::operator !=");
  if (expected_mod_count != ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator !=");
  if (ref_map != rhsASI->ref_map)
    throw ComparingDifferentIteratorsError("HashMap::Iterator::operator !=");

  //write code here
  return current != rhsASI->current;
}

template<class KEY,class T>
ics::pair<KEY,T>& HashMap<KEY,T>::Iterator::operator *() const {
  if (expected_mod_count !=
      ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator *");
  if (!can_erase || current.second == nullptr)
    throw IteratorPositionIllegal("HashMap::Iterator::operator * Iterator illegal: exhausted");

  //write code here
  return current.second->value;
}

template<class KEY,class T>
ics::pair<KEY,T>* HashMap<KEY,T>::Iterator::operator ->() const {
  if (expected_mod_count !=
      ref_map->mod_count)
    throw ConcurrentModificationError("HashMap::Iterator::operator *");
  if (!can_erase || current.second == nullptr)
    throw IteratorPositionIllegal("HashMap::Iterator::operator -> Iterator illegal: exhausted");

  //write code here
  return &(current.second->value);
}

}

#endif /* HASH_MAP_HPP_ */
