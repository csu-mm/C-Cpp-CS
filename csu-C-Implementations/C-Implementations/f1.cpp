#include <iostream>
#include <list>
using namespace std;

// max heap:  https://www.youtube.com/watch?v=B7hVxCmfPtM&t=750s
// https://www.youtube.com/watch?v=HqPJF2L5h9U
// max/min heap : insert O is O(logn), delete O(logn) // that's why we need max/min heap to construct Priority Queue

// representation of binary tree using array:
// let say tree has 7 elements , so height = 2 , nodes = 2**(height+1) - 1 = 2**3 - 1 = 7
// we need array with size = 7 (index:0-6)
// so, it's a complete binary tree
//
// if node 'A' exists at index = i
//		then it's parent will be at index floor[(i+1)/2] - 1
//		then it's left child will be at index 2*(i+1) - 1 = 2*i +1
//		then it's right child will be at index 2*(i+1)
// root node will have same index as it's parent's index
//

// BinarySearch on Sorted collection
int BinarySearch(int* arr, int low, int high, int searchItem)
{
    if (!arr || low < 0 || low > high) return -1; // edge case: not found
    
	int mid = low + (high - low) / 2 ;
        
	return *(arr + mid) == searchItem ? mid :    // found
			// not found here. so, apply divide and conquer strategy
			*(arr+mid) > searchItem ? BinarySearch(arr, low, mid-1, searchItem)   // Search left half
                                    : BinarySearch(arr, mid+1, high, searchItem); // Search right half
}

struct tnode
{
	struct tnode* left;
	struct tnode* right;
	int data;
};

void AddNode2Tree(tnode** pRootNode, int value)
{
	if (!pRootNode) return;  // invalid input

	struct tnode* pNewNode = (struct tnode*)malloc(sizeof(struct tnode));
	pNewNode->data = value;
	pNewNode->left = NULL;
	pNewNode->right = NULL;

	if (*pRootNode == NULL)
	{
		*pRootNode = pNewNode;
		return;
	}

	if ((*pRootNode)->data > value)
		AddNode2Tree(&(*pRootNode)->left, value);
	else
		AddNode2Tree(&(*pRootNode)->right, value);
}

#define MAX_LEN 100
int heap[MAX_LEN];
int len = 0;

void heapifyUp(int index) 
{
	int temp;
	int parent = (index - 1) / 2;
	if (index > 0 && heap[index] > heap[parent])
	{
		temp = heap[index];
		heap[index] = heap[parent];
		heap[parent] = temp;		
		heapifyUp(parent);
	}
}

void heapifyUpNR(int currentIndex)
{
	int temp;
	int parentIndex = (currentIndex - 1) / 2;
	while (currentIndex > 0 && heap[currentIndex] > heap[parentIndex])
	{
		temp = heap[currentIndex];
		heap[currentIndex] = heap[parentIndex];
		heap[parentIndex] = temp;
		
		currentIndex = parentIndex; // heapifyUp(parent);
		parentIndex = (currentIndex - 1) / 2;
	}
}

// Insert into max-heap
void insert(int value) 
{
	if (len >= MAX_LEN)
	{
		printf("Heap is full\n");
		return;
	}
	heap[len] = value;
	heapifyUp(len);
	len++;
}

void addItem(int value)
{
	if (len >= MAX_LEN)
	{
		printf("Heap is full\n");
		return;
	}
	int temp;
	int currentIndex = len, parentIndex = (currentIndex - 1) / 2;
	heap[currentIndex] = value;
	while (currentIndex > 0 && heap[currentIndex] > heap[parentIndex])
	{
		temp = heap[currentIndex];
		heap[currentIndex] = heap[parentIndex];
		heap[parentIndex] = temp;

		currentIndex = parentIndex;
		parentIndex = (currentIndex - 1) / 2;
	}
	len++;
}

// needed to remove item
void heapifyDown(int i) 
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < len && heap[left] > heap[largest])
		largest = left;

	if (right < len && heap[right] > heap[largest])
		largest = right;

	if (largest != i) 
	{		
		left = heap[i];
		heap[i] = heap[largest];
		heap[largest] = left;
		heapifyDown(largest);
	}
}

void printHeap() 
{
	for (int i = 0; i < len; i++)
		printf("%d ", heap[i]);
	printf("\n");
}


struct Point { int x; int y; };
struct gNode
{
	Point node;
	int data;
	list<gNode> neighbours;
};

struct gEdge
{
	int weight;
	Point fromNode;
	Point toNode;
};

struct graph
{
	list<gNode> gNodes;
	list<gEdge> gEdges;
};

void QuickSort1(int* a, int itemCount)
{
	if (!a || itemCount < 2) return; // edge case

	// pivot: a[0]
	int i = 0, j = itemCount - 1;
	int temp;

	while (i < j)
	{
		while (*(a+i) <= *a) i++;
		while (*(a+j) > *a) j--;
		if (i < j)
		{
			temp = *(a+i);
			*(a+i) = *(a+j);
			*(a+j) = temp;
		}
	}

	temp = *a;
	*a = *(a+j);
	*(a+j) = temp;

	QuickSort1(a, j);
	QuickSort1((a+j+1), itemCount-1-j);
}


struct dataItem
{
	int val;
	char name[20];
};

void QuickSort(struct dataItem* a, int itemCount)
{
	if (!a || itemCount < 2) return;  // edge case

	// pivot: a[0]
	int i = 0, j = itemCount - 1;
	struct dataItem temp;

	while (i < j)
	{
		while ((a + i)->val <= a->val) i++;
		while ((a + j)->val > a->val) j--;
		if (i < j)
		{
			temp = *(a+i);
			*(a+i) = *(a+j);
			*(a+j) = temp;
		}
	}
	temp = *a;
	*a = *(a+j);
	*(a+j) = temp;
	// now, apply divide and conquer strategy
	QuickSort(a, j);
	QuickSort(a+j+1, itemCount-1-j);
}

void main()
{
	printf("\nApplication Started...\n\n");

	printf("\nTest: Max-Heap: ");
	addItem(20);
	addItem(105);
	addItem(30);
	addItem(10);
	addItem(40);
	addItem(20);
	//printf("Max-Heap: ");
	//printHeap();  // Output will show largest element at root
	printf("\n");
	while (len > 0)
	{
		printf("Removed top: %d\n", heap[0]);
		heap[0] = heap[len - 1];  // Replace root with last element(highest levels right most child)
		len--;                    // Shrink the heap length
		heapifyDown(0);
	}
	//char inputChar = 'x';
	//int(*functionPtr)(char);
	//functionPtr = &ReadNumericValueOfKeyPressedInMobile;	
	//printf("\nint(*functionPtr)(char) : %d", (*functionPtr)(inputChar));
	//printf("\n\n");
	//char str1[10]; strcpy_s(str1, "123");
	//Permute(str1, 0, 3);	

	printf("\nTest: void QuickSort1(int* a, int itemCount)");
	int a1[] = { 5,3,3 };
	printf("\nBefore sort:  ");
	for (size_t i = 0; i < 3; i++) printf("  %d  ", *(a1 + i));
	QuickSort1(a1, 3);
	printf("\nAfter sort:  ");
	for (size_t i = 0; i < 3; i++) printf("  %d  ", *(a1 + i));
	
	printf("\n\nTest: void QuickSort(struct dataItem* a, int itemCount)");	
	dataItem arrDataItem[3];	
	arrDataItem[0].val = 5; strcpy_s(arrDataItem[0].name, "first-5");	
	arrDataItem[1].val = 5; strcpy_s(arrDataItem[1].name, "second-5");
	arrDataItem[2].val = 3; strcpy_s(arrDataItem[2].name, "first-3");	
	//arrDataItem[3].val = 3; strcpy_s(arrDataItem[3].name, "second-3");

	printf("\nBefore sort:  ");
	for (int i = 0; i < 3; i++)
		printf("  {%d , %s}  ", (arrDataItem + i)->val, (arrDataItem + i)->name);

	QuickSort(arrDataItem, 3);
	printf("\nAfter sort:   ");
	for (int i = 0; i < 3; i++)
		printf("  {%d , %s}  ", (arrDataItem + i)->val, (arrDataItem + i)->name);

	printf("\n\nApplication Closing..."); getchar();
}