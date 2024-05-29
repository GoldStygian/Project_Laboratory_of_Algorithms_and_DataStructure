#include "queuelst.hpp"

namespace lasd {

    // Copy assignment
    template <typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queue){
        List<Data>::operator=(queue);
        return *this;
    }

    // Move assignment
    template <typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queue){
        List<Data>::operator=(std::move(queue));
        return *this;
    }

    // Comparison operators
    template <typename Data>
    bool QueueLst<Data>::operator==(const QueueLst& queue) const noexcept{
        return List<Data>::operator==(queue);
    }

    template <typename Data>
    inline bool QueueLst<Data>::operator!=(const QueueLst& queue) const noexcept{
        return List<Data>::operator!=(queue);
    }

    // Specific member functions (inherited from Queue)
    template <typename Data>
    inline const Data& QueueLst<Data>::Head() const{   // Override Queue member (non-mutable version; must throw std::length_error when empty)
        return List<Data>::Front();
    }

    template <typename Data>
    inline Data& QueueLst<Data>::Head(){   // Override Queue member (mutable version; must throw std::length_error when empty)
        return List<Data>::Front();
    }

    template <typename Data>
    inline void QueueLst<Data>::Dequeue(){   // Override Queue member (must throw std::length_error when empty)
        List<Data>::RemoveFromFront();
    }

    template <typename Data>
    inline Data QueueLst<Data>::HeadNDequeue(){   // Override Queue member (must throw std::length_error when empty)
        return List<Data>::FrontNRemove();
    }

    template <typename Data>
    inline void QueueLst<Data>::Enqueue(const Data& data){   // Override Queue member (copy of the value)
        List<Data>::InsertAtBack(data);
    }

    template <typename Data>
    inline void QueueLst<Data>::Enqueue(Data&& data){   // Override Queue member (move of the value)
        List<Data>::InsertAtBack(data);
    }

}