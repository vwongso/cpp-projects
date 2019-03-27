#ifndef LINKED_SET_HPP_
#define LINKED_SET_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "set.hpp"

namespace ics {

template<class T> class LinkedSet : public Set<T>	{
  public:
	  LinkedSet();
	  LinkedSet(const LinkedSet<T>& to_copy);
	  LinkedSet(std::initializer_list<T> il);
	  LinkedSet(ics::Iterator<T>& start, const ics::Iterator<T>& stop);
	  virtual ~LinkedSet();

    virtual bool empty      () const;
    virtual int  size       () const;
    virtual bool contains   (const T& element) const;
    virtual std::string str () const;

    virtual bool contains (ics::Iterator<T>& start, const ics::Iterator<T>& stop) const;

    virtual int  insert (const T& element);
    virtual int  erase  (const T& element);
    virtual void clear  ();

    virtual int insert (ics::Iterator<T>& start, const ics::Iterator<T>& stop);
    virtual int erase  (ics::Iterator<T>& start, const ics::Iterator<T>& stop);
    virtual int retain (ics::Iterator<T>& start, const ics::Iterator<T>& stop);

    virtual LinkedSet<T>& operator = (const LinkedSet<T>& rhs);
    virtual bool operator == (const Set<T>& rhs) const;
    virtual bool operator != (const Set<T>& rhs) const;
    virtual bool operator <= (const Set<T>& rhs) const;
    virtual bool operator <  (const Set<T>& rhs) const;
    virtual bool operator >= (const Set<T>& rhs) const;
    virtual bool operator >  (const Set<T>& rhs) const;

    template<class T2>
    friend std::ostream& operator << (std::ostream& outs, const LinkedSet<T2>& s);

  private:
    class LN;

  public:
    class Iterator : public ics::Iterator<T> {
      public:
        //KLUDGE should be callable only in begin/end
        Iterator(LinkedSet<T>* fof, LN* initial);
        virtual ~Iterator();
        virtual T           erase();
        virtual std::string str  () const;
        virtual const ics::Iterator<T>& operator ++ ();
        virtual const ics::Iterator<T>& operator ++ (int);
        virtual bool operator == (const ics::Iterator<T>& rhs) const;
        virtual bool operator != (const ics::Iterator<T>& rhs) const;
        virtual T& operator *  () const;
        virtual T* operator -> () const;
      private:
        LN*           current;  //if can_erase is false, this value is unusable
        LinkedSet<T>* ref_set;
        int           expected_mod_count;
        bool          can_erase = true;
    };

    //For explicit use: Iterator<...>& it = c.ibegin(); ... or for (Iterator<...>& it = c.ibegin(); it != c.iend(); ++it)...
    virtual ics::Iterator<T>& ibegin () const;
    virtual ics::Iterator<T>& iend   () const;

    //For implicit use: for (... i : c)...
    virtual Iterator begin () const;
    virtual Iterator end   () const;

  private:
    class LN {
      public:
        LN ()                      {}
        LN (const LN& ln)          : value(ln.value), next(ln.next){}
        LN (T v,  LN* n = nullptr) : value(v), next(n){}

        T   value;
        LN* next   = nullptr;
    };

    int used      = 0;             //Cache of # values in set
    LN* front     = new LN();
    LN* trailer   = front;
    int mod_count = 0;             //For sensing concurrent modification
    int erase_at(LN* p);
    void delete_list(LN*& front);  //Recycle storage, set front's argument to nullptr;
  };



//See code in array_set.hpp and linked_queue.hpp and linked_priority_queue.hpp

//Write the constructors, methods, and operators here for LinkedSet

//Write the constructor, destructor, methods, and operators here for
//  LinkedSet's Iterator

template<class T>
LinkedSet<T>::LinkedSet(){
   front = front->next;
}

template<class T>
LinkedSet<T>::LinkedSet(const LinkedSet<T>& to_copy){
   used = to_copy.used;
   mod_count = to_copy.mod_count;
   front = to_copy.front;
   trailer = front;
   //   used = to_copy.used;
   //   mod_count = to_copy.mod_count;
   //   LN* p = to_copy.front;
   //   front = new LN(p->value, nullptr);
   //   rear = front;
   //   p = p->next;
   //   for(;p != nullptr; p = p->next)
   //      rear=rear->next=new LN(p->value, rear->next);
}

template<class T>
LinkedSet<T>::LinkedSet(std::initializer_list<T> il){
   for(T val:il)
      insert(val);
}

template<class T>
LinkedSet<T>::LinkedSet(ics::Iterator<T>& start, const ics::Iterator<T>& stop){
   while(start != stop){
      insert(*start++);
   }
}

template<class T>
LinkedSet<T>::~LinkedSet(){
   delete_list(front);
}

template<class T>
bool LinkedSet<T>::empty()const{
   return used == 0 && front == trailer;
}

template<class T>
int LinkedSet<T>::size()const{
   return used;
}

template<class T>
bool LinkedSet<T>::contains   (const T& element) const{
   for(LN* p = front->next; p != nullptr; p = p->next){
      if(p->value == element)
         return true;
   }
   return false;
}

template<class T>
std::string LinkedSet<T>::str() const {
  std::ostringstream answer;
  answer << *this << "(length=" << size() << ",used=" << used << ",mod_count=" << mod_count << ")";
  return answer.str();
}

template<class T>
bool LinkedSet<T>::contains (ics::Iterator<T>& start, const ics::Iterator<T>& stop) const{
   for (; start != stop; ++start)
     if (!contains(*start))
       return false;

   return true;
}

template<class T>
int LinkedSet<T>::insert(const T& element) {
   for(LN* p = front->next; p != nullptr; p = p->next){
      if( p->value == element){
         return 0;
      }
   }

   front = new LN(element,front);
   ++mod_count;
   ++used;
   return 1;
//  for (int i=0; i<used; ++i)
//    if (set[i] == element)
//      return 0;
//
//  this->ensure_length(used+1);
//  set[used++] = element;
//  ++mod_count;
//  return 1;
}

template<class T>
int LinkedSet<T>::erase(const T& element) {
   for( LN* p = front->next; p != nullptr; p = p->next){
      if( p->value == element )
         return erase_at(p);
   }
   --used;
   ++mod_count;
   return 0;

//   LN<T>* to_delete = p->next;
//   *p = *to_delete;
//   delete to_delete;
//   return to_delete;

//  for (int i=0; i<used; ++i)
//    if (set[i] == element)
//      return erase_at(i);
//
//  return 0;
}

template<class T>
void LinkedSet<T>::clear() {
   delete_list(front);
}

template<class T>
int LinkedSet<T>::insert(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
  int count = 0;
  for (; start != stop; ++start)
    count += insert(*start);

  return count;
}

template<class T>
int LinkedSet<T>::erase(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
  int count = 0;
  for (; start != stop; start++)
    count += erase(*start);
  return count;
}

template<class T>
int LinkedSet<T>::retain(ics::Iterator<T>& start, const ics::Iterator<T>& stop) {
   LinkedSet<T> s(start,stop);
   int count = 0;
   for ( LN* p = front->next; p != nullptr; p = p->next ){
      if( !s.contains (p->value)){
         erase_at(p);
         //prev
      }
      else
         ++count;
   }

   return count;
//  ArraySet<T> s(start,stop);
//  int count = 0;
//  for (int i=0; i<used; i++)
//    if (!s.contains(set[i])) {
//      erase_at(i);
//      --i;
//    }else
//      ++count;
//
//  return count;
}

template<class T>
LinkedSet<T>& LinkedSet<T>::operator = (const LinkedSet<T>& rhs) {
   if (this == &rhs)
      return *this;
   for(LN* p = front->next; p != nullptr; p = p->next){
      insert(p->value);
   }

   return *this;
//  if (this == &rhs)
//    return *this;
//  this->ensure_length(rhs.used);
//  used = rhs.used;
//  for (int i=0; i<used; ++i)
//    set[i] = rhs.set[i];
//  ++mod_count;
//  return *this;
}

template<class T>
bool LinkedSet<T>::operator == (const Set<T>& rhs) const {
   if (this == &rhs)
      return true;
   if (used != rhs.size())
      return false;
   for (LN* p = front->next; p != nullptr; p = p->next){
      if (!rhs.contains(p->value))
         return false;
   }
//  if (this == &rhs)
//    return true;
//  if (used != rhs.size())
//    return false;
//  for (int i=0; i<used; ++i)
//    if (!rhs.contains(set[i]))
//      return false;

  return true;
}

template<class T>
bool LinkedSet<T>::operator != (const Set<T>& rhs) const {
  return !(*this == rhs);
}

template<class T>
bool LinkedSet<T>::operator <= (const Set<T>& rhs) const {
  if (this == &rhs)
    return true;
  if (used > rhs.size())
    return false;
  for (LN* p = front->next; p != nullptr; p = p->next)
     if (!rhs.contains(p->value))
        return false;

  return true;
}

template<class T>
bool LinkedSet<T>::operator < (const Set<T>& rhs) const {
  if (this == &rhs)
    return false;
  if (used >= rhs.size())
    return false;
  for (LN* p = front->next; p != nullptr; p = p->next)
     if(!rhs.contains(p->value))
        return false;

  return true;
}

template<class T>
bool LinkedSet<T>::operator >= (const Set<T>& rhs) const {
  return rhs <= *this;
}

template<class T>
bool LinkedSet<T>::operator > (const Set<T>& rhs) const {
  return rhs < *this;
}

template<class T>
std::ostream& operator << (std::ostream& outs, const LinkedSet<T>& s) {
  outs << "set[";
  if(!s.empty()){
     Iterator<T>& p = s.ibegin();
     outs << *p;
     ++p;
     for(;p != s.iend(); p++){
        outs << ",";
        outs << *p;
     }
  }
  outs << "]";
  return outs;
//
//  if (!s.empty()) {
//    outs << s.set[0];
//    for (int i = 1; i < s.used; ++i)
//      outs << ","<< s.set[i];
//  }
//
//  outs << "]";
//  return outs;
}

template<class T>
auto LinkedSet<T>::ibegin () const -> ics::Iterator<T>& {
  return *(new Iterator(const_cast<LinkedSet<T>*>(this),front));
}

template<class T>
auto LinkedSet<T>::iend () const -> ics::Iterator<T>& {
  return *(new Iterator(const_cast<LinkedSet<T>*>(this),nullptr));
}

template<class T>
auto LinkedSet<T>::begin () const -> LinkedSet<T>::Iterator {
  return Iterator(const_cast<LinkedSet<T>*>(this),front);
}


template<class T>
auto LinkedSet<T>::end () const -> LinkedSet<T>::Iterator {
  return Iterator(const_cast<LinkedSet<T>*>(this),nullptr);
}

template<class T>
int LinkedSet<T>::erase_at(LN* p) {
//   set[i] = set[--used];
   ++mod_count;
   return 1;
}

template<class T>
void LinkedSet<T>::delete_list(LN*& front){
   LN* temp;
//   while(front != nullptr){
//      if(front == ){
//         trailer = trailer->n;
//      }
      temp = front;
      front = front->next;
      delete temp;
//   }
//   used = 0;
   ++mod_count;

}

template<class T>
LinkedSet<T>::Iterator::~Iterator() {}

template<class T>
T LinkedSet<T>::Iterator::erase() {
   if (expected_mod_count != ref_set->mod_count)
      throw ConcurrentModificationError("LinkedSet::Iterator::erase");
   if (!can_erase)
      throw CannotEraseError("LinkedSet::Iterator::erase Iterator cursor already erased");
   if (current == nullptr)
      throw CannotEraseError("LinkedSet::Iterator::erase Iterator cursor beyond data structure");
   can_erase = false;

}

template<class T>
std::string LinkedSet<T>::Iterator::str() const {
  std::ostringstream answer;
  answer << ref_set->str() << "(current=" << current << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
  return answer.str();
}

template<class T>
const ics::Iterator<T>& LinkedSet<T>::Iterator::operator ++ () {
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("LinkedSet::Iterator::operator ++");

  if(current == nullptr)
     return *this;
  if(!can_erase)
     can_erase = true;
  else{
     prev = current;
     current = current->next;
  }
  return *this;
}

template<class T>
const ics::Iterator<T>& LinkedSet<T>::Iterator::operator ++ (int) {
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("LinkedSet::Iterator::operator ++(int)");

//  if (current >= ref_set->used)
//    return *this;
//
  Iterator* to_return = new Iterator(this->ref_set,current-1);
  if (!can_erase)
    can_erase = true;
  else{
    ++to_return->current;
    ++current;
  }

  return *to_return;
}


template<class T>
bool LinkedSet<T>::Iterator::operator == (const ics::Iterator<T>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("LinkedSet::Iterator::operator ==");
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("LinkedSet::Iterator::operator ==");
  if (ref_set != rhsASI->ref_set)
    throw ComparingDifferentIteratorsError("LinkedSet::Iterator::operator ==");

  return current == rhsASI->current;
}

template<class T>
bool LinkedSet<T>::Iterator::operator != (const ics::Iterator<T>& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("LinkedSet::Iterator::operator !=");
  if (expected_mod_count != ref_set->mod_count)
    throw ConcurrentModificationError("LinkedSet::Iterator::operator !=");
  if (ref_set != rhsASI->ref_set)
    throw ComparingDifferentIteratorsError("LinkedSet::Iterator::operator !=");

  return current != rhsASI->current;
}

template<class T>
T& LinkedSet<T>::Iterator::operator *() const {
   if (expected_mod_count != ref_set->mod_count)
      throw ConcurrentModificationError("LinkedSet::Iterator::operator *");
   if (!can_erase || current == nullptr) {
      std::ostringstream where;
      where << current
            << " when front = " << ref_set->front << " and "
            << " and rear = " << ref_set->trailer;
      throw IteratorPositionIllegal("LinkedSet::Iterator::operator * Iterator illegal: "+where.str());
   }
   return current->value;
}

template<class T>
T* LinkedSet<T>::Iterator::operator ->() const {
   if (expected_mod_count != ref_set->mod_count)
      throw ConcurrentModificationError("LinkedSet::Iterator::operator *");
   if (!can_erase || current == nullptr) {
      std::ostringstream where;
      where << current
            << " when front = " << ref_set->front << " and "
            << " and rear = " << ref_set->trailer;
      throw IteratorPositionIllegal("LinkedQueue::Iterator::operator * Iterator illegal: "+where.str());
   }

   return &(current->value);
}


//template<class T>
//const ics::Iterator<T>& LinkedQueue<T>::Iterator::operator ++ () {
//   if (expected_mod_count != ref_queue->mod_count)
//      throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++");
//  //Fill in the rest of the code here
//   if(current == nullptr)
//      return *this;
//   if(!can_erase)
//      can_erase = true;
//   else{
//      prev = current;
//      current = current->next;
//   }
//   return *this;
//}
//
////KLUDGE: can create garbage! (can return local value!)
//template<class T>
//const ics::Iterator<T>& LinkedQueue<T>::Iterator::operator ++ (int) {
//   if (expected_mod_count != ref_queue->mod_count)
//      throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++(int)");
//  //Fill in the rest of the code here
//   if(current == nullptr)
//      return *this;
//   Iterator * result = new Iterator(this->ref_queue,current);
//   if(!can_erase)
//      can_erase = true;
//   else{
//      prev = current;
//      current = current->next;
//   }
//   return *result;
//}


}

#endif /* LINKED_SET_HPP_ */
