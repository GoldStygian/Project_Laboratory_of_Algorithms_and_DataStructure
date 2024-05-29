#include "stackvec.hpp"

namespace lasd {

    // Move constructor
    template <typename Data>
    StackVec<Data>::StackVec(StackVec&& st): Vector<Data>(std::move(st)){
        std::swap(index, st.index); //Move constructor non esegue swap di index (perche non c'è)
    }


    // Copy assignment
    template <typename Data>
    StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& st){
        Vector<Data>::operator=(st);
        this->index = st.index;
        return *this;
    }

    // Move assignment
    template <typename Data>
    StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& st){
        Vector<Data>::operator=(std::move(st));
        this->index = st.index;
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data>& st) const noexcept{
        if(st.index != index) return false;

        for(ulong i = 0; i<index; i++){
            if(st.Elements[i] != Elements[i]) return false;
        }

        return true;
        
    }

    template <typename Data>
    inline bool StackVec<Data>::operator!=(const StackVec<Data>& st) const noexcept{
        return !(*this == st);
    }

    // Specific member functions (inherited from Stack)
    template <typename Data>
    inline const Data& StackVec<Data>::Top() const { // Override Stack member (non-mutable version; must throw std::length_error when empty)

        if (index != 0) {
            return this->Elements[index - 1];
        }else{
            throw std::length_error("Access to an empty stack");
        }
    }

    template <typename Data>
    inline Data& StackVec<Data>::Top() { // Override Stack member (non-mutable version; must throw std::length_error when empty)
        if (index != 0) {
            return this->Elements[index - 1];
        }else{
            throw std::length_error("Access to an empty stack");
        }
    }

    // Funzioni ausiliarie
    template <typename Data>
    void StackVec<Data>::Reduce() {
        if (index == size / 4) Vector<Data>::Resize(size / 2);
    }

    template <typename Data>
    void StackVec<Data>::Expand() {
        if (index == size) Vector<Data>::Resize(size * 2);
    }

    template <typename Data>
    inline void StackVec<Data>::Pop() { // Rimuve solamente
        if (index!=0){
            Reduce();
            this->index--;
        }else{
            throw std::length_error("Access to an empty stack");
        }
    }

    // Specific member functions (inherited from Stack)
    template <typename Data>
    inline Data StackVec<Data>::TopNPop() { // Override Stack member (must throw std::length_error when empty)
        if (index!=0){
            Reduce();
            this->index--;
            return std::move(Elements[index]);
        }else{
            throw std::length_error("Access to an empty stack");
        }
    }

    template <typename Data>
    inline void StackVec<Data>::Push(const Data& data) {// Override Stack member (copy of the value)
        Expand();
        Elements[index] = data;
        index++;
    }

    template <typename Data>
    inline void StackVec<Data>::Push(Data&& data) { // Override Stack member (move of the value)
        Expand();
        Elements[index] = std::move(data);
        index++;
    }

    // Specific member functions (inherited from Container)
    template <typename Data>
    inline bool StackVec<Data>::Empty() const noexcept { // Override Container member
        return (this->index == 0);
    }

    template <typename Data>
    inline ulong StackVec<Data>::Size() const noexcept { // Override Container member
        return this->index;
    }

    // Specific member function (inherited from ClearableContainer)
    template <typename Data>
    void StackVec<Data>::Clear() { // Override ClearableContainer member
        this->index=0;
        Vector<Data>::Resize(1);
    }
}