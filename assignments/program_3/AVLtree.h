#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

struct AVLnode {
	string value;
	string wtype;
	AVLnode *left;
	AVLnode *right;
	AVLnode *parent;
	int avlValue;
	AVLnode(string word, string type) {
		value = word;
		wtype = type;
		left = right = parent = NULL;
		avlValue = 0;
	}
};

class avlTree {

private:
	AVLnode * root;
	bool rightHeavy(AVLnode *);
	bool leftHeavy(AVLnode *);
	void insert(AVLnode *&, AVLnode *&);
	void inorder(AVLnode *);
	void preorder(AVLnode *);
	void postorder(AVLnode *);
	AVLnode* remove(AVLnode*&, string);
	AVLnode* predSuccessor(AVLnode*);
	void printNode(AVLnode *, string);
	int  height(AVLnode *);
	void computeAvlValues(AVLnode *&);
	void rotateLeft(AVLnode *&);
	void rotateRight(AVLnode *&);
	int  avlValue(AVLnode *);
	int auxNumAdj(AVLnode *, string, int);
	int auxNumAdv(AVLnode *, string, int);
	int auxNumAni(AVLnode *, string, int);
	int auxNumNoun(AVLnode *, string, int);
	int auxNumVerb(AVLnode *, string, int);
	int auxComparisons(AVLnode *, string, int);


public:
	avlTree();
	~avlTree();
	void doDumpTree(AVLnode *);
	void dumpTree() {
		cout << "---------------------------------" << endl;
		cout << "Root:   " << root << "\n";
		doDumpTree(root);
	};
	void insert(string, string);
	void showInorder() { inorder(root); };
	void showPreorder() { preorder(root); };
	void showPostorder() { postorder(root); };
	bool search(string);
	void remove(string word) { root = remove(root, word); };
	int  treeHeight();
	void graphVizGetIds(AVLnode *, ofstream &);
	void graphVizMakeConnections(AVLnode *, ofstream &);
	void graphVizOut(string);
	avlTree buildTree();
	int numAdj(string);
	int numAdv(string);
	int numAni(string);
	int numNoun(string);
	int numVerb(string);
	int comparisons(string);
};