#include "linear.hpp"

namespace lasd {

    template <typename Data>
    inline const Data& LinearContainer<Data>::Front() const{
        return operator[](0);
    }

    template <typename Data>
    inline Data& LinearContainer<Data>::Front(){
        return operator[](0);
    }

    template <typename Data>
    inline const Data& LinearContainer<Data>::Back() const{
        return operator[](Container::size -1);
    }

    template <typename Data>
    inline Data& LinearContainer<Data>::Back(){
        return operator[](Container::size -1);
    }

    //stabilisco una funzione di default quando chiamo Traverse
    template <typename Data>
    inline void LinearContainer<Data>::Traverse(TraverseFun functionTraverse) const{
        PreOrderTraverse(functionTraverse);
    }

    template <typename Data>
    inline void LinearContainer<Data>::PreOrderTraverse(TraverseFun functionTraverse) const{
        for (ulong i = 0; i<Container::size; i++){
            functionTraverse(operator[](i));
        }
    }

    template <typename Data>
    inline void LinearContainer<Data>::PostOrderTraverse(TraverseFun functionTraverse) const{
        
        ulong i = Container::size;
        while (i>0){
            i--;
            functionTraverse(operator[](i));
        }

    }

    //stabilisco una funzione di default quando chiamo Map
    template <typename Data>
    inline void LinearContainer<Data>::Map(MapFun fun){
        PreOrderMap(fun);
    }

    template <typename Data>
    inline void LinearContainer<Data>::PreOrderMap(MapFun fun){
        for (ulong i = 0; i<Container::size; ++i){
            fun(operator[](i));
        }
    }

    template <typename Data>
    inline void LinearContainer<Data>::PostOrderMap(MapFun fun){

        // std::cout<<"[d] size: "<<Container::size<<"\n";
        ulong i = Container::size;
        while (i>0){
            --i;
            fun(operator[](i));
        }
    }

    template <typename Data>
    inline bool LinearContainer<Data>::operator==(const LinearContainer<Data>& conToCmp) const noexcept{

        if(this->size != conToCmp.Size()) return false;

        for(ulong i = 0; i<this->size; i++){
            if(this->operator[](i)!=conToCmp.operator[](i)){
                return false;
            }
        }

        return true;

    }

    template <typename Data>
    inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& conToCmp) const noexcept{

        return !(*this == conToCmp);

    }

    template <typename Data>
    inline void SortableLinearContainer<Data>::Sort() noexcept {
        QuickSort(0, Container::size-1);
    }

    template <typename Data>
    inline void SortableLinearContainer<Data>::QuickSort (ulong p, ulong r) noexcept{

        if(p<r){
            ulong q = Partition (p, r);
            QuickSort(p, q);
            QuickSort(q+1, r);
        }

    }

    template <typename Data>
    inline ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept{

        Data x = this->operator[](p);
        ulong i = p-1;
        ulong j = r+1;
        do{
            do{
                j--;
            }while(x<this->operator[](j));

            do{ 
                i++;
            }while(x>this->operator[](i));

            if(i<j){
                std::swap(this->operator[](i), this->operator[](j));
            }
        }while (i<j);

        return j;

    }

}
