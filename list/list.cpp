#include "list.hpp"

//copy assignment

namespace lasd {

    // Specific Constructor (Node)
    template <typename Data>
    List<Data>::Node::Node(Data&& data) noexcept{
        std::swap(element, data);
    }
    
    //Move Constructor (Node)
    template <typename Data>
    List<Data>::Node::Node(Node&& node) noexcept{
        std::swap(element, node.element);
        std::swap(next, node.next);
    }

    //Destructor (Node)
    template <typename Data>
    List<Data>::Node::~Node(){
        delete next;
    }

    // Comparison operators (Node)
    template <typename Data>
    bool List<Data>::Node::operator==(const Node& other) const noexcept{
    
        return (element==other.element) && \
        ((next==nullptr && other.next==nullptr) || \
         ((next!=nullptr && other.next!=nullptr)&&(*next==*(other.next))));
    
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node& node) const noexcept{
        //ritorno true se il valore del nodo attuale e quello passato uguali
        return !(this->operator==(node));
    }

    template <typename Data>
    typename List<Data>::Node * List<Data>::Node::Clone(Node* tail){
        //43 (0) Executing fold in pre order - obtained value is "14": Correct!
        if( next == nullptr){
            return tail;
        }else{
            Node* node = new Node(element);
            node->next = next->Clone(tail);
            return node;
        }

    }
    /*
        Copia tutta la lista di "nodi" e mette alla fine il nodo passato
        restituendo il nodo clone della nuova lista  
    */

    // Specific constructor (List) 
    template <typename Data>
    List<Data>::List(const TraversableContainer<Data>& TContainer){
        TContainer.Traverse(
            [this](const Data& data){
                InsertAtBack(data);
            }
        );
    }
    /*
        Ricevo una struttura dati su cui è defibile delle operazioni di scorrimento
        e inserisco ogni volta i dati alla fine della lista
    */

    template <typename Data>
    List<Data>::List(MappableContainer<Data>&& MContainer){
        MContainer.Map(
            [this](Data& data){
                InsertAtBack(std::move(data));
            }
        );
    }

    // Copy constructor
    template <typename Data>
    List<Data>::List(const List<Data>& ListToCopy){
        if (ListToCopy.tail != nullptr){ //altimenti copia infinita
            tail = new Node(*(ListToCopy.tail));
            head = ListToCopy.head->Clone(tail);
            size = ListToCopy.size;
        }
    }

    // Move constructor
    template <typename Data>
    List<Data>::List(List<Data>&& ListToMove){
        std::swap(this->head, ListToMove.head);
        std::swap(this->tail, ListToMove.tail);
        std::swap(this->size, ListToMove.size);
    }

    // Destructor
    template <typename Data>
    List<Data>::~List(){
        delete head;
    }

    // Copy assignment
    template <typename Data>
    List<Data>& List<Data>::operator=(const List<Data>& lst){
    
       //not is this the problem
       if (size <= lst.size){
        if(tail == nullptr){
            List<Data>* tmplist = new List<Data>(lst);
            std::swap(*tmplist, *this);
            delete tmplist;
        }else{
            Node* ocur = lst.head;
            for (Node* ncur = head; ncur!=nullptr; ncur = ncur->next, ocur = ocur->next){
                ncur->element = ocur ->element;
            }
            if(ocur != nullptr){
                Node* newtail = new Node(*lst.tail);
                tail->next = ocur->Clone(newtail);
                tail = newtail;
            }
        }
       }else{
        if(lst.tail == nullptr){
            delete head;
            head = tail = nullptr;
        }else{
            Node* ncur = head;
            for (Node* ocur = lst.head; ocur != nullptr; ocur = ocur->next, tail = ncur, ncur = ncur->next){
                ncur->element = ocur->element;
            }
            delete ncur;
            tail->next = nullptr;
        }
       }
        size = lst.size;
        return *this;
    }

    /*
        copia della lista solo se la lista si partenza ha gia predisposta lo stesso / minore
        numero di nodi della lista da copiare 
    */

    template <typename Data>
    List<Data>& List<Data>::operator=(List<Data>&& ListToMove){
        std::swap(head, ListToMove.head);
        std::swap(tail, ListToMove.tail);
        std::swap(size, ListToMove.size);
        return *this;
    }

    // Comparison operators
    template <typename Data>
    inline bool List<Data>::operator==(const List& listToCmp) const noexcept{
        
        if (this->size != listToCmp.size) return false;

        bool result = Size() != 0 ? *this->head == *listToCmp.head : true; 
        //arrivati a questo punto le 2 size sono uguali, se uno è = 0 allora true altrimenti confronto tra radici

        return result;
        
    }

    template <typename Data>
    inline bool List<Data>::operator!=(const List& ListToCmp) const noexcept{
        return !(*this == ListToCmp);
    }

    // Specific member functions
    template <typename Data>
    void List<Data>::InsertAtFront(const Data& data){
        
        Node* nuovo = new Node(data);
        nuovo->next = this->head;
        head = nuovo;

        if (this->tail == nullptr) { //la lista è vuota
            this->tail = nuovo;
        }

        this->size++;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data&& data){
        
        Node* nuovo = new Node(std::move(data));
        nuovo->next = this->head;
        head = nuovo;

        if (this->tail == nullptr) { //la lista è vuota
            this->tail = nuovo;
        }

        this->size++;
    }

    template <typename Data>
    void List<Data>::RemoveFromFront(){

        if(this->head != nullptr){
            Node* nodeToDel = head;

            if(this->head == this->tail){
                this->head = nullptr;
                this->tail = nullptr;
            }else{
                head = head->next; //perche altrimenti elimini il resto dei nodi
            }

            nodeToDel->next = nullptr;
            delete nodeToDel;

            this->size--;

        }else{
            throw std::length_error("Access to empty list");
        }

    }

    template <typename Data>
    Data List<Data>::FrontNRemove(){
        Node NodeToReturn (*this->head);
        this->RemoveFromFront();
        return NodeToReturn.element;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data& data){
        
        Node* NodeToIndert = new Node(data);
        if(tail == nullptr){//my if(this->size == 0){ 
            head = NodeToIndert;
        }else{
            this->tail->next = NodeToIndert;
        }

        this->tail = NodeToIndert;
        this->size++;

    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data&& data){
        
        Node* NodeToIndert = new Node(std::move(data));
        if(tail == nullptr){//my if(this->size == 0){ 
            head = NodeToIndert;
        }else{
            this->tail->next = NodeToIndert;
        }

        this->tail = NodeToIndert;
        this->size++;

    }

    // Specific member function (inherited from ClearableContainer)
    template <typename Data>
    void List<Data>::Clear(){
        this->size = 0;
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    // Specific member functions inherited from DictionaryContainer)
    template <typename Data>
    bool List<Data>::Insert(const Data& data){
        for (Node* current = this->head; current != nullptr; current=current->next){
            if(current->element == data) return false;
        }

        InsertAtBack(data);
        return true;

    }
    /*
        ritorna falso se il dato è gia presente
    */

    template <typename Data>
    bool List<Data>::Insert(Data&& data){ // Move of the value
        for (Node* current = this->head; current != nullptr; current=current->next){
            if(current->element == data) return false;
        }

        InsertAtBack(std::move(data));
        return true;
    }

    template <typename Data>
    bool List<Data>::Remove(const Data& data){
        Node* current = this->head;
        Node* last = nullptr;

        while ( (current != nullptr) && (current->element != data) ){
            last = current;
            current = current->next;
        }

        if (current != nullptr){
            Node* toDel = current;

            if (last!=nullptr){ //not head
                last->next = current->next;
            }else{ //head
                this->head = current->next;
                if(this->head == nullptr){ // if head was the only node
                    this->tail = nullptr;
                }
            }

            if(tail == toDel){
                tail = last;
            }

            toDel->next = nullptr;
            delete toDel;
            this->size--;

            return true;
        }

        return false;

    }
    
    // Specific member functions (inherited from LinearContainer)
    template <typename Data>
    const Data& List<Data>::operator[](const ulong index) const{

        if(index < this->size){ //size è +1 dell'indice

            Node* current = this->head;
            for(ulong idx=0; idx<index; idx++){
                current = current->next;
            }

            return current->element;

        }else{
            throw std::out_of_range("Access to invalid index");
        }

    }

    template <typename Data>
    Data& List<Data>::operator[](const ulong index){

        if(index < this->size){ //size è +1 dell'indice

            Node* current = this->head;
            for(ulong idx=0; idx<index; idx++){
                current = current->next;
            }

            return current->element;

        }else{
            throw std::out_of_range("Access to invalid index");
        }

    }

    template <typename Data>
    const Data& List<Data>::Front() const{
        
        if(this->size == 0){
            throw std::length_error("Access to empty list");
        }else{
            return head->element;
        }
        
    }

    template <typename Data>
    Data& List<Data>::Front(){
        
        if(this->size == 0){
            throw std::length_error("Access to empty list");
        }else{
            return head->element;
        }
    }

    template <typename Data>
    const Data& List<Data>::Back() const{
        
        if(this->size == 0){
            throw std::length_error("Access to empty list");
        }else{
            return tail->element;
        }
    }

    template <typename Data>
    Data& List<Data>::Back(){
        
        if(this->size == 0){
            throw std::length_error("Access to empty list");
        }else{
            return tail->element;
        }
    }

    // Specific member function (inherited from TraversableContainer)
    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun) const{
        this->PreOrderTraverse(fun, this->head);
    }

    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const{
        this->PreOrderTraverse(fun, this->head);
    }

    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const{
        this->PostOrderTraverse(fun, this->head);
    }

    template <typename Data>
    void List<Data>::Map(MapFun fun){
        PreOrderMap(fun, this->head);
    }

    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun){
        PreOrderMap(fun, this->head);
    }

    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun){
        PostOrderMap(fun, this->head);
    }

    // Funzioni ausiliari
    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun, const Node* node) const{

        for(; node!=nullptr; node=node->next){
            fun(node->element);
        }

    }

    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun, const Node* node) const{
        if(node != nullptr){
            PostOrderTraverse(fun, node->next);
            fun(node->element);
        }
    }

    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun, Node* node){

        for(; node!=nullptr; node=node->next){
            fun(node->element);
        }

    }

    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun, Node* node){
        if(node != nullptr){
            PostOrderMap(fun, node->next);
            fun(node->element);
        }
    }


}