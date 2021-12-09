#include <iostream>
#include <fstream>
using namespace std;

// Option 1: Start with index 0
// Children of a[i]
// Left=a[2i+1]
// Right=a[2i+2]
// Parent of a[i]=(i-1)/2

int currLast = 0;
const int ARR_SIZE = 10;
int minHeap[ARR_SIZE];
int temp = 0;

void siftUp(int nodeIndex) // for use in insert
{
    //figure out parent index
    int parent = (nodeIndex- 1)/2;
    
    // base case
    if(parent == -1)
    {
        return;
    }
    
    //if parent is greater, then swap and siftUp parentindex 
    if(minHeap[parent] > minHeap[nodeIndex])
    {
        temp = minHeap[nodeIndex];
        minHeap[nodeIndex] = minHeap[parent];
        minHeap[parent] = temp;
        temp = 0;
        siftUp(parent);
    }
}

void insertItem(int value)
{
    // insert item to last
    minHeap[currLast] = value;
    siftUp(currLast);
    currLast ++;
}

void siftDown(int parent) // for use in delete
{
    // base case
    if (2*parent+1 >= currLast)
    {
        return;
    }

    // figure out which child is smaller
    int smallestIndex = 0;
    if(minHeap[2*parent+1] < minHeap[2*parent+2])
    {
        smallestIndex = 2*parent+1;
    }
    else
    {
        smallestIndex = 2*parent+2;
    }

    // if the parent is > smallest child, then swap and siftDown on the index of the smallest child

    if(minHeap[parent] > minHeap[smallestIndex])
    {
        temp = minHeap[smallestIndex];
        minHeap[smallestIndex] = minHeap[parent];
        minHeap[parent] = temp;
        temp = 0;
        siftDown(smallestIndex);
    }
}

void deleteItem()
{
    // replace 0 item with last
    minHeap[0]= minHeap[currLast];
    minHeap[currLast] = 0;
    currLast --;
    siftDown(0);
    // use siftDown
}


int main()
{
    ifstream ifs;
    ifs.open("input.txt");

    for(int i = 0; i < ARR_SIZE; i++)
    {
        ifs >> temp;
        insertItem(temp);
        temp = 0;
        // cout << minHeap[i] << '\n';
    }
    cout << '\n';

    for(int i = 0; i < ARR_SIZE; i ++)
    {
        cout << minHeap[i] << '\n';
    }
    cout << '\n';
    // cout << "parent 1: " << minHeap[0] << '\n';
    // cout << "parent 1 left: " << minHeap[2*0+1] << '\n';
    // cout << "parent 1 right: " << minHeap[2*0+2] << '\n';
    // cout << "parent 2: " << minHeap[1] << '\n';
    // cout << "parent 2 left: " << minHeap[2*1+1] << '\n';
    // cout << "parent 2 right: " << minHeap[2*1+2] << '\n';
    // cout << minHeap[7] << currLast;
    deleteItem();
    for(int i = 0; i < currLast; i ++)
    {
        cout << minHeap[i] << '\n';
    }
    // deleteItem();
    // deleteItem();
    // deleteItem();
    // deleteItem();
    
}