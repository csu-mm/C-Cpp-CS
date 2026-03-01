// Left rotate
void leftRotate(struct tnode** x)
{
	if (!x) return; // nothing to do

	struct tnode* y = (*x)->right;
	struct tnode* T2 = y->left;

	y->left = *x;
	(*x)->right = T2;

	(*x)->height = max((*x)->left == NULL ? 0 : (*x)->left->height, (*x)->right == NULL ? 0 : (*x)->right->height) + 1;
	y->height = max(y->left == NULL ? 0 : y->left->height, y->right == NULL ? 0 : y->right->height) + 1;
}

// Right rotate
void rightRotate(struct tnode** y)
{
	if (!y) return; // nothing to do

	struct tnode* x = (*y)->left;
	struct tnode* T2 = x->right;

	x->right = *y;
	(*y)->left = T2;

	(*y)->height = max((*y)->left == NULL ? 0 : (*y)->left->height, (*y)->right == NULL ? 0 : (*y)->right->height) + 1;
	x->height = max(x->left == NULL ? 0 : x->left->height, x->right == NULL ? 0 : x->right->height) + 1;
}

void AddNodeToAVL(tnode** pCurrentRoot, int value)
{
	if (!pCurrentRoot) return;  // invalid pCurrentRoot containing pointer

	struct tnode* pNewNode = (struct tnode*)malloc(sizeof(struct tnode));
	pNewNode->data = value;
	pNewNode->height = 1;
	pNewNode->left = NULL;
	pNewNode->right = NULL;

	if (*pCurrentRoot == NULL)
	{		
		*pCurrentRoot = pNewNode;
		return;
	}

	if ((*pCurrentRoot)->data == value)
	{
		// duplicate node is not allowed
		free(pNewNode);
		return;
	}
	else if ((*pCurrentRoot)->data > value)
		AddNodeToAVL(&(*pCurrentRoot)->left, value);
	else
		AddNodeToAVL(&(*pCurrentRoot)->right, value);
	
	int lHeight = (*pCurrentRoot)->left == NULL ? 0 : (*pCurrentRoot)->left->height;
	int rHeight = (*pCurrentRoot)->right == NULL ? 0 : (*pCurrentRoot)->right->height;
	(*pCurrentRoot)->height = max(lHeight, rHeight) + 1;

	int balance = lHeight - rHeight;

	// Left Left Case
	if (balance > 1 && value < (*pCurrentRoot)->left->data)
		rightRotate(&*pCurrentRoot);

	// Right Right Case
	if (balance < -1 && value >(*pCurrentRoot)->right->data)
		leftRotate(&*pCurrentRoot);

}

/*
int height(struct Node* N) 
{
	if (N == NULL)
		return 0;
	return N->height;
}
*/