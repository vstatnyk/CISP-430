#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

void append(Node*& head, int value)
{
    if(!head)
    {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        head = newNode;
    }
    else
    {   
        for(Node* curr = head; curr != nullptr; curr = curr->next)
        {
            if(!curr->next)
            {
                Node* newNode = new Node;
                newNode->value = value;
                newNode->next = nullptr;
                curr->next = newNode;
                break;
            }
        }
        Node* curr = head;
    }
}

void split (Node* head, Node*& a,Node*& b)
{
    int length = 0,
        counter = 0;

    for(Node* curr = head; curr != nullptr; curr = curr->next)
    {
        length ++;
    }
    
    for(Node* curr = head; curr != nullptr; curr = curr->next)
    {
        if (counter < length/2)
        {
            append(a, curr->value);
        }
        else
        {
            append(b, curr->value);
        }
        counter ++;
    }
};

Node* merge(Node* a, Node* b)
{   
    Node* fin = NULL;
    while(a && b)
    {   
        if(a->value <= b->value)
        {   
            append(fin, a->value);
            a = a->next;
        }
        else
        {
            append(fin, b->value);
            b = b->next;
        }
    }
    if(!a)
    {
        while(b)
        {
            append(fin, b->value);
            b = b->next;
        }
    }
    if(!b)
    {
        while(a)
        {
            append(fin, a->value);
            a = a->next;
        }
    }
    return(fin);
};

Node* mergeSort( Node* head)
{
    if(!head){return head;} 
    if(!head->next){return head;}

    Node *headLeft = nullptr;
    Node *headRight = nullptr;

    split(head, headLeft, headRight);

    headLeft = mergeSort(headLeft);
    headRight = mergeSort(headRight);
    
    Node*  leftRight = merge(headLeft, headRight);
    return (leftRight);
};


int main()
{
    const int ARRAY_SIZE = 27;
    int numbersToSort[ARRAY_SIZE] = {1, 23, 57, 43, 67, 343, 56, 65, 4556, 3, 674, 6, 3456, 7, 5, 87, 8, 89, 45, 8765, 854, 788, 95, 4, 556, 764, 21};
    Node *head = nullptr;

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        append(head, numbersToSort[i]);
    }

    cout << "Original list\n";
    cout << '[' << head->value;
    for(Node* curr = head->next; curr != nullptr; curr = curr->next)
    {
        cout <<", " << curr->value;
    }
    cout << ']';

    head = mergeSort(head);

    cout << "\nSorted list\n";
    cout << '[' << head->value;
    for(Node* curr = head->next; curr != nullptr; curr = curr->next)
    {
        cout <<", " << curr->value;
    }
    cout << ']';

    return 0;
}
