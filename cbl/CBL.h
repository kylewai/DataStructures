#ifndef CBL_H
#define CBL_H
#include "List.h"
#include <stdexcept>
#include <math.h>

namespace cop3530{
template <typename E>
class CBL : public List<E>
{
    public:
        CBL();
        CBL(unsigned int capacity);
        CBL(CBL<E> const &source);
        CBL<E>& operator =(CBL<E> const &source);
        CBL(CBL<E> const &&source);
        CBL<E>& operator =(CBL<E> const &&source);
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
        bool testCap();

        ~CBL();


    private:
        int head;
        int tail;
        E *data;
        unsigned int capacity;
        int originalCap;
        int findPos(int pos);
        void increment(int &index);
        void reduce();
        void decrement(int &index);

    public:
        template <typename T>
        class CBL_Iter
        {
            public:
                using value_type = T;
                using reference = T&;
                using pointer = T*;
                using difference_type = std::ptrdiff_t;
                using iterator_category = std::forward_iterator_tag;
                using self_type = CBL_Iter;
                using self_reference = CBL_Iter&;
            private:
                T *arr;
                int here;
                int tailEnd;
                int capacity;

            public:
                explicit CBL_Iter(T *arr = nullptr, int here = 0, int tailEnd = 0, int capacity = 0){
                    this->arr = arr;
                    this->here = here;
                    this->tailEnd = tailEnd;
                    this->capacity = capacity;
                }
                CBL_Iter(CBL_Iter const &src){
                    here = src.here;
                    arr = src.arr;
                    tailEnd = src.tailEnd;
                    capacity = src.capacity;
                }
                self_reference operator=(CBL_Iter<T> const &src){
                    if(this == &src){
                        return *this;
                    }
                    arr = src.arr;
                    here = src.here;
                    tailEnd = src.tailEnd;
                    capacity = src.capacity;
                    return *this;
                }
                reference operator*() const{
                    if(here == tailEnd){
                        throw std::runtime_error("Iterator exhausted: no such point");
                    }
                    return arr[here];
                }
                pointer operator->() const{
                    return &(operator*());
                }
                self_reference operator++(){
                    if(here != tailEnd){
                        if(here == capacity - 1){
                            here = 0;
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
                bool operator==(CBL_Iter<T> const &rhs) const{
                    return (here == rhs.here && arr == rhs.arr && tailEnd == rhs.tailEnd && capacity = rhs.capacity);
                }
                bool operator!=(CBL_Iter<T> const &rhs) const{
                    return (here != rhs.here || arr != rhs.arr || tailEnd != rhs.tailEnd || capacity != rhs.capacity);
                }

        };
    public:
        //using size_t = std::size_t;
        using value_type = E;
        using iterator = CBL_Iter<E>;
        using const_iterator = CBL_Iter<E const>;

        iterator begin(){
            return iterator(data, head, tail, capacity);
        }
        iterator end(){
            return iterator(data, tail, tail, capacity);
        }
        const_iterator begin() const{
            return const_iterator(data, head, tail, capacity);
        }

        const_iterator end() const{
            return const_iterator(data, tail, tail, capacity);
        }
};

//--------------constructors

//default

template <typename E>
CBL<E>::CBL(){
    originalCap = 51;
    capacity = 51;
    data = new E[capacity];
    head = 0;
    tail = 0;
}

//parameterized

template <typename E>
CBL<E>::CBL(unsigned int capacity){
    originalCap = capacity + 1;
    data = new E[capacity + 1];
    this->capacity = capacity + 1;
    tail = 0;
    head = 0;
}

//copy

template <typename E>
CBL<E>::CBL(CBL<E> const &source){
    data = new E[source.capacity];
    for(size_t i = 0 ; i < source.capacity; i++){
        data[i] = source.data[i];
    }
    capacity = source.capacity;
    originalCap = source.originalCap;
    tail = source.tail;
    head = source.head;

}

//move

template <typename E>
CBL<E>::CBL(CBL<E> const && source){
    data = source.data;
    capacity = source.capacity;
    tail = source.tail;
    head = source.head;
    originalCap = source.originalCap;
    source.originialCap = 51;
    source.capacity = 51;
    source.tail = 0;
    source.head = 0;
    source.data = nullptr;
}

//--------------assignment operators

//copy

template <typename E>
CBL<E>& CBL<E>::operator =(CBL<E> const &source){
    delete[] data;
    data = new E[source.capacity];
    for(size_t i = 0 ; i < source.capacity; i++){
        data[i] = source.data[i];
    }
    capacity = source.capacity;
    originalCap = source.originalCap;
    tail = source.tail;
    head = source.head;
    return *this;
}

//move

template <typename E>
CBL<E>& CBL<E>::operator =(CBL<E> const && source){
    delete[] data;
    data = source.data;
    capacity = source.capacity;
    tail = source.tail;
    head = source.head;
    originalCap = source.originalCap;
    source.originialCap = 50;
    source.capacity = 50;
    source.tail = 0;
    source.head = 0;
    source.data = nullptr;
    return *this;
}

//--------------insert

template <typename E>
void CBL<E>::insert(E element, int position){

    if(position < 0 || ((unsigned int)position > length() && position != 0)){
        throw std::runtime_error("CBL<E>::insert(E element, int position): Invalid position");
    }
    if(is_empty()){
        push_front(element);
        return;
    }
    if((unsigned int)position == length()){
        push_back(element);
        return;
    }
    position = findPos(position);
    if(length() + 1 == capacity){   //If the array must be resized to fit the added element
        E *temp = new E[(unsigned int)ceil(capacity * 1.5)];

        int currIndex = head;
        size_t i;
        for(i = 0; i < length() + 1; i++){
            if(i == (unsigned int)position){
                temp[i] = element;
                continue;
            }
            else{
                temp[i] = data[currIndex];
                increment(currIndex);
            }
        }
        capacity = ceil(capacity * 1.5);
        tail = ++i;
        head = 0;

        E *temp2 = data;
        data = temp;
        delete[] temp2;
    }
    else{   //Case where the array does not need to be resized

        int curr = position;
        E prev = 0;
        while(curr != tail){
            prev = data[curr];
            data[curr] = element;
            element = prev;
            increment(curr);
        }
        data[curr] = element;
        increment(tail);
    }
    reduce();
}

//--------------push_back

template <typename E>
void CBL<E>::push_back(E element){

    if(length() + 1 == capacity){
        E *temp = new E[(unsigned int)ceil(capacity * 1.5)];

        int currIndex = head;
        size_t i = 0;
        for(i = 0; i < length(); i++){
            temp[i] = data[currIndex];
            increment(currIndex);
        }
        temp[i] = element;
        capacity = ceil(capacity * 1.5);
        tail = ++i;
        head = 0;

        E *temp2 = data;
        data = temp;
        delete[] temp2;
    }
    else{
        data[tail] = element;   //Insert at the tail and then increment the tail
        increment(tail);
    }
    reduce();

}

//--------------push_front

template <typename E>
void CBL<E>::push_front(E element){

    if(length() + 1 == capacity){
        E *temp = new E[(unsigned int)ceil(capacity * 1.5)];

        int currIndex = head;
        size_t i = 0;
        temp[i] = element;

        for(i = 1; i < length() + 1; i++){
            temp[i] = data[currIndex];
            increment(currIndex);
        }
        capacity = ceil(capacity * 1.5);
        tail = i;
        head = 0;

        E *temp2 = data;
        data = temp;
        delete[] temp2;
    }
    else{
        decrement(head);    //Decrement head and then insert at head
        data[head] = element;
    }
    reduce();
}

//--------------replace

template <typename E>
E CBL<E>::replace(E element, int position){

    if(is_empty()){
        throw std::runtime_error("CBL<E>::replace(E element, int position): Empty list");
    }

    if(position < 0 || (unsigned int)position + 1 > length()){
        throw std::runtime_error("CBL<E>::replace(E element, int position): Invalid position");
    }
    position = findPos(position);
    E datum = data[position];
    data[position] = element;
    return datum;

}

//--------------remove

template <typename E>
E CBL<E>::remove(int position){

    if(is_empty()){
        throw std::runtime_error("CBL<E>::remove(E element, int position): Empty list");
    }
    if(position < 0 || (unsigned int)position + 1 > length()){
        throw std::runtime_error("CBL<E>::remove(E element, int position): Invalid position");
    }
    position = findPos(position);
    E datum = data[position];
    int currIndex = head;
    int next = head;
    increment(next);
    E *temp = new E[capacity];
    bool posFound = false;
    for(size_t i = 0; i < length() - 1; i++){ //Copying items to new array but omitting the removed item
        if(currIndex == position){
            temp[currIndex] = data[next];
            posFound = true;
        }
        if(!posFound){
            temp[currIndex] = data[currIndex];
        }
        else{
            temp[currIndex] = data[next];
        }
        increment(currIndex);
        increment(next);
    }
    E *temp2 = data;
    data = temp;
    delete temp2;

    decrement(tail);
    reduce();
    return datum;
}

//--------------pop_back

template <typename E>
E CBL<E>::pop_back(){
    if(is_empty()){
        throw std::runtime_error("CBL<E>:: pop_back(): Empty List");
    }
    decrement(tail);
    reduce();
    return data[tail];
}

//--------------pop_front

template <typename E>
E CBL<E>::pop_front(){
    if(is_empty()){
        throw std::runtime_error("CBL<E>:: pop_front(): Empty List");
    }
    E datum = data[head];
    increment(head);
    reduce();
    return datum;
}

//--------------item_at

template <typename E>
E& CBL<E>::item_at(int position){

    if(is_empty()){
        throw std::runtime_error("CBL<E>:: item_at(int position): Empty list");
    }
    if(position < 0 || (unsigned int)position + 1 > length()){
        throw std::runtime_error("CBL<E>:: item_at: Invalid position");
    }
    position = findPos(position);
    return data[position];
}

//--------------peek_back

template <typename E>
E& CBL<E>::peek_back(){
    if(is_empty()){
        throw std::runtime_error("CBL<E>:: peek_back(): Empty list");
    }
    if(tail == 0){
        return data[capacity - 1];
    }
    return data[tail - 1];
}

//--------------peek_front

template <typename E>
E& CBL<E>::peek_front(){
    if(is_empty()){
        throw std::runtime_error("CBL<E>:: peek_front(): Empty list");
    }
    return data[head];
}

//--------------is_empty

template <typename E>
bool CBL<E>::is_empty(){
    return head == tail;

}

//--------------is_full

template <typename E>
bool CBL<E>::is_full(){
    return false;
}

//--------------length

template <typename E>
size_t CBL<E>::length(){
    if(tail > head){
        return tail - head;
    }
    else if(head > tail){
        return tail + (capacity - head);
    }
    else{
        return 0;
    }
}

//--------------clear

template <typename E>
void CBL<E>::clear(){
    head = 0;
    tail = 0;
}

//--------------contains

template <typename E>
bool CBL<E>::contains(E element, bool (*equals_function)(const E &element, const E &element2)){
    int currIndex = head;
    while(currIndex != tail){
        if(equals_function(element, data[currIndex])){
            return true;
        }
        increment(currIndex);
    }
    return false;
}

//--------------print

template <typename E>
std::ostream& CBL<E>::print(std::ostream& stream){
    if(is_empty()){
        std::string temp = "<empty list>";
        stream << temp;
    }
    else{
        std::string fbracket = "[";
        stream << fbracket;
        int currIndex = head;
        for(size_t i = 0; i < length(); i++){
            stream << data[currIndex];

            if(i == length() - 1){
                std::string bbracket = "]";
                stream << bbracket;
            }
            else{
                std::string comma = ",";
                stream << comma;
            }
            increment(currIndex);
        }

    }
    return stream;
}

//--------------contents

template <typename E>
E* CBL<E>::contents(){
    if(is_empty()){
        throw std::runtime_error("CBL<E>::contents(): Empty List");
    }
    E *arr = new E[length()];
    int currIndex = head;
    for(size_t i = 0; i < length(); i++){
        arr[i] = data[currIndex];
        increment(currIndex);
    }
    return arr;
}

//--------------destructor

template <typename E>
CBL<E>::~CBL(){
    head = 0;
    tail = 0;
    delete data;

}

//--------------findPos

template <typename E>
int CBL<E>::findPos(int pos){   //Used to find the corresponding index of positions in the list
    int i = head;
    for(int j = 0; j < pos; j++){
        increment(i);
    }
    return i;


}

//--------------increment

template <typename E>
void CBL<E>::increment(int &index){ //Shifts an index to the "right" in the backing array
    if((unsigned int)index == capacity - 1){
        index = 0;
    }
    else{
        index++;
    }
}

//--------------decrement

template <typename E>
void CBL<E>::decrement(int &index){ //Shifts an index to the "left" in the backing array
    if(index == 0){
        index = capacity - 1;
    }
    else{
        index--;
    }
}


//--------------reduce

template <typename E>
void CBL<E>::reduce(){
    if(length() < capacity / 2 && capacity >= 2 * (unsigned int)originalCap){
        E *temp = new E[(unsigned int)(capacity * 0.75)];
        int curr = head;
        size_t i;
        size_t k = length();
        for(i = 0; i < k; i++){
            temp[i] = data[curr];
            increment(curr);
        }
        capacity = capacity * 0.75;
        head = 0;
        tail = i;
        E *temp2 = data;
        data = temp;
        delete temp2;
    }
}

//---------------testCap-Tests the capacity to make sure it does not violate the condition

template <typename E>
bool CBL<E>::testCap(){
        if(length() < capacity / 2 && capacity >= 2 * (unsigned int)originalCap){
            return false;
        }
        return true;

}


}

#endif // CBL_H
