#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

#include "IAO.h"
#include "csvstream.h"

using namespace std;

class A {
    int value;
    int underVal;
public:
    A() {
        this->value = rand() % 1000000 - 500000;
        this->underVal = rand() % 100;
    }
    
    int get_sortorder() {
        return this->value;
    }

    int getUnder() {
        return this->underVal;
    }
};

class notMatchError {
    vector<A> a_arr;
    vector<A*> arrayForIAO;
    vector<A*> arrayForSort;
    vector<A*> arrayForStable;
public:
    notMatchError(vector<A> a_arr, vector<A*> arrayForIAO, vector<A*> arrayForSort, vector<A*> arrayForStable):
a_arr(a_arr), arrayForIAO(arrayForIAO), arrayForSort(arrayForSort), arrayForStable(arrayForStable){}

    ~notMatchError() = default;
    friend ostream& operator << (ostream& out, notMatchError &e);
};

ostream& operator << (ostream& out, notMatchError &e) {
    out << "Does not match on " << e.a_arr.size() << " elements:\n";
    out << "------------------------------------------------------------------------\n";
    
    out << "Start: ";
    for (vector<A>::iterator iter = e.a_arr.begin(); iter != e.a_arr.end(); iter++) out << (*iter).get_sortorder() << " ";
    out << "\n------------------------------------------------------------------------\n";

    out << "IAO: ";
    for (vector<A*>::iterator iter = e.arrayForIAO.begin(); iter != e.arrayForIAO.end(); iter++) out << (*iter)->get_sortorder() << " ";
    out << "\n------------------------------------------------------------------------\n";

    out << "std::sort: ";
    for (vector<A*>::iterator iter = e.arrayForSort.begin(); iter != e.arrayForSort.end(); iter++) out << (*iter)->get_sortorder() << " ";
    out << "\n------------------------------------------------------------------------\n";

    out << "std::stable_sort: ";
    for (vector<A*>::iterator iter = e.arrayForStable.begin(); iter != e.arrayForStable.end(); iter++) out << (*iter)->get_sortorder() << " ";
    out << "\n------------------------------------------------------------------------\n";

    return out;
}

int main() {
    try {
        dataWriter writer("compTimeAnalis_2");
        writer << "data_power" << "IAO_time" << "sort_time" << "stable_time" << dataWriter::endentry;
        
        size_t N = 1000000000;
        size_t start = 1000000;

        writer << 0 << 0 << 0 << 0 << dataWriter::endentry;
        int prevPersent = 0;
        for (size_t n = start; n < N; n+=start) {
            vector<A> a_arr(n);
            vector<A*> arrayForIAO(n);
            vector<A*> arrayForSort(n);
            vector<A*> arrayForStable(n);

            clock_t t1, t2;

            for (size_t i = 0; i < n; i++) {
                arrayForIAO[i] = &a_arr[i]; //cout << a_arr[i].get_sortorder() << "[" << a_arr[i].getUnder() << "] ";
                arrayForSort[i] = &a_arr[i];
                arrayForStable[i] = &a_arr[i];
            }
            // IAO:
            vector<A*>::iterator first = arrayForIAO.begin();
            vector<A*>::iterator last = arrayForIAO.end();
            t1 = clock();
            IAO_sort<vector<A*>::iterator, A>(first, last, first, [](A* obj) {return obj->get_sortorder();});
            t2 = clock();
            double timeForIAO = ((double)(t2 - t1))/CLOCKS_PER_SEC;
            //---

            // Sort:
            first = arrayForSort.begin();
            last = arrayForSort.end();
            t1 = clock();
            sort(first, last, [](A* _1, A* _2){
                return _1->get_sortorder() < _2->get_sortorder();
            });
            t2 = clock();
            double timeForSort = ((double)(t2 - t1))/CLOCKS_PER_SEC;
            //---

            // Stable:
            first = arrayForStable.begin();
            last = arrayForStable.end();
            t1 = clock();
            stable_sort(first, last, [](A* _1, A* _2){
                return _1->get_sortorder() < _2->get_sortorder();
            });
            t2 = clock();
            double timeForStable = ((double)(t2 - t1))/CLOCKS_PER_SEC;
            //---

            //for (size_t i = 0; i < n; i++) {
            //    if (arrayForIAO[i] != arrayForStable[i] || arrayForIAO[i]->get_sortorder() != arrayForSort[i]->get_sortorder())
            //        throw notMatchError(a_arr, arrayForIAO, arrayForSort, arrayForStable);
            //}

            writer << n << timeForIAO << timeForSort << timeForStable << dataWriter::endentry;

            if ((int)(((double)(n - start)) / (double)(N - start) * 100) > prevPersent) {
                prevPersent = (int)(((double)(n - start)) / (double)(N - start) * 100);
                cout << prevPersent << "%\n";
            }
        }
        cout << "OK" << endl;
    } catch (notMatchError &err) {
        cout << err << endl;
    } catch (exception& e) {cout << e.what();}

    return 0;
    
    /*
    for (int i = 0; i < N; i++) 
    cout << array_2[i]->get_sortorder() << "[" << array_2[i]->getUnder() << "] ";
    */
    return 0;
}