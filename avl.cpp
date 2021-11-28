#include <iostream>
#include <fstream>
using namespace std;

// avl functions
struct node
{
    int key;
    struct node* left;
    struct node* right;
    int height;
};

int height(node *node)
{   
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        return(node->height);
    }

}

node *newNode(int key)
{
    struct node* nn = new node;
    nn->key = key;
    nn->height = 0;
    nn->left = NULL;
    nn->right = NULL;
    return nn;
} 

int getBalance(node *node)
{
    int leftHeight = -1;
    int rightHeight = -1;
    if (node->left != NULL)
    {
        leftHeight = node->left->height;
    }
    if(node->right != NULL)
    {
        rightHeight = node->right->height;
    }
    return(leftHeight - rightHeight);
}

node *leftRotate(node *x)
{
    struct node *y = x->right;
    //add more code to rotate to the left, update heights for x and y
    x->right = y->left;
    y->left = x;    
    x->height = max(height(x->left), height(x->right)) + 1; 
    y->height = max(height(y->left), height(y->right)) + 1;
    return(y);
}

node *rightRotate(node *x)
{
    struct node *y=x->left;
    //add more code to rotate to the right, update heights for x and y
    x->left = y->right;
    y->right = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return(y);
}

node *rebalance(node *node)
{    
    node->height = max(height(node->left), height(node->right)) + 1;    
    int balance = getBalance(node);  //node->left - node->right
    int rightBalance = 0;
    int leftBalance = 0;
    
    if(node->right)
    {
        rightBalance = getBalance(node->right);
    }
    if(node->left)
    {
        leftBalance = getBalance(node->left);
    } 
    
    // do rotations as necessary
    // If Left heavy outside :
    if(balance > 1 && leftBalance >= 0)
    {
    
        return rightRotate(node);
    }    
    // If right heavy outside:
    if(balance < -1 && rightBalance <= 0)
    {
        return leftRotate(node);
    }  
    // If left heavy inside:  left rotation first, right rotation 2nd, return top node
    if(balance > 1 && leftBalance < 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    // if right heavy inside: right rotation first, left rotation 2nd, return top node
    if(balance < -1 && rightBalance > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return (node);
}

node *insert(node*& node, int key)
{
    //recursive Code for inserting a node 
    //When insert happens set height to 0 for the node     
    if (node == NULL)
    {
        node = newNode(key);
        return(node);
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else
    {
        node->right = insert(node->right, key);
    } 
    //update heights and rebalance
    node = rebalance(node);
    return node;
}

// print functions
struct quenode
{
    struct node* value;
    struct quenode* next;
};

void enqueue(quenode*& head, node* value)
{
    if(!head)
    {
        quenode* newNode = new quenode;
        newNode->value = value;
        newNode->next = nullptr;
        head = newNode;
    }
    else
    {   
        for(quenode* curr = head; curr != nullptr; curr = curr->next)
        {
            if(!curr->next)
            {
                quenode* newNode = new quenode;
                newNode->value = value;
                newNode->next = nullptr;
                curr->next = newNode;
                break;
            }
        }
        quenode* curr = head;
    }
}

quenode *dequeue(quenode *&head)
{
    if(head)
    {
        quenode *ret = NULL;
        ret = head;
        head = head->next;
        return ret;
    }
    return NULL;
}

void printlevel(quenode *&head, node *root)
{
    ofstream ofs;
    ofs.open("output.txt");
    struct node *delim = NULL;
    struct quenode *temp = NULL;
    enqueue(head, root);
    enqueue(head, delim);
    while(true)
    {
        temp = dequeue(head);
        if(temp->value != delim)
        {
            ofs << temp->value->key << '(' << temp->value->height << ", " << getBalance(temp->value) << ") ";
            if(temp->value->left != NULL)
            {
                enqueue(head, temp->value->left);
            }
            if(temp->value->right != NULL)
            {
                enqueue(head, temp->value->right);
            }
            delete temp;
        }
        else
        {
            ofs << '\n';
            if(head == NULL)
            {
                break;
            }
            enqueue(head, delim);
        }
    }
    ofs.close();
}


int main()
{
    struct quenode *head = NULL;
    struct node *root = NULL;
    int input;
    ifstream ifs;
    ifs.open("input.txt");
    while(ifs >> input)
    {
        insert(root, input);
    }
    ifs.close();
    
    printlevel(head, root);
    
}