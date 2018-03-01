#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BSTree.h"

using namespace std;

int main()

{

    srand(2342);



    BSTree B;



    B.insert(38);

    B.insert(10);

    B.insert(29);

    B.insert(27);

    B.insert(5);

    B.insert(43);

    B.insert(36);

    B.insert(3);

    B.printLevelOrder();

    B.GraphVizOut("before.txt");



     while(B.top()){

         cout<<"removing: "<<B.top()<<endl;

         B.DeleteNode(B.top());

     }



    B.DeleteNode(3);

    B.DeleteNode(29);

    B.DeleteNode(27);

    B.DeleteNode(10);

    B.printLevelOrder();



    B.GraphVizOut("after.txt");

    return 0;

}