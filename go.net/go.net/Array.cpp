//
// Created by fengdingwen on 17-4-12.
//

#include "Value.h"

Value &Array::operator[](int index) {
    return valueVec[index];
}

void Array::pushBack(const Value &val) {
    this->valueVec.push_back(val);
}

string Array::toJson() {
    string tmpStr = "[";
    for (auto itr = valueVec.begin(); itr != valueVec.end(); ++itr) {
        tmpStr += itr->toJson();
        tmpStr += ",";
    }
    tmpStr.erase(tmpStr.length() - 1);
    tmpStr += "]";
    return tmpStr;
}

vector<Value>::iterator Array::begin() {
    return this->valueVec.begin();
}

vector<Value>::iterator Array::end() {
    return this->valueVec.end();
}

void Array::clear() {
    this->valueVec.clear();
}

bool Array::empty() {
    return this->size() == 0;
}

unsigned long Array::size() {
    return this->valueVec.size();
}
