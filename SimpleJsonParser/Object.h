//
// Created by fengdingwen on 17-4-12.
//

#ifndef SIMPLEJSONPARSER_OBJECT_H
#define SIMPLEJSONPARSER_OBJECT_H

#include <string>
#include <map>

using std::map;
using std::string;

class Value;

class Object {
    map<string, Value> obj_map;
public:
    Value &operator[](const string &key);

    int size() const;

    string toJson();
};


#endif //SIMPLEJSONPARSER_OBJECT_H
