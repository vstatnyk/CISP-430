#include <iostream>
#include <fstream>
using namespace std;

struct Node
{
    Node* prev;
    string value;
    Node* next;
};

void addPart(Node *&head, Node *&tail, string value)
{
    if(!head->next && head != tail)
    {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        head = newNode;
        tail = newNode;
    }
    else
    {
        if(head == tail)
        {
            if(value > head->value)
            {
                Node* newNode= new Node;
                newNode->value = value;
                newNode->prev = head;
                newNode->next = nullptr;

                tail->next = newNode;
                tail = newNode;
            }
            else if(value < head->value)
            {
                Node* newNode= new Node;
                newNode->value = value;
                newNode->next = head;
                newNode->prev = nullptr;

                head->next = nullptr; 
                head->prev = newNode;
                tail = head;

                head = newNode;
            }
        }
        else
        {
            for(Node* curr = head; curr != tail; curr = curr->next)
            {
                if(curr->value < value && value < curr->next->value)
                {
                    Node* newNode = new Node;
                    newNode->value = value;
                    newNode->prev = curr;
                    newNode->next = curr->next;

                    curr->next->prev = newNode;
                    curr->next = newNode;
                    return;
                }
            }
            if(value > tail->value)
            {
                Node* newNode= new Node;
                newNode->value = value;
                newNode->prev = tail;
                newNode->next = nullptr;

                tail->next = newNode;
                tail = newNode;
            }
            else if(value < head->value)
            {
                Node* newNode= new Node;
                newNode->value = value;
                newNode->next = head;
                newNode->prev = nullptr;

                head->prev = newNode;
                head = newNode;
            }
        }
    }
};

void deletePart(Node *&head, Node *&tail, string value)
{
    if(head)
    {
        if(head->value == value)
        {
            Node* temp = head;
            head->next->prev = nullptr;
            head = head->next; 
            delete temp;
        }
        else if(tail->value == value)
        {
            Node* temp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev; 
            delete temp;
        }
        else
        {
            for(Node* curr = head->next; curr != tail; curr = curr->next)
            {
                if(curr->value == value)
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    delete curr;
                    return;
                }
                
            }
        }
    }
};

int main()
{
    string temp;
    Node *head = new Node;
    Node *tail = new Node;

    head->next = nullptr;
    tail->prev = nullptr;

    ifstream ifs;
    ifs.open("input.txt");

    ofstream ofs;
    ofs.open("output.txt");

    while(ifs >> temp)
    {
        if(temp == "delete")
        {
            ifs >> temp;
            deletePart(head, tail, temp);
        }
        else
        {
            addPart(head, tail, temp);
        }
    }
    ifs.close();

    //int counter = 1;
    
    for(Node* curr = head; curr != nullptr; curr = curr->next)
    {
        /*cout << "\nprinting Node #: " << counter << '\n';
        cout << "Node " << counter <<" address: " << curr << '\n';
        cout << "Node " << counter <<" value: " << curr->value << '\n';
        cout << "Node " << counter <<" prev: " << curr->prev << '\n';
        cout << "Node " << counter <<" next: " << curr->next << '\n';
        counter ++;*/
        ofs << curr->value << '\n';
    }

    ofs << "=============\n";

    //counter--;

    for(Node* curr = tail; curr != nullptr; curr = curr->prev)
    {
        /*cout << "\nprinting Node #: " << counter << '\n';
        cout << "Node " << counter <<" address: " << curr << '\n';
        cout << "Node " << counter <<" value: " << curr->value << '\n';
        cout << "Node " << counter <<" prev: " << curr->prev << '\n';
        cout << "Node " << counter <<" next: " << curr->next << '\n';
        counter --;*/
        ofs << curr->value << '\n';
    }

    ofs.close();
    return 0;
}
