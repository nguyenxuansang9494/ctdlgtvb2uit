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

//###INSERT CODE HERE -

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

int min(LinkedList linkedList)
{
    int minValue = linkedList.head->value;
    Node *current = linkedList.head;
    while (current != nullptr)
    {
        if (current->value < minValue)
            minValue = current->value;
        current = current->next;
    }
    return minValue;
}

int max(LinkedList linkedList)
{
    int maxValue = linkedList.head->value;
    Node *current = linkedList.head;
    while (current != nullptr)
    {
        if (current->value > maxValue)
            maxValue = current->value;
        current = current->next;
    }
    return maxValue;
}

int *count(LinkedList linkedList, int &maxEncounter)
{
    int minValue = min(linkedList);
    int maxValue = max(linkedList);
    int *result = (int *)malloc((maxValue + 1 - minValue) * sizeof(int));
    for (int i = 0; i <= maxValue; i++)
    {
        *(result + i) = 0;
    }
    Node *currentNode = linkedList.head;
    while (currentNode != nullptr)
    {
        *(result + currentNode->value - minValue) += 1;
        if (*(result + currentNode->value - minValue) > maxEncounter)
            maxEncounter = *(result + currentNode->value - minValue);
        currentNode = currentNode->next;
    }
    return result;
}

void reversePrintOutList(Node *node)
{
    if (node->next != nullptr)
    {
        reversePrintOutList(node->next);
    }
    std::cout << node->value << " ";
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
    int n;
    while (true)
    {
        std::cin >> n;
        if (n == 0)
            break;
        addHead(linkedList, n);
    }
    if (linkedList.size == 0)
    {
        std::cout << "Danh sach rong.\n";
        return 0;
    }
    printOutList(linkedList);
    int maxEncounter = 0;
    int *countArr = count(linkedList, maxEncounter);
    Node *currentNode = linkedList.head;
    int minValue = min(linkedList);
    while (currentNode != nullptr)
    {
        if (*(countArr + currentNode->value - minValue) == maxEncounter)
        {
            std::cout << currentNode->value << ": " << *(countArr + currentNode->value - minValue) << '\n';
            *(countArr + currentNode->value - minValue) = 0;
        }
        currentNode = currentNode->next;
    }
}
