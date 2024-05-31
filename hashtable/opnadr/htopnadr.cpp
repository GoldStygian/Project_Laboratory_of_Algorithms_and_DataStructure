#include "htopnadr.hpp"

namespace lasd {

    template <typename Data>
    void HashTableOpnAdr<Data>::init_perm(){
        
        perm.Resize(M);

        //genero la permutazione
        for (ulong i {0}; i<M; ++i){
            perm[i] = i;

        }

        std::random_device rd;

        // Inizializzare il generatore Mersenne Twister con il seed del generatore hardware
        std::mt19937 gen(rd());

        for (ulong i {0}; i<M-1; ++i){
            std::uniform_int_distribution<> distribuzione(i+1, M-1);
            ulong rand = distribuzione(gen);
            
            std::swap(perm[i], perm[rand]);
        }
    }

    template <typename Data>
    ulong HashTableOpnAdr<Data>::Probing(const ulong index) const{

        if ( index == 0 ) throw std::runtime_error("Index 0 has request for probing sequnce");

        return perm[index-1];
    }

    // Auxiliary member functions
    template <typename Data>
    ulong HashTableOpnAdr<Data>::HashKey(const Data& key) const{
        Hashable<Data> funHash;
        return funHash(key);
    }

    // Auxiliary member functions
    template <typename Data>
    ulong HashTableOpnAdr<Data>::FindEmpty(const Data& data){
        
        ulong pos, home;
        home = pos = HashKey(data) % M;

        // std::cout<<"home of "<<data<<" is "<<home<<" ";

        for (ulong index {1}; index<M; ++index){
            
            if (hashTable[pos]==nullptr || hashTable[pos]->deleted){
                // std::cout<<"empty slot at: "<<pos<<"\n";
                // printf("\n");
                return pos;
            }
            // else{ //analizzo un slot non vuoto
            //     if(hashTable[pos]->element == data) {std::cout<<"gia inserito\n"; return M;}
            // }
            // }

            pos = (home + Probing(index)) % M;

            // std::cout<<"next pos to search: "<<pos<<" data in: ";
            // if (hashTable[pos]!=nullptr) std::cout<<hashTable[pos]->element<<"\n";
            // else std::cout<<"null\n";
        }

        return M;

    }

    // Auxiliary member functions
    template <typename Data>
    ulong HashTableOpnAdr<Data>::Find(const Data& data) const noexcept{
        
        ulong home = this->HashKey(data);
        ulong pos = home % M;

        for (ulong index {1}; hashTable[pos]!=nullptr; ++index){
            if( !(hashTable[pos]->deleted) && hashTable[pos]->element == data) return pos;

            pos = (home + Probing(index)) % M;

        }

        return M;
    }

    // Specific constructors
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size){

        if (size < MIN_SIZE) {this->hashTable.Resize(MIN_SIZE); M = MIN_SIZE;}
        else {this->hashTable.Resize(size); M = size;}
        init_perm();

    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data>& container): HashTableOpnAdr(container.Size()) {

        if (container.Size() > 0 ){
            container.Traverse(
                [this](const Data& data){
                    Insert(data);
                }
            );
        }

    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, const TraversableContainer<Data>& container): HashTableOpnAdr(newSize) {

        if (container.Size() > 0 ){
            container.Traverse(
                [this](const Data& data){
                    Insert(data);
                }
            );
        }

    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data>&& container): HashTableOpnAdr(container.Size()){

        if (container.Size() > 0 ){
            container.Map(
                [this](Data& data){
                    Insert(std::move(data));
                }
            );
        }

    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, MappableContainer<Data>&& container): HashTableOpnAdr(newSize){

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
    HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& ht){
        
        this->hashTable.Resize(ht.M);

        ulong index {0};
    
        ht.hashTable.Traverse(
            [this, &index](Slot* ptr){

                if(ptr == nullptr) hashTable[index] = nullptr;
                else hashTable[index] = new Slot(*ptr);

                ++index;
            }

        );

        this->M = ht.M;
        this->size = ht.size;
        perm = ht.perm;

    }

    // Move constructor
    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& ht){

        std::swap(this->hashTable, ht.hashTable);
        std::swap(this->M, ht.M);
        std::swap(this->size, ht.size);
        std::swap(this->perm, ht.perm);

    }

    // Destructor
    template <typename Data>
    HashTableOpnAdr<Data>::~HashTableOpnAdr(){
        Clear();
    }

    // Copy assignment
    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& ht){
        HashTableOpnAdr<Data>* temp = new HashTableOpnAdr<Data>(ht);
        std::swap(*this, *temp);
        delete temp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& ht){
        std::swap(this->hashTable, ht.hashTable);
        std::swap(this->M, ht.M);
        std::swap(this->size, ht.size);
        std::swap(this->perm, ht.perm);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& ht) const noexcept{

        if ( ht.size != this->size ) return false;

        bool flag = true;

        hashTable.Traverse(
            [&flag, &ht](const Slot* ptr){
                if (ptr != nullptr && !(ptr->deleted)){
                    if (!(ht.Exists(ptr->element))) {flag = false; return;}
                }
            }

        );

        return flag;

    }

    template <typename Data>
    inline bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& ht) const noexcept{

        return !(*this == ht);

    }
    
    // Specific member functions (inherited from DictionaryContainer)
    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(const Data& data){
        
        if (Exists(data)) return false;
        //99+1 == 100 // se ho un solo slot disponibile
        if (size+1 == M) Resize(M*RESIZE_FACTOR);
        
        ulong emptyIndex = FindEmpty(data);
        // if (emptyIndex == M) return false;

        if (hashTable[emptyIndex] == nullptr) hashTable[emptyIndex] = new Slot(data);
        else {hashTable[emptyIndex]->element = data; hashTable[emptyIndex]->deleted = false;} 

        ++size;

        return true;

    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(Data&& data){

        if (Exists(data)) return false;
        if (size+1 == M) Resize(M*RESIZE_FACTOR);
        

        ulong emptyIndex = FindEmpty(data);
        
        // if (emptyIndex == M) return false;

        if (hashTable[emptyIndex] == nullptr) hashTable[emptyIndex] = new Slot(std::move(data));
        else {std::swap (hashTable[emptyIndex]->element, data); hashTable[emptyIndex]->deleted = false;} 

        ++size;

        return true;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data& data){
        
        ulong index = Find(data);
        if (index != M) {

            hashTable[index]->deleted = true;

            --size;

            return true;
 
        }

        return false;

    }

    // Specific member functions (inherited from TestableContainer)
    template <typename Data>
    bool HashTableOpnAdr<Data>::Exists(const Data& data) const noexcept{

        if ( Find(data) == M ) return false;

        return true;
    }

    // Specific member functions (inherited from ResizableContainer)
    template <typename Data>
    void HashTableOpnAdr<Data>::Resize(const ulong newSize){
        
        if(newSize == 0) return Clear();

        HashTableOpnAdr<Data>* newHashTable = new HashTableOpnAdr<Data>(newSize);

        this->hashTable.Traverse(
            [&newHashTable](const Slot* ptr){
                if(ptr != nullptr && !(ptr->deleted)){
                    newHashTable->Insert(ptr->element);
                }
            }
        );

        std::swap(*this, *newHashTable);
        delete newHashTable;

    }

    // Specific member functions (inherited from ClearableContainer)
    template <typename Data>
    void  HashTableOpnAdr<Data>::Clear(){
        for(ulong i = 0; i < hashTable.Size(); ++i) {
            delete hashTable[i];
            hashTable[i] = nullptr;
        }

        hashTable.Resize(MIN_SIZE);
        M = MIN_SIZE;
        size=0;

        init_perm();
    }

}