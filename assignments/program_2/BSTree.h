#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct node

{

	int data;

	node *left;

	node *right;

	node()

	{

		data = -1;

		left = NULL;

		right = NULL;

	}

	node(int x)

	{

		data = x;

		left = NULL;

		right = NULL;

	}

};

class BSTree

{

  private:

    node *root;

    int count(node *);

    void insert(node *&, node *&emp);

    void print_node(node *, string);

    int height(node *);

    /* Print nodes at a given level */

    void printGivenLevel(node *, int );

    //************************************************************************

    // Method to help create GraphViz code so the expression tree can

    // be visualized. This method prints out all the unique node id's

    // by traversing the tree.

    // Recivies a node pointer to root and performs a simple recursive

    // tree traversal.

    //************************************************************************

    void GraphVizGetIds(node *, ofstream &VizOut);

    //************************************************************************

    // This method is partnered with the above method, but on this pass it

    // writes out the actual data from each node.

    // Don't worry about what this method and the above method do, just

    // use the output as your told:)

    //************************************************************************

    void GraphVizMakeConnections(node *, ofstream &VizOut);

  public:

	BSTree();

	~BSTree();

    int count();

    void insert(int);

    void DeleteNode(int);

    void minValue();

    int height(int);

    int top();

     /* Function to line by line print level order traversal a tree*/

    void printLevelOrder();

    //************************************************************************

    // Recieves a filename to place the GraphViz data into.

    // It then calls the above two graphviz methods to create a data file

    // that can be used to visualize your expression tree.

    //************************************************************************

    void GraphVizOut(string);

};