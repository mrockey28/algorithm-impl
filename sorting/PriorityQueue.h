#include "PairingHeap.h"

template <class S, class T>
class PriorityQueue 
{
public:
    PriorityQueue(bool isMinimumPriorityQueue = true) : heap(isMinimumPriorityQueue) {}

    typename PairingHeap<S,T>::node* top() const
    {
        return heap.FindTop();
    }

    bool empty() const
    {
        return heap.IsEmpty();
    }

    void push(std::pair<S, T> element)
    {
        heap.Insert(element);
    }

    void pop()
    {
        heap.DeleteTop();
    }


private:
    PairingHeap<S, T> heap;
};
