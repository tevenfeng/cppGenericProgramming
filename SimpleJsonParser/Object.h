//
// Created by fengdingwen on 17-4-12.
//

#ifndef SIMPLEJSONPARSER_OBJECT_H
#define SIMPLEJSONPARSER_OBJECT_H

#include <string>
#include <map>

using std::map;
using std::string;
using std::pair;

class Value;

class Object {
    map<string, Value> objMap;
public:
    Value &operator[](const string &key);

    unsigned long size() const;

    Value find(const string &key);

    void insert(const string &key, const Value &val);

    void erase(const string &key);

    map<string, Value>::iterator begin();

    map<string, Value>::iterator end();

    void clear();

    bool empty();

    string toJson();
};


#endif //SIMPLEJSONPARSER_OBJECT_H
