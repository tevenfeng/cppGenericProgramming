//
// Created by fengdingwen on 17-4-12.
//

#include "Value.h"

Value &Object::operator[](const string &key) {
    return this->objMap[key];
}

unsigned long Object::size() const {
    return this->objMap.size();
}

string Object::toJson() {
    string tmpStr = "{";
    for (auto itr = begin(); itr != end(); ++itr) {
        tmpStr = tmpStr + "\"" + itr->first + "\"" + ":" + itr->second.toJson() + ",";
    }
    tmpStr.erase(tmpStr.length() - 1);
    tmpStr += "}";

    return tmpStr;
}

void Object::insert(const string &key, const Value &val) {
    this->objMap.insert(pair<string, Value>(key, val));
}

void Object::erase(const string &key) {
    this->objMap.erase(key);
}

map<string, Value>::iterator Object::begin() {
    return this->objMap.begin();
}

map<string, Value>::iterator Object::end() {
    return this->objMap.end();
}

void Object::clear() {
    this->objMap.clear();
}

bool Object::empty() {
    return this->size() == 0;
}

Value Object::find(const string &key) {
    return this->objMap.find(key)->second;
}
