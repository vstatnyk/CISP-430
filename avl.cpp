#include <iostream>
using namespace std;

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
    return(node->height);
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

node *leftRotate(node *x){
    struct node *y = x->right;
    //add more code to rotate to the left, update heights for x and y
    y->left = x;
    x->right = NULL;
    y->height = max(height(x->left), height(x->right)) + 1;
    x->height --;
    if(y->right != NULL)
    {
        y->right->height ++;
    }  
    return(y);
}

node *rightRotate(node *x){
    struct node *y=x->left;
    //add more code to rotate to the right, update heights for x and y
    y->right = x;
    x->left = NULL;
    y->height = max(height(x->left), height(x->right)) + 1;
    x->height --;
    if(y->left != NULL)
    {
        y->left->height ++;
    }
    return(y);
}

node * rebalance(node *node){
    node->height = max(height(node->left), height(node->right)) + 1;    
    int balance = getBalance(node);  //node->left - node->right
    
    // do rotations as necessary
    // If Left heavy outside :
    if(balance > 1 && node->left->left != NULL)
    {
        return rightRotate(node);
    }    
    // If right heavy outside:
    else if(balance < -1 && node->right->right != NULL)
    {
        return leftRotate(node);
    }  
    // If left heavy inside:  left rotation first, right rotation 2nd, return top node
    else if(balance > 1 && node->left->left == NULL)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    // if right heavy inside: right rotation first, left rotation 2nd, return top node
    else if(balance < -1 && node->right->right == NULL )
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return (node);
}

node* insert(node*& node, int key)
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
    node = rebalance(node);  //update heights and rebalance
    return node;
}

void printLevel(node *node)
{
    struct node *endlevel = NULL;

}

void push(node *node)
{

}

void pop(node *node)
{

}

// Enqueue root ( NodesOnCurrentLevel++)   // add node in current level
// While NodesinCurrentLevel!=0                //or nodesInCurrentLevel !=0
// Dequeue and display //1st time (A)
// nodesInCurrentLevel--   //1st time dequeue A,NICL=0 
// enqueue left  child( nodesInNextLevel++)   //1st time enqueue B
// enqueue right child ( nodesInNextLevel++)   //1st time enqueue C
// If nodesInCurrentLevel==0 //1st time NICL=0
// NodesInCurrentlevel=NodesInNextLevel  //points to B C
// NodeinNextlevel=0 //Points to nothing
// cout<<endl //go to next line

int main()
{
    struct node *root = NULL;
    insert(root, 3);
    // cout << root->key;
    // cout << root->height << '\n';
    insert(root,5);
    // cout << root->left->key;
    // cout << root->left->height<<'\n';
    insert(root, 7);
    cout << root->key << " ";
    cout << root->height << '\n';
    cout << root->left->key<< " ";
    cout << root->left->height<<'\n';
    cout << root->right->key<< " ";
    cout << root->right->height<<'\n';
    printLevel(root);
}