#include <iostream>
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

node *leftRotate(node *x){
    struct node *y = x->right;
    //add more code to rotate to the left, update heights for x and y
    x->right = y->left;
    y->left = x;    
    x->height = max(height(x->left), height(x->right)) + 1; 
    y->height = max(height(y->left), height(y->right)) + 1;
    // cout << height(x->left) << height(x->right);
    return(y);
}

node *rightRotate(node *x){
    struct node *y=x->left;
    //add more code to rotate to the right, update heights for x and y
    x->left = y->right;
    y->right = x;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return(y);
}

// node *rebalance(node *node){
//     // cout << "start rebalance for node " << node->key << '\n';
//     // cout << "node " << node->key << " left height = " << height(node->left) << "   node " << node->key << " right height = " << height(node->right) << " max (get hieght ) is = " << max(height(node->left), height(node->right)) + 1 <<  '\n';
//     // cout << "balance of node " << node->key << "is " << getBalance(node) << '\n';
//     node->height = max(height(node->left), height(node->right)) + 1;    
//     int balance = getBalance(node);  //node->left - node->right
    
//     // do rotations as necessary
//     // If Left heavy outside :
//     if(balance > 1)
//     {
//         return rightRotate(node);
//     }    
//     // If right heavy outside:
//     if(balance < -1)
//     {
//         return leftRotate(node);
//     }  
//     // If left heavy inside:  left rotation first, right rotation 2nd, return top node
//     if(balance > 1 && node->left->left == NULL)
//     {
//         node->left =  leftRotate(node->left);
//         return rightRotate(node);
//     }
//     // if right heavy inside: right rotation first, left rotation 2nd, return top node
//     if(balance < -1 && node->right->right == NULL )
//     {
//         node->right = rightRotate(node->right);
//         return leftRotate(node);
//     }

//     return (node);
// }
node * rebalance( node *&node){

    node->height = max(height(node->left), height(node->right)) + 1;    
    int balance = getBalance(node);  //node->left - node->right

    if ((node->left != NULL) && (node->right != NULL)){
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    if ( balance < -1){ // RIGHT HEAVY
        balance=getBalance(node->right); // IS CHILD LEFT HEAVY ?
        if(balance>0){
            // double rotation right , left
            node->right=rightRotate(node->right);
            return node=leftRotate(node); //  if node is left heavy > 1
         }
         else
             return node=leftRotate(node); //  if node is left heavy > 1
    }
   if( balance > 1){ // LEFT HEAVY
         balance=getBalance(node->left); // IS CHILD RIGHT HEAVY ?
         if(balance<0){
            // double rotation left, right
            node->left=leftRotate(node->left);
            return node=rightRotate(node); //  if node is left heavy > 1
         }
         else
             return node=rightRotate(node); //  if node is left heavy > 1
    }

    return node;
}

node *insert(node*& node, int key)
{
    //recursive Code for inserting a node 
    //When insert happens set height to 0 for the node     
    if (node == NULL)
    {
        node = newNode(key);
        // cout << "creating node " <<'\n' << "key = " << node->key << " height = " <<node->height << '\n'; 
        return(node);
    }
    if (key < node->key)
    {
        // cout << "went to if in insert" <<'\n';
        node->left = insert(node->left, key);
    }
    else
    {
        // cout << "went to else in insert" <<'\n'; 
        node->right = insert(node->right, key);
    } 
    node = rebalance(node);  //update heights and rebalance
    return node;
}

// print functions
struct quenode
{
    struct node* value;
    struct quenode* next;
};

void append(quenode*& head, node* value)
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

quenode *returnLast(quenode *&head)
{
    quenode *ret = NULL;
    for(quenode* curr = head; curr != nullptr; curr = curr->next)
    {
        if(curr == head && !curr->next)
        {
            ret = curr;
            curr->next = NULL;
            return ret;
        }
        if(!curr->next->next)
        {
            ret = curr->next;
            curr->next = NULL;
            return ret;
        }
    }
    return ret;
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
    struct quenode *head = NULL;
    struct quenode *temp = NULL;
    struct node *root = NULL;
    insert(root, 10);
    insert(root, 15);
    insert(root, 6);
    insert(root, 3);
    insert(root, 8);
    insert(root, 9);
    cout << root->key << " ";
    cout << root->height << '\n';
    cout << root->left->key<< " ";
    cout << root->left->height<<'\n';
    cout << root->right->key<< " ";
    cout << root->right->height<<'\n';
    // cout << root->left->left->key<< " ";
    // cout << root->left->left->height<<'\n';
    // cout << root->right->left->key<< " ";
    // cout << root->right->left->height<<'\n';
    // cout << root->right->right->key<< " ";
    // cout << root->right->right->height<<'\n';
    // append(head, root);
    // append(head, root->left);
    // append(head, root->right);
    // temp = returnLast(head);
    // cout << temp->value->key;
    // delete temp;
    // temp = returnLast(head);
    // cout << temp->value->key;
    // delete temp;
    // temp = returnLast(head);
    // cout << temp->value->key;

    
}