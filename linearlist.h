#ifndef DUCKDODGERS_LINEARLIST_H
#define DUCKDODGERS_LINEARLIST_H

#include <cstdint>

template <typename ListType>
struct ListNode {
    ListType
            datum;
    ListNode<ListType>
            *next;
};

template <typename ListType>
class LinearList {
public:
    LinearList();
    LinearList(const LinearList<ListType> &); // copy constructor
    ~LinearList();

    uint32_t size();
    bool isEmpty();

    void clear();

    uint32_t search(const ListType &);
    ListType &operator[](int32_t);

    void map(void (*)(ListType &));

    void insert(uint32_t,const ListType &);
    void remove(uint32_t);
private:
    ListNode<ListType>
            *head;
    uint32_t
            count;
};

#include "linearlist-implementation.h"

#endif //DUCKDODGERS_LINEARLIST_H
