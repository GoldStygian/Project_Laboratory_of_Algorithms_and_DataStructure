#include "bst.hpp"

namespace lasd {

    // Specific constructors
    template <typename Data>
    BST<Data>::BST(const TraversableContainer<Data>& container){
        container.Traverse(
            [this](const Data &data){
                Insert(data);
            }
        );
    }

    template <typename Data>
    BST<Data>::BST(MappableContainer<Data>&& container){ // A bst obtained from a MappableContainer
        container.Map(
            [this](Data& data){
                Insert(std::move(data));
            }
        );
    }

    // Copy constructor
    template <typename Data>
    BST<Data>::BST(const BST& tree){
        if(tree.size > 0){
            tree.BreadthTraverse(
                [this](const Data& data){
                    Insert(data);
                }
            );
        }
    }

    // Move constructor
    template <typename Data>
    BST<Data>::BST(BST&& tree){
        std::swap(size, tree.size);
        std::swap(root, tree.root);
    }

    // Destructor
    template <typename Data>
    BST<Data>::~BST(){
        delete root;
        root = nullptr;
    }

    // Copy assignment
    template <typename Data>
    BST<Data>& BST<Data>::operator=(const BST& tree){
        //devo eliminare la copia attuale
        BST<Data>* tmp = new BST<Data>(tree);
        std::swap(*tmp, *this);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BST<Data>& BST<Data>::operator=(BST&& tree){
        std::swap(size, tree.size);
        std::swap(root, tree.root);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BST<Data>::operator==(const BST& tree) const noexcept{
        // if( Size() == tree.Size() && Size() > 0 ){
        //     BTPreOrderIterator<Data> ItrCmp(tree);
        //     BTPreOrderIterator<Data> ItrThis(*this);

        //     while (!ItrThis.Terminated()){
        //         if ( *ItrThis != *ItrCmp) return false;
        //         ++ItrThis;
        //         ++ItrCmp;
        //     }
        // }
        // return false;

        if (Size() != tree.Size()) return false;

        if (Size() > 0){
            BTPreOrderIterator<Data> Itr(tree);
            while (!Itr.Terminated()){
                if (Exists(*Itr) == false) return false;
                ++Itr;
            }
        }

        return true;


    }

    template <typename Data>
    bool BST<Data>::operator!=(const BST& tree) const noexcept{
        return !(*this == tree);
    }

    // Specific member functions
    template <typename Data>
    Data& BST<Data>::Min(){ // (concrete function must throw std::length_error when empty)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        return FindPointerToMin(this->root)->Element();
    }

    template <typename Data>
    Data BST<Data>::MinNRemove(){ // (concrete function must throw std::length_error when empty)
        if (this->Empty()) throw std::length_error("Access to an empty bst");

        typename BinaryTreeLnk<Data>::NodeLnk* MinToDel = FindPointerToMin(root);// DetachMin(nullptr, this->root);
        Data minData = MinToDel->Element();
        // delete MinToDel;
        // --size;
        Remove(minData);
        // if ( Size() == 0 ) root = nullptr;
        return minData;

    }

    template <typename Data>
    void BST<Data>::RemoveMin(){ // (concrete function must throw std::length_error when empty)
        if (this->Empty()) throw std::length_error("Access to an empty bst");

        typename BinaryTreeLnk<Data>::NodeLnk* MinToDel = FindPointerToMin(root);
        Remove(MinToDel->Element());
        // if (Size() == 0) root = nullptr;
    }

    template <typename Data>
    Data& BST<Data>::Max(){ // (concrete function must throw std::length_error when empty)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        return FindPointerToMax((this->root))->Element();
    }

    template <typename Data>
    Data BST<Data>::MaxNRemove(){ // (concrete function must throw std::length_error when empty)
        if (this->Empty()) throw std::length_error("Access to an empty bst");

        typename BinaryTreeLnk<Data>::NodeLnk* maxToDel = FindPointerToMax(root);//DetachMax(nullptr, this->root);
        Data maxData = maxToDel->Element(); std::cout<<" I find value: "<<maxData<<"! ";
        Remove(maxData);
        // if (Size() == 0) root = nullptr;
        return maxData;
    }

    template <typename Data>
    void BST<Data>::RemoveMax(){ // (concrete function must throw std::length_error when empty)
        if (this->Empty()) throw std::length_error("Access to an empty bst");

        typename BinaryTreeLnk<Data>::NodeLnk* maxToDel = FindPointerToMax(root);
        // delete maxToDel;
        // --size;
        Remove(maxToDel->Element());
        // if (Size() == 0) root = nullptr;
    }

    template <typename Data>
    Data& BST<Data>::Predecessor(const Data& data) const{ // (concrete function must throw std::length_error when not found)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        typename BinaryTreeLnk<Data>::NodeLnk* p =  FindPointerToPredecessor(this->root, data, nullptr);
        if ( p == nullptr ) throw std::length_error("Predecessor not found");
        return p->Element();
    }

    template <typename Data>
    Data BST<Data>::PredecessorNRemove(const Data& data){ // (concrete function must throw std::length_error when not found)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        typename BinaryTreeLnk<Data>::NodeLnk* p =  FindPointerToPredecessor(this->root, data, nullptr);
        if ( p == nullptr ) throw std::length_error("Predecessor not found");
        Data dataReturn = p->Element(); 
        Remove(dataReturn);
        if (Size() == 0) root = nullptr;
        return dataReturn; 

    }

    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data& data){ // (concrete function must throw std::length_error when not found)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        typename BinaryTreeLnk<Data>::NodeLnk* p =  FindPointerToPredecessor(this->root, data, nullptr);
        if ( p == nullptr ) throw std::length_error("Predecessor not found");
        Remove(p->Element());
        if (Size() == 0) root = nullptr;
    }

    template <typename Data>
    Data& BST<Data>::Successor(const Data& data) const{ // (concrete function must throw std::length_error when not found)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        typename BinaryTreeLnk<Data>::NodeLnk* s = FindPointerToSuccessor(this->root, data, nullptr);
        if ( s == nullptr ) throw std::length_error("Successor not found");
        return s->Element();
    }

    template <typename Data>
    Data BST<Data>::SuccessorNRemove(const Data& data){ // (concrete function must throw std::length_error when not found)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        typename BinaryTreeLnk<Data>::NodeLnk* s =  FindPointerToSuccessor(this->root, data, nullptr);
        if ( s == nullptr ) throw std::length_error("Successor not found");
        Data dataReturn = s->Element();
        Remove(dataReturn);
        return dataReturn; 
    }

    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data& data){ // (concrete function must throw std::length_error when not found)
        if (this->Empty()) throw std::length_error("Access to an empty bst");
        typename BinaryTreeLnk<Data>::NodeLnk* s =  FindPointerToSuccessor(this->root, data, nullptr);
        if ( s == nullptr ) throw std::length_error("Successor not found");
        Remove(s->Element());
    }

    // Specific member function (inherited from BinaryTree)
    template <typename Data>
    const typename BinaryTreeLnk<Data>::NodeLnk& BST<Data>::Root() const{ // Override BinaryTree member
        if(root == nullptr) throw std::length_error("Access to an empty tree");
        return *root;
    }

    // Specific member functions (inherited from DictionaryContainer)
    template <typename Data>
    bool BST<Data>::Insert(const Data& data){ // Override DictionaryContainer member (Copy of the value)

        typename BinaryTreeLnk<Data>::NodeLnk* nodeIns = new typename BinaryTreeLnk<Data>::NodeLnk(data);

        // std::cout<<"set "<<data<<" as root\n";
        if (this->Empty()) {
            root = nodeIns;
        }else{
            
            typename BinaryTreeLnk<Data>::NodeLnk* current = root;
            typename BinaryTreeLnk<Data>::NodeLnk* parent = nullptr;

            while(current != nullptr){
                parent = current;
                if (current->Element() > data) current = current->Sx;
                else if (current->Element() < data) current = current->Dx;
                else { // sto inserendo un duplicato
                    delete nodeIns;
                    return false;
                }
            }

            // std::cout<<"set "<<data<<" as ";
            if (parent->Element() > data) {
                parent->Sx = nodeIns;
                //  std::cout<<"left child";
            } else {
                parent->Dx = nodeIns;
                //  std::cout<<"righ child";
            }
            //  std::cout<<"of "<<parent->Element()<<"\n";
    
        }

        ++size;
        return true;

    }

    template <typename Data>
    bool BST<Data>::Insert(Data&& data){ // Override DictionaryContainer member (Move of the value)
    
        typename BinaryTreeLnk<Data>::NodeLnk* nodeIns = new typename BinaryTreeLnk<Data>::NodeLnk(std::move(data));

        if (this->Empty()) {
            root = nodeIns;
        }else{
            
            typename BinaryTreeLnk<Data>::NodeLnk* current = root;
            typename BinaryTreeLnk<Data>::NodeLnk* parent = nullptr;

            while(current != nullptr){
                parent = current;
                if (current->Element() > data) current = current->Sx;
                else if (current->Element() < data) current = current->Dx;
                else { // sto inserendo un duplicato
                    delete nodeIns;
                    return false;
                }
            }

            if (parent->Element() > data) {
                parent->Sx = nodeIns;
            } else {
                parent->Dx = nodeIns;
            }
    
        }

        this->size++;
        return true;

    }

    template <typename Data>
    bool BST<Data>::Remove(const Data& data){ // Override DictionaryContainer member
        
        if( Size() == 0 ) return false;
        
        ulong oldSize = Size();
        // if(root==nullptr) std::cout<<" root vuota ";
        // else std::cout<<" value root: "<<root->Element();
        root = RemoveHelper(root, data);
        
        if(oldSize == Size()) return false;
        else {
            if (Size() == 0) root = nullptr;
            return true;
        }

    }

    template <typename Data>
    bool BST<Data>::Exists(const Data& data) const noexcept{ // Override TestableContainer member

        // std::cout<<"[BST exist] data  = "<<data<<" ";
        if( root != nullptr ){
            typename BinaryTreeLnk<Data>::NodeLnk* current = root;
            // std::cout<<"current: "<<current->Element()<<" ";
            while ( current != nullptr ) {

                if( current->Element() > data ) current = current->Sx;
                else if (current->Element() < data ) current = current->Dx;
                else {/*std::cout<<"FIND!\n"; */return true;}// ho trovato il dato

            }
        
        }
        // std::cout<<"not find\n";
        return false;

    }

    // Specific member function (inherited from ClearableContainer)
    template <typename Data>
    void BST<Data>::Clear(){ // Override ClearableContainer member
        delete root;
        root = nullptr;
        size = 0;
    }

    /* AUX Function */
    template <typename Data>
    Data BST<Data>::DataNDelete(typename BinaryTreeLnk<Data>::NodeLnk * node){
        Data data = node->Element();
        node->Sx = nullptr;
        node->Dx = nullptr;
        delete node;
        return data;
    }
    
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::DeleteNode(typename BinaryTreeLnk<Data>::NodeLnk* node){
        
        typename BinaryTreeLnk<Data>::NodeLnk * minNode = nullptr;
        //std::cout<<"Arrived in deleteNode\n";
        if(node->HasRightChild() && node->HasLeftChild()){ // se ha entrambi i figli allora devo prendere il piu piccolo del sotto-albero dx
            //std::cout<<"before call DetachMin\n";
            minNode = DetachMin(&(node->RightChild()), node);
            // if (minNode == nullptr ) std::cout <<"min vuoto\n";
            // std::cout<<"DetachMin after return: "<<minNode->Element()<<"\n";
            node->element = DataNDelete(minNode);
    
        }else if(node->HasRightChild()){
            //std::cout<<"not left\n";
            node = Skip2RightDel(node);

        }else if(node->HasLeftChild()){
            //std::cout<<"not\n";
            node = Skip2LeftDel(node);

        }else{
            delete node;
            node = nullptr;
        }

        return node;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::RemoveHelper(typename BinaryTreeLnk<Data>::NodeLnk* node, const Data& data){
        
        if(node == nullptr) std::cout<<" is Null ";
        else std::cout<<" value node: "<<node->Element();
        if (node != nullptr){
            if(node->Element() > data){
                std::cout<<"Sx ";
                node->Sx = RemoveHelper(node->Sx, data);//if(node->HasLeftChild()) node->Sx = RemoveHelper(node->Sx, data);
            }else if (node->Element() < data){
                std::cout<<"Dx";
                node->Dx = RemoveHelper(node->Dx, data);//if(node->HasRightChild()) node->Dx = RemoveHelper(node->Dx, data);
            }else{ // data == Element() ho trovato il dato
                node = DeleteNode(node);
                std::cout<<" FIND! ";
                --size;
            }
        }

        return node;

    }
    
    /* Function AUX Skip2LeftDel(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2LeftDel(typename BinaryTreeLnk<Data>::NodeLnk* node){
        typename BinaryTreeLnk<Data>::NodeLnk* nodeReturn = &node->LeftChild();
        node->Sx = nullptr;
        delete node;
        return nodeReturn;
    }

    /* Function AUX Skip2RightDel(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2RightDel(typename BinaryTreeLnk<Data>::NodeLnk* node){
        typename BinaryTreeLnk<Data>::NodeLnk* nodeReturn = &node->RightChild();
        node->Dx = nullptr;
        delete node;
        return nodeReturn;
    }

    /* Function AUX Skip2Right(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2Right(typename BinaryTreeLnk<Data>::NodeLnk* node){
        typename BinaryTreeLnk<Data>::NodeLnk* nodeReturn = &node->RightChild();
        node->Dx = nullptr;
        return nodeReturn;
    }

    /* Function AUX Skip2Left(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2Left(typename BinaryTreeLnk<Data>::NodeLnk* node){
        typename BinaryTreeLnk<Data>::NodeLnk* nodeReturn = &node->LeftChild();
        node->Sx = nullptr;
        return nodeReturn;
    }

    /* Function AUX FindPointerMin(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk* node) const {
        
        if (!(node->HasLeftChild())) return node;
        else return FindPointerToMin( &(node->LeftChild()) );

    }

    /* Function AUX FindPointerMax(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk* node) const {
        
        if (!(node->HasRightChild())) return node;
        else return FindPointerToMax( &(node->RightChild()) );

    }

    /* Function AUX DetachMin(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMin(typename BinaryTreeLnk<Data>::NodeLnk * node, typename BinaryTreeLnk<Data>::NodeLnk * parent) {
        
        // std::cout <<"\n";
        // if (parent != nullptr) { std::cout << "parent = "<<parent->Element()<<"\n";}
        // else {std::cout << "parent = null\n";}
        // if (node != nullptr) { std::cout << "node = "<<node->Element()<<"\n";}
        // else {std::cout << "node = null\n";}

        if (node != nullptr && node->HasLeftChild()) {
            return DetachMin(&node->LeftChild(), node);
        }

        typename BinaryTreeLnk<Data>::NodeLnk * rightChild = (node != nullptr && node->HasRightChild()) ? &node->RightChild() : nullptr;
        
        if (parent == nullptr) {
            // std::cout <<"0\n";
            this->root = rightChild;
        } else if (parent->HasRightChild() && parent->RightChild().Element() == node->Element()) {
            // std::cout <<"1\n";
            parent->Dx = rightChild;
        } else {
            // std::cout <<"2\n";
            parent->Sx = rightChild;
        }
        // std::cout <<"OK\n";
        return node;
    }

    /* Function AUX DetachMax(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMax(typename BinaryTreeLnk<Data>::NodeLnk * node, typename BinaryTreeLnk<Data>::NodeLnk * parent) {
        if (node->HasRightChild()) {
            return DetachMax(&node->RightChild(), node);
        }

        typename BinaryTreeLnk<Data>::NodeLnk * leftChild = node->HasLeftChild() ? &node->LeftChild() : nullptr;

        if (parent == nullptr) {
            this->root = leftChild;
        } else if (parent->HasLeftChild() && parent->LeftChild().Element() == node->Element()) {
            parent->Sx = leftChild;
        } else {
            parent->Dx = leftChild;
        }

        return node;
    }

    /* Function AUX FindPointerToPredecessor(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::FindPointerToPredecessor(typename BinaryTreeLnk<Data>::NodeLnk* node, const Data& data, typename BinaryTreeLnk<Data>::NodeLnk* p) const{
        
        // if (!(node->IsLeaf())){
        //     if (node->Element() < data){
        //         if(node->HasRightChild()) return FindPointerToPredecessor(&(node->RightChild()), data, node);
        //     }
        //     else{
        //         if(node->HasLeftChild()) return FindPointerToPredecessor(&(node->LeftChild()), data, p);
        //     }
        // }else{
        //     if(data > node->Element()) p =  node;  
        // }

        // return p;

        if ( node != nullptr ){ // se passo un nullptr come root allora ritorna nullptr
            if (node->Element() < data){
                return FindPointerToPredecessor(node->Dx, data, node);
            }
            else{
                return FindPointerToPredecessor(node->Sx, data, p);
            }
        }
        // else{
        //     if(data > node->Element()) p =  node;  
        // }

        return p;

    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::FindPointerToPredecessor(typename BinaryTreeLnk<Data>::NodeLnk* node, const Data& data, typename BinaryTreeLnk<Data>::NodeLnk* p){
        
        // if (!(node->IsLeaf())){
        //     if (node->Element() < data){
        //         if(node->HasRightChild()) return FindPointerToPredecessor(&(node->RightChild()), data, node);
        //     }
        //     else{
        //         if(node->HasLeftChild()) return FindPointerToPredecessor(&(node->LeftChild()), data, p);
        //     }
        // }else{
        //     if(data > node->Element()) p =  node;  
        // }

        // return p;

        if ( node != nullptr ){ // se passo un nullptr come root allora ritorna nullptr
            if (node->Element() < data){
                return FindPointerToPredecessor(node->Dx, data, node);
            }
            else{
                return FindPointerToPredecessor(node->Sx, data, p);
            }
        }
        // else{
        //     if(data > node->Element()) p =  node;  
        // }

        return p;

    }

    /* Function AUX FindPointerToSuccessor(...) */
    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::FindPointerToSuccessor(typename BinaryTreeLnk<Data>::NodeLnk* node, const Data& data, typename BinaryTreeLnk<Data>::NodeLnk* s) const{
        
        if ( node != nullptr ){
            if (node->Element() > data) {
                return FindPointerToSuccessor(node->Sx, data, node);
            }else {   
                return FindPointerToSuccessor(node->Dx, data, s);
            }
        }

        return s;

    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::FindPointerToSuccessor(typename BinaryTreeLnk<Data>::NodeLnk* node, const Data& data, typename BinaryTreeLnk<Data>::NodeLnk* s){
        
        // if (!(node->IsLeaf())){
        //     if (node->Element() > data) {
        //         if(node->HasLeftChild()) return FindPointerToSuccessor(&(node->LeftChild()), data, node);
        //     }else {   
        //         if(node->HasRightChild()) return FindPointerToSuccessor(&(node->RightChild()), data, s);
        //     }
        // }else{
        //     if(data < node->Element()) s =  node;  
        // }

        // return s;
        if ( node != nullptr ){
            if (node->Element() > data) {
                return FindPointerToSuccessor(node->Sx, data, node);
            }else {   
                return FindPointerToSuccessor(node->Dx, data, s);
            }
        }

        return s;

    }

}
