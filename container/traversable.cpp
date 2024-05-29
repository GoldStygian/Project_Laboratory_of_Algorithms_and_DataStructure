#ifndef TRAVERSABLE_CPP//da togliere
#define TRAVERSABLE_CPP

#include "traversable.hpp"

namespace lasd {

/*reminder
  using TraverseFun = std::function<void(const Data &)>; //alias per una funzione
  virtual void Traverse(TraverseFun) = 0;

  come parametro di Traverse (gli passo una "funzione")
  ma quello che fa traverse l'ho ancora implementato
*/

//implementazione di fold
template<typename Data>
template<typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const{
    Traverse(
        [fun, &acc](const Data& data){ //&acc è il riferimento ad acc
            acc = fun (data, acc);
        }
    );
    return acc;
}

//implementazione di exists
template<typename Data>
inline bool TraversableContainer<Data>::Exists(const Data& data) const noexcept{
    bool flag = false;
    Traverse(
        [data, &flag](const Data& val){
            flag |= (data == val);//flag = flag || (data == val)
        }
    );
    return flag;
}

//implementazione di PreOrderFold
template<typename Data>
template<typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    
    PreOrderTraverse(
        [fun, &acc](const Data& data){ //&acc è il riferimento ad acc
            acc = fun (data, acc);
        }
    );
    return acc;
}

//implementazione di PostOrderFold
template<typename Data>
template<typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    PostOrderTraverse(
        [fun, &acc](const Data& data){ //&acc è il riferimento ad acc
            acc = fun (data, acc);
        }
    );
    return acc;
}

//implementazione di InOrderFold
template<typename Data>
template<typename Accumulator>
inline Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    InOrderTraverse(
        [fun, &acc](const Data& data){ //&acc è il riferimento ad acc
            acc = fun (data, acc);
        }
    );
    return acc;
}

//implementazione di BreadthFold
template<typename Data>
template<typename Accumulator>
inline Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    BreadthTraverse(
        [fun, &acc](const Data& data){ //&acc è il riferimento ad acc
            acc = fun (data, acc);
        }
    );
    return acc;
}

}

#endif