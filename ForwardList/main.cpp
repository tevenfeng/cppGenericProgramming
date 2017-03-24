#include <iostream>
#include "ForwardList.h"

using namespace std;

bool isEven(int a) {
    return a % 2 == 0;
}

bool compare(int a, int b) {
    return a > b;
}

template<typename T>
void traverse(ForwardList<T> list) {
    for (ForwardList<int>::Iterator itr = list.begin; itr != list.end; itr++) {
        cout << *itr << " ";
    }
    cout << endl;
}

int main() {

    ForwardList<int> myList = ForwardList<int>();
    ForwardList<int> myList1 = ForwardList<int>();

    cout << "调用push_front和insert_after初始化两个链表。\n请输入一号链表的五个数：" << endl;
    int a;
    for (int i = 0; i < 5; i++) {
        cin >> a;
        myList.push_front(a);
    }
    cout << "请输入二号链表的五个数：" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> a;
        myList1.insert_after(myList1.begin, a);
    }

    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    cout << "调用pop_front删除一号链表第一个元素后的结果：" << endl;
    myList.pop_front();
    cout << "两个链表情况：" << endl;
    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    cout << "调用erase_after删除二号链表begin迭代器后的元素：" << endl;
    myList1.erase_after(myList1.begin);
    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    cout << "调用remove函数删除一号链表中指定值的某个元素：" << endl;
    cout << "请输入要删除的一号链表中的元素值：";
    cin >> a;
    myList.remove(a);
    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    cout << "调用remove_if删除二号链表中满足特定条件的元素(是偶数)：" << endl;
    myList1.remove_if(isEven);
    myList.remove(a);
    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    cout << "对两个链表都调用sort进行升序排序：" << endl;
    myList.sort(compare);
    myList1.sort(compare);
    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    cout << "调用merge将二号链表合并到一号链表：" << endl;
    myList.merge(myList1);
    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    cout << "对一号链表进行reverse：" << endl;
    myList.reverse();
    cout << "一号链表：";
    traverse(myList);
    cout << "二号链表：";
    traverse(myList1);

    return 0;
}