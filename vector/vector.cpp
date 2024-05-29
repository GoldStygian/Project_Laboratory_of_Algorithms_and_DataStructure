#include "vector.hpp"

namespace lasd {

    /* Vector */

    // Specific constructors 
    template <typename Data>
    Vector<Data>::Vector(const ulong newSize){
        size = newSize;
        Elements = new Data[size] {}; //{} inizzializza il vettore al valore di default di Data
    }

    template <typename Data>
    Vector<Data>::Vector(const TraversableContainer<Data>& container): Vector(container.Size()){
        ulong index {0};
        container.Traverse(
            [this, &index](const Data& data){ //this per Elements
                Elements[index++] = data;
            }
        );
        //Traverse funzione che scorre tutta l astruttura dati
        //accetta come parametro una funzione che fa qualcosa di specifico per un solo elemento della struttura
    }

    template <typename Data>
    Vector<Data>::Vector(MappableContainer<Data>&& container): Vector(container.Size()){
        ulong index {0};
        container.Map(
            [this, &index](Data& data){ //this per Elements
                // Elements[index++] = std::move(data);
                std::swap(Elements[index++], data);
            }
        );
    }

    // Copy Constructor
    template <typename Data>
    Vector<Data>::Vector(const Vector& VectorToCopy){
        size = VectorToCopy.size;
        Elements = new Data[size] {};
        std::copy(VectorToCopy.Elements, VectorToCopy.Elements + size, Elements);
    }

    // Move Constructor
    template <typename Data>
    Vector<Data>::Vector(Vector&& VectorToMove){
        std::swap(size, VectorToMove.size);
        std::swap(Elements, VectorToMove.Elements);
    }

    // Destructor
    template <typename Data>
    Vector<Data>::~Vector(){ //devo liberare la memoria dinamica
        delete[] Elements;
    }

    // Copy assignment
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vec){
        Vector<Data>* tempVector = new Vector<Data>(vec);
        std::swap(*tempVector, *this);
        delete tempVector;
        return *this;
    }

    // Move assignment
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vec){
        std::swap(this->size, vec.size);
        std::swap(this->Elements, vec.Elements);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool Vector<Data>::operator==(const Vector& vector) const noexcept{
        if (this->size == vector.size){
            for(ulong i = 0; i<this->size; i++){
                if (this->Elements[i] != vector.Elements[i]){
                    return false;
                }
            }
        }else{
            return false;
        }

        return true;
    }

    template <typename Data>
    bool Vector<Data>::operator!=(const Vector& vector) const noexcept{
        return !(*this == vector);
    }

    // Specific member function
    template <typename Data>
    void Vector<Data>::Clear(){
        delete[] Elements;
        Elements = nullptr;
        this->size = 0;
    }

    template <typename Data>
    void Vector<Data>::Resize(const ulong newSize){

        if (newSize == 0 ) Clear();
        else if (this->size != newSize){
            Data * tempElements = new Data[newSize] {};

            ulong minSize; //newSize può essere > o < di size
            if (size < newSize) minSize = size; //sto allungado Data[]
            else minSize = newSize; //sto restringendo Data[]

            for(ulong i = 0; i<minSize; i++){
                std::swap(tempElements[i], Elements[i]);
            }

            std::swap(Elements, tempElements);
            size = newSize;
            delete[] tempElements;

        }
    }

    template <typename Data>
    const Data& Vector<Data>::operator[](const ulong index) const{
        if(index < this->size){
            return Elements[index];
        }else{
            throw std::out_of_range("Access at index "+ std::to_string(index) +" but vector size is " + std::to_string(this->size));
        }
    }

    template <typename Data>
    Data& Vector<Data>::operator[](const ulong index){
        if(index < this->size){
            return Elements[index];
        }else{
            throw std::out_of_range("Access at index "+ std::to_string(index) +" but vector size is " + std::to_string(this->size));
        }
    }

    template <typename Data>
    const Data& Vector<Data>::Front() const{
        if(this->size == 0) throw std::length_error("Access to an empty vector");
        
        return Elements[0];
    }

    template <typename Data>
    Data& Vector<Data>::Front(){
        if(this->size == 0) throw std::length_error("Access to an empty vector");
        
        return Elements[0];
    }

    template <typename Data>
    const Data& Vector<Data>::Back() const{
        if(this->size == 0) throw std::length_error("Access to an empty vector");
        
        return Elements[this->size - 1];
    }

    template <typename Data>
    Data& Vector<Data>::Back(){
        if(this->size != 0){
            return Elements[this->size - 1];
        }else{
            throw std::length_error("Access to an empty vector");
        }
    }

    /* SortableVector */

    // Specific constructors
    template <typename Data>
    SortableVector<Data>::SortableVector(const ulong initSize): Vector<Data>(initSize){}

    template <typename Data>
    SortableVector<Data>::SortableVector(const TraversableContainer<Data>& container): Vector<Data>(container){}

    template <typename Data>
    SortableVector<Data>::SortableVector(MappableContainer<Data>&& container): Vector<Data>(std::move(container)){}

    template <typename Data>
    SortableVector<Data>::SortableVector(const SortableVector& SVector): Vector<Data>(SVector) {}

    template <typename Data>
    SortableVector<Data>::SortableVector(SortableVector&& SVector): Vector<Data>(std::move(SVector)) {}

    // Copy assignment
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(const SortableVector<Data>& vec){
        Vector<Data>::operator=(vec);
        return *this;
    }

     // Move assignment
    template <typename Data>
    SortableVector<Data>& SortableVector<Data>::operator=(SortableVector<Data>&& vec){
        Vector<Data>::operator=(std::move(vec));
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool SortableVector<Data>::operator==(const SortableVector& Svec) const noexcept{
        return Vector<Data>::operator==(Svec);
    }

    template <typename Data>
    bool SortableVector<Data>::operator!=(const SortableVector& vector) const noexcept{
        return !(*this == vector);
    }

}