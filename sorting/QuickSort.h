#include <stdint.h>
#include <iostream>


template <typename T>
void QuickSort(std::vector<T>& v, int begin, int end)
{
    //Don't compare length 1 sub-vectors
    if (end - begin < 1) return;

    //TODO -- improve this. Should pick the middle of begin, end, and (end-begin)/2
    uint64_t pivot = v[end];
    uint64_t i = begin;
    uint64_t j = begin;

    while (j <= end)
    {
        //If j is pointing at a value greater than the pivot,
        //but i is less than it, swap the two values.
        if (v[j] <= pivot && v[i] > pivot)
        {
            T temp = v[i];
            v[i++] = v[j];
            v[j++] = temp;
        }
        else 
        {
            j++;
            if (v[i] <= pivot) i++;
        }
    }

    //Sort the sub-heaps
    QuickSort(v, begin, i-2);
    QuickSort(v, i, end);
}


template <typename T>
void QuickSort(std::vector<T>& v)
{
    QuickSort<T>(v, 0, v.size()-1);
}
