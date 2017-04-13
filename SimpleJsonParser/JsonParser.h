//
// Created by fengdingwen on 17-4-12.
//

#ifndef SIMPLEJSONPARSER_JSONPARSER_H
#define SIMPLEJSONPARSER_JSONPARSER_H

#include <string>
#include "Value.h"
#include "Object.h"

class JsonParser {
    void readChar(string str, int &index, char target);

    Value readValue(const string &str, int &p);

    Array readArray(const string &str, int &p);

    string readString(const string &str, int &p);

    bool readBool(const string &str, int &p);

    Value readNumber(const string &str, int &p);

public:
    Object readObject(const string &str, int &p);
};


#endif //SIMPLEJSONPARSER_JSONPARSER_H
