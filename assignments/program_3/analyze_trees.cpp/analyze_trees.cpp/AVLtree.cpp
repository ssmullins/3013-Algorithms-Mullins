#include <iostream>
#include <fstream>
#include <time.h>
#include "avlTree.h"

//https://visualgo.net/en/bst

using namespace std;

avlTree::avlTree() {
	root = NULL;
}

avlTree::~avlTree() {

}

//************************************************************************
// Method Name: insert
//
// Private 
//
// Purpose: Inserts a node into a binary tree
//
// Arguments: reference to the root, and a reference to the new node
//
// Returns: Nothing.
//*************************************************************************
void avlTree::insert(AVLnode *&nodePtr, AVLnode *&newNode) {

	if (nodePtr == NULL) {
		nodePtr = newNode;
	}
	else if (newNode->value <= nodePtr->value) {
		newNode->parent = nodePtr;
		insert(nodePtr->left, newNode);

	}
	else {
		newNode->parent = nodePtr;
		insert(nodePtr->right, newNode);
	}

}

//************************************************************************
// Method Name: insertNode
//
// Public 
//
// Purpose: Creates a new node and assigns the passed in value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location. 
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void avlTree::insert(string word, string type) {
	AVLnode *newNode;

	newNode = new AVLnode(word, type);
	insert(root, newNode);
	computeAvlValues(root);
}

//************************************************************************
// Method Name: inorder,postorder,preorder (all the same)
//
// Public 
//
// Purpose: Traverses a binary tree 
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void avlTree::inorder(AVLnode *nodePtr) {
	if (nodePtr) {
		inorder(nodePtr->left);
		cout << nodePtr->value << " " << "(" << nodePtr->avlValue << ") ";
		inorder(nodePtr->right);
	}
}

void avlTree::postorder(AVLnode *nodePtr) {
	if (nodePtr) {
		inorder(nodePtr->left);
		inorder(nodePtr->right);
		cout << nodePtr->value << " " << "(" << nodePtr->avlValue << ") ";
	}
}

void avlTree::preorder(AVLnode *nodePtr) {
	if (nodePtr) {
		cout << nodePtr->value << " " << "(" << nodePtr->avlValue << ") ";
		inorder(nodePtr->left);
		inorder(nodePtr->right);
	}
}

//************************************************************************
// Method Name: searchNode
//
// Public 
//
// Purpose: Traverses a binary tree looking for a key value
//
// Arguments: integer to look for
//
// Returns: true if found, false otherwise 
//*************************************************************************
bool avlTree::search(string word) {
	AVLnode *nodePtr = root;

	while (nodePtr) {
		if (nodePtr->value == word)
			return true;
		else if (word < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return false;
}


//************************************************************************
// Method Name: remove
//
// Private 
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of node to be deleted
//
// Returns: void 
//*************************************************************************

AVLnode* avlTree::remove(AVLnode*& root, string key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->value)
	{
		cout << "going left" << endl;
		root->left = remove(root->left, key);
	}
	else if (key > root->value)
	{
		cout << "going right" << endl;
		root->right = remove(root->right, key);
	}
	else
	{
		if (root->left == NULL)
		{
			AVLnode *temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			AVLnode *temp = root->left;
			delete root;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		AVLnode *temp = predSuccessor(root);

		printNode(temp, "predSuccessor");

		// Copy the inorder successor's content to this node
		root->value = temp->value;

		// Delete the inorder successor
		root->right = remove(root->right, temp->value);
	}
	return root;
}

void avlTree::printNode(AVLnode *n, string label = "")
{
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->value << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->value << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->value << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

AVLnode* avlTree::predSuccessor(AVLnode *root)
{
	AVLnode *current = root;

	if (root->right)
	{
		current = root->right;
		while (current->left != NULL)
		{
			current = current->left;
		}
	}
	else if (root->left)
	{
		current = root->left;
		while (current->right != NULL)
		{
			current = current->right;
		}
	}

	return current;
}
//************************************************************************
// Method Name: height
//
// Private 
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of the root of the tree (or subtree)
//
// Returns: void 
//*************************************************************************
int avlTree::height(AVLnode *nodePtr) {
	int left_height = 0;
	int right_height = 0;
	if (nodePtr == NULL)
		return 0;
	else {
		left_height = height(nodePtr->left);
		right_height = height(nodePtr->right);
	}
	if (left_height>right_height)
		return 1 + left_height;
	else
		return 1 + right_height;
}

//************************************************************************
// Method Name: treeHeight
//
// Public 
//
// Purpose: Public method to call the private height method
//
// Arguments: none
//
// Returns: void 
//*************************************************************************
int avlTree::treeHeight() {
	return height(root);
}

//************************************************************************
// Method Name: avlValue
//
// Private 
//
// Purpose: Private method to calculate the avl value of a node.
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
int avlTree::avlValue(AVLnode *nodePtr)
{
	return height(nodePtr->right) - height(nodePtr->left);
}

//************************************************************************
// Method Name: computeAvlValues
//
// Private 
//
// Purpose: Private method to calculate the avl values of the entire tree.
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
void avlTree::computeAvlValues(AVLnode *&nodePtr)
{
	if (nodePtr) {
		computeAvlValues(nodePtr->left);
		computeAvlValues(nodePtr->right);
		nodePtr->avlValue = avlValue(nodePtr);
		if (nodePtr->avlValue > 1) {
			rotateLeft(nodePtr);
		}
		else if (nodePtr->avlValue < -1) {
			rotateRight(nodePtr);
		}
	}
}

//************************************************************************
// Method Name: rotateLeft 
//
// Private 
//
// Purpose: Private method to perform a left rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
void avlTree::rotateLeft(AVLnode *&SubRoot)
{


	if (leftHeavy(SubRoot->right)) {
		rotateRight(SubRoot->right);
	}

	AVLnode *Temp;

	Temp = SubRoot->right;
	SubRoot->right = Temp->left;
	Temp->left = SubRoot;
	SubRoot = Temp;

	computeAvlValues(SubRoot);
}

//************************************************************************
// Method Name: rotateLeft 
//
// Private 
//
// Purpose: Private method to perform a right rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
void avlTree::rotateRight(AVLnode *&SubRoot)
{
	if (rightHeavy(SubRoot->left)) {
		rotateLeft(SubRoot->left);
	}

	AVLnode *Temp;

	Temp = SubRoot->left;
	SubRoot->left = Temp->right;
	Temp->right = SubRoot;
	SubRoot = Temp;

	computeAvlValues(SubRoot);
}

//************************************************************************
// Method to help create GraphViz code so the expression tree can 
// be visualized. This method prints out all the unique node id's
// by traversing the tree.
// Recivies a node pointer to root and performs a simple recursive 
// tree traversal.
//************************************************************************
void avlTree::graphVizGetIds(AVLnode *nodePtr, ofstream &VizOut) {
	static int NullCount = 0;
	if (nodePtr) {
		graphVizGetIds(nodePtr->left, VizOut);
		VizOut << "node" << nodePtr->value
			<< "[label=\"" << nodePtr->value << "\\n"
			<< "Avl:" << nodePtr->avlValue << "\\n"
			//<<"Add:"<<nodePtr<<"\\n"
			//<<"Par:"<<nodePtr->parent<<"\\n"
			//<<"Rt:"<<nodePtr->right<<"\\n"
			//<<"Lt:"<<nodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!nodePtr->left) {
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		graphVizGetIds(nodePtr->right, VizOut);
		if (!nodePtr->right) {
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;

		}
	}
}

//************************************************************************
// This method is partnered with the above method, but on this pass it 
// writes out the actual data from each node.
// Don't worry about what this method and the above method do, just
// use the output as your told:)
//************************************************************************
void avlTree::graphVizMakeConnections(AVLnode *nodePtr, ofstream &VizOut) {
	static int NullCount = 0;
	if (nodePtr) {
		graphVizMakeConnections(nodePtr->left, VizOut);
		if (nodePtr->left)
			VizOut << "node" << nodePtr->value << "->" << "node" << nodePtr->left->value << endl;
		else {
			NullCount++;
			VizOut << "node" << nodePtr->value << "->" << "nnode" << NullCount << endl;
		}

		if (nodePtr->right)
			VizOut << "node" << nodePtr->value << "->" << "node" << nodePtr->right->value << endl;
		else {
			NullCount++;
			VizOut << "node" << nodePtr->value << "->" << "nnode" << NullCount << endl;
		}

		graphVizMakeConnections(nodePtr->right, VizOut);

	}
}

//************************************************************************
// Recieves a filename to place the GraphViz data into.
// It then calls the above two graphviz methods to create a data file
// that can be used to visualize your expression tree.
//************************************************************************
void avlTree::graphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	graphVizGetIds(root, VizOut);
	graphVizMakeConnections(root, VizOut);
	VizOut.close();

}

//************************************************************************
// Method Name: doDumpTree 
//
// Private 
//
// Purpose: Private method to show the basic pointer structure of the tree. 
//          Initially written to help with debugging.
//
// Arguments: address of a node
//
// Returns: void 
// Outputs: tree information
//*************************************************************************
void avlTree::doDumpTree(AVLnode *nodePtr)
{
	if (nodePtr) {
		cout << "Add:    " << nodePtr << "\n"
			<< "Parent->" << nodePtr->parent << "\n"
			<< "Val:    " << nodePtr->value << "\n"
			<< "Avl:    " << nodePtr->avlValue << "\n"
			<< "Left->  " << nodePtr->left << "\n"
			<< "Right-> " << nodePtr->right << "\n\n";

		doDumpTree(nodePtr->left);
		doDumpTree(nodePtr->right);
	}
}

//************************************************************************
// Method Name: leftHeavy,rightHeavy 
//
// Private 
//
// Purpose: Compares the subtrees of a node to see which is taller
//
// Arguments: address of a node
//
// Returns: true if (left/right) heavy 
//
//*************************************************************************
bool avlTree::leftHeavy(AVLnode *nodePtr)
{
	return height(nodePtr->left)>height(nodePtr->right);
}

bool avlTree::rightHeavy(AVLnode *nodePtr)
{
	return height(nodePtr->right)>height(nodePtr->left);

}

/*This function builds an AVL tree and fills it with the words
from the list and returns the created AVL tree.*/
avlTree avlTree::buildTree() {
	avlTree aTree;
	string w;
	ifstream infile;

	infile.open("Adjectives.txt");
	while (getline(infile, w)) {
		aTree.insert(w, "Adjective");
	}
	infile.close();

	infile.open("Adverb.txt");
	while (getline(infile, w)) {
		aTree.insert(w, "Adverb");
	}
	infile.close();

	infile.open("Animals.txt");
	while (getline(infile, w)) {
		aTree.insert(w, "Animal");
	}
	infile.close();

	infile.open("Noun.txt");
	while (getline(infile, w)) {
		aTree.insert(w, "Noun");
	}
	infile.close();

	infile.open("Verb.txt");
	while (getline(infile, w)) {
		aTree.insert(w, "Verb");
	}
	infile.close();

	cout << "aTree created successfully" << endl;

	return aTree;
}

int avlTree::auxNumAdj(AVLnode *root, string w, int n)
{
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->value == w)
	{
		if (root->wtype == "Adjective")
			num++;
		return num;
	}
	else if (w < root->value)
	{
		if (root->wtype == "Adjective")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumAdj(root, w, num);

	}
	else if (w > root->value)
	{
		if (root->wtype == "Adjective")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumAdj(root, w, num);
	}
}
int avlTree::auxNumAdv(AVLnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->value == w)
	{
		if (root->wtype == "Adverb")
			num++;
		return num;
	}
	else if (w < root->value)
	{
		if (root->wtype == "Adverb")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumAdv(root, w, num);

	}
	else if (w > root->value)
	{
		if (root->wtype == "Adverb")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumAdv(root, w, num);
	}
}
int avlTree::auxNumAni(AVLnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->value == w)
	{
		if (root->wtype == "Animal")
			num++;
		return num;
	}
	else if (w < root->value)
	{
		if (root->wtype == "Animal")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumAni(root, w, num);

	}
	else if (w > root->value)
	{
		if (root->wtype == "Animal")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumAni(root, w, num);
	}
}
int avlTree::auxNumNoun(AVLnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->value == w)
	{
		if (root->wtype == "Noun")
			num++;
		return num;
	}
	else if (w < root->value)
	{
		if (root->wtype == "Noun")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumNoun(root, w, num);

	}
	else if (w > root->value)
	{
		if (root->wtype == "Noun")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumNoun(root, w, num);
	}
}
int avlTree::auxNumVerb(AVLnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->value == w)
	{
		if (root->wtype == "Verb")
			num++;
		return num;
	}
	else if (w < root->value)
	{
		if (root->wtype == "Verb")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumVerb(root, w, num);

	}
	else if (w > root->value)
	{
		if (root->wtype == "Verb")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumVerb(root, w, num);
	}
}

int avlTree::numAdj(string w)
{
	return avlTree::auxNumAdj(root, w, 0);
}
int avlTree::numAdv(string w)
{
	return avlTree::auxNumAdv(root, w, 0);
}
int avlTree::numAni(string w)
{
	return avlTree::auxNumAni(root, w, 0);
}
int avlTree::numNoun(string w)
{
	return avlTree::auxNumNoun(root, w, 0);
}
int avlTree::numVerb(string w)
{
	return avlTree::auxNumVerb(root, w, 0);
}

int avlTree::auxComparisons(AVLnode *root, string w, int x)
{
	int count = x;

	if (!root)
	{
		return NULL;
	}
	if (root->value == w)
	{
		++count;
		return count;
	}
	else if (w < root->value)
	{
		//cout << "going left" << endl;
		root = root->left;
		++count;
		return auxComparisons(root, w, count);

	}
	else if (w > root->value)
	{
		//cout << "going right" << endl;
		root = root->right;
		++count;
		return auxComparisons(root, w, count);
	}
}

int avlTree::comparisons(string w)
{
	return avlTree::auxComparisons(root, w, 0);

}