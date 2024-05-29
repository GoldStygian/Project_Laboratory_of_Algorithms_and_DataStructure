#include "queuevec.hpp"

namespace lasd {

  // Specific constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const TraversableContainer<Data>& container): Vector<Data>(container), idTail(size){// A stack obtained from a TraversableContainer
    //vector init size, elements, copy
    if (size>0) Vector<Data>::Resize(size *2);
    else Vector<Data>::Resize(4);
  }

  template <typename Data>
  QueueVec<Data>::QueueVec(MappableContainer<Data>&& container): Vector<Data>(std::move(container)), idTail(size){  // A stack obtained from a MappableContainer
    if (size>0) Vector<Data>::Resize(size *2);
    else Vector<Data>::Resize(4);
  }

  // Move constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec<Data>&& queue): Vector<Data>(std::move(queue)){
    std::swap(idHead, queue.idHead);
    std::swap(idTail, queue.idTail);
    queue.Resize(4, 0);
  }

  // Copy assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue){
    Vector<Data>::operator=(queue);
    idTail = queue.idTail;
    idHead = queue.idHead;
    return *this;
  }

  // Move assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue){
    Vector<Data>::operator=(std::move(queue));
    std::swap(idTail, queue.idTail);
    std::swap(idHead, queue.idHead);
    return *this;
  }

  // Comparison operators
  template <typename Data>
  bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept{
    if(Size() == queue.Size()){ //se hanno effettivamente lo stesso numero di elementi "visibili"
        for( ulong idx = idHead, idx2 = queue.idHead; idx < idTail; idx++, idx2++){
            idx %= size;
            idx2 %= queue.size;
            if(Elements[idx] != queue.Elements[idx2]){
                return false;
            }
        }
    }else{
        return false;
    }

    return true;
  }

  template <typename Data>
  inline bool QueueVec<Data>::operator!=(const QueueVec& queue) const noexcept{
    return !(*this == queue);
  }

  // Specific member functions (inherited from Queue)
  template <typename Data>
  const Data& QueueVec<Data>::Head() const{ // Override Queue member (non-mutable version; must throw std::length_error when empty)
    if (Empty()){
        throw std::length_error("Access to an empty queue");
    }else{
        return Elements[idHead];
    }
  }


  template <typename Data>
  Data& QueueVec<Data>::Head(){ // Override Queue member (mutable version; must throw std::length_error when empty)
    if (Empty()){
        throw std::length_error("Access to an empty queue");
    }else{
        return Elements[idHead];
    }
  }

  template <typename Data>
  void QueueVec<Data>::Dequeue(){ // Override Queue member (must throw std::length_error when empty)
    if(Empty()){
        throw std::length_error("Access to an empty queue");
    }else{
        Reduce(); //verifico se posso diminuire la dimensione allocata della coda
        idHead++;
        idHead %= size;
    }
  }

  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue(){ // Override Queue member (must throw std::length_error when empty)
    if(Empty()){
        throw std::length_error("Access to an empty queue");
    }else{
        Reduce();
        Data data = std::move(Head());
        idHead++;
        idHead %= size;
        return data;
    }
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(const Data& data){ // Override Queue member (copy of the value)
    Expand();
    Elements[idTail] = data;
    idTail++;
    idTail%=size;
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(Data&& data){ // Override Queue member (move of the value)
    Expand();
    Elements[idTail] = std::move(data);
    idTail++;
    idTail%=size;
  }

  // Specific member functions (inherited from Container)
  template <typename Data>
  inline bool QueueVec<Data>::Empty() const noexcept{ // Override Container member
    return (idHead == idTail);
  }

  template <typename Data>
  inline ulong QueueVec<Data>::Size() const noexcept{
    return (((size + idTail)-idHead)%size); 
  }

  // Specific member function (inherited from ClearableContainer)
  template <typename Data>
  void QueueVec<Data>::Clear(){ // Override ClearableContainer member
    Vector<Data>::Resize(4);
    idHead = idTail = 0;
  }

  template <typename Data>
  void QueueVec<Data>::Expand(){
    ulong ele = Size();
    if (ele + 1 == size) Resize(size*2, ele);
  }

  template <typename Data>
  void QueueVec<Data>::Reduce(){
    ulong ele = Size();
    if (ele + 1 == size / 4) Resize(size/2, ele);
  }

  template <typename Data>
  void QueueVec<Data>::Resize(ulong newSize, ulong ele){
    
    Data* tmpElements = new Data[newSize];

    ulong minSize = (ele <= newSize) ? ele : newSize;
    
    for (ulong idx1 = idHead, idx2 = 0; idx2 < minSize; ++idx1 %= size, ++idx2) {
        std :: swap(Elements[idx1], tmpElements[idx2]);
    }
    std :: swap(Elements, tmpElements);
    delete[] tmpElements;
    idHead = 0;
    idTail = ele;
    size = newSize;
  }

}