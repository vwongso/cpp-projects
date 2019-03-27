#ifndef LINKED_QUEUE_HPP_
#define LINKED_QUEUE_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "iterator.hpp"
#include "queue.hpp"


namespace ics {

template<class T> class LinkedQueue : public Queue<T>  {
  public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<T>& to_copy);
    LinkedQueue(std::initializer_list<T> il);
    LinkedQueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop);
    virtual ~LinkedQueue();

    virtual bool empty      () const;
    virtual int  size       () const;
    virtual T&   peek       () const;
    virtual std::string str () const;

    virtual int  enqueue (const T& element);
    virtual T    dequeue ();
    virtual void clear   ();

    virtual int enqueue (ics::Iterator<T>& start, const ics::Iterator<T>& stop);

    virtual LinkedQueue<T>& operator = (const LinkedQueue<T>& rhs);
    virtual bool operator == (const Queue<T>& rhs) const;
    virtual bool operator != (const Queue<T>& rhs) const;

    template<class T2>
    friend std::ostream& operator << (std::ostream& outs, const LinkedQueue<T2>& s);

  private:
    class LN;

  public:
    class Iterator : public ics::Iterator<T> {
      public:
        //KLUDGE should be callable only in begin/end
        Iterator(LinkedQueue<T>* fof, LN* initial);
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
        LN*             prev = nullptr;  //if nullptr, current at front of list
        LN*             current;         //if can_erase is false, this value is unusable
        LinkedQueue<T>* ref_queue;
        int             expected_mod_count;
        bool            can_erase = true;
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
        LN* next = nullptr;
    };

    int used      =  0;
    LN* front     =  nullptr;
    LN* rear      =  nullptr;
    int mod_count =  0;            //For sensing of concurrent modification
    void delete_list(LN*& front);  //Recycle storage, set front's argument to nullptr;
};



//See code in array_queue.hpp

//Write the constructors, methods, and operators here for LinkedQueue
//Fill in the missing parts of the erase method and ++ operators
//  for LinkedQueue's Iterator
template<class T>
LinkedQueue<T>::LinkedQueue(){

}

template<class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& to_copy){
   used = to_copy.used;
   mod_count = to_copy.mod_count;
   LN* p = to_copy.front;
   front = new LN(p->value, nullptr);
   rear = front;
   p = p->next;
   for(;p != nullptr; p = p->next)
      rear=rear->next=new LN(p->value, rear->next);

}
template<class T>
LinkedQueue<T>::LinkedQueue(std::initializer_list<T> il){
   for(T val:il)
      enqueue(val);
}

template<class T>
LinkedQueue<T>::LinkedQueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop){
   while(start != stop){
      enqueue(*start++);
   }
}

template<class T>
LinkedQueue<T>::~LinkedQueue(){
   delete_list(front);
}

template<class T>
bool LinkedQueue<T>::empty()const{
   return front == nullptr && rear == nullptr;
}

template<class T>
int LinkedQueue<T>::size()const{
   return used;
}

template<class T>
T& LinkedQueue<T>::peek()const{
   if(front == nullptr)
      throw ics::EmptyError("queue::peek");
   return front->value;
}

template<class T>
std::string LinkedQueue<T>::str()const{
   std::ostringstream result;
   if(size() == 0)
      result << "queue[]";
   else{
      result << "queue[";
      for(ics::Iterator<T>& p = ibegin(); p != iend(); ++p){
         result << *p;
         result << (*p == rear->value?"]":",");
      }
   }
   result << "(length = " << size() << ", front = "<< front->value
         << ", rear = " << rear->value << ", mod_count = " << mod_count << ")";
   return result.str();
}

template<class T>
int LinkedQueue<T>::enqueue(const T& element){
   if(empty()){
      front = new LN(element, nullptr);
      rear = front;
      ++mod_count;
      ++used;
   }
   else{
      rear = rear->next = new LN(element,rear->next);
      ++mod_count;
      ++used;
   }
   return 1;
}

template<class T>
T LinkedQueue<T>::dequeue(){
   if(empty())
      throw EmptyError("queue::dequeue");
   T result = front->value;
   if(front == rear)
      rear = rear->next;
   front = front->next;
   --used;
   ++mod_count;
   return result;
}

template<class T>
void LinkedQueue<T>::clear(){
   delete_list(front);
}

template<class T>
int LinkedQueue<T>::enqueue(ics::Iterator<T>& start, const ics::Iterator<T>& stop){
   int count = 0;
   for(;start != stop; ++start){
      enqueue(*start);
      ++count;
   }
   return count;
}

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator =(const LinkedQueue<T>& rhs){
   if(this == &rhs)
      return * this;
   delete_list(front);
   for(LN* p = rhs.front; p != nullptr; p = p->next)
      enqueue(p->value);
   return *this;
}

template<class T>
bool LinkedQueue<T>::operator ==(const Queue<T>&rhs)const{
   if(this == &rhs)
      return true;
   if(this->size() != rhs.size())
      return false;
   ics::Iterator<T>& i = rhs.ibegin();
   for(LN* p = front;p != nullptr;p = p->next,++i)
      if(p->value != *i)
         return false;
   return true;
}

template<class T>
bool LinkedQueue<T>::operator !=(const Queue<T>& rhs)const{
   return ! (*this == rhs);
}

template<class T>
std::ostream& operator <<(std::ostream& outs,const LinkedQueue<T>& q){
   outs<<"queue[";
   if(!q.empty()){
      Iterator<T>& p = q.ibegin();
      outs << *p;
      ++p;
      for(;p != q.iend(); ++p){
         outs << ",";
         outs << *p;
      }
   }
   outs << "]:rear";
   return outs;
}

template<class T>
void LinkedQueue<T>::delete_list(LN*& front){
   LN* temp;
   while(front != nullptr){
      if(front == rear){
         rear = rear->next;
      }
      temp = front;
      front = front->next;
      delete temp;
   }
   used = 0;
   ++mod_count;
}

//KLUDGE: memory-leak
template<class T>
auto LinkedQueue<T>::ibegin () const -> ics::Iterator<T>& {
   return *(new Iterator(const_cast<LinkedQueue<T>*>(this),front));
}

//KLUDGE: memory-leak
template<class T>
auto LinkedQueue<T>::iend () const -> ics::Iterator<T>& {
   return *(new Iterator(const_cast<LinkedQueue<T>*>(this),nullptr));
}

template<class T>
auto LinkedQueue<T>::begin () const -> LinkedQueue<T>::Iterator {
   return Iterator(const_cast<LinkedQueue<T>*>(this),front);
}

template<class T>
auto LinkedQueue<T>::end () const -> LinkedQueue<T>::Iterator {
   return Iterator(const_cast<LinkedQueue<T>*>(this),nullptr);
}

template<class T>
LinkedQueue<T>::Iterator::Iterator(LinkedQueue<T>* fof, LN* initial) : current(initial), ref_queue(fof) {
   expected_mod_count = ref_queue->mod_count;
}

template<class T>
LinkedQueue<T>::Iterator::~Iterator() {}

template<class T>
T LinkedQueue<T>::Iterator::erase() {
   if (expected_mod_count != ref_queue->mod_count)
      throw ConcurrentModificationError("LinkedQueue::Iterator::erase");
   if (!can_erase)
      throw CannotEraseError("LinkedQueue::Iterator::erase Iterator cursor already erased");
   if (current == nullptr)
      throw CannotEraseError("LinkedQueue::Iterator::erase Iterator cursor beyond data structure");
  //Fill in the rest of the code here
   can_erase = false;
   T result = current->value;
      current = current->next;
   if(prev != nullptr){
      prev->next = current->next;
   }

   expected_mod_count =++ ref_queue->mod_count;
   return result;
}

template<class T>
std::string LinkedQueue<T>::Iterator::str() const {
   std::ostringstream answer;
   answer << ref_queue->str() << "(current = " << current
         << ", expected_mod_count = " << expected_mod_count
         << ", can_erase = " << can_erase << ")";
   return answer.str();
}

template<class T>
const ics::Iterator<T>& LinkedQueue<T>::Iterator::operator ++ () {
   if (expected_mod_count != ref_queue->mod_count)
      throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++");
  //Fill in the rest of the code here
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

//KLUDGE: can create garbage! (can return local value!)
template<class T>
const ics::Iterator<T>& LinkedQueue<T>::Iterator::operator ++ (int) {
   if (expected_mod_count != ref_queue->mod_count)
      throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++(int)");
  //Fill in the rest of the code here
   if(current == nullptr)
      return *this;
   Iterator * result = new Iterator(this->ref_queue,current);
   if(!can_erase)
      can_erase = true;
   else{
      prev = current;
      current = current->next;
   }
   return *result;
}

template<class T>
bool LinkedQueue<T>::Iterator::operator == (const ics::Iterator<T>& rhs) const {
   const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
   if (rhsASI == 0)
      throw IteratorTypeError("LinkedQueue::Iterator::operator ==");
   if (expected_mod_count != ref_queue->mod_count)
      throw ConcurrentModificationError("LinkedQueue::Iterator::operator ==");
   if (ref_queue != rhsASI->ref_queue)
      throw ComparingDifferentIteratorsError("LinkedQueue::Iterator::operator ==");

   return current == rhsASI->current;
}

template<class T>
bool LinkedQueue<T>::Iterator::operator != (const ics::Iterator<T>& rhs) const {
   const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
   if (rhsASI == 0)
      throw IteratorTypeError("LinkedQueue::Iterator::operator !=");
   if (expected_mod_count != ref_queue->mod_count)
      throw ConcurrentModificationError("LinkedQueue::Iterator::operator !=");
   if (ref_queue != rhsASI->ref_queue)
      throw ComparingDifferentIteratorsError("LinkedQueue::Iterator::operator !=");

   return current != rhsASI->current;
}

template<class T>
T& LinkedQueue<T>::Iterator::operator *() const {
   if (expected_mod_count != ref_queue->mod_count)
      throw ConcurrentModificationError("LinkedQueue::Iterator::operator *");
   if (!can_erase || current == nullptr) {
      std::ostringstream where;
      where << current
            << " when front = " << ref_queue->front << " and "
            << " and rear = " << ref_queue->rear;
      throw IteratorPositionIllegal("LinkedQueue::Iterator::operator * Iterator illegal: "+where.str());
   }
   return current->value;
}

template<class T>
T* LinkedQueue<T>::Iterator::operator ->() const {
   if (expected_mod_count != ref_queue->mod_count)
      throw ConcurrentModificationError("LinkedQueue::Iterator::operator *");
   if (!can_erase || current == nullptr) {
      std::ostringstream where;
      where << current
            << " when front = " << ref_queue->front << " and "
            << " and rear = " << ref_queue->rear;
      throw IteratorPositionIllegal("LinkedQueue::Iterator::operator * Iterator illegal: "+where.str());
   }

   return &(current->value);
}

}

#endif /* LINKED_QUEUE_HPP_ */
