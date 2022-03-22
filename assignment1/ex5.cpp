#include <iostream>

struct Node
{
    int info;
    Node *pNext;
};

struct LinkedList
{
    Node *head;
    Node *tail;
    int size;
};

LinkedList init(int info)
{
    Node *node = new Node{info, nullptr};
    return {node, node, 1};
}

LinkedList init()
{
    return {nullptr, nullptr, 0};
}

void add(LinkedList &linkedList, int index, int info)
{
    // index out of bound.
    if (index > linkedList.size || index < 0)
    {
        return;
    }
    // if size of list is 0, just init a list with size 1 and assign it to the original list
    if (linkedList.size == 0)
    {
        linkedList = init(info);
        return;
    }
    // if index is 0, assign a new node point to old head node to old head node
    if (index == 0)
    {
        linkedList.head = new Node{info, linkedList.head};
        linkedList.size++;
        return;
    }
    // if index equals to size, add a new node after tail and assign the new node to the tail
    if (index == linkedList.size)
    {
        linkedList.tail->pNext = new Node{info, nullptr};
        linkedList.tail = linkedList.tail->pNext;
        linkedList.size++;
        return;
    }
    // for loop to traverse to the node at the index
    Node *current = linkedList.head, *prevCurrent;
    for (int i = 1; i <= index; i++)
    {
        prevCurrent = current;
        current = current->pNext;
    }
    // add the new node at the (index)th position
    prevCurrent->pNext = new Node{info, current};
    // increment the list size
    linkedList.size++;
}

void addHead(LinkedList &linkedList, int info)
{
    add(linkedList, 0, info);
}

void addTail(LinkedList &linkedList, int info)
{
    add(linkedList, linkedList.size, info);
}

void remove(LinkedList &linkedList, int index)
{
    if (index >= linkedList.size || index < 0)
    {
        return;
    }
    if (index == 0)
    {
        Node *newhead = linkedList.head->pNext;
        delete linkedList.head;
        linkedList.head = newhead;
        linkedList.size--;
        return;
    }
    Node *current = linkedList.head, *prevCurrent;
    for (int i = 1; i <= index; i++)
    {
        prevCurrent = current;
        current = current->pNext;
    }
    prevCurrent->pNext = current->pNext;
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
        current = current->pNext;
    }
    return current;
}

void printOutList(LinkedList linkedList)
{
    Node *current = linkedList.head;
    while (current != nullptr)
    {
        std::cout << current->info << " ";
        current = current->pNext;
    }
    std::cout << "\n";
}

int min(LinkedList linkedList)
{
    int minValue = linkedList.head->info;
    Node *current = linkedList.head;
    while (current != nullptr)
    {
        if (current->info < minValue)
            minValue = current->info;
        current = current->pNext;
    }
    return minValue;
}

int max(LinkedList linkedList)
{
    int maxValue = linkedList.head->info;
    Node *current = linkedList.head;
    while (current != nullptr)
    {
        if (current->info > maxValue)
            maxValue = current->info;
        current = current->pNext;
    }
    return maxValue;
}

LinkedList *seperate(LinkedList linkedList)
{
    LinkedList *result = new LinkedList[2];
    result[0] = init();
    result[1] = init();
    int minValue = min(linkedList);
    int maxValue = max(linkedList);
    int *valueArr = new int[maxValue + 1 - minValue];
    for (int i = 0; i <= maxValue - minValue; i++)
    {
        valueArr[i] = 0;
    }
    Node *current = linkedList.head;
    while (current != nullptr)
    {
        if (current->info % 2 == 0 && valueArr[current->info - minValue] == 0)
        {
            addTail(result[0], current->info);
            valueArr[current->info - minValue]++;
        }
        else if (current->info % 2 != 0 && valueArr[current->info - minValue] == 0)
        {
            addTail(result[1], current->info);
            valueArr[current->info - minValue]++;
        }
        current = current->pNext;
    }
    return result;
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
    LinkedList *result = seperate(linkedList);
    std::cout << "Cac so chan trong danh sach la: ";
    printOutList(result[0]);
    std::cout << "Cac so le trong danh sach la: ";
    printOutList(result[1]);
    return 0;
}
