#include <iostream>
#include "Array.h"
#include "Object.h"
#include "JsonParser.h"

using namespace std;


int main() {

    Object obj;
    obj["title"] = "Thinking in C++";
    obj["price"] = 116.0f;
    obj["pages"] = 927;
    obj["authors"] = Array();
    obj["authors"].pushBack("Bruce Eckel");
    obj["authors"].pushBack("Chuck Allison");
    obj["pub_info"] = Object();
    obj["pub_info"]["name"] = "China Machine Press";

    cout << obj.toJson() << endl;

    JsonParser myParser = JsonParser();
    int p = 0;
    Object tmp = myParser.readObject(obj.toJson(), p);

    cout << "将上述结果作为输入，转化为Object后再次输出结果为：" << endl << tmp.toJson() << endl;

    return 0;
}