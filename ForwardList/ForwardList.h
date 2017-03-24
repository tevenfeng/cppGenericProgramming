//
// Created by fengdingwen on 17-3-19.
//

#ifndef FORWARDLIST_FORWARDLIST_H
#define FORWARDLIST_FORWARDLIST_H


#include "ForwardListNode.h"

template<typename T>
class ForwardList {
private:
    int list_size;
    ForwardListNode<T> *head = nullptr, *tail = nullptr;

    void swap(ForwardListNode<T> *first, ForwardListNode<T> *sec) {
        T tmp;
        tmp = sec->data;
        sec->data = first->data;
        first->data = tmp;
    }

public:
    class Iterator {
        friend class ForwardList;

    private:
        ForwardListNode<T> *p;
    public:
        Iterator(ForwardListNode<T> *q) {
            p = q;
        }

        T &operator*() {
            return p->data;
        }

        Iterator &operator++() {
            p = p->next;
            return *this;
        }

        Iterator &operator++(int) {
            Iterator tmp = *this;
            p = p->next;
            return tmp;
        }

        bool operator==(Iterator latter) {
            return this->p == latter.p;
        }

        bool operator!=(Iterator latter) {
            return this->p != latter.p;
        }
    };

    Iterator begin = Iterator(nullptr), end = Iterator(nullptr);

    ForwardList() {
        this->list_size = 0;
    }

    // 在链表前端插入value
    void push_front(T value) {
        ForwardListNode<T> *tmp = new ForwardListNode<T>();
        tmp->data = value;
        tmp->next = head;
        head = tmp;

        begin = Iterator(head);
        this->list_size++;
    }

    // 取出并删除链表第一个元素
    T pop_front() {
        if (this->list_size > 0) {
            T tmp = head->data;
            head = head->next;
            this->list_size--;
            begin = Iterator(head);
            return tmp;
        }
    }

    // 在指定迭代器后插入给定元素
    bool insert_after(Iterator pos, T valueToInsert) {
        ForwardListNode<T> *tmpNode = new ForwardListNode<T>();
        tmpNode->data = valueToInsert;
        if (pos.p != nullptr) {
            tmpNode->next = pos.p->next;
            pos.p->next = tmpNode;
            this->list_size++;
        } else {
            if (this->head == nullptr) {
                this->head = tmpNode;
                this->begin = Iterator(head);
                tmpNode->next = nullptr;
                this->list_size++;
            } else {
                return false;
            }
        }

        return true;
    }

    // 删除指定迭代器后的所有元素
    void erase_after(Iterator pos) {
        if (pos.p->next != nullptr) {
            ForwardListNode<T> *tmp = pos.p->next;
            pos.p->next = pos.p->next->next;
            this->list_size--;
            delete tmp;
        }
    }

    // 获取当前链表的元素个数
    int size() {
        return list_size;
    }

    // 清空链表
    void clear() {
        this->list_size = 0;
        head = nullptr;
        begin = end = Iterator(nullptr);
    }

    // 当前链表是否为空
    bool empty() {
        return this->list_size == 0;
    }

    // 删除某个元素
    void remove(T valueToRemove) {
        ForwardListNode<T> *before = head;
        ForwardListNode<T> *current = head;
        while (current != nullptr && current->data != valueToRemove) {
            before = current;
            current = current->next;
        }
        if (current != nullptr) {
            before->next = current->next;
            if (current == head) {
                head = current->next;
                begin = Iterator(head);
            }
            if (current == tail) {
                tail = before;
                end = Iterator(tail);
            }
            this->list_size--;
            delete current;
        }
    }

    // 删除满足特定条件的元素
    template<typename UnaryPredicate>
    void remove_if(UnaryPredicate iffunction) {
        ForwardListNode<T> *before = head;
        ForwardListNode<T> *current = head;

        while (current != nullptr) {             // 是否到达最后一个
            if (iffunction(current->data)) {     // 是否满足谓词逻辑的条件
                if (current == head) {
                    // 如果current是第一个节点则删除并
                    // 将head、current、before均向后移动一次，同时刷新begin
                    head = current->next;
                    delete current;
                    current = head;
                    this->list_size--;
                    before = head;
                    begin = Iterator(head);
                } else {
                    // 若current不是第一个，则此时before已经指向current的前一个节点，
                    // 此时只需要讲current正常删除即可
                    before->next = current->next;
                    delete current;
                    current = before->next;
                    this->list_size--;
                }
            } else {
                // current不满足谓词条件，直接跳过
                before = current;
                current = current->next;
            }
        }
    }

    // 链表翻转
    void reverse() {
        ForwardListNode<T> *current, *before;
        current = before = tail = head;
        current = current->next;
        while (current != nullptr) {
            before = current;
            current = current->next;
            before->next = head;
            head = before;
        }

        // 由于刚开始将tail等于了第一个元素（翻转后的最后一个），
        // 因此此时需要将tail置为nullptr
        tail->next = nullptr;
        tail = tail->next;
        begin = Iterator(head);
        end = Iterator(tail);
    }

    // 两个链表合并
    // 这两个链表要求为升序
    void merge(ForwardList<T> other) {
        ForwardListNode<T> *first = this->head;
        ForwardListNode<T> *second = other.head;
        ForwardListNode<T> *newHead = nullptr;
        ForwardListNode<T> *tmp = new ForwardListNode<T>();

        if (second == nullptr) {
            return;
        }

        if (first == nullptr) {
            newHead = second;
            begin = Iterator(newHead);
            list_size = other.list_size;
            return;
        }

        if (first->data < second->data) {
            newHead = this->head;
            first = first->next;
            tmp = newHead;
        } else {
            newHead = other.head;
            second = second->next;
            tmp = newHead;
        }

        while (first != nullptr && second != nullptr) {
            if (first->data < second->data) {
                tmp->next = first;
                tmp = tmp->next;
                first = first->next;
            } else {
                tmp->next = second;
                tmp = tmp->next;
                second = second->next;
            }
        }
        if (first != nullptr)
            tmp->next = first;
        if (second != nullptr)
            tmp->next = second;

        this->head = newHead;
        this->begin = Iterator(this->head);
        this->list_size = this->list_size + other.list_size;
    }

    // 选择排序
    template<typename BinaryPredicate>
    void sort(BinaryPredicate iffunction) {
        if (head != nullptr && head->next != nullptr) {
            ForwardListNode<T> *startNode = new ForwardListNode<T>();
            startNode->data = 0;
            startNode->next = head;
            ForwardListNode<T> *tailAfterSort = startNode;

            while (tailAfterSort->next != nullptr) {
                ForwardListNode<T> *minNode = tailAfterSort->next, *p = tailAfterSort->next->next;
                while (p != nullptr) {
                    if (p->data < minNode->data)
                        minNode = p;
                    p = p->next;
                }
                swap(minNode, tailAfterSort->next);
                tailAfterSort = tailAfterSort->next;
            }

            head = startNode->next;
            this->begin = Iterator(this->head);
            delete startNode;
        }
    }
};


#endif //FORWARDLIST_FORWARDLIST_H
