//
// Created by fengdingwen on 17-4-12.
//

#ifndef SIMPLEJSONPARSER_JSONPARSER_H
#define SIMPLEJSONPARSER_JSONPARSER_H

#include <string>
#include "Value.h"
#include "Object.h"

class JsonParser {
    void readChar(string str, int &index, char target) {
        while (str[index] != target) {
            ++index;
        }
        ++index;
    }

public:
    Object readObject(const string &str, int &p) {
        Object obj;
        readChar(str, p, '{');
        while (1) {
            if (str[p] == '}') {
                readChar(str, p, '}');
                break;
            }

            string key = readString(str, p);
            readChar(str, p, ':');
            Value val = readValue(str, p);
            // insert key:val to obj.
            obj[key] = val;

            if (str[p] == '}') {
                readChar(str, p, '}');
                break;
            } else {
                readChar(str, p, ',');
            }
        }
        return obj;
    }

    Value readValue(const string &str, int &p) {
        Value val;
        if (str[p] == '{') {
            val = readObject(str, p);
        } else if (str[p] == '\"') {
            val = readString(str, p);
        } else if (str[p] == '[') {
            val = readArray(str, p);
        } else if (str[p] == 't' || str[p] == 'f') {
            val = readBool(str, p);
        } else if (str[p] == '-' || isdigit(str[p])) {
            val = readNumber(str, p);
        }
        return val;
    }

    Array readArray(const string &str, int &p) {
        Array arr;
        readChar(str, p, '[');
        while (1) {
            if (str[p] == ']') {
                readChar(str, p, ']');
                break;
            }

            Value tmp = readValue(str, p);
            arr.pushBack(tmp);

            if (str[p] == ']') {
                readChar(str, p, ']');
                break;
            } else {
                readChar(str, p, ',');
            }
        }
        return arr;
    }

    string readString(const string &str, int &p) {
        readChar(str, p, '\"');

        string tmpStr = "";
        while (str[p] != '\"') {
            tmpStr.append(1, str[p]);
            readChar(str, p, str[p]);
        }
        readChar(str, p, '\"');

        return tmpStr;
    }

    bool readBool(const string &str, int &p) {
        if (str[p] == 't') {
            readChar(str, p, 'e');
            return true;
        } else {
            readChar(str, p, 'e');
            return false;
        }
    }

    Value readNumber(const string &str, int &p) {
        Value tmpValue;

        bool isPositive = true;
        if (str[p] == '-') {
            isPositive = false;
            readChar(str, p, '-');
        }

        string tmpStr = "";
        bool isDouble = false;
        while (str[p] == '.' || isdigit(str[p])) {
            tmpStr.append(1, str[p]);
            if (str[p] == '.') {
                isDouble = true;
            }
            p++;
        }
        if (isDouble) {
            float tmpFloat = atof((char *) tmpStr.c_str());
            if (!isPositive) {
                tmpFloat = 0 - tmpFloat;
            }
            tmpValue = Value(tmpFloat);
        } else {
            int tmpInt = atoi((char *) tmpStr.c_str());
            if (!isPositive) {
                tmpInt = 0 - tmpInt;
            }
            tmpValue = Value(tmpInt);
        }

        return tmpValue;
    }
};


#endif //SIMPLEJSONPARSER_JSONPARSER_H
