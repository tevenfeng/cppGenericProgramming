//
// Created by fengdingwen on 17-4-12.
//

#ifndef SIMPLEJSONPARSER_VALUETYPE_H
#define SIMPLEJSONPARSER_VALUETYPE_H


enum ValueType {
    INT,        // JSON's int
    FLOAT,      // JSON's float 3.14 12e-10
    BOOL,       // JSON's boolean (true, false)
    STRING,     // JSON's string " ... "
    OBJECT,     // JSON's object { ... }
    ARRAY,      // JSON's array [ ... ]
    NIL         // JSON's null
};


#endif //SIMPLEJSONPARSER_VALUETYPE_H
