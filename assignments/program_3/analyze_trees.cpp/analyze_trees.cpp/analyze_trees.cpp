#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include"AVLtree.h"
#include"BSTree.h"

using namespace std;

int main(int argc, char** argv) {
	//string wordfile = argv[1];
	//cout << wordfile << endl;
	
	ifstream infile;
	infile.open(argv[1]);

	BSTree bTree = bTree.buildTree();
	avlTree aTree = aTree.buildTree();

	string in_word;
	int bnumComps = 0;
	int bnumAdjectives = 0;
	int bnumAdverbs = 0;
	int bnumAnimals = 0;
	int bnumNouns = 0;
	int bnumVerbs = 0;

	while (infile >> in_word)
	{
		//cout << in_word << " BST Comparisons = " << bTree.comparisons(in_word) << endl;
		bnumComps += bTree.comparisons(in_word);
		bnumAdjectives += bTree.numAdj(in_word);
		bnumAdverbs += bTree.numAdv(in_word);
		bnumAnimals += bTree.numAni(in_word);
		bnumNouns += bTree.numNoun(in_word);
		bnumVerbs += bTree.numVerb(in_word);
	}
	ofstream outfile("analysis.out");
	cout << "BST Comparisons = " << bnumComps << endl;
	cout << "Number of Adjectives = " << bnumAdjectives << endl;
	cout << "Number of Adverbs = " << bnumAdverbs << endl;
	cout << "Number of Animals = " << bnumAnimals << endl;
	cout << "Number of Nouns = " << bnumNouns << endl;
	cout << "Number of Verbs = " << bnumVerbs << endl;
	outfile << "BST Comparisons = " << bnumComps << endl;
	outfile << "Number of Adjectives = " << bnumAdjectives << endl;
	outfile << "Number of Adverbs = " << bnumAdverbs << endl;
	outfile << "Number of Animals = " << bnumAnimals << endl;
	outfile << "Number of Nouns = " << bnumNouns << endl;
	outfile << "Number of Verbs = " << bnumVerbs << endl;
	infile.close();

	int anumComps = 0;
	int anumAdjectives = 0;
	int anumAdverbs = 0;
	int anumAnimals = 0;
	int anumNouns = 0;
	int anumVerbs = 0;

	infile.open(argv[1]);
	while (infile >> in_word)
	{
		infile >> in_word;
		//cout << in_word << "AVL Comparisons = " << avlTree.comparisons(in_word) << endl;
		anumComps += aTree.comparisons(in_word);
		anumAdjectives += aTree.numAdj(in_word);
		anumAdverbs += aTree.numAdv(in_word);
		anumAnimals += aTree.numAni(in_word);
		anumNouns += aTree.numNoun(in_word);
		anumVerbs += aTree.numVerb(in_word);
	}
	cout << "AVL Comparisons = " << anumComps << endl;
	cout << "Number of Adjectives = " << anumAdjectives << endl;
	cout << "Number of Adverbs = " << anumAdverbs << endl;
	cout << "Number of Animals = " << anumAnimals << endl;
	cout << "Number of Nouns = " << anumNouns << endl;
	cout << "Number of Verbs = " << anumVerbs << endl;
	outfile << "AVL Comparisons = " << anumComps << endl;
	outfile << "Number of Adjectives = " << anumAdjectives << endl;
	outfile << "Number of Adverbs = " << anumAdverbs << endl;
	outfile << "Number of Animals = " << anumAnimals << endl;
	outfile << "Number of Nouns = " << anumNouns << endl;
	outfile << "Number of Verbs = " << anumVerbs << endl;
	
	infile.close();
	outfile.close();

	return 0;
}