//
// Created by fengdingwen on 17-3-19.
//

#ifndef FORWARDLIST_FORWARDLISTNODE_H
#define FORWARDLIST_FORWARDLISTNODE_H

template <typename T>
class ForwardListNode {
public:
    T data;
    ForwardListNode<T> *next;
};


#endif //FORWARDLIST_FORWARDLISTNODE_H
