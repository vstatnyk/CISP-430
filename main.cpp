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
    int parent = (nodeIndex- 1)/2;
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
        siftUp(parent);
    }
    
}

void insert(int value)
{
    minHeap[currLast] = value;
    siftUp(currLast);
    currLast ++;
}

void siftDown(int parent) // for use in delete
{
    // figure out which child is smaller
    // if the parent is > biggest child, then swap and siftDown on the 
    // index of the smallest child
}

void deleteItem(int arr[])
{

}


int main()
{
    ifstream ifs;
    ifs.open("input.txt");

    for(int i = 0; i < ARR_SIZE; i++)
    {
        ifs >> temp;
        insert(temp);
        temp = 0;
        // cout << minHeap[i] << '\n';
    }

    for(int i = 0; i < ARR_SIZE; i ++)
    {
        cout << minHeap[i] << '\n';
    }
    cout << "parent 1: " << minHeap[0] << '\n';
    cout << "parent 1 left: " << minHeap[2*0+1] << '\n';
    cout << "parent 1 right: " << minHeap[2*0+2] << '\n';
    cout << "parent 2: " << minHeap[1] << '\n';
    cout << "parent 2 left: " << minHeap[2*1+1] << '\n';
    cout << "parent 2 right: " << minHeap[2*1+2] << '\n';
    // cout << minHeap[7] << currLast;
}