#include "htclsadr.hpp"

namespace lasd {

    // Specific constructors
    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong size){
        
        if (size < MIN_SIZE) {this->hashTable.Resize(MIN_SIZE); M = MIN_SIZE;}
        else {this->hashTable.Resize(size); M = size;}

    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data>& container): HashTableClsAdr(container.Size()) {

        if (container.Size() > 0 ){
            container.Traverse(
                [this](const Data& data){
                    Insert(data);
                }
            );
        }

    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const TraversableContainer<Data>& container): HashTableClsAdr(newSize) {

        if (container.Size() > 0 ){
            container.Traverse(
                [this](const Data& data){
                    Insert(data);
                }
            );
        }

    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data>&& container): HashTableClsAdr(container.Size()){

        if (container.Size() > 0 ){
            container.Map(
                [this](Data& data){
                    Insert(std::move(data));
                }
            );
        }

    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MappableContainer<Data>&& container): HashTableClsAdr(newSize){
        
        if (container.Size() > 0 ){
            container.Map(
                [this](Data& data){
                    Insert(std::move(data));
                }
            );
        }

    }

    // Copy constructor
    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& ht){
        
        this->hashTable.Resize(ht.M);

        ulong index {0};

        ht.hashTable.Traverse(
            [this, &index](const BST<Data>* ptr){
                
                if(ptr == nullptr) hashTable[index] = nullptr;
                else hashTable[index] = new BST(*ptr);

                ++index;
            }

        );

        this->M = ht.M;
        this->size = ht.size;

    }

    // Move constructor
    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& ht){

        std::swap(this->hashTable, ht.hashTable);
        std::swap(this->M, ht.M);
        std::swap(this->size, ht.size);

    }

    // Destructor
    template <typename Data>
    HashTableClsAdr<Data>::~HashTableClsAdr(){

        Clear();

    }

    // Copy assignment
    template <typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& ht){
        HashTableClsAdr<Data>* temp = new HashTableClsAdr<Data>(ht);
        std::swap(*this, *temp);
        delete temp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& ht){
        std::swap(this->hashTable, ht.hashTable);
        std::swap(this->M, ht.M);
        std::swap(this->size, ht.size);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& ht) const noexcept{
        
        if (this->size != ht.size) return false;

        bool flag = true;
        this->hashTable.Traverse(
            [this, &ht, &flag](const BST<Data>* ptr){
                
                if (ptr != nullptr) { // devo cecare nell'altro albero il dato
                    ptr->Traverse(
                        [&ht, &flag](const Data& data){
                            if (!(ht.Exists(data))){
                                flag = false;
                                return;
                            }
                        }
                    );
                }
            }
        );
    
        return flag;

    }

    // Specific member functions (inherited from TestableContainer)
    template <typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data& data) const noexcept{

        ulong index = this->HashKey(data);

        if (hashTable[index]==nullptr) return false;
        else return (hashTable[index]->Exists(data)); // sto analizzando un BST

    }

    template <typename Data>
    inline bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& ht) const noexcept{
        return !(*this == ht);
    }

    // Specific member functions (inherited from DictionaryContainer)
    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data& data){
        
        if (Exists(data)) return false;
        // std::cout<<"\n[]not exit --> insert\n";
        ulong home = this->HashKey(data);

        if (hashTable[home]==nullptr) hashTable[home] = new BST<Data>();
        
        hashTable[home]->Insert(data); //BST*->Insert

        ++size;

        return true;

    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(Data&& data){

        if (Exists(data)) return false;

        ulong home = this->HashKey(data);

        if (hashTable[home]==nullptr) hashTable[home] = new BST<Data>();
        
        hashTable[home]->Insert(std::move(data)); //BST*->Insert

        ++size;

        return true;

    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data& data){

        ulong home = this->HashKey(data);

        if (hashTable[home]==nullptr) return false;
        // std::cout<<"BST["<<home<<"] size: "<<hashTable[home]->Size()<<" ----- ";
        if ( hashTable[home]->Remove(data)) {

            --size;
            // std::cout<<"BST["<<home<<"] size: "<<hashTable[home]->Size()<<"\n";
            if (hashTable[home]->Size() == 0) { delete hashTable[home]; hashTable[home] = nullptr; }
            return true;
        }
        else return false;
    }

    // Specific member functions (inherited from ResizableContainer)
    template <typename Data>
    void HashTableClsAdr<Data>::Resize(const ulong newSize){

        if(newSize == 0) return Clear();

        HashTableClsAdr<Data>* newHashTable = new HashTableClsAdr(newSize);

        this->hashTable.Traverse(
            [&newHashTable](const BST<Data>* ptr){
                if(ptr != nullptr){
                    ptr->Traverse([&newHashTable](const Data& data){newHashTable->Insert(data);});
                }
            }
        );

        std::swap(this->hashTable, newHashTable->hashTable);
        std::swap(this->M, newHashTable->M);
        delete newHashTable;

    }

    // Specific member functions (inherited from ClearableContainer)
    template <typename Data>
    void HashTableClsAdr<Data>::Clear(){

        for(ulong i = 0; i < hashTable.Size(); ++i) {
            delete hashTable[i];
            hashTable[i] = nullptr;
        }

        hashTable.Resize(MIN_SIZE);
        M = MIN_SIZE;
        size=0;
    }

}