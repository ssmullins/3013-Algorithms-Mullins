Name: Samuel Mullins
Date: March 25, 2018
Assignment: program_3
Description:
	The goal of this program was to take list of words, ie;(Adjectives, Adverbs, Animals, Nouns, Verbs),
	and create 10k crazy words out of them. A crazy word is a word made up of at least 2 but up to 5
	words from the list mentioned. After creating 10k words, we build a Binary Search Tree and an AVL Tree
	and fill them with the words from the 5 forementioned list. We then read in our 10k crazy words and
	break them down word by word and run a search in both the trees keeping track of how many comparisons
	it takes each tree to find the word and also how many of each type of word is seen while searching. We
	then output our data to an outfile and to the screen.
Files:
	generate_words.cpp
	BSTree.h
	tenthousandwords.txt
	word_files
		nouns.txt
		adverbs.txt
		animals.txt
		adjectives.txt
	verbs.txt
	README.md
	analysis.out
	analyze_trees.exe
	analyze_trees.cpp
	AVLtree.h