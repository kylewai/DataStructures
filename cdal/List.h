#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <string>

namespace cop3530{
template <typename E>
class List
{
    public:
        virtual void insert(E element, int position) = 0;
        virtual void push_back(E element) = 0;
        virtual void push_front(E element) = 0;
        virtual E replace(E element, int position) = 0;
        virtual E remove(int position) = 0;
        virtual E pop_back() = 0;
        virtual E pop_front() = 0;
        virtual E& item_at(int position) = 0;
        virtual E& peek_back() = 0;
        virtual E& peek_front() = 0;
        virtual bool is_empty() = 0;
        virtual bool is_full() = 0;
        virtual size_t length() = 0;
        virtual void clear() = 0;
        virtual bool contains(E element, bool (*equals_function)(const E &element, const E &element2)) = 0;
        virtual std::ostream& print(std::ostream& stream) = 0;
        virtual E* contents() = 0;

        virtual ~List(){};
};
}

#endif // LIST_H
