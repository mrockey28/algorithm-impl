#include <stdint.h>
#include <iostream>
template <typename T>
void QuickSort(std::vector<T>& v, int begin, int end)
{
    if (end - begin < 1) return;

    uint64_t pivot = v[end];
    uint64_t i = begin;
    uint64_t j = begin;

    while (j <= end)
    {
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

    /*std::cout << "Array from " << begin << " to " << end << " with pivot " << pivot << " at element " << i-1 << std::endl;
    for (int i = begin; i <= end; i++)
    {
        std::cout << i << "(" << v[i] << ")" << std::endl;
    }*/

    //array must have already been sorted.
    //if (end-begin <= 1) return;

    QuickSort(v, begin, i-2);
    QuickSort(v, i, end);
}

template <typename T>
void QuickSort(std::vector<T>& v)
{
    QuickSort<T>(v, 0, v.size()-1);
}
