#include <iostream>
#include <list>
#include <map>
#include <set>
using namespace std;

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
			// not found here. so, divide and then search in each part
			*(arr+mid) > searchItem ? BinarySearch(arr, low, mid-1, searchItem)   // Search left half
                                    : BinarySearch(arr, mid+1, high, searchItem); // Search right half
}

struct tnode
{
	struct tnode* left;
	struct tnode* right;
	int data;
	//int height;
};

// returns:
// -1 : item not found
// +ve : number of comparison happened till found
int comparisonCount = 0;
int SearchInBST(struct tnode* pCurrentRoot, int value)
{
	if (!pCurrentRoot) return -1; // edge case, not found
		
	comparisonCount++;
	
	return pCurrentRoot->data == value ? comparisonCount // found, return comparison count.
		// otherwise search in childs
		: pCurrentRoot->data < value ? SearchInBST(pCurrentRoot->right, value) 
		: SearchInBST(pCurrentRoot->left, value);

	return -1; // not found
}

void AddNodeToBST(tnode** pCurrentRoot, int value)
{
	if (!pCurrentRoot) return;  // invalid pCurrentRoot containing pointer

	struct tnode* pNewNode = (struct tnode*)malloc(sizeof(struct tnode));
	pNewNode->data = value;
	// pNewNode->height = 1;
	pNewNode->left = NULL;
	pNewNode->right = NULL;
	
	if (*pCurrentRoot == NULL)
	{
		*pCurrentRoot = pNewNode;
		return;
	}

	if ((*pCurrentRoot)->data == value)
	{
		// duplicate not allowed
		free(pNewNode);
		return;
	}
	
	if ((*pCurrentRoot)->data > value)
		AddNodeToBST(&(*pCurrentRoot)->left, value);
	else
		AddNodeToBST(&(*pCurrentRoot)->right, value);
}

// <<<<<<< HEAD  =======
list<int> discovered;
list<list<int>> allPaths;
void ShowAllPaths(struct tnode* root)
{
	if (!root) return;

	list<int>::iterator it;
	discovered.push_back(root->data);

	ShowAllPaths(root->left);

	if (root->left == NULL && root->right == NULL)
	{
		list<int> currentPath;
		it = discovered.begin();
		while (it != discovered.end())
		{			
			currentPath.push_back(*it);
			it++;
		}
		allPaths.push_back(currentPath);
		it--;
		discovered.remove(*it);
		return;
	}

	ShowAllPaths(root->right);
	it = discovered.end(); it--;
	discovered.remove(*it);
}

map<int, list<int>> mapLevelNodeData2;
map<int, list<int>> CreateLevelNodeValuesCollection2(tnode* root, int level)
{
	if (!root) return mapLevelNodeData2;

	map<int, list<int>>::iterator itMap;
	itMap = mapLevelNodeData2.find(level);
	if (itMap == mapLevelNodeData2.end())
	{
		mapLevelNodeData2.insert(pair<int, list<int>>(level, { root->data }));
	}
	else
	{
		itMap->second.push_back(root->data);
	}

	level++;
	CreateLevelNodeValuesCollection2(root->left, level);
	CreateLevelNodeValuesCollection2(root->right, level);

	return mapLevelNodeData2;
}

int CompareTwoBinaryTrees(struct tnode* a, struct tnode* b)
{
	// returns :  0 if equal, otherwise 1
	if (!a && !b) return 0;
	if (!a || !b) return 1;

	return (
		   a->data == b->data
		&& CompareTwoBinaryTrees(a->left, b->left) == 0
		&& CompareTwoBinaryTrees(a->right, b->right) == 0
		);
}

void ReverseWordsInString(char* str)
{
	if (!str) return;

	int wlen;
	char ch1;
	int i;

	while (*str)
	{
		while (*str == ' ') str++;
		wlen = -1;
		while (str[++wlen] && str[wlen] != ' ');
		i = -1;
		while (++i < wlen / 2)
		{
			ch1 = str[i];
			str[i] = str[wlen - 1 - i];
			str[wlen - 1 - i] = ch1;
		}
		if (str[wlen] == '\0') return;
		str += wlen;
	}
}

void RemoveTokensInString(char* pCharSrc, char* pCharToken)
{
	if (!pCharSrc || !pCharToken || !*pCharSrc || !*pCharToken) return;
	char* pCharBackup = pCharSrc;

	int i, j;
	while (*pCharSrc)
	{
		i = 0;
		while (pCharSrc[i] && pCharToken[i] && pCharSrc[i] == pCharToken[i]) i++;
		if (!pCharToken[i])
		{
			j = -1;
			while (pCharSrc[i + ++j])
				pCharSrc[j] = pCharSrc[i + j];
			pCharSrc[j] = '\0';			
		}
		else
		{
			pCharSrc++;
		}
	}
}

void PrintAllCombination(char *pChar)
{
	if (!pChar) return;
	printf("");
	if (!*pChar) return;

	int len = -1;
	while(pChar[++len]);
	int combinationCount = 1 << len;
	printf("\n");
	for (int i = 0; i < combinationCount; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if ((1 << j)&i) printf("%c", pChar[j]);
		}
		printf("\n");
	}
}

list<list<int>> GetItemIndexesForGroupCombination(int collectionItemCount, int groupItemCount)
{
	list<list<int>> groupItemsIndexes;
	
	if (collectionItemCount < 1) return groupItemsIndexes;

	int allCombinationsCount = 1 << collectionItemCount;
	//int groupsCount = factorial(itemsCount) / (factorial(groupItemCount) * factorial(itemsCount - groupItemCount));

	for (int i = 0; i < allCombinationsCount; i++)
	{
		list<int> indexes;
		for (int j = 0; j < collectionItemCount; j++)
		{
			if ((1 << j) & i)
			{
				indexes.push_back(j);
			}
		}
		if (indexes.size() == groupItemCount)
		{
			groupItemsIndexes.push_back(indexes);
		}
	}

	return groupItemsIndexes;
}
char* LongestSubStringWithNonRepeatingChar(char* str)
{
	if (!str || !*str) return str;
	set<char> SetChar;
	int startTemp = 0;
	int startIndex = 0;
	int endIndex = 0;

	int i = -1;
	while (str[++i])
	{
		if (SetChar.insert(str[i]).second == false) // repeating char found
		{
			if (i-1-startTemp > endIndex-startIndex)
			{
				startIndex = startTemp;
				endIndex = i - 1;
			}

			// next start
			startTemp = i;
			SetChar.clear();
			SetChar.insert(str[i]);
		}
	}

	if (endIndex > startIndex)
	{
		char* ret = (char*)malloc(1+(endIndex-startIndex+1) * sizeof(char));
		i = -1;
		while (++i <= endIndex-startIndex)
		{
			ret[i] = str[startIndex+i];
		}
		ret[i] = '\0';
		return ret;
	}

	return NULL;
}

int getIterationNumberOfGeneration(const char* str)
{
	if (!str || !*str) return -1;
	std::cout << "\ninput sequence:\t\t" << str << ". Length = " << strlen(str) << endl;
	int len = -1;
	while (str[++len] && (str[len] == '0' || str[len] == '1' || str[len] == '2'));
	if (len < 1 || str[len] != '\0') return -1;
	if (len == 1 && str[0] != '0') return -1;  // invalid digit for the sequence
	if (len % 2 != 0) return -1; // invalid number of digits

	int it = -1;
	while (len > pow(2, ++it));
	if (len != pow(2, it)) return -1;  // invalid generation

	// Create the sequence string
	char seq[1024];
	int usedCharCount = 0;
	while (usedCharCount < len)
	{
		if (usedCharCount == 0)
		{
			seq[0] = '0';
			usedCharCount++;
		}
		else if (usedCharCount == 1)
		{
			seq[1] = '1';
			usedCharCount++;
		}
		else // if (usedCharCount > 1)
		{
			int i = -1;
			while (++i < usedCharCount)
			{
				if (seq[i] == '0')
					seq[i + usedCharCount] = '1';
				else if (seq[i] == '1')
					seq[i + usedCharCount] = '2';
				else
					seq[i + usedCharCount] = '0';
			}
			usedCharCount *= 2;
		}
	}
	seq[usedCharCount] = '\0';
	std::cout << "App generated sequence: " << seq << endl;
	return strcmp(str, seq) == 0 ? it : -1;
}


class Date
{
	int month, day, year;
public:
	Date()
	{
		month = day = year = 0;
	}
	Date(int mo, int d, int yr)
	{
		month = mo; day = d; year = yr;
	}

	friend ostream& operator << (ostream& os, const Date& dt);

	//friend istream& operator >> (istream& is, Date& dt);
	friend void operator >> (istream& is, Date& dt);
};

//istream& operator >> (istream& is, Date& dt)
void operator >> (istream& is, Date& dt)
{
	is >> dt.month >> dt.day >> dt.year;
}

ostream& operator << (ostream& os, const Date& dt)
{
	os << dt.month << "/" << dt.day << "/" << dt.year;
	return os;
}

struct SListNode
{
	int data;
	struct SListNode* next;
};
void ReverseSList(struct SListNode** head)
{
	if (!head || !*head || !((*head)->next)) return;

	struct SListNode* Current = *head;
	struct SListNode* Prev = NULL;
	struct SListNode* Next = NULL;

	while (Current)
	{
		Next = Current->next;
		Current->next = Prev;
		Prev = Current;
		Current = Next;
	}
	*head = Prev;
}

//>>>>>>> 2f658db65d9321f6b2090d90c4fadabd3eb288a4

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

struct gNode2
{
	Point node;
	int data;
	list<gNode2> neighbours;
};

struct gEdge2
{
	int weight;
	Point fromNode;
	Point toNode;
};

struct graph2
{
	list<gNode2> gNodes;
	list<gEdge2> gEdges;
};

struct gNode
{	
	int data;
	list<gNode> neighbours;
};

struct gEdge
{
	int weight;
	struct gNode fromNode;
	struct gNode toNode;
};

struct graph
{
	list<gNode> gNodes;
	list<gEdge> gEdges;
};

void CreateLevelNodesCollection(gNode* currentStartNode, int level, map<int, list<int>>& mapLevelNodeData)
{
	if (currentStartNode != NULL)
	{
		auto itMap = mapLevelNodeData.find(level);
		if (itMap == mapLevelNodeData.end())
		{
			mapLevelNodeData.insert(pair<int, list<int>>(level, { currentStartNode->data }));
			level++;
		}
		else
		{
			itMap->second.push_back(currentStartNode->data);
		}
		
		for (auto& neighbour : currentStartNode->neighbours)
		{
			CreateLevelNodesCollection(&neighbour, level, mapLevelNodeData);
		}
	}
}

//void CreateLevelNodesCollection(gNode* currentStartNode, int level, map<int, list<int>>& mapLevelNodeData)
//{
//	//static map<int, list<int>> mapLevelNodeData;
//
//	if (currentStartNode != NULL)
//	{
//		//map<int, list<int>>::iterator itMap;
//		auto itMap = mapLevelNodeData.find(level);
//		if (itMap == mapLevelNodeData.end())
//		{
//			mapLevelNodeData.insert(pair<int, list<int>>(level, { currentStartNode->data }));
//		}
//		else
//		{
//			itMap->second.push_back(currentStartNode->data);
//		}
//
//		level++;
//		for (auto& neighbour : currentStartNode->neighbours)
//		{
//			CreateLevelNodesCollection(&neighbour, level, mapLevelNodeData);
//		}
//	}
//	// CreateLevelNodeValuesCollection(root->left, level);
//	// CreateLevelNodeValuesCollection(root->right, level);
//
//	// return mapLevelNodeData;
//}
// 
//struct gNode 
// {
//	int data;
//	std::vector<gNode*> neighbours;
//};
//
//void CreateLevelNodesCollection(gNode* startNode, std::map<int, std::list<int>>& mapLevelNodeData) {
//	if (!startNode) return;
//
//	std::queue<std::pair<gNode*, int>> q;
//	std::unordered_set<gNode*> visited;
//
//	q.push({ startNode, 0 });
//	visited.insert(startNode);
//
//	while (!q.empty()) 
//  {
//		auto [node, level] = q.front();
//		q.pop();
//
//		mapLevelNodeData[level].push_back(node->data);
//
//		for (gNode* neighbor : node->neighbours) 
//		{
//			if (visited.find(neighbor) == visited.end()) 
//			{
//				q.push({ neighbor, level + 1 });
//				visited.insert(neighbor);
//			}
//		}
//	}
//}


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

	printf("\nTest: Graph: ");
	// Create Graph of few nodes 
	struct graph g;
	struct gNode n1,n2,n3,n4,n5,n6,n7,n8,n9,n10;
	n1.data = 1; n2.data = 2; n3.data = 3; n4.data = 4; n5.data = 5;
	n6.data = 6; n7.data = 7; n8.data = 8; n9.data = 9; n10.data = 10;
	n1.neighbours.push_back(n2); n1.neighbours.push_back(n4); n1.neighbours.push_back(n5);
	n3.neighbours.push_back(n6); 
	n4.neighbours.push_back(n7); 
	n5.neighbours.push_back(n3); n5.neighbours.push_back(n8);
	n6.neighbours.push_back(n9);
	n7.neighbours.push_back(n10);
	n8.neighbours.push_back(n10);

	// void CreateLevelNodesCollection(gNode* currentStartNode, int level, map<int, list<int>>& mapLevelNodeData)
	map<int, list<int>> mapLevelNodeData;
	CreateLevelNodesCollection(&n1, 0, mapLevelNodeData);
	for (auto& kv : mapLevelNodeData)
	{
		printf("\n Level: %d => ", kv.first);
		for (auto& v : kv.second)
			printf("  %d  ", v);
	}
	//g.gNodes.push_back()

	printf("\n\nApplication Closing..."); getchar(); return;

	printf("\nTest: BST and AVL: ");
	struct tnode* rootBST1 = NULL; struct tnode* rootBST2 = NULL;
	//struct tnode* rootAVL = NULL;
	AddNodeToBST(&rootBST1, 12); AddNodeToBST(&rootBST1, 8); AddNodeToBST(&rootBST1, 15); AddNodeToBST(&rootBST1, 25); 
	AddNodeToBST(&rootBST1, 9);  AddNodeToBST(&rootBST1, 6); AddNodeToBST(&rootBST1, 14);
	
	AddNodeToBST(&rootBST2, 6); AddNodeToBST(&rootBST2, 8); AddNodeToBST(&rootBST2, 9);  AddNodeToBST(&rootBST2, 12);  
	AddNodeToBST(&rootBST2, 14); AddNodeToBST(&rootBST2, 15); AddNodeToBST(&rootBST2, 25);	
	// this will create BST only with 'right' child.

	int searchVal = 25;
	comparisonCount = 0;
	printf("\nBST1 SeachItem value = %d, Comparison Count = %d", searchVal, SearchInBST(rootBST1, searchVal));
	comparisonCount = 0;
	printf("\nBST2 SeachItem value = %d, Comparison Count = %d", searchVal, SearchInBST(rootBST2, searchVal));

	//printf("\nAVL SeachItem value = %d, Comparison Count = %d", searchVal, SearchInBST(rootAVL, searchVal));
	printf("\n\nApplication Closing..."); getchar(); return;

	//AddNodeToAVL(&rootAVL, 15);
	//AddNodeToAVL(&rootAVL, 8);
	//AddNodeToAVL(&rootAVL, 25);
	//AddNodeToAVL(&rootAVL, 12);
	//AddNodeToAVL(&rootAVL, 9);
	//AddNodeToAVL(&rootAVL, 6);
	//AddNodeToAVL(&rootAVL, 7);
	//AddNodeToAVL(&rootAVL, 5);

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
