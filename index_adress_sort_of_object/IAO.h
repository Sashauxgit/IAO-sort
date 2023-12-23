#include "singlyDirected_listNode.h"

#include <vector>
#include <functional>

struct rangeCoords {
public:
    long long int min_value;
    long long int max_value;
};

template <class RandomAccessIterator, typename typeObject>
rangeCoords getRangeValues(RandomAccessIterator first, RandomAccessIterator last, std::function<long long int(typeObject*)> get_sortorder) {
    rangeCoords range = {get_sortorder(*first), get_sortorder(*first)};

    for (RandomAccessIterator iter = first; iter != last; ++iter) {
        if (get_sortorder(*iter) < range.min_value) range.min_value = get_sortorder(*iter);
        else if (get_sortorder(*iter) > range.max_value) range.max_value = get_sortorder(*iter);
    }
    
    return range;
}

template<class RandomAccessIterator, typename typeObject> 
void IAO_sort(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator place_for_sort,
std::function<long long int(typeObject*)> get_sortorder) {
    rangeCoords range = getRangeValues<RandomAccessIterator>(first, last, get_sortorder);

    singlyDirected_listNode<typeObject> *series = new singlyDirected_listNode<typeObject>[range.max_value - range.min_value + 1];
    for (RandomAccessIterator iter = first; iter != last; ++iter) {
        series[get_sortorder(*iter) - range.min_value].setObject(*iter);
        ++place_for_sort;
    }

    singlyDirected_listNode<typeObject> *series_iter = series + range.max_value - range.min_value;
    for (RandomAccessIterator iter = --place_for_sort; series_iter >= series; --iter) {
        typeObject *curElem = series_iter->deleteElemNear();
        if (curElem) *iter = curElem;
        else {
            curElem = (series_iter--)->getObject();
            if (curElem) *iter = curElem;
            else ++iter;
        }
    }

    delete[] series;
}

template<class RandomAccessIterator, typename typeObject> 
void IAO_sort_multilevel(RandomAccessIterator first, RandomAccessIterator last, 
RandomAccessIterator place_for_sort, singlyDirected_listNode<typeObject> *addition_elem = nullptr, int level = 0) {
    if (!addition_elem) {
        *last;
    }
    
    rangeCoords range = getRangeValues<RandomAccessIterator>(first, last);

    singlyDirected_listNode<typeObject> *series = new singlyDirected_listNode<typeObject>[range.max_value - range.min_value + 1];
    for (RandomAccessIterator iter = first; iter != last; ++iter) {
        series[(*iter)->get_sortorder() - range.min_value].setObject(*iter);
        ++place_for_sort;
    }



    /*
    singlyDirected_listNode<typeObject> *series_iter = series + range.max_value - range.min_value;
    for (RandomAccessIterator iter = --place_for_sort; series_iter >= series; --iter) {
        typeObject *curElem = series_iter->deleteElemNear();
        if (curElem) *iter = curElem;
        else {
            curElem = (series_iter--)->getObject();
            if (curElem) *iter = curElem;
            else ++iter;
        }
    }
    */
    delete[] series;
}