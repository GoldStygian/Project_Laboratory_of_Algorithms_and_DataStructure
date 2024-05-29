#include <stdexcept>

namespace lasd {

    // NODE

    // Comparison operators (Node)
    template <typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node& compNode) const noexcept{ // OK
        
        if (compNode.Element() == this->Element()){ // se hanno lo stesso dato verifico i figli

            bool hasDX = this->HasRightChild(); // figli del nodo
            bool hasSX = this->HasLeftChild(); 

            bool cmpDX = compNode.HasRightChild(); // figli del nodo compNode
            bool cmpSX = compNode.HasLeftChild();

            bool right = (hasDX == cmpDX);
            bool left = (hasSX == cmpSX);

            if (left && right){ // se hanno entrambi figli a sx (oppure no) e hanno figlio dx (oppure no)
                if (hasSX && hasDX){
                    return ((compNode.LeftChild() == LeftChild()) && (compNode.RightChild() == RightChild()));
                } 
                else if (hasSX){
                    return (compNode.LeftChild() == LeftChild());
                }else if (hasDX){
                    return (compNode.RightChild() == RightChild());
                }else{
                    return true;
                }
            }
        }

        return false;
    }

    template <typename Data>
    inline bool BinaryTree<Data>::Node::operator!=(const Node& compNode) const noexcept{ // OK
        return !(compNode == *this);
    }
    
    // Specific member functions (Node)
    template <typename Data>
    inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept{
        return !(this->HasLeftChild() || this->HasRightChild()); //se ha almeno uno dei due fligli non è una foglia
    }

    /* BinaryTree */

    // Comparison operators
    template <typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree& cmpBTree) const noexcept{ // OK
        
        if (this->size == cmpBTree.size){
            if (this->size == 0) return true;
            else {
                bool test = (cmpBTree.Root() == this->Root());
                return test;
            }
        }
        return false;
    }

    template <typename Data>
    inline bool BinaryTree<Data>::operator!=(const BinaryTree& cmpBTree) const noexcept{ // OK
        return !(cmpBTree == *this);
    }

    // Specific member function (inherited from TraversableContainer)
    template <typename Data>
    inline void BinaryTree<Data>::Traverse(TraverseFun fun) const{
        PreOrderTraverse(fun, Root());
    }

    // Specific member function (inherited from PreOrderTraversableContainer)
    template <typename Data>
    inline void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const{
        PreOrderTraverse(fun, Root()); // no need controll - test show correct if a trow is launched
    }
    
    // Specific member function (inherited from PostOrderTraversableContainer)
    template <typename Data>
    inline void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const{
        PostOrderTraverse(fun, Root()); // no need controll - test show correct if a trow is launched
    }

    // Specific member function (inherited from InOrderTraversableContainer)
    template <typename Data>
    inline void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const {
        InOrderTraverse(fun, Root()); // no need controll - test show correct if a trow is launched
    }

    // Specific member function (inherited from BreadthTraversableContainer)
    template <typename Data>
    inline void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const{
        BreadthTraverse(fun, Root()); // no need controll - test show correct if a trow is launched
    }

    // Auxiliary functions
    template <typename Data>
    void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun, const Node& node) const{
        fun(node.Element());
        if(!node.IsLeaf()){
            if(node.HasLeftChild()) PreOrderTraverse(fun, node.LeftChild());
            if(node.HasRightChild()) PreOrderTraverse(fun, node.RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun, const Node& node) const{
        if(!node.IsLeaf()){
            if(node.HasLeftChild()) PostOrderTraverse(fun, node.LeftChild());
            if(node.HasRightChild()) PostOrderTraverse(fun, node.RightChild());
        }
        fun(node.Element());
    }

    template <typename Data>
    void BinaryTree<Data>::InOrderTraverse(TraverseFun fun, const Node& node) const{
        
        if(!node.IsLeaf()){
            if(node.HasLeftChild()) InOrderTraverse(fun, node.LeftChild());
            fun(node.Element());
            if(node.HasRightChild()) {
                InOrderTraverse(fun, node.RightChild());
            }
        }else{
            fun(node.Element());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node& node) const{

        if(!node.IsLeaf()){
            QueueVec<const Node*> queue;
            queue.Enqueue(&node);

            while(!queue.Empty()){
                const Node* current = queue.HeadNDequeue();
                if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
                if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
                fun(current->Element());
            }

        }else{
            fun(node.Element());
        }

    }

    /* MutableBinaryTree */

    // Specific member functions
    template <typename Data>
    inline void MutableBinaryTree<Data>::Map(MapFun fun) // Override MappableContainer member
    {
        PreOrderMap(fun);
    }

    // Specific member function (inherited from PreOrderMappableContainer)
    template <typename Data>
    inline void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) // Override PreOrderMappableContainer member
    {
        if(this->size!=0) PreOrderMap(fun, Root());
    }

    // Specific member function (inherited from PostOrderMappableContainer)
    template <typename Data>
    inline void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) // Override PostOrderMappableContainer member
    {
        if(this->size!=0) PostOrderMap(fun, Root());
    }

    // Specific member function (inherited from InOrderMappableContainer)
    template <typename Data>
    inline void MutableBinaryTree<Data>::InOrderMap(MapFun fun) // Override InOrderMappableContainer member
    {
        if(this->size!=0) InOrderMap(fun, Root());
    }

    // Specific member function (inherited from BreadthMappableContainer)
    template <typename Data>
    inline void MutableBinaryTree<Data>::BreadthMap(MapFun fun) // Override BreadthMappableContainer member
    {
        if(this->size!=0) BreadthMap(fun, Root());
    }

    // Auxiliary functions
    template <typename Data>
    void MutableBinaryTree<Data>::PreOrderMap(MapFun fun, MutableNode& node){
        fun(node.Element());
        if(!node.IsLeaf()){
            if(node.HasLeftChild()) PreOrderMap(fun, node.LeftChild());
            if(node.HasRightChild()) PreOrderMap(fun, node.RightChild());
        }
    }

    template <typename Data>
    void MutableBinaryTree<Data>::PostOrderMap(MapFun fun, MutableNode& node){
        if(!node.IsLeaf()){
            if(node.HasLeftChild()) PreOrderMap(fun, node.LeftChild());
            if(node.HasRightChild()) PreOrderMap(fun, node.RightChild());
        }
        fun(node.Element());
    }

    template <typename Data>
    void MutableBinaryTree<Data>::InOrderMap(MapFun fun, MutableNode& node){
        
        if(!node.IsLeaf()){
            if(node.HasLeftChild()) PreOrderMap(fun, node.LeftChild());
            fun(node.Element());
            if(node.HasRightChild()) PreOrderMap(fun, node.RightChild());
        }else{
            fun(node.Element());
        }
    }

    template <typename Data>
    void MutableBinaryTree<Data>::BreadthMap(MapFun fun, MutableNode& node){

        if(!node.IsLeaf()){
            QueueVec<MutableNode*> queue;
            queue.Enqueue(&node);

            while(!queue.Empty()){
                MutableNode* current = queue.HeadNDequeue();
                if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild()));
                if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
                fun(current->Element());
            }

        }else{
            fun(node.Element());
        }

    }

    /*--------------------*/
    /* BTPreOrderIterator */
    /*--------------------*/
 
    // Specific constructors
    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& tree){
        current = &tree.Root(); //Node* = indirizzo del Nodo della radice
        root = current;
        // if (current == nullptr) std::cout<<"C. current null\n";
        // else std::cout<<"C. current :"<<current->Element()<<"\n";
    }

    // Copy constructor
    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data>& itr){
        current = itr.current;
        stk = itr.stk;
        root = itr.root;

    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data>&& itr){
        std::swap(current, itr.current);
        std::swap(stk, itr.stk);
        std::swap(root, itr.root);
    }

    template <typename Data>
    BTPreOrderIterator<Data>::~BTPreOrderIterator(){
        stk.Clear();
        current = nullptr;
        root = nullptr;
    }

    // Copy assignment
    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& itr){
        BTPreOrderIterator<Data>* tmp = new BTPreOrderIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& itr){
        std::swap(stk, itr.stk);
        std::swap(current, itr.current);
        std::swap(root, itr.root);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& itr) const noexcept{

        // Non c'è l'uguaglianze della root

        if(*current == *(itr.current) && stk == itr.stk) return true;
        
        return false;

    }

    template <typename Data>
    inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator& itr) const noexcept{

        return !(*this == itr);

    }

    // Specific member functions (inherited from Iterator)
    template <typename Data>
    const Data& BTPreOrderIterator<Data>::operator*() const{

        if(Terminated()) throw std::out_of_range("Access to an empty iterator");

        return current->Element();

    }

    template <typename Data>
    inline bool BTPreOrderIterator<Data>::Terminated() const noexcept{
        return (current==nullptr);
    }

    // Specific member functions (inherited from ForwardIterator)
    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++(){
        
        if(Terminated()) throw std::out_of_range("Iterator is terminated");

        if (current->HasRightChild()) stk.Push(&(current->RightChild()));
        if (current->HasLeftChild()) stk.Push(&(current->LeftChild()));

        if(stk.Empty()) current = nullptr;
        else current = stk.TopNPop();

        return *this;
    }

    // Specific member functions (inherited from ForwardIterator)
    template <typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept{

        stk.Clear();
        current = root;

    }

    /* BTPreOrderMutableIterator */

    // Copy assignment
    template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& itr){
        BTPreOrderMutableIterator<Data>* tmp = new BTPreOrderMutableIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& itr){
        std::swap(this->stk, itr.stk);
        std::swap(this->current, itr.current);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BTPreOrderMutableIterator<Data>::operator==(const BTPreOrderMutableIterator& itr) const noexcept{
        if(*(this->current) == *(itr.current) && this->stk == itr.stk) return true;
        
        return false;
    }

    template <typename Data>
    bool BTPreOrderMutableIterator<Data>::operator!=(const BTPreOrderMutableIterator& itr) const noexcept{
        return !(*this == itr);
    }

    // Specific member functions (inherited from MutableIterator)
    template <typename Data>
    Data& BTPreOrderMutableIterator<Data>::operator*(){
          
        if(this->Terminated()) throw std::out_of_range("Access to an empty iterator");

        return const_cast<Data &>(this->current->Element());

    }

    /*---------------------*/
    /* BTPostOrderIterator */
    /*---------------------*/

    template <typename Data>
    void BTPostOrderIterator<Data>::getMostLeftLeaf(){
        
        if (current == nullptr) return;

        while(current->HasLeftChild()){
            stk.Push(current);
            current = &(current->LeftChild());
        }

        if(current->HasRightChild()){
            stk.Push(current);
            current = &(current->RightChild());
            getMostLeftLeaf();
        }

        // if(current == nullptr) return;

        // while(current->HasLeftChild() || current->HasRightChild()){
        //     if(current->HasLeftChild()){
        //         stk.Push(current);
        //         current = &(current->LeftChild());
        //     }else if(current->HasRightChild()){
        //         stk.Push(current);
        //         current = &(current->RightChild());   
        //     }
        // }

    }

    // Specific constructors
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& tree) {

        current = &tree.Root();
        root = current;
        getMostLeftLeaf();

    }

    // Copy constructor
    template <typename Data>    
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& itr){
        current = itr.current;
        stk = itr.stk;
        root = itr.root;
    }

    // Move constructor
    template <typename Data>    
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& itr){
        std::swap(current, itr.current);
        std::swap(stk, itr.stk);
        std::swap(root, itr.root);
    }

    // Copy assignment
    template <typename Data> 
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& itr){
        BTPostOrderIterator<Data>* tmp = new BTPostOrderIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data> 
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& itr){
        std::swap(stk, itr.stk);
        std::swap(current, itr.current);
        std::swap(root, itr.current);
        return *this;
    }
    
    // Destructor
    template <typename Data>
    BTPostOrderIterator<Data>::~BTPostOrderIterator(){
        stk.Clear();
        root = nullptr;
        current = nullptr;
    }

    // Comparison operators
    template <typename Data> 
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& itr) const noexcept{

        if(*current == *(itr.current) && stk == itr.stk) return true;
        return false;
        
    }

    template <typename Data> 
    inline bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator& itr) const noexcept{
        return !(itr == *this);
    }

    // Specific member functions (inherited from Iterator)
    template <typename Data>
    const Data& BTPostOrderIterator<Data>::operator*() const{

        if(this->Terminated()) throw std::out_of_range("Access to an empty structure");

        return current->Element();

    }

    template <typename Data>
    inline bool BTPostOrderIterator<Data>::Terminated() const noexcept{
        return (current==nullptr);
    }

    // Specific member functions (inherited from ForwardIterator)
    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
        
        if(Terminated()) throw std::out_of_range("Iterator is terminated");
        
        if (stk.Empty()) current = nullptr;
        else{
            if((stk.Top())->HasLeftChild()){
                if(current == &(stk.Top())->LeftChild()){ //NOTA: confronto indirizzo
                    if((stk.Top())->HasRightChild()){
                        current = &((stk.Top()->RightChild()));
                        getMostLeftLeaf();
                    }else{
                        current = stk.TopNPop();
                    }
                }else{
                    current = stk.TopNPop();
                }
            
            }else if((stk.Top())->HasRightChild()){
                if(current == &(stk.Top())->RightChild()){ //NOTA: confronto indirizzo
                    current = stk.TopNPop();
                }
            }else{
                current = stk.TopNPop();
            }

            // if(stk.Empty()){
            //     current = nullptr;
            // }
        }

        return *this;
    }

    // Specific member functions (inherited from ResettableIterator)
    template <typename Data>
    void BTPostOrderIterator<Data>::Reset() noexcept{
        stk.Clear();
        current = root;
        getMostLeftLeaf();
    }

    /*----------------------------*/
    /* BTPostOrderMutableIterator */
    /*----------------------------*/

    // Copy assignment
    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& itr){
        BTPostOrderMutableIterator<Data>* tmp = new BTPostOrderMutableIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& itr){
        std::swap(this->stk, itr.stk);
        std::swap(this->current, itr.current);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BTPostOrderMutableIterator<Data>::operator==(const BTPostOrderMutableIterator<Data>& itr) const noexcept{
        if(*(this->current) == *(itr.current) && this->stk == itr.stk) return true;
        return false;
    }

    template <typename Data>
    bool BTPostOrderMutableIterator<Data>::operator!=(const BTPostOrderMutableIterator<Data>& itr) const noexcept{
        return !(itr == *this);
    }

    // Specific member functions (inherited from MutableIterator)
    template <typename Data>
    Data& BTPostOrderMutableIterator<Data>::operator*(){ // (throw std::out_of_range when terminated)
        
        if(this->Terminated()) throw std::out_of_range("Access to an empty structure");

        return const_cast<Data &>(this->current->Element());
    }

    /*-----------------*/
    /*BTInOrderIterator*/
    /*-----------------*/

    // Specific constructors
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& tree){
        current = &(tree.Root());
        root = current;
        getMostLeftNode();
        //stk.Pop(); // in caso di errori rimuovere
    }

    // Copy constructor
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& itr){
       current = itr.current;
       root = itr.root;
       stk = itr.stk;
    }

    // Move constructor
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& itr){
        std::swap(current, itr.current);
        std::swap(stk, itr.stk);
        std::swap(root, itr.root);
    }

    // Destructor
    template <typename Data>
    BTInOrderIterator<Data>::~BTInOrderIterator(){
        stk.Clear();
        //delete &stk;
        root = nullptr;
        current = nullptr;
    }

    // Copy assignment
    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& itr){
        BTInOrderIterator<Data>* tmp = new BTInOrderIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& itr){
        std::swap(stk, itr.stk);
        std::swap(current, itr.current);
        std::swap(root, itr.current);
        return *this;
    }
    
    // Comparison operators
    template <typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& itr) const noexcept{
        if(*current == *(itr.current) && stk == itr.stk) return true;
        return false;
    }

    template <typename Data>
    inline bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& itr) const noexcept{
        return !(itr == *this);
    }

    // Specific member functions (inherited from Iterator)
    template <typename Data>
    const Data& BTInOrderIterator<Data>::operator*() const{
        if(this->Terminated()) throw std::out_of_range("Access to an empty structure");
        return current->Element();
    }

    template <typename Data>
    inline bool BTInOrderIterator<Data>::Terminated() const noexcept{
        return (current==nullptr);
    }

    template <typename Data>
    void BTInOrderIterator<Data>::getMostLeftNode(){
        
        if (current == nullptr) return;

        while(current->HasLeftChild()){
            stk.Push(current);
            current = &(current->LeftChild());
        }

        //current = &(stk.TopNPop());
    }

    // Specific member functions (inherited from ForwardIterator)
    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++(){

        if(Terminated()) throw std::out_of_range("Iterator is terminated");

        //current = &(stk.TopNPop());
        if(current->HasRightChild()){
            current = &(current->RightChild());
            getMostLeftNode();
        }else{
            if(stk.Empty()) current = nullptr; 
            else current = stk.TopNPop();
        }

        return (*this);

    }

    // Specific member functions (inherited from ResettableIterator)
    template <typename Data>
    void BTInOrderIterator<Data>::Reset() noexcept{
        stk.Clear();
        current = root;
        getMostLeftNode();
    }

    /*------------------------*/
    /*BTInOrderMutableIterator*/
    /*------------------------*/

    // Copy assignment
    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator<Data>& itr){
        BTInOrderMutableIterator<Data>* tmp = new BTInOrderMutableIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator<Data>&& itr){
        std::swap(this->stk, itr.stk);
        std::swap(this->current, itr.current);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BTInOrderMutableIterator<Data>::operator==(const BTInOrderMutableIterator<Data>& itr) const noexcept{
        if(*(this->current) == *(itr.current) && this->stk == itr.stk) return true;
        return false;
    }

    template <typename Data>
    bool BTInOrderMutableIterator<Data>::operator!=(const BTInOrderMutableIterator<Data>& itr) const noexcept{
        return !(itr == *this);
    }

    // Specific member functions (inherited from MutableIterator)
    template <typename Data>
    Data& BTInOrderMutableIterator<Data>::operator*(){ // (throw std::out_of_range when terminated)
        if(this->Terminated()) throw std::out_of_range("Access to an empty structure");
        return const_cast<Data &>(this->current->Element());
    }

    /*-----------------*/
    /*BTBreadthIterator*/
    /*-----------------*/

    // Specific constructors
    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& tree){ // An iterator over a given binary tree
        //current = &(tree.Root());
        root = &(tree.Root());
        queue.Enqueue(root);
    }

    // Copy constructor
    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data>& itr){
        //current = itr.current;
        root = itr.root;
        queue = itr.queue;
    }

    // Move constructor
    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data>&& itr){
        //std::swap(current, itr.current);
        std::swap(queue, itr.queue);
        std::swap(root, itr.root);
    }

    // Destructor
    template <typename Data>
    BTBreadthIterator<Data>::~BTBreadthIterator(){
        queue.Clear();
        //delete &queue;
        root = nullptr;
        //current = nullptr;
    }

    // Copy assignment
    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& itr){
        BTBreadthIterator<Data>* tmp = new BTBreadthIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& itr){
        std::swap(queue, itr.queue);
        //std::swap(current, itr.current);
        std::swap(root, itr.root);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator& itr) const noexcept{
        return (queue == itr.queue);
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator& itr) const noexcept{
        return !(itr == *this);
    }

    // Specific member functions (inherited from Iterator)
    template <typename Data>
    const Data& BTBreadthIterator<Data>::operator*() const{
        if(this->Terminated()) throw std::out_of_range("Access to an empty structure");
        return queue.Head()->Element(); //current->Element();
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::Terminated() const noexcept{
        return queue.Empty();
    }

    // Specific member functions (inherited from ForwardIterator)
    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++(){
        if(Terminated()) throw std::out_of_range("Iterator is terminated");

        if( (queue.Head())->HasLeftChild() ) queue.Enqueue(&(queue.Head())->LeftChild());
        if( (queue.Head())->HasRightChild() ) queue.Enqueue(&(queue.Head())->RightChild());

        //current = queue.HeadNDequeue();
        queue.Dequeue();

        return *this;

    }

    // Specific member functions (inherited from ResettableIterator)
    template <typename Data>
    void BTBreadthIterator<Data>::Reset() noexcept{
        queue.Clear();
        queue.Enqueue(root);
    }

    /*------------------------*/
    /*BTBreadthMutableIterator*/
    /*------------------------*/

    // Copy assignment
    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator& itr){
        BTBreadthMutableIterator<Data>* tmp = new BTBreadthMutableIterator<Data>(itr);
        std::swap(*this, *tmp);
        delete tmp;
        return *this;
    }

    // Move assignment
    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator&& itr){
        std::swap(this->queue, itr.queue);
        std::swap(this->root, itr.root);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool BTBreadthMutableIterator<Data>::operator==(const BTBreadthMutableIterator& itr) const noexcept{
        // if(*current == *(itr.current) && queue == itr.queue) return true;
        if(this->queue == itr.queue) return true;
        return false;
    }

    template <typename Data>
    bool BTBreadthMutableIterator<Data>::operator!=(const BTBreadthMutableIterator& itr) const noexcept{
        return !(itr == *this);
    }

    // Specific member functions (inherited from MutableIterator)
    template <typename Data>
    Data& BTBreadthMutableIterator<Data>::operator*(){
        if(this->Terminated()) throw std::out_of_range("Access to an empty structure");
        return const_cast<Data &>(this->queue.Head()->Element());
    }

}