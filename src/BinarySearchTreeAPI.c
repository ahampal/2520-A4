#include "BinarySearchTreeAPI.h"

/**
 * Creates a TreeNode. TreeNode children are set to NULL and data is set to the passed in data.
 * @param data - the data to be stored within the Node. 
 * @return Newly created TreeNode
 *
 */
TreeNode* createTreeNode(TreeDataPtr data) {
	TreeNode *newNode;
	newNode = malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parentTree = NULL;
	return newNode;
}

/**
 * createBinTree allocates memory for Tree and assigned function pointers
 * @param  compare [Function pointer to Compare data in tree nodes]
 * @param  del     [Function pointer to delete data from node]
 * @return Newly created Tree
 */
Tree * createBinTree(CompareFunc compare, DeleteFunc del) {
	Tree *newTree;
	newTree = malloc(sizeof(Tree));
	newTree->root = NULL;
	newTree->compareFunc = compare;
	newTree->deleteFunc = del;
	return newTree;
}

/**
 * destroyBinTree - remove all items and free memory
 * @param  toDestroy - the tree
 * @return
 */
void  destroyBinTree(Tree * toDestroy) {
	if(toDestroy == NULL) {
		return;
	}
	delTree(toDestroy->root, toDestroy->deleteFunc, toDestroy->compareFunc);
	free(toDestroy);
	toDestroy = NULL;
	return;
}

/**
 * Add data to a tree
 * @param theTree 
 * @param data    
 */
void addToTree(Tree * theTree, TreeDataPtr data) {
	theTree->root = insert(theTree->root, data, theTree->compareFunc, theTree);
	return;
}
		
/**
 * Remove data from the tree
 * @param theTree 
 * @param data    
 */
void removeFromTree(Tree * theTree, TreeDataPtr data) {
	theTree->root = deleteNode(theTree->root, data, theTree->compareFunc, theTree->deleteFunc);
	return;
}


/**
 * This function searches the tree for the target data
 * @param  theTree 
 * @param  data    
 * @return         NULL if fail, otherwise return data
 */
TreeDataPtr findInTree( Tree* theTree, TreeDataPtr data ) {
	TreeNode *currNode = NULL;
	currNode = findNode(theTree->root, data, theTree->compareFunc);
	if(currNode != NULL) {
		return currNode->data;
	}
	return NULL;
}

/**
 * Get data from the root of the Tree if it exists.
 * @param  theTree 
 * @return NULL if tree is empty, otherwise return root
 */
TreeDataPtr getRootData(Tree * theTree) {
	TreeDataPtr data;
	if(theTree == NULL) {
		return NULL;
	}
	if(theTree->root == NULL) {
		return NULL;
	}
	return data = theTree->root->data;
}

/**
 * [printInOrder This function prints the tree using an inOrder traversal
 * @param theTree   [pointer to the tree]
 * @param printData [pointer to the print function]
 */
void printInOrder(Tree * theTree, PrintFunc printData) {
	if(isTreeEmpty(theTree) == 1) {
		printf("Empty Tree\n");
	}
	else {
		inOrder(theTree->root, printData);
	}
}

/**
 * [printPreOrder This function prints the tree using an preOrder traversal
 * @param theTree   [pointer to the tree]
 * @param printData [pointer to the print function]
 */
void printPreOrder(Tree * theTree, PrintFunc printData) {
	if(isTreeEmpty(theTree) == 1) {
		printf("Empty Tree\n");
	}
	else {
		preOrder(theTree->root, printData);
	}
}

/**
 * [printPostOrder This function prints the tree using an postOrder traversal
 * @param theTree   [pointer to the tree]
 * @param printData [pointer to the print function]
 */
void printPostOrder(Tree * theTree, PrintFunc printData) {
	if(isTreeEmpty(theTree) == 1) {
		printf("Empty Tree\n");
	}
	else {
		postOrder(theTree->root, printData);
	}
}

/**
 * Checks if a tree is empty
 * @param  theTee [pointer to the tree]
 * @return        0 if false, 1 otherwise
 */
int isTreeEmpty(Tree* theTee) {
	if(theTee == NULL) {
		return 1;
	}
	else if(theTee->root == NULL) {
		return 1;
	}
	else if(theTee->root->data == NULL) {
		return 1;
	}
	return 0;
}

/**
 * Helper function for checking if a single node is a leaf (no children)
 * @param  treeNode [pointer to the node being checked]
 * @return          0 if false, 1 otherwise
 */
int isLeaf( TreeNode * treeNode) {
	if(treeNode == NULL) {
		return 0;
	}
	if(treeNode->left == NULL && treeNode->right == NULL) {
		return 1;
	}
	return 0;
}

/**
 * Helper funciton for checking if a single node has two children.
 * @param  treeNode [pointer to node being checked]
 * @return         0 if false, 1 otherwise
 */
int hasTwoChildren( TreeNode *treeNode) {
	if(treeNode->left != NULL && treeNode->right != NULL) {
		return 1;
	}
	return 0;
}

/**
 * Helper funciton Get the height of a particulat Node in the tree. 
 * @param  treeNode [pointer to node being checked]
 * @return    (1-Based) heigh for the tree. 
 */
int getHeight( TreeNode* treeNode ) {
	TreeNode *root = treeNode->parentTree->root;
	int count;
	count = 1;
	while(isLeaf(root) == 0) {
		if(treeNode->parentTree->compareFunc(root, treeNode) > 0) {
			count++;
			root = root->left;
		}
		else if(treeNode->parentTree->compareFunc(root, treeNode) < 0) {
			count++;
			root = root->right;
		}
		else {
			break;
		}
	}
	return count;
}

/**
 * Internal function to print tree in pre order
 * @param treeNode
 * @param print function pointer
 */
void preOrder(TreeNode *root, PrintFunc printFunction) {
	if(root == NULL) {
		return;
	}
	printFunction(root->data);
	preOrder(root->left, printFunction);
	preOrder(root->right, printFunction);
}

/**
 * Internal function to print tree in in order
 * @param treeNode
 * @param print function pointer
 */
void inOrder(TreeNode *root, PrintFunc printFunction) {
	if(root == NULL) {
		return;
	}
	inOrder(root->left, printFunction);
	printFunction(root->data);
	inOrder(root->right, printFunction);
}

/**
 * Internal function to print tree in post order
 * @param treeNode
 * @param print function pointer
 */
void postOrder(TreeNode *root, PrintFunc printFunction) {
	if(root == NULL) {
		return;
	}
	postOrder(root->left, printFunction);
	postOrder(root->right, printFunction);
	printFunction(root->data);
}
/**
 * Internal function to delete the entire tree, recursivel
 * @param root 
 * @param del
 * @param compareData
 */
void delTree(TreeNode *root, DeleteFunc del, CompareFunc compareData) {
	if(root == NULL) {
		return;
	}
	delTree(root->left, del, compareData);
	delTree(root->right, del, compareData);
	del(root->data);
	free(root);
}

/**
 * Internal function to insert a node into the tree
 * @param root
 * @param data pointer
 * @param compare function pointer
 * @param tree pointer
 * @return pointer to node that has been inserted
 */
TreeNode* insert(TreeNode *root, TreeDataPtr data, CompareFunc compareData, Tree *theTree){
	if(root == NULL) {
		TreeNode *newNode = createTreeNode(data);
		newNode->parentTree = theTree;
		return newNode;
	}
	if(compareData(root->data, data) > 0) {
		root->left = insert(root->left, data, compareData, theTree);
	}
	else if(compareData(root->data, data) < 0) {
		root->right = insert(root->right, data, compareData, theTree);
	}
	return root;
}

/**
 * Internal function to find a node in tree
 * @param pointer to root
 * @param pointer to data
 * @param pointer to compare function
 * @return pointer to found node, NULL if not found
 */
TreeNode* findNode(TreeNode *root, TreeDataPtr data, CompareFunc cd) {
	TreeNode *currNode = root;
	TreeNode *search = NULL;
	if(currNode != NULL) {
		if(cd(currNode->data, data) == 0) {
			return currNode;
		}
		else {
			search = findNode(currNode->left, data, cd);
			if(search == NULL) {
				search = findNode(currNode->right, data, cd);
			}
			return search;
		}
	}
	else {
		return NULL;
	}
}

/**
 * Internal delete function
 * @param pointer to root node
 * @param pointer to data
 * @param compare function pointer
 * @param delete function pointer
 * @return pointer to altered node
 */
TreeNode* deleteNode(TreeNode *root, TreeDataPtr data, CompareFunc compareData, DeleteFunc del) {
	int returnVal = 0;
	if(root == NULL) {
		return root;
	}
	returnVal = compareData(root->data, data);
	if (returnVal > 0) {
		root->left = deleteNode(root->left, data, compareData, del);
	}
	else if(returnVal < 0) {
		root->right = deleteNode(root->right, data, compareData, del);
	}
	else if(returnVal == 0){
		if(isLeaf(root) == 1) {
			del(root->data);
			free(root);
			root = NULL;
		}
		else if(root->left == NULL) {
			TreeNode *tmp;
			tmp = root;
			root = root->right;
			del(tmp->data);
			free(tmp);
			tmp = NULL;
		}
		else if(root->right == NULL) {
			TreeNode *tmp;
			tmp = root;
			root = root->left;
			del(tmp->data);
			free(tmp);
			tmp = NULL;
		}
		else  {
			TreeNode *newRoot;
			newRoot = findMax(root->left);
			root->data = newRoot->data;
			root->left = deleteNode(root->left, newRoot->data, compareData, del);
		}
	}
	return root;
}												
/**
 * Function to find the maximum node in a tree
 * @param pointer to root
 * @return pointer to max node
 */
TreeNode* findMax(TreeNode *root) {
	while(root->right != NULL) {
		root= root->right;
	}
	return root;
}
