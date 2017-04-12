//
// Created by fengdingwen on 17-4-12.
//

#include "Value.h"

Value::Value() {
}

string &Value::toString() {
}

float &Value::toFloat() {
}

int &Value::toInt() {
}

bool &Value::toBool() {
}

Object &Value::toObject() {
}

Array &Value::toArray() {
}

Value &Value::operator=(const string &val) {
}

Value &Value::operator=(const float &val) {
}

Value &Value::operator=(const int &val) {
}

Value &Value::operator=(const bool &val) {
}

Value &Value::operator=(const Object &val) {
}

Value &Value::operator=(const Array &val) {
}

string Value::toJson() {
    return string();
}

ValueType Value::getType() {
    return ValueType();
}
