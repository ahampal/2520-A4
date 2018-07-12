#ifndef BST_GUARD
#define BST_GUARD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

/**************************************
Interface for a Binary Tree ADT
Author:  Judi McCuaig
October, 2012
Modfied: James Fraser (Nov 2017)
**************************************/

/**
 * Function pointer tyepdefs
 */
typedef int (*CompareFunc)(const void* a, const void* b);
typedef void (*DeleteFunc)(void* data);
typedef void (*PrintFunc)(void* data);

/*
 * Typedef the void* to make the API cleaner and more readable.
 */
typedef void* TreeDataPtr;

/*
 * A Single Binary Tree Node.
 * Left and Right branches
 * void* data
 */
typedef struct binTreeNode TreeNode;
struct binTreeNode{
	TreeDataPtr data;
	TreeNode * left;
	TreeNode * right;
    struct binTree* parentTree;
};

/**
 * This is the definition of the Binary Tree.
 *
 */
typedef struct binTree
{
	TreeNode *root;
	CompareFunc compareFunc;
	DeleteFunc deleteFunc;

	// Additions must work with abstract data types.
	// Additional function pointers to generalize tree.
	// Additional properties can be added such as count.
} Tree;

/**
 * Creates a TreeNode. TreeNode children are set to NULL and data is set to the passed in data.
 * @param data - the data to be stored within the Node. 
 * @return Newly created TreeNode
 *
 */
TreeNode* createTreeNode(TreeDataPtr data);

/**
 * createBinTree allocates memory for Tree and assigned function pointers
 * @param  compare [Function pointer to Compare data in tree nodes]
 * @param  del     [Function pointer to delete data from node]
 * @return Newly created Tree
 */
Tree * createBinTree(CompareFunc compare, DeleteFunc del);

/**
 * destroyBinTree - remove all items and free memory
 * @param  toDestroy - the tree
 * @return
 */
void  destroyBinTree(Tree * toDestroy);

/**
 * Add data to a tree
 * @param theTree 
 * @param data    
 */
void addToTree(Tree * theTree, TreeDataPtr data);

/**
 * Remove data from the tree
 * @param theTree 
 * @param data    
 */
void removeFromTree(Tree * theTree, TreeDataPtr data);


/**
 * This function searches the tree for the target data
 * @param  theTree 
 * @param  data    
 * @return         NULL if fail, otherwise return data
 */
TreeDataPtr findInTree( Tree* theTree, TreeDataPtr data );

/**
 * Get data from the root of the Tree if it exists.
 * @param  theTree 
 * @return NULL if tree is empty, otherwise return root
 */
TreeDataPtr getRootData(Tree * theTree);

/**
 * [printInOrder This function prints the tree using an inOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printInOrder(Tree * theTree, PrintFunc printData);

/**
 * [printPreOrder This function prints the tree using an preOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printPreOrder(Tree * theTree, PrintFunc printData);

/**
 * [printPostOrder This function prints the tree using an postOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printPostOrder(Tree * theTree, PrintFunc printData);

/**
 * Checks if a tree is empty
 * @param  theTee [description]
 * @return        0 if false, 1 otherwise
 */
int isTreeEmpty(Tree* theTee);


/**
 * Helper function for checking if a single node is a leaf (no children)
 * @param  treeNode [description]
 * @return          0 if false, 1 otherwise
 */
int isLeaf( TreeNode * treeNode);

/**
 * Helper funciton for checking if a single node has two children.
 * @param  treeNode [description]
 * @return         0 if false, 1 otherwise
 */
int hasTwoChildren( TreeNode *treeNode);

/**
 * Helper funciton Get the height of a particulat Node in the tree. 
 * @param  treeNode [description]
 * @return    (1-Based) heigh for the tree. 
 */
int getHeight( TreeNode* treeNode );


/**
 * You may add additional API functions below this comment if you want to extend the funcitonality.
 */

/**
 * Internal function to print tree in pre order
 * @param treeNode
 * @param print function pointer
 */
void preOrder(TreeNode *root, PrintFunc printFunction);

/**
 * Internal function to print tree in in order
 * @param treeNode
 * @param print function pointer
 */
void inOrder(TreeNode *root, PrintFunc printFunction);

/**
 * Internal function to print tree in post order
 * @param treeNode
 * @param print function pointer
 */
void postOrder(TreeNode *root, PrintFunc printFunction);

/**
 * Internal function to delete the entire tree, recursivel
 * @param root 
 * @param del
 * @param compareData
 */
void delTree(TreeNode *root, DeleteFunc del, CompareFunc compareData);

/**
 * Internal function to insert a node into the tree
 * @param root
 * @param data pointer
 * @param compare function pointer
 * @param tree pointer
 * @return pointer to node that has been inserted
 */
TreeNode* insert(TreeNode *root, TreeDataPtr data, CompareFunc compareData, Tree *theTree);

/**
 * Internal delete function
 * @param pointer to root node
 * @param pointer to data
 * @param compare function pointer
 * @param delete function pointer
 * @return pointer to altered node
 */
TreeNode* deleteNode(TreeNode *root, TreeDataPtr data, CompareFunc compareData, DeleteFunc del);

/**
 * Function to find the maximum node in a tree
 * @param pointer to root
 * @return pointer to max node
 */
TreeNode* findMax(TreeNode *root);

/**
 * Internal function to find a node in tree
 * @param pointer to root
 * @param pointer to data
 * @param pointer to compare function
 * @return pointer to found node, NULL if not found
 */
TreeNode* findNode(TreeNode *root, TreeDataPtr data, CompareFunc cd);


#endif
