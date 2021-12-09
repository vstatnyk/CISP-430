#include <iostream>
#include <fstream>
using namespace std;

void insert(int arr[], int &last, int value)
{
    arr[last] = value;
    last ++;
}

void siftUp()
{

}

int main()
{
    int currLast = 7;
    const int ARR_SIZE = 10;
    int minHeap[ARR_SIZE] = {1,2,3,4,5,6};
    for(int i = 0; i < 10; i++)
    {
        cout << minHeap[i] << '\n';
    }

    cout << "parent 1: " << minHeap[0] << '\n';
    cout << "parent 1 left: " << minHeap[2*0+1] << '\n';
    cout << "parent 1 right: " << minHeap[2*0+2] << '\n';
    cout << "parent 2: " << minHeap[1] << '\n';
    cout << "parent 2 left: " << minHeap[2*1+1] << '\n';
    cout << "parent 2 right: " << minHeap[2*1+2] << '\n';
    insert(minHeap, currLast, 8);
    cout << minHeap[7] << currLast;
}
// Option 1: Start with index 0
// Children of a[i]
// Left=a[2i+1]
// Right=a[2i+2]
// Parent of a[i]=(i-1)/2