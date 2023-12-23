#include <iostream>
#include "singlyDirected_listNode.h"

#define ITER

using namespace std;

void printList(singlyDirected_listNode<int>* node) {
#ifndef ITER
    if (node->getObject()) cout << *node->getObject();
        else cout << "<empty>";
    if (node->getNext()) {
        cout << "-->";
        printList(node->getNext());
    } else cout << "\n";
#else
    for (singlyDirected_listNode<int>::Iterator iter = node->begin(); iter != node->end(); ++iter) {
        if (*iter) cout << **iter;
        else cout << "<empty>";
        cout << "-->";
    }
    cout << "\n";
#endif
}

int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    singlyDirected_listNode<int> head(arr);
    
    for (int i = 1; i < 10; i++) head.addElemNear(arr + i);
    cout << "\n|" << sizeof(head) << "|\n";
    printList(&head);

    singlyDirected_listNode<int>::Iterator iter = head.begin();
    *iter = arr + 5;
    cout << "\n|" << sizeof(iter) << "|\n";
    printList(&head);

    cout << "\n--------------------------------\n";

    for (int i = 0; i < 9; i++) {
        cout << *head.deleteElemNear() << "\n";
        printList(&head);
    }

    return 0;
}