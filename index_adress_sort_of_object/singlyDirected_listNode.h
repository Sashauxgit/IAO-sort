#ifndef SDLN_H
#define SDLN_H

#include <iostream>

template <typename typeObject>
class singlyDirected_listNode {

    typeObject *objectAdress;
    singlyDirected_listNode *nextElem;

public:
    singlyDirected_listNode(): objectAdress(nullptr), nextElem(nullptr){}

    singlyDirected_listNode(typeObject *objectAdress): objectAdress(objectAdress), nextElem(nullptr){}

    singlyDirected_listNode(typeObject *objectAdress, singlyDirected_listNode *nextElem): 
objectAdress(objectAdress), nextElem(nextElem){}

    ~singlyDirected_listNode() = default;

    typeObject *getObject(){
        return this->objectAdress;
    }

    singlyDirected_listNode *getNext(){
        return this->nextElem;
    }

    void addElemNear(typeObject *objectAdress){
        this->nextElem = new singlyDirected_listNode(objectAdress, this->nextElem);
    }

    void setObject(typeObject *objectAdress) {
        if (this->objectAdress) this->addElemNear(objectAdress);
        else this->objectAdress = objectAdress;
    }

    typeObject *deleteElemNear(){
        singlyDirected_listNode *deleteNode = nextElem;
        if (!deleteNode) return nullptr;
        typeObject *value = deleteNode->getObject();
        nextElem = deleteNode->getNext();
        delete deleteNode;
        return value;
    }

    class Iterator {
        singlyDirected_listNode *current;
    public:
        Iterator(singlyDirected_listNode *current): current(current){}
        bool operator==(const Iterator& other) const { return current == other.current;}
        bool operator!=(const Iterator& other) const { return current != other.current;}

        typeObject *&operator * () {
            if (!current) throw std::out_of_range("'singlyDirected_listNode &operator *': invalid element dereference");
            return current->objectAdress;
        }

        Iterator &operator++(){
            if (current != nullptr) current = current->nextElem;
            return *this;
        }
    };

    Iterator begin() {return Iterator(this);}
    Iterator end() {return Iterator(nullptr);}
};

#endif