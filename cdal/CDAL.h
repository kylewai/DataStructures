#ifndef CDAL_H
#define CDAL_H
#include "List.h"
#include <stdexcept>
#include <math.h>

namespace cop3530{

template <typename E>
class CDAL : public List<E>
{
    public:
        CDAL();
        CDAL(CDAL<E> const &source);
        CDAL<E>& operator =(CDAL<E> const &source);
        CDAL(CDAL<E> const &&source);
        CDAL<E>& operator =(CDAL<E> const &&source);
        void insert(E element, int position) override;
        void push_back(E element) override;
        void push_front(E element) override;
        E replace(E element, int position) override;
        E remove(int position) override;
        E pop_back() override;
        E pop_front() override;
        E& item_at(int position) override;
        E& peek_back() override;
        E& peek_front() override;
        bool is_empty() override;
        bool is_full() override;
        size_t length() override;
        void clear() override;
        bool contains(E element, bool (*equals_function)(const E &element, const E &element2)) override;
        std::ostream& print(std::ostream& stream) override;
        E* contents() override;
        bool noLength();
        ~CDAL();

    private:
        struct Node{
            E *data;
            Node *next;
            Node(){
                data = nullptr;
                next = nullptr;
            }
            ~Node(){
                delete[] data;
            }
        };
        Node *chain;
        int tail;
        void reduce();

    public:
        template <typename T>
        class CDAL_Iter
        {
            public:
                using value_type = T;
                using reference = T&;
                using pointer = T*;
                using difference_type = std::ptrdiff_t;
                using iterator_category = std::forward_iterator_tag;
                using self_type = CDAL_Iter;
                using self_reference = CDAL_Iter&;
            private:
                Node *hNode;
                int here;
                int counts;
                int capacity;

            public:
                explicit CDAL_Iter(Node *hNode = nullptr, int index = 0, int capacity = 0){
                    this->hNode = hNode;
                    this->here = index;
                    this->capacity = capacity;
                    counts = 0;
                }
                CDAL_Iter(CDAL_Iter const &src){
                    here = src.here;
                    hNode = src.hNode;
                    capacity = src.capacity;
                    counts = src.counts;
                }
                static self_type make_begin(Node *hNode, int capacity){
                    CDAL_Iter s(hNode, 0, capacity);
                    return s;
                }
                static self_type make_end(Node *hNode, int capacity){
                    CDAL_Iter s(hNode, (capacity - 1) % 50, capacity);
                    return s;
                }
                self_reference operator=(CDAL_Iter<T> const &src){
                    if(this == &src){
                        return *this;
                    }
                    hNode = src.hNode;
                    here = src.here;
                    counts = src.counts;
                    capacity = src.capacity;
                    return *this;
                }
                reference operator*() const{
                    if(capacity == counts){
                        throw std::runtime_error("Iterator exhausted: no such element");
                    }
                    return hNode->data[here];
                }
                pointer operator->() const{
                    return &(operator*());
                }
                self_reference operator++(){
                    if(capacity != counts ){
                        if(here == 49){
                            hNode = hNode->next;
                            here = 0;
                            counts++;
                        }
                        else{
                            here++;
                        }
                        return *this;
                    }
                    return *this;
                }
                self_type operator++(int){
                    self_type temp(*this);
                    ++(*this);
                    return temp;
                }
                bool operator==(CDAL_Iter<T> const &rhs) const{
                    return (here == rhs.here && hNode == rhs.hNode && capacity == rhs.capacity);
                }
                bool operator!=(CDAL_Iter<T> const &rhs) const{
                    return (here != rhs.here || hNode != rhs.hNode || capacity != rhs.capacity);
                }

        };
    public:
        //using size_t = std::size_t;
        using value_type = E;
        using iterator = CDAL_Iter<E>;
        using const_iterator = CDAL_Iter<E const>;

        iterator begin(){
            return iterator::make_begin(chain, length() + 1);
        }
        iterator end(){
            Node *temp = chain;
            while(temp->next && temp->next->data){
                temp = temp->next;
            }
            iterator s = iterator::make_end(temp, length() + 1);
            temp = nullptr;
            delete temp;
            return s;
        }
        const_iterator begin() const{
            return iterator::make_begin(chain, length() + 1);
        }
        const_iterator end() const{
            Node *temp = chain;
            while(temp->next && temp->next->data){
                temp = temp->next;
            }
            iterator s = iterator::make_end(temp, length() + 1);
            temp = nullptr;
            delete temp;
            return s;
        }

};


//--------------constructors

template <typename E>
CDAL<E>::CDAL(){
    chain = new Node();
    chain->data = new E[50];
    tail = 0;
}

template <typename E>
CDAL<E>::CDAL(CDAL<E> const &source){
    Node *temp = source.chain;
    chain = new Node();
    Node *temp2 = chain;
    while(temp){
        if(temp->data){
            temp2->data = new E[50];
            for(int i = 0; i < 50; i++){
                temp2->data[i] = temp->data[i];
            }
        }

        temp = temp->next;
        temp2 = temp2->next;
        if(temp){
            temp2 = new Node();
        }
    }
    tail = source.tail;

}

template <typename E>
CDAL<E>::CDAL(CDAL<E> const && source){
     chain = source.chain;
     tail = source.tail;
     source.chain = nullptr;
     source.tail = 0;
}

template <typename E>
CDAL<E>& CDAL<E>::operator =(CDAL<E> const &source){
    delete chain;
    Node *temp = source.chain;
    chain = new Node();
    Node *temp2 = chain;
    while(temp){
        if(temp->data){
            temp2->data = new E[50];
            for(int i = 0; i < 50; i++){
                temp2->data[i] = temp->data[i];
            }
        }
        temp = temp->next;
        temp2 = temp2->next;
        if(temp){
            temp2 = new Node();
        }

    }
    tail = source.tail;
    return *this;
}


template <typename E>
CDAL<E>& CDAL<E>::operator =(CDAL<E> const && source){
    delete chain;
    chain = source.chain;
    tail = source.tail;
    source.chain = nullptr;
    source.tail = 0;
    return *this;

}


//--------------insert

template <typename E>
void CDAL<E>::insert(E element, int position){

    if(position < 0 || (((unsigned int)position > length()) && position != 0)){
        throw std::runtime_error("CDAL<E>::insert(E element, int position): Invalid position");
    }
    if((unsigned int)position == length()){
        push_back(element);
        return;
    }
    Node *temp = chain;
    while(temp->next && temp->next->data){
        temp = temp->next;
    }
    if(tail % 50 == 0 && tail != 0){     //Handles the case where the end of the list will overflow

        if(temp->next){
            temp->next->data = new E[50];
        }
        else{
            temp->next = new Node();
            temp->next->data = new E[50];
        }
    }


    temp = chain;

    for(int i = 0; i < position / 50; i++){
        temp = temp->next;
    }
    if((tail % 50 == 0 && tail != 0) || (unsigned int)position < length() - tail % 50){ //If there is going to be carry over into the next arrays
        E *tempArr = new E[50];
        E lastDat = temp->data[49]; //Save the last element of the current array to be inserted into
        for(int i = 49; i >= 0; i--){ //Insert the element into the array
            if(i > position){
                tempArr[i] = temp->data[i - 1];
            }
            else if(i == position){
                tempArr[i] = element;
            }
            else{
                tempArr[i] =  temp->data[i];
            }
        }
        int *tempDel = temp->data;
        temp->data = tempArr;
        delete[] tempDel;

        E firstDat = lastDat;
        int replaceList;

        while(temp->next && temp->next->data){

            temp = temp->next;

            if(temp->next && temp->next->data){
                lastDat = temp->data[49];
            }
            if(!temp->next || !temp->next->data){
                replaceList = tail % 50;
            }
            else{
                replaceList = 49;
            }
            for(int i = replaceList; i >= 0; i--){
                if(i == 0){
                    temp->data[i] = firstDat;
                }
                else{
                    temp->data[i] = temp->data[i - 1];
                }
            }

            firstDat = lastDat;
        }

    }

    else{ //No carry over into the next array

        E *tempArr = new E[50];
        for(int i = tail % 50; i >= 0; i--){ //Insert the element into the array
            if(i > position){
                tempArr[i] = temp->data[i - 1];
            }
            else if(i == position){
                tempArr[i] = element;
            }
            else{
                tempArr[i] =  temp->data[i];
            }
        }
        int *tempDel = temp->data;
        temp->data = tempArr;
        delete[] tempDel;
    }

    tail++;


}


//--------------push_back

template <typename E>
void CDAL<E>::push_back(E element){

    Node *temp = chain;
    while(temp->next && temp->next->data){
        temp = temp->next;
    }
    if(tail % 50 == 0 && tail != 0){
        if(!temp->next){
            temp->next = new Node();
        }
        if(!temp->next->data){
            temp->next->data = new E[50];
        }
        temp = temp->next;
        temp->data[0] = element;
    }
    else{
        temp->data[tail % 50] = element;
    }
    tail++;
}


//--------------push_front

template <typename E>
void CDAL<E>::push_front(E element){
    insert(element, 0);
}


//--------------replace

template <typename E>
E CDAL<E>::replace(E element, int position){

    if(is_empty()){
        throw std::runtime_error("CDAL<E>::replace(E element, int position): Empty list");
    }

    if(position >= tail || position < 0){
        throw std::runtime_error("CDAL<E>::replace(E element, int position): Invalid position");
    }
    Node *temp = chain;
    for(int i = 0; i < position / 50; i++){
        if(temp->next){
            temp = temp->next;
        }
    }
    E datum = temp->data[position % 50];
    temp->data[position % 50] = element;
    return datum;
}


//--------------remove

template <typename E>
E CDAL<E>::remove(int position){

    if(is_empty()){
        throw std::runtime_error("CDAL<E>::remove(int position): Empty List");
    }
    if(position >= tail || position < 0){
        throw std::runtime_error("CDAL<E>::remove(int position): Invalid position");
    }
    if(position == tail - 1){
        return pop_back();
    }
    Node *temp = chain;
    for(int i = 0; i < position / 50; i++){
        temp = temp->next;
    }

    unsigned int replaceList;
    E datum = temp->data[position % 50];

    if(!temp->next || !temp->next->data){
        replaceList = (tail - 1) % 50;
    }
    else{
        replaceList = 49;
    }
    for(size_t i = 0; i < replaceList; i++){
        if(i >= (unsigned int)position % 50){
            temp->data[i] = temp->data[i + 1];
        }
    }
    while(temp->next && temp->next->data){
        E lastDat = temp->next->data[0];
        temp->data[49] = lastDat;
        temp = temp->next;
        if(!temp->next || !temp->next->data){
            replaceList = (tail - 1) % 50;
        }
        else{
            replaceList = 49;
        }
        for(size_t i = 0; i < replaceList; i++){
            temp->data[i] = temp->data[i + 1];
        }
    }


    temp = chain;
    for(int i = 0; i < (tail - 1) / 50; i++){
        temp = temp->next;
    }
    if(tail % 50 == 0 && temp->next){
        delete[] temp->next->data;
        temp->next->data = nullptr;
    }
    tail--;

    reduce();

    return datum;
}


//--------------pop_back

template <typename E>
E CDAL<E>::pop_back(){

    if(is_empty()){
        throw std::runtime_error("CDAL<E>::pop_back(): Empty List");
    }
    Node *temp = chain;
    for(int i = 0; i < (tail - 1) / 50; i++){
        temp = temp->next;
    }

    if(tail % 50 == 0 && temp->next){
        delete[] temp->next->data;
        temp->next->data = nullptr;
    }
    E datum = temp->data[(tail - 1) % 50];
    tail--;
    reduce();
    return datum;

}


//--------------pop_front

template <typename E>
E CDAL<E>::pop_front(){

    if(is_empty()){
        throw std::runtime_error("CDAL<E>::pop_front(): Empty List");
    }
    return remove(0);

}


//--------------item_at

template <typename E>
E& CDAL<E>::item_at(int position){

    if(is_empty()){
        throw std::runtime_error("CDAL<E>::item_at(int position): Empty List");
    }
    if(position >= tail || position < 0){
        throw std::runtime_error("CDAL<E>::item_at(int position): Invalid position");
    }
    Node *temp = chain;

    for(int i = 0; i < position / 50; i++){
        temp = temp->next;
    }
    return temp->data[position % 50];

}


//--------------peek_back

template <typename E>
E& CDAL<E>::peek_back(){

    if(is_empty()){
        throw std::runtime_error("CDAL<E>:: peek_back(): Empty list");
    }

    return item_at(length() - 1);

}


//--------------peek_front

template <typename E>
E& CDAL<E>::peek_front(){

    if(is_empty()){
        throw std::runtime_error("CDAL<E>:: peek_front(): Empty list");
    }

    return chain->data[0];

}


//--------------is_empty

template <typename E>
bool CDAL<E>::is_empty(){

    return tail == 0;

}


//--------------is_full

template <typename E>
bool CDAL<E>::is_full(){
    return false;
}


//--------------length

template <typename E>
size_t CDAL<E>::length(){
    return tail;
}


//--------------clear

template <typename E>
void CDAL<E>::clear(){

    while(!is_empty()){
        pop_back();
    }

}


//--------------contains

template <typename E>
bool CDAL<E>::contains(E element, bool (*equals_function)(const E &element, const E &element2)){

    Node *temp = chain;
    while(temp && temp->data){
        for(size_t i = 0; i < 50; i++){

            if(equals_function(temp->data[i], element)){
                return true;
            }
            if((!temp->next || !temp->next->data) && i == (unsigned int)tail % 50){
                break;
            }
        }
        temp = temp->next;
    }
    return false;

}


//--------------print

template <typename E>
std::ostream& CDAL<E>::print(std::ostream& stream){
    if(is_empty()){
        std::string temp = "<empty list>";
        stream << temp;
    }
    else{
        std::string fbracket = "[";
        stream << fbracket;
        Node *temp = chain;
        while(temp && temp->data){
            for(size_t i = 0; i < 50; i++){
                stream << temp->data[i];
                if((!temp->next || !temp->next->data) && i == (unsigned int)(tail - 1) % 50){
                    std::string bbracket = "]";
                    stream << bbracket;
                    break;
                }
                else{
                    std::string comma = ",";
                    stream << comma;
                }
            }
            temp = temp->next;
        }
    }
    return stream;

}


//--------------contents

template <typename E>
E* CDAL<E>::contents(){

    if(is_empty()){
        throw std::runtime_error("SSLL<E>::contents(): Empty List");
    }
    E *tempArr = new E[length()];
    int k = 0;
    Node *temp = chain;
    while(temp && temp->data){

        for(int i = 0; i < 50; i++){
            tempArr[k] = temp->data[i];
            if((!temp->next || !temp->next->data) && i == tail % 50){
                break;
            }
            k++;
        }
        temp = temp->next;

    }
    return tempArr;

}

template <typename E>
void CDAL<E>::reduce(){
    int i = 0;
    int k = 0;
    Node *temp = chain;
    while(temp){

        if(!temp->data){
            i++;
        }
        k++;
        temp = temp->next;
    }
    if(i > 1){
        for(int j = 0; j < i - 1; j++){
            temp = chain;
            while(temp->next->next){
                temp = temp->next;
            }
            Node *temp2 = temp->next;
            delete temp2;
            temp->next = nullptr;
            j++;
        }
    }


}
template <typename E>
bool CDAL<E>::noLength(){
    int i = 0;
    int k = 0;
    Node *temp = chain;
    while(temp){
        if(!temp->data){
            i++;
        }
        k++;
        temp = temp->next;
    }
    return i > 1;
}


template <typename E>
CDAL<E>::~CDAL(){
    while(chain){
        Node *temp = chain;
        chain = chain->next;

        delete temp;
    }
}


}

#endif // CDAL_H
