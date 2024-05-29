#include "dictionary.hpp"

namespace lasd {

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container) {
    bool flag = true;
    container.Traverse(
        [this, &flag](const Data& data){ //this sta per dictionary container visto che andremo ad utilizzare un suo metodo 
            flag &= Insert(data);
        }
    );
    return flag;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container) {
    bool flag = true;
    container.Map(
        [this, &flag](const Data& data){ //this sta per dictionary container visto che andremo ad utilizzare un suo metodo 
            flag &= Insert(std::move(data));
        }
    );
    return flag;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container) {
    bool flag = true;
    container.Traverse(
        [this, &flag](const Data& data){ //this sta per dictionary container visto che andremo ad utilizzare un suo metodo 
            flag &= Remove(data);
        }
    );
    return flag;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& container) {
    bool flag = false;
    container.Traverse(
        [this, &flag](const Data& data){ //this sta per dictionary container visto che andremo ad utilizzare un suo metodo 
            flag |= Insert(data);
        }
    );
    return flag;
}

template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container) {
    bool flag = false;
    container.Map(
        [this, &flag](const Data& data){ //this sta per dictionary container visto che andremo ad utilizzare un suo metodo 
            flag |= Insert(std::move(data));
        }
    );
    return flag;
}

template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container){ // From TraversableContainer; True if some is removed
    bool flag = false;
    container.Traverse(
        [this, &flag](const Data& data){ //this sta per dictionary container visto che andremo ad utilizzare un suo metodo 
            flag |= Remove(data);
        }
    );
    return flag;
}

}