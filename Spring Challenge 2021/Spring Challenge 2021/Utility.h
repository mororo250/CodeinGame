#pragma once

#include <algorithm>

template<class T>
struct delete_ptr // Helper function to ease cleanup of container
{
    void operator () (T p)
    {
        delete p;
    }
};

template <class T>
void delete_all(T& container)
{
    typedef typename T::value_type value_type;
    std::for_each(container.begin(), container.end(), delete_ptr<value_type>());
    container.clear();
}
