#include <iostream>
#include <fstream>
using namespace std;



void siftUp(int minHeap[], int nodeIndex) // for use in insert
{
    //figure out parent index
    int parent = (nodeIndex - 1)/2;
    
    // base case
    if(parent == -1)
    {
        return;
    }
    
    //if parent is greater, then swap and siftUp parentindex 
    if(minHeap[parent] > minHeap[nodeIndex])
    {
        int temp = minHeap[nodeIndex];
        minHeap[nodeIndex] = minHeap[parent];
        minHeap[parent] = temp;
        temp = 0;
        siftUp(minHeap, parent);
    }
}

void insertItem(int &currLast, int minHeap[], int value)
{
    // insert item to last
    minHeap[currLast] = value;
    siftUp(minHeap, currLast);
    currLast ++;
}

void siftDown(int parent, int &currLast, int minHeap[]) // for use in delete
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
        int temp = minHeap[smallestIndex];
        minHeap[smallestIndex] = minHeap[parent];
        minHeap[parent] = temp;
        temp = 0;
        siftDown(smallestIndex, currLast, minHeap);
    }
}

void deleteItem(int minHeap[], int &currLast)
{
    // replace 0 item with last
    minHeap[0]= minHeap[currLast];
    minHeap[currLast] = 0;
    currLast --;

    // use siftDown
    siftDown(0, currLast, minHeap);
}

void printHeap(int minHeap[], int &currLast)
{
    int itemsOnLevel = 1;
    int numbersPrinted = 0;
    while(numbersPrinted <= currLast)
    {
        for(int i = 0; i != itemsOnLevel; i ++)
        {
            if (numbersPrinted > currLast)
            {
                return;
            }
            cout << minHeap[numbersPrinted] << ' ';
            numbersPrinted ++;
        }
        itemsOnLevel *= 2;
        cout <<'\n';
    }
}

int main()
{
    int currLast = 0;
    const int ARR_SIZE = 10;
    int minHeap[ARR_SIZE];
    int temp = 0;


    ifstream ifs;
    ifs.open("input.txt");

    for(int i = 0; i < ARR_SIZE; i++)
    {
        ifs >> temp;
        insertItem(currLast, minHeap, temp);
        // temp = 0;
    }
    currLast --;
    printHeap(minHeap, currLast);

    for(int i = 0; i < 5; i++)
    {
        cout << "\n\n";
        deleteItem(minHeap, currLast);
        printHeap(minHeap, currLast);
    }
    
}