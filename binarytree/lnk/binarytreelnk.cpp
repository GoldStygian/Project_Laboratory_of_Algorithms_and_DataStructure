#include "binarytreelnk.hpp"
#include <stdexcept>

namespace lasd {

    /*--------------*/
    /*struct NodeLnk*/
    /*--------------*/

    // template <typename Data>
    // using Node = typename BinaryTree<Data>::Node;

    // template <typename Data>
    // using MutableNode = typename MutableBinaryTree<Data>::MutableNode;


    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& data){
        element = data;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& data){
        std::swap(element, data);
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
        delete Sx;
        delete Dx;
    }

    // Specific member functions
    template <typename Data>
    Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept{
        return element;
    }
    
    template <typename Data>
    const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept{
        return element;
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{
        return (this->Sx != nullptr);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
        return (this->Dx != nullptr);
    }

    template <typename Data>
    //const typename BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
        if (Sx == nullptr) throw std::out_of_range("Left child does not exists");
        return *Sx;
    }

    template <typename Data>
    // const typename BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    const typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
        if (Dx == nullptr) throw std::out_of_range("Right child does not exists");
        return *Dx;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() {
        if (Sx == nullptr) throw std::out_of_range("Left child does not exists");
        return *Sx;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild(){
        if (Dx == nullptr) throw std::out_of_range("Right child does not exists");
        return *Dx;
    }

    /*-------------*/
    /*BinaryTreeLnk*/
    /*-------------*/

    // Specific constructors
    template <typename Data>
    void BinaryTreeLnk<Data>::insert(const Data& data){
        
        NodeLnk* node = new NodeLnk(data);

        if (this->root == nullptr) root = node;
        else{
            QueueVec<NodeLnk*> queue;
            queue.Enqueue(this->root); // NOTA: chiamare metodo

            while(!queue.Empty()){
                NodeLnk* current = queue.HeadNDequeue();
                if (current->HasLeftChild()) queue.Enqueue( &(current->LeftChild()) );
                else { current->Sx = node; ++size; return; }

                if (current->HasRightChild()) queue.Enqueue( &(current->RightChild()) ); //return mutable node
                else { current->Dx = node; ++size; return; }
            }
        }
        
        ++size;

    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data>& conatiner){
        conatiner.Traverse(
            [this](const Data& data){
                insert(data);
            }
        );
    }

    template <typename Data>
    void BinaryTreeLnk<Data>::insert(Data&& data){
        
        NodeLnk* node = new NodeLnk(std::move(data));

        if (this->root == nullptr) root = node;
        else{
            QueueVec<struct NodeLnk*> queue;
            queue.Enqueue(this->root);

            while(!queue.Empty()){
                struct NodeLnk* current = queue.HeadNDequeue();
                if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
                else { current->Sx = node; ++size; return; }

                if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
                else { current->Dx = node; ++size; return; }

            }
        }

        ++size;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data>&& container){
        container.Map(
            [this](Data& data){
                this->insert(std::move(data));
            }
        );
    }

    // Copy constructor
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::copyTree(const NodeLnk* node) {

        struct NodeLnk* nodo = nullptr;

        if(node!=nullptr){
            nodo = new NodeLnk(node->element);

            if(node->Sx!=nullptr)
                nodo->Sx = copyTree(node->Sx);

            if(node->Dx!=nullptr)
                nodo->Dx = copyTree(node->Dx);
        }

        return nodo;

    }
    // template<typename Data>
    // void BinaryTreeLnk<Data>::copyTree2(const BinaryTreeLnk & btl){
    //     btl.BreadthTraverse(
    //         [this](const Data & dat) {
    //             insert(dat);
    //         }
    //     );

    // }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& tree){
        size = tree.size;
        
        if(size > 0) {
            root = copyTree(tree.root);
        }
        // if(tree.size > 0){
        //     copyTree2(tree);
        // }
    }

    // Move constructor
    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& tree): BinaryTreeLnk<Data>(){
        std::swap(root, tree.root);
        std::swap(size, tree.size);
    }

    // Destructor
    template <typename Data>
    BinaryTreeLnk<Data>::~BinaryTreeLnk(){
        Clear();
    }

    // Copy assignment
    template <typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& tree){
        if (tree.size != 0 ){
            //devo elinimiare il vecchio contenuto di this
            BinaryTreeLnk<Data> *tmp = new BinaryTreeLnk<Data>(tree);
            std::swap(*this, *tmp);
            delete tmp;   
        }else{
            //se sto copiando un albero vuoto allora swoto questo attuale
            Clear();
        }

        return *this;
    }

    // Move assignment
    template <typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& tree){
        std::swap(root, tree.root);
        std::swap(size, tree.size);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    inline bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk& tree) const noexcept{
        return *this == tree;
    }

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk& tree) const noexcept{
        return *this != tree;
    }

    // Specific member functions (inherited from BinaryTree)
    template <typename Data>
    const typename BinaryTree<Data>::Node& BinaryTreeLnk<Data>::Root() const{
        if(root == nullptr) throw std::length_error("Access to an empty tree");
        return *root;
    }

    // Specific member function (inherited from MutableBinaryTree)
    template <typename Data>
    typename MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::Root(){
        if(root == nullptr) throw std::length_error("Access to an empty tree");
        return *root;
    }

    // Specific member function (inherited from ClearableContainer)
    template <typename Data>
    void BinaryTreeLnk<Data>::Clear(){
        delete root;
        root = nullptr;
        size = 0;
    }

}
