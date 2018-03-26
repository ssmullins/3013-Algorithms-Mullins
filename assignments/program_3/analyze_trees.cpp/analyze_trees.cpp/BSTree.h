#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//http://www.webgraphviz.com/

using namespace std;

struct BSTnode
{
	string data;
	string wtype;
	BSTnode *left;
	BSTnode *right;
	BSTnode()
	{
		data = "";
		wtype = "";
		left = NULL;
		right = NULL;
	}
	BSTnode(string w, string x)
	{
		data = w;
		wtype = x;
		left = NULL;
		right = NULL;
	}
};

class BSTree {

private:
	BSTnode * root;
	int count(BSTnode *);
	void insert(BSTnode *&, BSTnode *&);
	void print_node(BSTnode *, string);
	BSTnode *minValueNode(BSTnode *);
	BSTnode *deleteNode(BSTnode *&, string);
	int height(BSTnode *);
	void printGivenLevel(BSTnode *, int);
	void GraphVizGetIds(BSTnode *, ofstream &);
	void GraphVizMakeConnections(BSTnode *, ofstream &);
	int auxComparisons(BSTnode *, string, int);
	int auxNumAdj(BSTnode *, string, int);
	int auxNumAdv(BSTnode *, string, int);
	int auxNumAni(BSTnode *, string, int);
	int auxNumNoun(BSTnode *, string, int);
	int auxNumVerb(BSTnode *, string, int);


public:
	BSTree();
	~BSTree();
	int count();
	void insert(string, string);
	void deleteNode(string);
	void minValue();
	int height(string);
	string top();
	void printLevelOrder();
	void GraphVizOut(string);
	int comparisons(string);
	BSTree buildTree();
	int numAdj(string);
	int numAdv(string);
	int numAni(string);
	int numNoun(string);
	int numVerb(string);
};