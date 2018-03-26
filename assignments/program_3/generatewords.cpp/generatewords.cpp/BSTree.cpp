#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BSTree.h"

//http://www.webgraphviz.com/

using namespace std;


int BSTree::count(BSTnode *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		return 1 + count(root->left) + count(root->right);
	}
}

void BSTree::insert(BSTnode *&root, BSTnode *&temp)
{
	if (!root)
	{
		root = temp;
	}
	else
	{
		if (temp->data < root->data)
		{
			insert(root->left, temp);
		}
		else
		{
			insert(root->right, temp);
		}
	}
}

void BSTree::print_node(BSTnode *n, string label = "")
{
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->data << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

/**
* type = ['predecessor','successor']
*/
BSTnode * BSTree::minValueNode(BSTnode *root)
{
	BSTnode *current = root;

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

BSTnode * BSTree::deleteNode(BSTnode *&root, string key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->data)
	{
		cout << "going left" << endl;
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data)
	{
		cout << "going right" << endl;
		root->right = deleteNode(root->right, key);
	}
	else
	{
		if (root->left == NULL)
		{
			BSTnode *temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			BSTnode *temp = root->left;
			delete root;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		BSTnode *temp = minValueNode(root);

		print_node(temp, "minvaluenode");

		// Copy the inorder successor's content to this node
		root->data = temp->data;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}

int BSTree::height(BSTnode *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int left = height(root->left);
		int right = height(root->right);
		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

/* Print nodes at a given level */
void BSTree::printGivenLevel(BSTnode *root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		print_node(root);
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}
//************************************************************************
// Method to help create GraphViz code so the expression tree can
// be visualized. This method prints out all the unique node id's
// by traversing the tree.
// Recivies a node pointer to root and performs a simple recursive
// tree traversal.
//************************************************************************
void BSTree::GraphVizGetIds(BSTnode *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizGetIds(nodePtr->left, VizOut);
		VizOut << "node" << nodePtr->data
			<< "[label=\"" << nodePtr->data << "\\n"
			//<<"Add:"<<nodePtr<<"\\n"
			//<<"Par:"<<nodePtr->parent<<"\\n"
			//<<"Rt:"<<nodePtr->right<<"\\n"
			//<<"Lt:"<<nodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!nodePtr->left)
		{
			NullCount++;
			VizOut << "nnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		GraphVizGetIds(nodePtr->right, VizOut);
		if (!nodePtr->right)
		{
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
void BSTree::GraphVizMakeConnections(BSTnode *nodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (nodePtr)
	{
		GraphVizMakeConnections(nodePtr->left, VizOut);
		if (nodePtr->left)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->left->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		if (nodePtr->right)
			VizOut << "node" << nodePtr->data << "->"
			<< "node" << nodePtr->right->data << endl;
		else
		{
			NullCount++;
			VizOut << "node" << nodePtr->data << "->"
				<< "nnode" << NullCount << endl;
		}

		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}

int BSTree::auxComparisons(BSTnode *root, string w, int x)
{
	int count = x;

	if (!root)
	{
		return NULL;
	}
	if (root->data == w)
	{
		++count;
		return count;
	}
	else if (w < root->data)
	{
		cout << "going left" << endl;
		root = root->left;
		++count;
		return auxComparisons(root, w, count);

	}
	else if (w > root->data)
	{
		cout << "going right" << endl;
		root = root->right;
		++count;
		return auxComparisons(root, w, count);
	}
}

int BSTree::comparisons(string w)
{
	return BSTree::auxComparisons(root, w, 0);

}

BSTree::BSTree()
{
	root = NULL;
}
BSTree::~BSTree()
{
}

int BSTree::count()
{
	return count(root);
}

void BSTree::insert(string x, string w)
{
	BSTnode *temp = new BSTnode(x, w);
	insert(root, temp);
}

void BSTree::deleteNode(string key)
{
	deleteNode(root, key);
}

void BSTree::minValue()
{
	print_node(minValueNode(root), "minVal");
}

int BSTree::height(string key = "")
{
	if (key != "")
	{
		//find node
	}
	else
	{
		return height(root);
	}
	return 0;
}

string BSTree::top()
{
	if (root)
		return root->data;
	else
		return 0;
}

/* Function to line by line print level order traversal a tree*/
void BSTree::printLevelOrder()
{
	cout << "Begin Level Order===================\n";
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printGivenLevel(root, i);
		cout << "\n";
	}
	cout << "End Level Order===================\n";
}

//************************************************************************
// Recieves a filename to place the GraphViz data into.
// It then calls the above two graphviz methods to create a data file
// that can be used to visualize your expression tree.
//************************************************************************
void BSTree::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	VizOut << "Digraph G {\n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "}\n";
	VizOut.close();
}

/*This function creates a BST and fills it with the words from the
given list then returns the created BST.*/
BSTree BSTree::buildTree() {
	BSTree bTree;
	string w;
	ifstream infile;

	infile.open("Adjectives.txt");
	while (getline(infile, w)) {
		bTree.insert(w, "Adjective");
	}
	infile.close();

	infile.open("Adverb.txt");
	while (getline(infile, w)) {
		bTree.insert(w, "Adverb");
	}
	infile.close();

	infile.open("Animals.txt");
	while (getline(infile, w)) {
		bTree.insert(w, "Animal");
	}
	infile.close();

	infile.open("Noun.txt");
	while (getline(infile, w)) {
		bTree.insert(w, "Noun");
	}
	infile.close();

	infile.open("Verb.txt");
	while (getline(infile, w)) {
		bTree.insert(w, "Verb");
	}
	infile.close();

	cout << "bTree created successfully" << endl;

	return bTree;
}

int BSTree::auxNumAdj(BSTnode *root, string w, int n)
{
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->data == w)
	{
		if (root->wtype == "Adjective")
			num++;
		return num;
	}
	else if (w < root->data)
	{
		if (root->wtype == "Adjective")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumAdj(root, w, num);

	}
	else if (w > root->data)
	{
		if (root->wtype == "Adjective")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumAdj(root, w, num);
	}
}
int BSTree::auxNumAdv(BSTnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->data == w)
	{
		if (root->wtype == "Adverb")
			num++;
		return num;
	}
	else if (w < root->data)
	{
		if (root->wtype == "Adverb")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumAdv(root, w, num);

	}
	else if (w > root->data)
	{
		if (root->wtype == "Adverb")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumAdv(root, w, num);
	}
}
int BSTree::auxNumAni(BSTnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->data == w)
	{
		if (root->wtype == "Animal")
			num++;
		return num;
	}
	else if (w < root->data)
	{
		if (root->wtype == "Animal")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumAni(root, w, num);

	}
	else if (w > root->data)
	{
		if (root->wtype == "Animal")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumAni(root, w, num);
	}
}
int BSTree::auxNumNoun(BSTnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->data == w)
	{
		if (root->wtype == "Noun")
			num++;
		return num;
	}
	else if (w < root->data)
	{
		if (root->wtype == "Noun")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumNoun(root, w, num);

	}
	else if (w > root->data)
	{
		if (root->wtype == "Noun")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumNoun(root, w, num);
	}
}
int BSTree::auxNumVerb(BSTnode *root, string w, int n) {
	int num = n;

	if (!root)
	{
		return NULL;
	}
	if (root->data == w)
	{
		if (root->wtype == "Verb")
			num++;
		return num;
	}
	else if (w < root->data)
	{
		if (root->wtype == "Verb")
			num++;
		//cout << "going left" << endl;
		root = root->left;
		return auxNumVerb(root, w, num);

	}
	else if (w > root->data)
	{
		if (root->wtype == "Verb")
			num++;
		//cout << "going right" << endl;
		root = root->right;
		return auxNumVerb(root, w, num);
	}
}

int BSTree::numAdj(string w)
{
	return BSTree::auxNumAdj(root, w, 0);
}
int BSTree::numAdv(string w)
{
	return BSTree::auxNumAdv(root, w, 0);
}
int BSTree::numAni(string w)
{
	return BSTree::auxNumAni(root, w, 0);
}
int BSTree::numNoun(string w)
{
	return BSTree::auxNumNoun(root, w, 0);
}
int BSTree::numVerb(string w)
{
	return BSTree::auxNumVerb(root, w, 0);
}