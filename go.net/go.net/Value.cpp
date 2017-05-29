//
// Created by fengdingwen on 17-4-12.
//

#include "Value.h"

Value::Value() {
}

string &Value::toString() {
    return valueString;
}

float &Value::toFloat() {
    return valueFloat;
}

int &Value::toInt() {
    return valueInt;
}

bool &Value::toBool() {
    return valueBool;
}

Object &Value::toObject() {
    return valueObject;
}

Array &Value::toArray() {
    return valueArray;
}

Value &Value::operator[](const string &key) {
    return this->valueObject[key];
}

Value &Value::operator[](const int &index) {
    return this->valueArray[index];
}

Value &Value::operator=(const string &val) {
    this->valueString = val;
    this->type = STRING;
	return *this;
}

Value &Value::operator=(const float &val) {
    this->valueFloat = val;
    this->type = FLOAT;
	return *this;
}

Value &Value::operator=(const int &val) {
    this->valueInt = val;
    this->type = INT;
	return *this;
}

Value &Value::operator=(const bool &val) {
    this->valueBool = val;
    this->type = BOOL;
	return *this;
}

Value &Value::operator=(const Object &val) {
    this->valueObject = val;
    this->type = OBJECT;
	return *this;
}

Value &Value::operator=(const Array &val) {
    this->valueArray = val;
    this->type = ARRAY;
	return *this;
}

Value &Value::operator=(const char *val) {
    string tmpStr = val;
    this->valueString = val;
    this->type = STRING;
	return *this;
}

string Value::toJson() {
    switch (type) {
        case STRING:
            return "\"" + valueString + "\"";
        case INT:
            return std::to_string(valueInt);
        case FLOAT:
            return std::to_string(valueFloat);
        case BOOL:
            if (valueBool)
                return "true";
            else return "false";
        case ARRAY:
            return valueArray.toJson();
        case OBJECT:
            return valueObject.toJson();
    }
}

ValueType Value::getType() {
    return ValueType();
}

void Value::pushBack(const Value &val) {
    this->valueArray.pushBack(val);
}
