#include <iostream>

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
    Node *current = linkedList.head, *prevCurrent;
    for (int i = 1; i <= index; i++)
    {
        prevCurrent = current;
        current = current->next;
    }
    // add the new node at the (index)th position
    prevCurrent->next = new Node{value, current};
    if (index == linkedList.size)
    {
        linkedList.tail = linkedList.tail->next;
    }
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

int main(int argc, char const *argv[])
{
    LinkedList linkedList = init();
    addTail(linkedList, 10);
    addTail(linkedList, 20);
    addHead(linkedList, 30);
    add(linkedList, 3, 40);
    add(linkedList, 1, 100);
    printOutList(linkedList);
    remove(linkedList, 1);
    printOutList(linkedList);
    remove(linkedList, 0);
    printOutList(linkedList);
    remove(linkedList, linkedList.size - 1);
    printOutList(linkedList);
    return 0;
}
