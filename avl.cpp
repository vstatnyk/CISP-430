#include <iostream>
using namespace std;

struct node
{
    int key;
    node* left;
    node* right;
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
    node* nn = new node;
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

void printLevel(node *node)
{

}

node *leftRotate(node *x){
   struct node *y = x->right;
   //add more code to rotate to the left, update heights for x and y
   y->left = x;
   x->right = NULL;
   y->height ++;
   x->height --;  
   return(y);
}

node *rightRotate(node *x){
   struct node *y=x->left;
   //add more code to rotate to the right, update heights for x and y
   y->right = x;
   x->left = NULL;
   y->height ++;
   x->height --;  
   return(y);
}
// int max( node *L, node *R){

//       if (L == NULL && R == NULL){
//         return -1;
//       }
//       else if (L == NULL){
//             return (R->height);
//       }
//       else{

//         return (L->height);
//       }
// }
// node *leftRotate( node *x){

//     node *y=x->right;

//     // add more code to rotate to the left,
//     x->right=y->left;
//     y->left=x;

//     // update heights for x and y
//     x->height = (max(x->left, x->right)) + 1;
//     y->height = (max(y->left, y->right)) + 1;

//    //return root of the tree
//     return y;
// }

// node *rightRotate( node *x){

//     node *y=x->left;
//    //add more code to rotate to the right,
//     x->left=y->right;
//     y->right=x;

//     //   update heights for x and y
//     x->height = (max(x->left, x->right)) + 1;
//     y->height = (max(y->left, y->right)) + 1;

//     //   return root of the tree
//     return y;
// }

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
        return(newNode(key));
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

int main()
{
    node *root = NULL;
    root = insert(root, 9);
    cout << root->key;
    cout << root->height << '\n';
    root = insert(root, 5);
    cout << root->left->key;
    cout << root->left->height<<'\n';
    root = insert(root, 3);
    cout << root->key;
    cout << root->height << '\n';
    cout << root->left->key;
    cout << root->left->height<<'\n';
    cout << root->right->key;
    cout << root->right->height<<'\n';
}