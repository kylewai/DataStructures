#ifndef BOUNDED_DEQUEUE_H
#define BOUNDED_DEQUEUE_H
#include <stdexcept>

//*************Bounded_Dequeue.h

template <typename E>
class Bounded_Dequeue{

    public:
        Bounded_Dequeue(int dequeue_size);
        void push_front(E element);
        void push_back(E element);
        E pop_front();
        E pop_back();
        E peek_front();
        E peek_back();
        int length();
        bool is_empty();
        bool is_full();
        void clear();
        void decrement(int &index);
        void increment(int &index);
        ~Bounded_Dequeue();


    private:
        int dequeue_size;
        int head;
        int tail;
        E *dequeue;
};

//-------------constructor

template <typename E>
Bounded_Dequeue<E>::Bounded_Dequeue(int dequeue_size){
    this->dequeue_size = dequeue_size + 1;
    head = 0;
    tail = 0;
    dequeue = new E[this->dequeue_size];
}

//-------------push_front- If it is the first added element, head is not incremented but tail is. This is done
// to maintain the condition that head == tail implies is_empty;

template <typename E>
void Bounded_Dequeue<E>::push_front(E element){
    if(is_full()){
        throw std::runtime_error("Error in Bounded_Queue<E>:: push_front(E element): Full dequeue");
    }
    if(is_empty()){
        dequeue[head] = element;
        increment(tail);
        return;
    }
    decrement(head);
    dequeue[head] = element;

}

//-------------push_back

template <typename E>
void Bounded_Dequeue<E>::push_back(E element){
    if(is_full()){
        throw std::runtime_error("Error in Bounded_Queue<E>:: push_back(E element): Full dequeue");
    }
    dequeue[tail] = element;
    increment(tail);
}

//-------------pop_front

template <typename E>
E Bounded_Dequeue<E>::pop_front(){
    if(is_empty()){
        throw std::runtime_error("Error in Bounded_Dequeue<E>:: pop_front(): Empty dequeue");
    }
    int temp = head;
    increment(head);
    return dequeue[temp];
}

//-------------pop_back

template <typename E>
E Bounded_Dequeue<E>::pop_back(){
    if(is_empty()){
        throw std::runtime_error("Error in Bounded_Dequeue<E>:: pop_back(): Empty dequeue");
    }
    decrement(tail);
    return dequeue[tail];
}

//-------------peek_front

template <typename E>
E Bounded_Dequeue<E>::peek_front(){
    if(is_empty()){
        throw std::runtime_error("Error in Bounded_Dequeue:: peek_front(): Empty dequeue");
    }
    return dequeue[head];
}

//-------------peek_back

template <typename E>
E Bounded_Dequeue<E>::peek_back(){
    if(is_empty()){
        throw std::runtime_error("Error in Bounded_Dequeue:: peek_back(): Empty dequeue");
    }
    if(tail == 0){
        return dequeue[dequeue_size - 1];
    }
    return dequeue[tail - 1];
}

//-------------length

template <typename E>
int Bounded_Dequeue<E>::length(){
    if(tail > head){
        return tail - head;
    }
    else if(head > tail){
        return tail + (dequeue_size - head);
    }
    else{
        return 0;
    }
}

//-------------is_empty

template <typename E>
bool Bounded_Dequeue<E>::is_empty(){
    return head == tail;
}

//-------------is_full

template <typename E>
bool Bounded_Dequeue<E>::is_full(){
    return length() == dequeue_size - 1;
}

//-------------clear

template <typename E>
void Bounded_Dequeue<E>::clear(){
    head = 0;
    tail = 0;
}

//-------------decrement: decrements either head or tail

template <typename E>
void Bounded_Dequeue<E>::decrement(int &index){
    if(index == 0){
        index = dequeue_size - 1;
    }
    else{
        index--;
    }
}

//-------------increment: increments either head or tail

template <typename E>
void Bounded_Dequeue<E>::increment(int &index){
    if(index == dequeue_size - 1){
        index = 0;
    }
    else{
        index++;
    }
}

//-------------destructor

template <typename E>
Bounded_Dequeue<E>::~Bounded_Dequeue(){
    delete[] dequeue;
}


#endif // BOUNDED_DEQUEUE_H
