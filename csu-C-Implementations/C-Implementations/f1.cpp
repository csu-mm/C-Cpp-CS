#include <iostream>
#include <list>
using namespace std;



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