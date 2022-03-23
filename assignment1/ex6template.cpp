#include <iostream>
using namespace std;
struct node
{
    int info;
    node *pNext;
};
struct List
{
    node *pHead;
    node *pTail;
};
void CreateList(List &l)
{
    l.pHead = NULL;
    l.pTail = NULL;
}
void ReverseList(List &l);

void xuat(List list)
{
    while (list.pHead != NULL)
    {
        cout << list.pHead->info << ' ';
        list.pHead = list.pHead->pNext;
    }
    cout << '\n';
}

void nhap(List &l)
{
    int n = 0;
    cin >> n;
    while (n != 0)
    {
        if (l.pHead == NULL)
        {
            node *nnode = new node{n, NULL};
            l.pHead = nnode;
            l.pTail = nnode;
        }
        else
        {
            l.pTail->pNext = new node{n, NULL};
            l.pTail = l.pTail->pNext;
        }
        cin >> n;
    }
}

void ReverseList(List &l)
{
    node *prevCur, *cur, *nextCur;
    prevCur = l.pHead;
    cur = prevCur->pNext;
    if (cur == NULL)
        return;
    nextCur = cur->pNext;
    if (nextCur == NULL)
    {
        cur->pNext = prevCur;
        prevCur->pNext = NULL;
        l.pHead = cur;
        l.pTail = prevCur;
        return;
    }
    prevCur->pNext = NULL;
    while (cur != NULL)
    {
        cur->pNext = prevCur;
        prevCur = cur;
        cur = nextCur;
        if (nextCur != NULL)
            nextCur = nextCur->pNext;
    }
    node *nhead = l.pTail;
    node *ntail = l.pHead;
    l.pHead = nhead;
    l.pTail = ntail;
}
//###INSERT CODE HERE -

int main()
{
    List l;
    CreateList(l);
    nhap(l);
    if (l.pHead == NULL)
        cout << "Danh sach rong.";
    else
    {
        cout << "Danh sach vua nhap la: ";
        xuat(l);
        ReverseList(l);
        cout << endl
             << "Danh sach sau khi dao nguoc la: ";
        xuat(l);
    }
    return 0;
}
