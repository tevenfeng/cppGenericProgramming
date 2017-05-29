//
// Created by fengdingwen on 17-4-12.
//

#ifndef SIMPLEJSONPARSER_ARRAY_H
#define SIMPLEJSONPARSER_ARRAY_H

#include <vector>
#include <string>

class Value;

using std::string;
using std::vector;

class Array {
    vector<Value> valueVec;
public:
    Value &operator[](int index);

    void pushBack(const Value &val);

    vector<Value>::iterator begin();

    vector<Value>::iterator end();

    void clear();

    bool empty();

    unsigned long size();

    string toJson();
};

#endif //SIMPLEJSONPARSER_ARRAY_H
