/* 
 * File:   main.cpp
 * Author: super0
 *
 * Created on December 15, 2015, 4:29 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "tree.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    cout << "Testing the Tree Class!!!\n\n";
    Tree<string> myTree;
    // Testing insertion and re-balancing
    string input;

    // height(), length(), isEmpty(), and getRoot() functions
    cout << "\nCreating an empty tree. Height of tree is "
            << myTree.height() << ". Size of the tree is " << myTree.length()
            << ". The root is: " << (!myTree.isEmpty() ? myTree.getRoot() : " Empty tree\n\n");
    // getRoot() throws an Empty() exception)

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();


    // insert(), height(), length(), and root() functions
    input = "canteloupe";
    myTree.insert(input);
    cout << "\nTesting myTree.insert(" << input << "). Height of tree is "
            << myTree.height() << ". Size of the tree is " << myTree.length()
            << ". The root is " << myTree.getRoot() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();


    // contains(), remove(), height(), and size() and contains functions
    cout << "\n\nTesting myTree.remove(" << input << ")\n";
    cout << "Tree contains " << input << (myTree.contains(input) ? ": true\n " : ": false\n");
    if (!myTree.isEmpty())
        myTree.remove(input);
    cout << "After removing " << input << " .Tree contains " << input
            << (myTree.contains(input) ? ": true\n" : ": false\n");
    cout << "Tree height is " << myTree.height() << " the tree is size "
            << myTree.length() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();


    // insert(), height(), length(), and root() functions
    input = "apple";
    myTree.insert(input);
    cout << "\nTesting myTree.insert(" << input << "). Height of tree is "
            << myTree.height() << ". Size of the tree is " << myTree.length()
            << ". The root is " << myTree.getRoot() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();

    // insert(), height(), length(), and root() functions
    input = "banana";
    myTree.insert(input);
    cout << "\nTesting myTree.insert(" << input << "). Height of tree is "
            << myTree.height() << ". Size of the tree is " << myTree.length()
            << ". The root is " << myTree.getRoot() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();

    // contains(), remove(), height(), and size() and contains functions
    cout << "\n\nTesting the remove function. \n";
    cout << "Tree contains " << input << (myTree.contains(input) ? ": true " : ": false\n");
    myTree.remove(input);
    cout << "After removing " << input << ".Tree contains " << input
            << (myTree.contains(input) ? ": true\n" : ":false\n");
    cout << "Tree height is " << myTree.height() << " the tree is size "
            << myTree.length() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();

    // insert(), height(), length(), and root() functions
    input = "cranberry";
    myTree.insert(input);
    cout << "\nTesting myTree.insert(" << input << "). Height of tree is "
            << myTree.height() << ". Size of the tree is " << myTree.length()
            << ". The root is " << myTree.getRoot() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();

    // insert(), height(), length(), and root() functions
    input = "pear";
    myTree.insert(input);
    cout << "\nTesting myTree.insert(" << input << "). Height of tree is "
            << myTree.height() << ". Size of the tree is " << myTree.length()
            << ". The root is " << myTree.getRoot() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();

    // insert(), height(), length(), and root() functions
    input = "pomegranate";
    myTree.insert(input);
    cout << "\nTesting myTree.insert(" << input << "). Height of tree is "
            << myTree.height() << ". Size of the tree is " << myTree.length()
            << ". The root is " << myTree.getRoot() << "\n\n";

    // inorder(), preorder(), postorder() functions
    cout << "\nContents of myTree in order:\n";
    cout << "\nItems in order:\n";
    myTree.inOrder();
    cout << "\nItems pre order:\n";
    myTree.preOrder();
    cout << "\nItems post order:\n";
    myTree.postOrder();
    cout << "\nItems level order:\n";
    myTree.levelOrder();

    Tree<string> newTree(input);
    cout << "\n\nTesting main constructor: Tree<string> newTree("
            << input << "). \nHeight of tree is " << newTree.height()
            << ". Size of the tree is " << newTree.length()
            << ". The root is " << newTree.getRoot() << "\n\n";


    // inorder(), preorder(), postorder() functions
    cout << "\nContents of newTree in order:\n";
    cout << "\nItems in order:\n";
    newTree.inOrder();
    cout << "\nItems pre order:\n";
    newTree.preOrder();
    cout << "\nItems post order:\n";
    newTree.postOrder();
    cout << "\nItems level order:\n";
    newTree.levelOrder();

    cout << "\n\nTesting the assignment operator newTree = myTree\n";
    newTree = myTree;
    cout << "\nItems in myTree in order:\n";
    myTree.inOrder();
    cout << "\nItems in newTree in order:\n";
    newTree.inOrder();

    cout << "\nItems in myTree pre order:\n";
    myTree.preOrder();
    cout << "\nItems in newTree pre order:\n";
    newTree.preOrder();

    cout << "\nItems in myTree post order:\n";
    myTree.postOrder();
    cout << "\nItems in newTree post order:\n";
    newTree.postOrder();

    cout << "\nItems in myTree level order:\n";
    myTree.levelOrder();
    cout << "\nItems in newTree level order:\n";
    newTree.levelOrder();

    cout << "Testing the copy constructor: tempTree(myTree)\n";
    Tree<string> tempTree(myTree);

    cout << "Contents of tempTtree in order: " << tempTree.toStringInOrder() << endl;
    cout << "Contents of myTtree in order: " << myTree.toStringInOrder() << endl;
    cout << "\nContents of tempTtree in preorder: " << tempTree.toStringPreOrder() << endl;
    cout << "Contents of myTtree in preorder: " << myTree.toStringPreOrder() << endl;
    cout << "\nContents of tempTtree in postorder: " << tempTree.toStringPreOrder() << endl;
    cout << "Contents of myTtree in postorder: " << myTree.toStringPreOrder() << endl;
    cout << "\nContents of tempTtree in level-order: " << tempTree.toStringLevelOrder() << endl;
    cout << "Contents of myTtree in level-order: " << myTree.toStringLevelOrder() << endl;
    
    cout<<"\nTesting the tempTree.clear() function\n";
    tempTree.clear();
    cout<<"Is tempTree empty now"<< (tempTree.isEmpty() ? ": true " : ": false\n")
            << "Size of tempTree now:"<< tempTree.length() << endl;

    return 0;
}

