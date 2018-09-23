#ifndef BSTLEAF_H
#define BSTLEAF_H
#include <stdexcept>
#include <iostream>
#include "Bounded_Dequeue.h"

namespace cop3530{

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
class BSTLEAF
{
    public:
        BSTLEAF();
        BSTLEAF(BSTLEAF<E, F, comparison_function, equality_function> const &source);
        BSTLEAF<E, F, comparison_function, equality_function>& operator =(BSTLEAF<E, F, comparison_function, equality_function> const &source);
        BSTLEAF(BSTLEAF<E, F, comparison_function, equality_function> const &&source);
        BSTLEAF<E, F, comparison_function, equality_function>& operator =(BSTLEAF<E, F, comparison_function, equality_function> const &&source);
        ~BSTLEAF();
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
        void print();
        E* contents();

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
        void recurseDeepCopy(Node *obj, Node *& mine);
        void recurseClear(Node *& obj);
        size_t recurseSize(Node *obj);
        int subHeight(Node *& obj);
        int balFact(Node *& obj);
        Node *root;

};

//--------------constructors

//default
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTLEAF<E, F, comparison_function, equality_function>::BSTLEAF(){
    root = nullptr;
}

//copy
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTLEAF<E, F, comparison_function, equality_function>::BSTLEAF(BSTLEAF<E, F, comparison_function, equality_function> const &source){
    recurseDeepCopy(source.root, this->root);
}

//recurseDeepCopy - recursively performs a deep copy of the given BST

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::recurseDeepCopy(Node *obj, Node *& mine){

    if(obj){
        mine = new Node(obj->key, obj->value);
        recurseDeepCopy(obj->left, mine->left);
        recurseDeepCopy(obj->right, mine->right);
    }

}

//move
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTLEAF<E, F, comparison_function, equality_function>::BSTLEAF(BSTLEAF<E, F, comparison_function, equality_function> const &&source){
    this->root = source.root;
}

//--------------assignment operators

//copy
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTLEAF<E, F, comparison_function, equality_function>& BSTLEAF<E, F, comparison_function, equality_function>::operator =(BSTLEAF<E, F, comparison_function, equality_function> const &source){
    clear();
    recurseDeepCopy(source.root, this->root);
    return *this;
}
//move
template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTLEAF<E, F, comparison_function, equality_function>& BSTLEAF<E, F, comparison_function, equality_function>::operator =(BSTLEAF<E, F, comparison_function, equality_function> const &&source){
    clear();
    this->root = source.root;
    return *this;
}

//-------------destructor

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
BSTLEAF<E, F, comparison_function, equality_function>::~BSTLEAF(){
    clear();
}

//-------------insert

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::insert(E key, F value){
    if(contains(key)){
        lookup(key) = value;
        return;
    }
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

//------------remove - calls partNext

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::remove(E key){
    Node *curr = root;

    if(curr && equality_function(key, curr->key)){
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
        if(curr->right && equality_function(key, curr->right->key)){
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

        if(comparison_function(key, curr->key)){
            curr = curr->left;
        }
        else{
            curr = curr->right;

        }
    }
    throw std::runtime_error("BSTLEAF<E, F, comparison_function, equality_function>::remove: This key does not exist in the map");


}

//-------------lookup

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
F& BSTLEAF<E, F, comparison_function, equality_function>::lookup(E key){
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
    throw std::runtime_error("BSTLEAF<E, F, comparison_function, equality_function>::lookup: This key does not exist in the map");

}

//-------------clear - calls recurseClear

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::clear(){
    recurseClear(root);
}

//-------------contains

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
bool BSTLEAF<E, F, comparison_function, equality_function>::contains(E key){
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
bool BSTLEAF<E, F, comparison_function, equality_function>::is_empty(){
    if(!root){
        return true;
    }
    return false;
}

//-------------is_full

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
bool BSTLEAF<E, F, comparison_function, equality_function>::is_full(){
    return false;
}

//------------size - calls recurseSize

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
size_t BSTLEAF<E, F, comparison_function, equality_function>::size(){
    return recurseSize(root);
}

//-------------height - calls subHeight

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTLEAF<E, F, comparison_function, equality_function>::height(){
    int height = subHeight(root);
    if(height == -1){
        return 0;
    }
    return height;
}

//-------------balance - calls balFact

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTLEAF<E, F, comparison_function, equality_function>::balance(){
    if(!root){
        return 0;
    }
    return balFact(root);
}

//-------------partNext - used to bring the next largest Node up to the position removed - calls rotateRight

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::partNext(Node *& obj){
    if(obj->left){
        partNext(obj->left);
        rotateRight(obj);
    }
    return;
}

//-------------rotateRight - performs a right rotation

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::rotateRight(Node *& obj){
    Node *temp = obj;
    obj = obj->left;
    temp->left = obj->right;
    obj->right = temp;
}



//------------recurseClear - recursively deletes all Nodes in the BST

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::recurseClear(Node *& obj){
    if(obj){
        recurseClear(obj->left);
        recurseClear(obj->right);
        delete obj;
        obj = nullptr;
    }
}

//------------recurseSize - recursively calculates the size of the BST

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
size_t BSTLEAF<E, F, comparison_function, equality_function>::recurseSize(Node *obj){
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

//--------------subHeight - returns the subHeight of a given subtree using recursion

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTLEAF<E, F, comparison_function, equality_function>::subHeight(Node *& obj){
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

//--------------balFact - returns the balance factor of a given node in the tree - calls subHeight

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
int BSTLEAF<E, F, comparison_function, equality_function>::balFact(Node *& obj){
    return subHeight(obj->left) - subHeight(obj->right);
}

//--------------print - prints level order traversal

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
void BSTLEAF<E, F, comparison_function, equality_function>::print(){
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

//--------------contents - returns a packed-array representation of level order traversal

template <typename E, typename F, bool (*comparison_function)(const E&, const E&), bool (*equality_function)(const E&, const E&)>
E* BSTLEAF<E, F, comparison_function, equality_function>::contents(){
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

}


#endif // BSTLEAF_H
