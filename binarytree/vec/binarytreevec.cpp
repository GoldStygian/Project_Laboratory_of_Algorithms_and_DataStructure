#include "binarytreevec.hpp"

namespace lasd {

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& data, ulong pos, Vector<struct BinaryTreeVec<Data>::NodeVec*>* ptrVec){
        this->element = data;
        this->pos = pos;
        this->ptrVec = ptrVec;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& data, ulong pos, Vector<struct BinaryTreeVec<Data>::NodeVec*>* ptrVec){
        std::swap(data, this->element);
        std::swap(pos, this->pos);
        std::swap(ptrVec, this->ptrVec);
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::~NodeVec(){

        ptrVec->operator[](this->pos) = nullptr; // setto il puntatore di indice pos a nullptr

        if (this->HasLeftChild()) delete &LeftChild();
        if (this->HasRightChild()) delete &RightChild();

        this->ptrVec = nullptr; // per non chiamare il distruttore del vec
    }   

    template <typename Data>
    Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept{
        return element;
    }

    template <typename Data>
    const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept{
        return element;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
        
        ulong indice = pos*2+1;
        if ( (indice) < ptrVec->Size() ){
            if (ptrVec->operator[](indice) == nullptr) return false;
            return true;
        } 

        return false;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
        
        ulong indice = pos*2+2;
        if ( (indice) < ptrVec->Size() ){
            if (ptrVec->operator[](indice) == nullptr) return false;
            return true;
        } 

        return false;
    }

    template <typename Data>
    const BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
        ulong indice = pos*2+1;
        if(indice>=ptrVec->Size() ) throw std::out_of_range("Node has no left child");
        return *ptrVec->operator[](indice);
    }

    template <typename Data>
    const BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const{
        ulong indice = pos*2+2;
        if(indice>=ptrVec->Size() ) throw std::out_of_range("Node has no right child");
        return *ptrVec->operator[](indice);
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild(){
        ulong indice = pos*2+1;
        if(indice>=ptrVec->Size() ) throw std::out_of_range("Node has no left child");
        return *ptrVec->operator[](indice);
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild(){
        ulong indice = pos*2+2;
        if(indice>=ptrVec->Size() ) throw std::out_of_range("Node has no right child");
        return *ptrVec->operator[](indice);
    }

    // Specific constructors
    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& container){
        this->vec.Resize(container.Size());
        ulong count = 0;
        container.Traverse(
            [this, &count](const Data& data){
                vec[count] = new NodeVec(data, count, &vec);
                count++;
                this->size++;
            }
        );
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data>&& container){
        vec.Resize(container.Size());
        ulong count = 0;
        container.Map(
            [this, &count](Data& data){
                vec[count] = new NodeVec(data, count, &vec); //
                count++;
                this->size++;
            }
        );
    }

    // Copy constructor
    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec& tree){
        vec.Resize(tree.vec.Size());
        ulong count = 0;
        tree.vec.Traverse(
            [this, &count](const BinaryTreeVec<Data>::NodeVec* data){
                vec[count] = new NodeVec(data->Element(), count, &vec);
                count++;
                this->size++;
            }
        );
    }

    // Move constructor
    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& tree){
        std::swap(vec, tree.vec);
        std::swap(size, tree.size);

        tree.vec.Traverse(
            [this, &tree](BinaryTreeVec<Data>::NodeVec* ptrNode){
                ptrNode->ptrVec = &(tree.vec);
            }
        );

        vec.Traverse(
            [this](BinaryTreeVec<Data>::NodeVec* ptrNode){
                ptrNode->ptrVec = &(this->vec);
            }
        );

    }

    // Destructor
    template <typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec(){
        if (vec.Size() > 0){
            delete vec[0];
        }
    }

    // Copy assignment
    template <typename Data>
    typename BinaryTreeVec<Data>::BinaryTreeVec& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& tree){
        BinaryTreeVec<Data>* tmp = new BinaryTreeVec<Data>(tree);
        std::swap(*tmp, *this);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    typename BinaryTreeVec<Data>::BinaryTreeVec& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& tree){
        std::swap(vec, tree.vec);
        std::swap(size, tree.size);
        
        tree.vec.Traverse(
            [this, &tree](BinaryTreeVec<Data>::NodeVec* ptrNode){
                ptrNode->ptrVec = &(tree.vec);
            }
        );

        vec.Traverse(
            [this](BinaryTreeVec<Data>::NodeVec* ptrNode){
                ptrNode->ptrVec = &(this->vec);
            }
        );

        return *this;
    }

    // Comparison operators
    template <typename Data>
    inline bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec& tree) const noexcept{
        return *this == tree;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec& tree) const noexcept{
        return *this != tree;
    }

    // Specific member functions (inherited from BinaryTree)
    template <typename Data>
    const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
        if ( size == 0 ) throw std::length_error("Access to an empty tree");
        return *vec[0];
    }

    // Specific member function (inherited from MutableBinaryTree)
    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root(){
        if ( size == 0 ) throw std::length_error("Access to an empty tree");
        return *vec[0];
    }

    // Specific member function (inherited from ClearableContainer)
    template <typename Data>
    void BinaryTreeVec<Data>::Clear(){
        // void Vector<Data>::Clear(){
        //     delete[] Elements;
        //     Elements = nullptr;
        //     this->size = 0;
        // }
        if (vec.Size() > 0){
            delete vec[0]; // elimina i nodi //vec[0] puntatore alla radice
            vec.Clear();
            size = 0;
        }
    }
    
    // Specific member function (inherited from BreadthTraversableContainer)
    template <typename Data>
    void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const{
        if (vec.Size() > 0) BreadthTraverse(fun, *vec[0]);
    }

    template <typename Data>
    void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun, NodeVec& node) const{
        
        if(!node.IsLeaf()){
            QueueVec<NodeVec*> queue;
            queue.Enqueue(&node);

            while(!queue.Empty()){
                NodeVec* current = queue.HeadNDequeue();
                if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
                if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
                fun(current->Element());
            }

        }else{
            fun(node.Element());
        }

    }

    // // Specific member function (inherited from BreadthMappableContainer
    template <typename Data>
    void BinaryTreeVec<Data>::BreadthMap(MapFun fun){
        if (vec.Size() > 0) BreadthMap(fun, *vec[0]);
    }

    template <typename Data>
    void BinaryTreeVec<Data>::BreadthMap(MapFun fun, NodeVec& node){
        
        if(!node.IsLeaf()){
            QueueVec<NodeVec*> queue;
            queue.Enqueue(&node);

            while(!queue.Empty()){
                NodeVec* current = queue.HeadNDequeue();
                if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
                if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
                fun(current->Element());
            }

        }else{
            fun(node.Element());
        }

    }



}