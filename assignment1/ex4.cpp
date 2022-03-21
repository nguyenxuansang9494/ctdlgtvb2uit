#include <iostream>
#include <math.h>

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

Node *goFrom(LinkedList linkedList, Node *startNode, int step)
{
    Node *destinationNode = startNode;
    while (step != 0 && destinationNode != nullptr)
    {
        destinationNode = destinationNode->next;
        step--;
    }
    return destinationNode;
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

bool isPrime(int number)
{
    if (number <= 1)
        return false;
    for (int i = 2; i < (int)sqrt(number); i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    LinkedList linkedList = init();
    int n;
    while (true)
    {
        std::cin >> n;
        if (n == 0)
            break;
        addTail(linkedList, n);
    }
    if (linkedList.size == 0)
    {
        std::cout << "Danh sach rong.\n";
        return 0;
    }
    std::cout << "Danh sach vua nhap la: ";
    printOutList(linkedList);
    int primeCount = 0;
    Node *currentNode = linkedList.head;
    while (currentNode != nullptr)
    {
        if (isPrime(currentNode->value))
            primeCount++;
        currentNode = goFrom(linkedList, currentNode, 2);
    }
    std::cout << "Danh sach co " << primeCount << " so nguyen to o vi tri le.\n";
    return 0;
}