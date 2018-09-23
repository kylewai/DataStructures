#ifndef BSTRAND_H
#define BSTRAND_H
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "Bounded_Dequeue.h"

namespace cop3530{

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
class BSTRAND
{
    public:
        BSTRAND();
        BSTRAND(BSTRAND<E, F, comparison_function, equality_function> const &source);
        BSTRAND<E, F, comparison_function, equality_function>& operator =(BSTRAND<E, F, comparison_function, equality_function> const &source);
        BSTRAND(BSTRAND<E, F, comparison_function, equality_function> const &&source);
        BSTRAND<E, F, comparison_function, equality_function>& operator =(BSTRAND<E, F, comparison_function, equality_function> const &&source);
        void insert(E key, F value);
        void remove(E key);
        F& lookup(E key);
        void clear();
        bool contains(E key);
        bool is_empty();
        bool is_full();
        size_t size();
        int height();
        int balance();
        ~BSTRAND();

    private:

        struct Node{
            E key;
            F value;
            Node *left;
            Node *right;
            Node(E key, F value){
                this->key = key;
                this->value = value;
                left = nullptr;
                right = nullptr;
            }
        };
        void partNext(Node *& obj);
        void rotateRight(Node *& obj);
        void rotateLeft(Node *& obj);
        void insert_at_root(E key, F value, Node *& obj);
        void recurseDeepCopy(Node *obj, Node *& mine);
        void recurseClear(Node *& obj);
        size_t recurseSize(Node *obj);
        int subHeight(Node *& obj);
        int balFact(Node *& obj);
        size_t mapSize;


    public:
        Node *root;
        void print();
        E* contents();


};

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTRAND<E, F, comparison_function, equality_function>::BSTRAND(){
    root = nullptr;
    mapSize = 0;
}

//copy
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTRAND<E, F, comparison_function, equality_function>::BSTRAND(BSTRAND<E, F, comparison_function, equality_function> const &source){
    this->mapSize = source.mapSize;
    recurseDeepCopy(source.root, this->root);
}

//recurseDeepCopy - recursively performs a deep copy of the given BST

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::recurseDeepCopy(Node *obj, Node *& mine){

    if(obj){
        mine = new Node(obj->key, obj->value);
        recurseDeepCopy(obj->left, mine->left);
        recurseDeepCopy(obj->right, mine->right);
    }

}

//move
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTRAND<E, F, comparison_function, equality_function>::BSTRAND(BSTRAND<E, F, comparison_function, equality_function> const &&source){
    this->mapSize = source.mapSize;
    this->root = source.root;
}

//--------------assignment operators

//copy
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTRAND<E, F, comparison_function, equality_function>& BSTRAND<E, F, comparison_function, equality_function>::operator =(BSTRAND<E, F, comparison_function, equality_function> const &source){
    clear();
    this->mapSize = source.mapSize;
    recurseDeepCopy(source.root, this->root);
    return *this;

}
//move
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTRAND<E, F, comparison_function, equality_function>& BSTRAND<E, F, comparison_function, equality_function>::operator =(BSTRAND<E, F, comparison_function, equality_function> const &&source){
    clear();
    this->mapSize = source.mapSize;
    this->root = source.root;
    return *this;
}

//---------------destructor

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTRAND<E, F, comparison_function, equality_function>::~BSTRAND(){
    clear();
}


template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::insert(E key, F value){
    srand(time(NULL));
    if(contains(key)){
        lookup(key) = value;
        return;
    }
    int random = rand() % (mapSize + 1);
    if(random == 0){
        insert_at_root(key, value, root);
    }
    else{
        Node *curr = root;
        Node *insertion = new Node(key, value);
        Node *parent = root;
        if(!curr){
            root = insertion;
            return;
        }
        while(curr){

            if(comparison_function(key, curr->key)){
                curr = curr->left;
                if(curr){
                    parent = curr;
                }
            }
            else if(equality_function(key, curr->key)){
                curr->value = value;
                return;
            }
            else{
                curr = curr->right;
                if(curr){
                    parent = curr;
                }
            }
        }

        if(comparison_function(key, parent->key)){
            parent->left = insertion;
        }
        else{
            parent->right = insertion;
        }
    }
    mapSize++;

}

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::remove(E key){
    Node *curr = root;
    if(equality_function(key, curr->key)){
        if(!root->right && !root->left){
            delete root;
            root = nullptr;
        }
        else if(!root->right){
            Node *temp = root;
            root = root->left;
            delete temp;
        }
        else if(!root->left){
            Node *temp = root;
            root = root->right;
            delete temp;
        }
        else{
            Node *temp = root;
            Node *temp2 = root->left;
            Node *temp3 = root->right;
            partNext(temp3);
            root = temp3;

            delete temp;

            root->left = temp2;
        }
        return;
    }
    while(curr){
        if(curr->left && equality_function(key, curr->left->key)){
            Node *temp = curr->left;
            if(!temp->right && !temp->left){
                delete temp;
                curr->left = nullptr;
            }
            else if(!temp->right){
                curr->left = temp->left;
                delete temp;
            }
            else if(!temp->left){
                curr->left = temp->right;
                delete temp;
            }
            else{

                Node *temp2 = temp->left;
                Node *temp3 = temp->right;
                partNext(temp3);
                curr->left = temp3;

                delete temp;

                curr->left->left = temp2;
            }
            return;
        }
        else if(curr->right && equality_function(key, curr->right->key)){
            Node *temp = curr->right;
            if(!temp->right && !temp->left){
                delete temp;
                curr->right = nullptr;
            }
            else if(!temp->right){
                curr->right = temp->left;
                delete temp;
            }
            else if(!temp->left){
                curr->right = temp->right;
                delete temp;
            }
            else{
                Node *temp2 = temp->left;
                Node *temp3 = temp->right;
                partNext(temp3);
                curr->right = temp3;
                delete temp;
                curr->right->left = temp2;
            }
            return;
        }

        else if(comparison_function(key, curr->key)){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }

    }
    throw std::runtime_error("BSTRAND<E, F, comparison_function, equality_function>::lookup: This key does not exist in the map");


}

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
F& BSTRAND<E, F, comparison_function, equality_function>::lookup(E key){
    Node *curr = root;
    while(curr){
        if(equality_function(key, curr->key)){
            return curr->value;
        }
        if(comparison_function(key, curr->key)){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    throw std::runtime_error("BSTRAND<E, F, comparison_function, equality_function>::lookup: This key does not exist in the map");

}

//---------------partNext

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::partNext(Node *& obj){
    if(obj->left){
        partNext(obj->left);
        rotateRight(obj);
    }
    return;
}

//---------------rotateRight

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::rotateRight(Node *& obj){
    Node *temp = obj;
    obj = obj->left;
    temp->left = obj->right;
    obj->right = temp;
}

//---------------rotateLeft

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::rotateLeft(Node *& obj){
    Node *temp = obj;
    obj = obj->right;
    temp->right = obj->left;
    obj->left = temp;
}

//-------------print

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::print(){
    Bounded_Dequeue<Node*> *bq = new Bounded_Dequeue<Node*>(100000);
    if(is_empty()){
        return;
    }

    bq->push_back(root);
    while(!bq->is_empty()){
        Node *curr = bq->pop_front();
        std::cout << curr->key;
        if(curr->left){
            bq->push_back(curr->left);
        }
        if(curr->right){
            bq->push_back(curr->right);
        }
        if(!bq->is_empty()){
            std::cout << "->";
        }
    }
    delete bq;
    std::cout << std::endl;
}

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
E* BSTRAND<E, F, comparison_function, equality_function>::contents(){
    Bounded_Dequeue<Node*> *bq = new Bounded_Dequeue<Node*>(100000);

    E *arr = new E[size()];
    int i = 0;

    bq->push_back(root);
    while(!bq->is_empty()){
        Node *curr = bq->pop_front();
        arr[i] = curr->key;
        if(curr->left){
            bq->push_back(curr->left);
        }
        if(curr->right){
            bq->push_back(curr->right);
        }
        i++;
    }
    delete bq;

    return arr;
}


template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::insert_at_root(E key, F value, Node *& obj){
    if(!obj){
        obj = new Node(key, value);
        return;
    }
    if(comparison_function(key, obj->key)){
        insert_at_root(key, value, obj->left);
        rotateRight(obj);

    }
    else{
        insert_at_root(key, value, obj->right);
        rotateLeft(obj);

    }
}

//-------------clear

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::clear(){
    recurseClear(root);
}

//------------recurseClear - recursively deletes all Nodes in the BST

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTRAND<E, F, comparison_function, equality_function>::recurseClear(Node *& obj){
    if(obj){
        recurseClear(obj->left);
        recurseClear(obj->right);
        delete obj;
        obj = nullptr;
    }
}

//-------------contains

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
bool BSTRAND<E, F, comparison_function, equality_function>::contains(E key){
    Node *curr = root;
    while(curr){
        if(equality_function(key, curr->key)){
            return true;
        }
        if(comparison_function(key, curr->key)){
            curr = curr->left;
        }
        else{
            curr = curr->right;
        }
    }
    return false;
}

//-------------is_empty

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
bool BSTRAND<E, F, comparison_function, equality_function>::is_empty(){
    if(!root){
        return true;
    }
    return false;
}

//-------------is_full

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
bool BSTRAND<E, F, comparison_function, equality_function>::is_full(){
    return false;
}

//------------size

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
size_t BSTRAND<E, F, comparison_function, equality_function>::size(){
    return recurseSize(root);
}

//------------recurseSize - recursively calculates the size of the BST

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
size_t BSTRAND<E, F, comparison_function, equality_function>::recurseSize(Node *obj){
    size_t sizes = 0;
    if(!obj){
        return sizes;
    }
    sizes = 1;
    if(obj->left){
        sizes += recurseSize(obj->left);
    }
    if(obj->right){
        sizes += recurseSize(obj->right);
    }
    return sizes;

}

//-------------height

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTRAND<E, F, comparison_function, equality_function>::height(){
    int height = subHeight(root);
    if(height == -1){
        return 0;
    }
    return height;
}

//-------------balance

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTRAND<E, F, comparison_function, equality_function>::balance(){
    if(!root){
        return 0;
    }
    return balFact(root);
}

//--------------balFact - returns the balance factor of a given node in the tree

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTRAND<E, F, comparison_function, equality_function>::balFact(Node *& obj){
    return subHeight(obj->left) - subHeight(obj->right);
}

//--------------subHeight - returns the subHeight of a given subtree

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTRAND<E, F, comparison_function, equality_function>::subHeight(Node *& obj){
    int heightLeft = 0;
    int heightRight = 0;
    if(!obj){
        return -1;  //NECESSARY
    }
    if(obj->left){
        heightLeft = 1 + subHeight(obj->left);
    }
    if(obj->right){
        heightRight = 1 + subHeight(obj->right);
    }
    if(heightLeft > heightRight){
        return heightLeft;
    }
    return heightRight;
}

}

#endif // BSTRAND_H
