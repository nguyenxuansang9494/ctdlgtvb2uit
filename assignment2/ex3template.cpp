/*###Begin banned keyword - each of the following line if appear in code will raise error. regex supported
define
include
class
[
]
template

###End banned keyword*/

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Node
{
    int value;
    Node *next;
};

struct LinkedList
{
    Node *head;
    Node *tail;
    int size;
};

LinkedList init(int value)
{
    Node *node = new Node{value, nullptr};
    return {node, node, 1};
}

LinkedList init()
{
    return {nullptr, nullptr, 0};
}

void add(LinkedList &linkedList, int index, int value)
{
    // index out of bound.
    if (index > linkedList.size || index < 0)
    {
        return;
    }
    // if size of list is 0, just init a list with size 1 and assign it to the original list
    if (linkedList.size == 0)
    {
        linkedList = init(value);
        return;
    }
    // if index is 0, assign a new node point to old head node to old head node
    if (index == 0)
    {
        linkedList.head = new Node{value, linkedList.head};
        linkedList.size++;
        return;
    }
    // if index equals to size, add a new node after tail and assign the new node to the tail
    if (index == linkedList.size)
    {
        linkedList.tail->next = new Node{value, nullptr};
        linkedList.tail = linkedList.tail->next;
        linkedList.size++;
        return;
    }
    // for loop to traverse to the node at the index
    Node *current = linkedList.head;
    for (int i = 1; i < index; i++)
    {
        current = current->next;
    }
    // add the new node at the (index)th position
    current->next = new Node{value, current->next};
    // increment the list size
    linkedList.size++;
}

void addHead(LinkedList &linkedList, int value)
{
    add(linkedList, 0, value);
}

void addTail(LinkedList &linkedList, int value)
{
    add(linkedList, linkedList.size, value);
}

void remove(LinkedList &linkedList, int index)
{
    if (index >= linkedList.size || index < 0)
    {
        return;
    }
    if (index == 0)
    {
        Node *newhead = linkedList.head->next;
        delete linkedList.head;
        linkedList.head = newhead;
        linkedList.size--;
        return;
    }
    Node *current = linkedList.head, *prevCurrent;
    for (int i = 1; i <= index; i++)
    {
        prevCurrent = current;
        current = current->next;
    }
    prevCurrent->next = current->next;
    if (index == linkedList.size - 1)
    {
        linkedList.tail = prevCurrent;
    }
    delete current;
    linkedList.size--;
}

Node *get(LinkedList linkedList, int index)
{
    if (index < 0 || index >= linkedList.size)
    {
        return nullptr;
    }
    Node *current = linkedList.head;
    for (int i = 1; i <= index; i++)
    {
        current = current->next;
    }
    return current;
}

void removeAll(LinkedList &linkedList, int value)
{
    Node *cur = linkedList.head;
    while (cur != nullptr)
    {
        if (cur->value == value && cur == linkedList.head)
        {
            if (linkedList.tail == cur)
                linkedList.tail = nullptr;
            Node *temp = cur;
            cur = cur->next;
            linkedList.head = cur;
            delete temp;
            linkedList.size--;
            continue;
        }
        if (cur->next != nullptr && cur->next->value == value)
        {
            if (cur->next == linkedList.tail)
                linkedList.tail = cur;
            Node *temp = cur->next;
            cur->next = temp->next;
            delete temp;
            linkedList.size--;
        }
        if (cur->next == nullptr || cur->next->value != value)
            cur = cur->next;
    }
}

int find(LinkedList linkedList, int value)
{
    Node *current = linkedList.head;
    int index = 0;
    while (current != nullptr)
    {
        if (current->value == value)
        {
            return index;
        }
        index++;
        current = current->next;
    }
    return -1;
}

void printOutList(LinkedList linkedList)
{
    Node *current = linkedList.head;
    while (current != nullptr)
    {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void reversePrintOutList(Node *node)
{
    if (node->next != nullptr)
    {
        reversePrintOutList(node->next);
    }
    std::cout << node->value << " ";
}

int main(int argc, char const *argv[])
{
    LinkedList linkedList = init();
    int n;
    int value;
    while (true)
    {
        std::cin >> n;
        if (n == 0)
            break;
        addTail(linkedList, n);
    }
    std::cin >> value;
    if (linkedList.size == 0)
    {
        std::cout << "Danh sach rong.\n";
        return 0;
    }
    int index = find(linkedList, value);
    if (index == -1)
    {
        std::cout << "Khong tim thay " << value << " trong danh sach:\n";
        printOutList(linkedList);
        return 0;
    }
    removeAll(linkedList, value);
    if (linkedList.size == 0)
    {
        std::cout << "Danh sach rong.\n";
        return 0;
    }
    printOutList(linkedList);
    return 0;
}
