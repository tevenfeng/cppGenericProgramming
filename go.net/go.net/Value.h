//
// Created by fengdingwen on 17-4-12.
//

#ifndef SIMPLEJSONPARSER_VALUE_H
#define SIMPLEJSONPARSER_VALUE_H

#include <string>
#include "ValueType.h"
#include "Array.h"
#include "Object.h"

using std::string;

class Value {
    string valueString;
    float valueFloat;
    int valueInt;
    bool valueBool;
    Object valueObject;
    Array valueArray;
    ValueType type;
public:
    Value &operator[](const string &key);

    Value &operator[](const int &index);

    Value();

    Value(char *v) : valueString(v), type(STRING) {};

    Value(string v) : valueString(v), type(STRING) {};

    Value(float v) : valueFloat(v), type(FLOAT) {};

    Value(int v) : valueInt(v), type(INT) {};

    Value(bool v) : valueBool(v), type(BOOL) {};

    Value(Object v) : valueObject(v), type(OBJECT) {};

    Value(Array v) : valueArray(v), type(ARRAY) {};

    string &toString();

    float &toFloat();

    int &toInt();

    bool &toBool();

    Object &toObject();

    Array &toArray();

    Value &operator=(const string &val);

    Value &operator=(const char *val);

    Value &operator=(const float &val);

    Value &operator=(const int &val);

    Value &operator=(const bool &val);

    Value &operator=(const Object &val);

    Value &operator=(const Array &val);

    string toJson();

    ValueType getType();

    void pushBack(const Value &val);
};


#endif //SIMPLEJSONPARSER_VALUE_H
