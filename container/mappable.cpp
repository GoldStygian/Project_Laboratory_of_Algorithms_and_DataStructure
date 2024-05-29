#include "mappable.hpp"

namespace lasd {

    //reminder Map(MapFun)
    //reminder Map(function<void(Data &)>)
    //devo dire cosa fare a map con la function

    /*
    template<typename Data>
    inline void PreOrderMappableContainer<Data>::PreOrderMap(MapFun fun){
        Map(
            [&fun](Data & dat){
                fun(dat);
            }
        );
    }

    template<typename Data>
    inline void PostOrderMappableContainer<Data>::PostOrderMap(MapFun fun){
        Map(
            [fun](Data & dat){
                fun(dat);
            }
        );
    }

    template<typename Data>
    inline void InOrderMappableContainer<Data>::InOrderMap(MapFun fun){
        Map(
            [fun](Data & dat){
                fun(dat);
            }
        );
    }

    template<typename Data>
    inline void BreadthMappableContainer<Data>::BreadthMap(MapFun fun){
        Map(
            [fun](Data & dat){
                fun(dat);
            }
        );
    }
    */
   
    //Specific member function (PreOrderMappableContainer)

    template <typename Data>
    inline void PreOrderMappableContainer<Data>::Map(MapFun fun){
        PreOrderMap(fun);
    }

    //Specific member funtion (PostOrderMappableContainer)

    template <typename Data>
    inline void PostOrderMappableContainer<Data>::Map(MapFun fun){
        PostOrderMap(fun);
    }

    //Specific member function (InOrderMappableContainer)

    template <typename Data>
    inline void InOrderMappableContainer<Data>::Map(MapFun fun){
        InOrderMap(fun);
    }

    //Specific member function (BreadthMappableContainer)

    template <typename Data>
    inline void BreadthMappableContainer<Data>::Map(MapFun fun){
        BreadthMap(fun);
    }

}