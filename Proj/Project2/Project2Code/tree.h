/* 
 * File:   tree.h
 * Author: Marlo Zeroth
 * Implements a template AVL tree
 * Created on December 15, 2015, 4:30 PM
 */

#ifndef TREE_H
#define	TREE_H

#include <sstream>
#include <string>
#include <QList>

#include "empty.h"
#include "stack.h"
#include "queue.h"
#include "list.h"

template <class T>
class Tree {
private:
    // Tree node struct

    struct Node {

        Node(T input, Node* leftChild, Node* rightChild) : data(input), left(leftChild), right(rightChild) {
        }

        ~Node() {
            delete left;
            delete right;
            left = NULL;
            right = NULL;
        }

        bool isLeaf() {
            return (left == NULL && right == NULL) ? true : false;
        }
        // Returns true if the node is a leaf and false otherwise

        T data;
        Node *left;
        Node *right;
    };

    // Utility struct to aid in balancing a tree. Keeps the parent and child node addresses    

    struct NodePair {
        Node *currentNode;
        Node *parentNode;
    };

    // Member node variables
    Node *root;
    unsigned int size; // Total number of nodes in the tree

    // Utility functions for balancing.

    bool isBalanced();
    // Returns true if the tree is balanced.

    Node* rotateLeft(Node* node);
    // Returns a reference to the new root after rotating left.

    Node* rotateRight(Node* node);
    // Returns a reference to the new root after rotating right.

    Node* rotateLeftRight(Node* node);
    // Returns a reference to the new root after a double rotation of left then right.

    Node* rotateRightLeft(Node* node);
    // Returns a reference to the new root after a double rotation of right then left.

    int heightDifference(Node* node);
    // Returns the difference between the left and right subtrees.

    int getHeight(Node *node);
    // Returns the height of the tree/subtree

    Node* rebalance(Node* node);
    // Balances the tree.

    // Utility functions for removing, inserting, copy constructor, and assignment operator
    void init();
    // Initializes an empty tree

    NodePair findNode(const T& entry);
    // Finds the parent and the node where the entry is found. If not found the node will be NULL.
    // Helps the contains and remove functions.

    NodePair predecessor(Node *node);
    // Returns a node pair of the right child node and parent node. Helps the remove function.

    void removeNode(Node *nodeToRemove, Node *parentNode);
    // Removes a node and exchanges it with its parent

    void copyTree(const Tree<T>& obj);
    // Helper function for copy constructor and assignment operator Recursively copies a tree in order.

    // Utility functions for errors and finding an entry

    Node* location(Node *node, const T& entry) const;
    // Returns node where the passed entry is found. Returns NULL if it is not found.

    void memError() const;
    // Helper function for issuing memory allocation error.

    void inOrder(Node * node) const;
    // Traverses the tree in order

    void preOrder(Node * node) const;
    // Traverses the tree in pre order

    void postOrder(Node * node) const;
    // Traverses the tree in post order

    void toStringInOrder(Node* node, std::stringstream& stream);
    // Returns a string of the tree contents in in-order

    void toStringPreOrder(Node* node, std::stringstream& stream);
    // Returns a string of the tree contents in in-order

    void toStringPostOrder(Node* node, std::stringstream& stream);
    // Returns a string of the tree contents in in-order

    void toList(Node* node, QList<T>& list);
    // Returns a list

public:

    Tree();
    // Default constructor

    Tree(const T& entry);
    // Main constructor

    Tree(const Tree<T>& obj);
    // Copy constructor

    ~Tree();
    // Destructor

    Tree<T>& operator=(const Tree<T>& obj);
    // Overloaded assignment operator

    void insert(const T& entry);
    // Inserts the passed entry into the tree

    void remove(const T& entry) throw (Empty);
    // deletes an entry from the tree. Throws an empty exception if the tree is empty.

    bool contains(const T& entry) const;
    // Returns true if an entry is in the tree, false otherwise.

    void inOrder() const;
    // Traverses the tree in order

    void preOrder() const;
    // Traverses the tree in pre order

    void postOrder() const;
    // Traverses the tree in post order

    void levelOrder()const;
    // Traverses the tree breadth first e.g. level-order

    T& getRoot() const throw (Empty);
    // Returns a reference to the root entry

    unsigned int length() {
        return size;
    }
    // Returns the size of the tree

    unsigned int height();
    // Returns the height of the tree    

    void clear() throw (Empty);
    // Removes all elements in the tree

    bool isEmpty() const {
        return root == NULL;
    }

    bool upDate(const T& entry, const T& newVal);
    // Updates the contents of the entry witht the newVal is the entry is in the tree

    // Returns true if the tree is empty

    std::string toStringInOrder();
    // Returns a string of the tree contents in in-order

    std::string toStringPreOrder();
    // Returns a string of the tree contents in pre-order

    std::string toStringPostOrder();
    // Returns a string of the tree contents in post-order

    std::string toStringLevelOrder();
    // Returns a string of the tree contents in level-order

    QList<T> toList();
    // Returns a list with the contents of the tree

};

// Default constructor

template<class T>
Tree<T>::Tree() {
    init();
}

// Main constructor

template<class T>
Tree<T>::Tree(const T& entry) {
    init();
    insert(entry);
}

// Copy constructor

template<class T>
Tree<T>::Tree(const Tree<T>& obj) {
    // Initialize root to NULL and size to 0
    init();
    // Copy all of obj's data
    copyTree(obj);
}

// Destructor

template<class T>
Tree<T>::~Tree() {
    if (root != NULL) {
        delete root;
        root = NULL; // Point it to NULL so we don't get garbage accessing it later
        size = 0;
    }
}

// Overloaded assignment operator

template<class T>
Tree<T>& Tree<T>::operator=(const Tree<T>& obj) {
    // Clear the current tree of all data
    if (!isEmpty())
        clear();
    // Initialize root to NULL and size to 0
    init();
    // Copy all of obj's data
    copyTree(obj);
}

// Removes all the entries from the tree

template<class T>
void Tree<T>::clear() throw (Empty) {
    if (root != NULL) {
        delete root;
        root = NULL; // Point it to NULL so we don't get garbage accessing it later
        size = 0;
    } else {
        std::string message = "Tree ";
        throw Empty(message);
    }
}

// Insert an entry into the tree. Iterate through the nodes until a
// place is found for the new node. Tree is re-balanced after insertion.

template<class T>
void Tree<T>::insert(const T& entry) {

    // If we have an empty tree just add a root
    if (root == NULL) {
        Node * node = new Node(entry, NULL, NULL);
        root = node;
        size++;
    } else {
        // If it is not empty go through the tree to find a place to put the
        // entry
        Node *node;
        node = root;
        bool added = false;
        while (!added) {
            // If the node is less than, go through the left tree and its
            // nodes
            if (entry < node->data) {
                // Find if the left node is empty
                if (node->left == NULL) {
                    // Create a new node and set its data member
                    Node *leaf = new Node(entry, NULL, NULL);
                    // Now set it as the left subtree of the current node
                    node->left = leaf;
                    size++;
                    added = true;
                } else {
                    // If not go to the next left node
                    node = node->left;
                }
            }// Otherwise go through the right tree and its nodes to find a
                // place to add it to the tree
            else {
                if (node->right == NULL) {
                    // Create a new node and set its data member
                    Node *leaf = new Node(entry, NULL, NULL);
                    // Now link it as the right sub node
                    node->right = leaf;
                    size++;
                    added = true;
                } else {
                    // If not go to the next right node
                    node = node->right;
                }
            }
        } // end while
        root = rebalance(root);
    } // end else
}

template<class T>
void Tree<T>::remove(const T& entry) throw (Empty) {
    if (root != NULL) {
        // Find the entry and its parent that matches the entry
        NodePair pair = findNode(entry);

        Node *nodeWithEntry = pair.currentNode;
        Node *parentEntryNode = pair.parentNode;

        // If the entry was found remove it
        if (nodeWithEntry != NULL) {
            // If this node has two children find one child that itself has
            // only one child or is a leaf. The replace the contents of that 
            // node with nodeWithEntry. We can delete this inorder predecessor node.
            if (nodeWithEntry->left != NULL && nodeWithEntry->right != NULL) {
                pair = predecessor(nodeWithEntry);
                Node *nodeToRemove = pair.currentNode;
                parentEntryNode = pair.parentNode;
                nodeWithEntry->data = nodeToRemove->data;
                nodeWithEntry = nodeToRemove;
            }
            // Remove the in-order predecessor
            removeNode(nodeWithEntry, parentEntryNode);
            // Balance the tree
            root = rebalance(root);
        }
    } else {
        std::string message = "Tree";
        throw Empty(message);
    }
}

// Returns true if the tree contains the passed entry, false otherwise.

template<class T>
bool Tree<T>::contains(const T& entry) const {
    Node *node = location(root, entry);
    return (node != NULL ? true : false);
}

// Updates the node with the given value
template<class T>
bool Tree<T>::upDate(const T &entry, const T &newVal){
    // Find the entry
    Node *node = location(root,entry);
    if(node){
    node->data = newVal;
    return true;
    }
    return false;
}

// Tree traversal - at moment only prints
// Traverses the tree in order

template<class T>
void Tree<T>::inOrder() const {
    inOrder(root);
}

// Traverses the tree in pre order

template<class T>
void Tree<T>::preOrder() const {
    preOrder(root);
}

// Traverses the tree in post order

template<class T>
void Tree<T>::postOrder() const {
    postOrder(root);
}

// Traverse the tree breadth first

template<class T>
void Tree<T>::levelOrder() const {
    if (root != NULL) {
        // To keep track of the node by level
        Queue<Node*> traverse;

        // Prepare the queue
        Node *cursor = root;
        traverse.push(cursor);

        // Iterate through the queue adding and removing nodes by level
        while (!traverse.isEmpty()) {
            cursor = traverse.front();
            traverse.pop();
            std::cout << cursor->data << "\n";
            // Store the left child
            if (cursor->left != NULL) {
                // Save the left children for later use
                traverse.push(cursor->left);
            }
            // Store the right child
            if (cursor->right != NULL) {
                // Save the left children for later use
                traverse.push(cursor->right);
            }
        }
    }
}

template<class T>
T& Tree<T>::getRoot() const throw (Empty) {
    if (root != NULL)
        return root->data;
    else {
        std::string message = "Tree ";
        throw Empty(message);
    }
}

// Returns the actual height of the whole tree

template<class T>
unsigned int Tree<T>::height() {
    if (!isEmpty())
        return getHeight(root);
    else return 0;
}

// Returns a string of the tree contents in in-order

template<class T>
std::string Tree<T>::toStringInOrder() {
    std::stringstream s;
    std::string contents;
    toStringInOrder(root, s);
    // Now get the contents of the stream
    contents = s.str();
    return contents;
}
// Returns a string of the tree contents in pre-order

template<class T>
std::string Tree<T>::toStringPreOrder() {
    std::stringstream s;
    std::string contents;
    // Fill the string stream using the recursive function
    toStringPreOrder(root, s);
    // Now get the contents of the stream
    contents = s.str();
    return contents;
}

// Returns a string of the tree contents in post-order

template<class T>
std::string Tree<T>::toStringPostOrder() {
    std::stringstream s;
    std::string contents;
    // Fill the string stream using the recursive function
    toStringPostOrder(root, s);
    // Now get the contents of the stream
    contents = s.str();
    return contents;
}

// Returns a string of the tree contents in level-order

template<class T>
std::string Tree<T>::toStringLevelOrder() {
    std::stringstream s;
    std::string contents = "in order";
    if (root != NULL) {
        // To keep track of the node by level
        Queue<Node*> traverse;

        // Prepare the queue
        Node *cursor = root;
        traverse.push(cursor);

        // Iterate through the queue adding and removing nodes by level
        while (!traverse.isEmpty()) {
            cursor = traverse.front();
            traverse.pop();
            s << cursor->data << " ";
            // Store the left child
            if (cursor->left != NULL) {
                // Save the left children for later use
                traverse.push(cursor->left);
            }
            // Store the right child
            if (cursor->right != NULL) {
                // Save the left children for later use
                traverse.push(cursor->right);
            }
        }
    }
    contents = s.str();
    return contents;
}

// Returns a list with the contents of the tree
template<class T>
QList<T> Tree<T>::toList(){
    QList<T> list;
    toList(root,list);
    return list;
}

// Utility functions

// Fills a string stream with the node data in in-order

template<class T>
void Tree<T>::toStringInOrder(Node* node, std::stringstream& stream) {
    if (node != NULL) {
        toStringInOrder(node->left, stream);
        stream << node->data << " ";
        toStringInOrder(node->right, stream);
    }
}

// Fills a string stream with the node data in pre-order

template<class T>
void Tree<T>::toStringPreOrder(Node* node, std::stringstream& stream) {
    if (node != NULL) {
        stream << node->data << " ";
        toStringPreOrder(node->left, stream);
        toStringPreOrder(node->right, stream);
    }
}

// Fills a string stream with the node data in pre-order

template<class T>
void Tree<T>::toStringPostOrder(Node* node, std::stringstream& stream) {
    if (node != NULL) {
        toStringPostOrder(node->left, stream);
        toStringPostOrder(node->right, stream);
        stream << node->data << " ";
    }
}


// Helper functions for returning strings depending on traversal

// Helper function for getting a list of the tree contents in order
template<class T>
void Tree<T>::toList(Node* node, QList<T> &list){
    if(node!=NULL){
        toList(node->left,list);
        list.append(node->data);
        toList(node->right,list);
    }
}


// Helper functions for traversing and printing the list

template<class T>
void Tree<T>::inOrder(Node* node) const {
    // If the node is null it will print the parent node
    if (node != NULL) {
        // First get the left node
        inOrder(node->left);
        std::cout << node->data << std::endl;
        // Get the right node
        inOrder(node->right);
    }
}

template<class T>
void Tree<T>::preOrder(Node* node) const {
    // If the node is null it will print the parent node
    if (node != NULL) {
        // Print
        std::cout << node->data << std::endl;
        // First get the left node
        preOrder(node->left);
        // Get the right node
        preOrder(node->right);
    }
}

template<class T>
void Tree<T>::postOrder(Node* node) const {
    // If the node is null it will print the parent node
    if (node != NULL) {
        // First get the left node
        postOrder(node->left);
        // Get the right node
        postOrder(node->right);
        // Print
        std::cout << node->data << std::endl;
    }
}

// Helper function to copy constructor and assignment operator. Initializes root to NULL and size to 0.

template<class T>
void Tree<T>::init() {
    root = NULL;
    size = 0;
}

// Helper function for the copy constructor and assignment operator. Copies the passed tree object
// iteratively in breath first traversal

template<class T>
void Tree<T>::copyTree(const Tree<T>& obj) {
    if (!obj.isEmpty()) {
        Queue<Node*> originQueue;
        Queue<Node*> copyQueue;

        // Node to traverse the original tree
        Node *cursor;
        cursor = obj.root;

        // create a root node
        Node *newNode;
        try {
            newNode = new Node(cursor->data, NULL, NULL);
        } catch (const::std::bad_alloc&) {
            memError();
        }

        size++; // Increment the total size of the tree
        root = newNode; // Set the root to be the new node

        originQueue.push(cursor);
        copyQueue.push(root);

        // Iterate through the nodes creating and copying tree nodes by level 
        while (!originQueue.isEmpty() && !copyQueue.isEmpty()) {
            cursor = originQueue.front();
            originQueue.pop();
            Node *temp = copyQueue.front();
            copyQueue.pop();
            // Process and store the left children
            if (cursor->left != NULL) {
                // Create a new left child node
                // and allocate memory for it
                Node *leftChild;
                try {
                    leftChild = new Node(cursor->left->data, NULL, NULL);
                } catch (const::std::bad_alloc&) {
                    memError();
                }
                // Link it with its parent node
                temp->left = leftChild;
                ++size;
                // Save the left children for later use
                originQueue.push(cursor->left);
                copyQueue.push(leftChild);
            }

            // Process and store the right children
            if (cursor->right != NULL) {
                // Create a new left child node
                // and allocate memory for it
                Node *rightChild;
                try {
                    rightChild = new Node(cursor->right->data, NULL, NULL);
                } catch (const::std::bad_alloc&) {
                    memError();
                }
                // Link it with its parent node
                temp->right = rightChild;
                ++size;

                // Save the left children for later use
                originQueue.push(cursor->right);
                copyQueue.push(rightChild);
            }
        }
    }
}

// Returns true if the tree is balanced.

template<class T>
bool Tree<T>::isBalanced() {
    // Get left and tree subtree heights
    int left = getHeight(root->left);
    int right = getHeight(root->right);
    // Return true if the difference between
    return ((left - right) > 1 || (left - right < -1) ? false : true);
}
// Returns a reference to the new root after rotating left.

template<class T>
typename Tree<T>::Node* Tree<T>::rotateLeft(Node *node) {
    // Code based on Carrano's book algorithm
    Node *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

// Returns a reference to the new root after rotating right.

template<class T>
typename Tree<T>::Node* Tree<T>::rotateRight(Node *node) {
    // Code based on Carrano's algorithm in book
    Node *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;

}

// Returns a reference to the new root after a double rotation of left then right.

template<class T>
typename Tree<T>::Node* Tree<T>::rotateLeftRight(Node *node) {
    // Code based on Carrano's algorithm
    Node *newRoot = node->left;
    node->left = rotateLeft(newRoot);
    return rotateRight(node);
}

template<class T>
typename Tree<T>::Node* Tree<T>::rotateRightLeft(Node *node) {
    // Code based on Carrano's algorithm
    Node *newRoot = node->right;
    node->right = rotateRight(newRoot);
    return rotateLeft(node);

}
// Returns a reference to the new root after a double rotation of right then left.

// Returns the difference between the left and right subtrees.

template<class T>
int Tree<T>::heightDifference(Node *node) {
    return (getHeight(node->left) - getHeight(node->right));
}

// Returns the height of the subtree

template<class T>
int Tree<T>::getHeight(Node* node) {
    // If the tree is empty return 0
    if (node == NULL) {
        return 0;
    }
    // Get the height of the left and right subtrees
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    // Now return the maximum between the left tree and right tree heights.
    return (leftHeight > rightHeight ? (1 + leftHeight) : (1 + rightHeight));
}


// Balances the tree according to the height difference between its subtrees

template<class T>
typename Tree<T>::Node* Tree<T>::rebalance(Node *node) {
    if (node != NULL) {
        // Get the height difference between left and right subtrees
        int heightDiff = heightDifference(node);

        if (heightDiff > 1) {
            // Now go through the subtrees and get difference with its
            // subtrees
            // Rotate as necessary
            if (heightDifference(node->left) > 0) {
                node = rotateRight(node);
            } else {
                node = rotateLeftRight(node);
            }
        } else if (heightDiff < -1) {
            if (heightDifference(node->right) < 0) {
                node = rotateLeft(node);
            } else {
                node = rotateRightLeft(node);
            }
        }
    }
    return node;
}

// Helper function to remove function. If found returns a NodePair where the 
// child node of the NodePair is where where the entry occurs and the parentNode 
// is the parent of that node. It returns a NodePair of nulls if not found.

template<class T>
typename Tree<T>::NodePair Tree<T>::findNode(const T& entry) {
    // Now we need to go as far to the right as possible

    // Initialize the node pair to return
    NodePair result;
    result.currentNode = NULL;
    result.parentNode = NULL;

    Node *cursor = root;
    Node *cursorParent = NULL;

    // Keep going right until we reach null
    while (cursor != NULL) {
        // If we found it return the pair of nodes
        if (cursor->data == entry) {
            result.currentNode = cursor;
            result.parentNode = cursorParent;

            return result;
        }// Search the left subtree if entry is less than current node data
        else if (entry < cursor->data) {
            cursorParent = cursor;
            cursor = cursor->left;
        }// Otherwise continue searching in the right subtree
        else {
            cursorParent = cursor;
            cursor = cursor->right;
        }
    }
    // Return the right subtree and its parent node
    return result;
}

// Helper function to remove function. Returns the rightmost node of the left 
// subtree and its parent node. The rightmost node is the inorder predecessor
// of the node to remove in the remove function.

template<class T>
typename Tree<T>::NodePair Tree<T>::predecessor(Node* node) {
    // First go left
    Node *leftSubTree = node->left;
    // Now we need to go as far to the right as possible
    Node *rightChild = leftSubTree;
    Node *parentNode = node;

    // Keep going right until we reach null
    while (rightChild->right != NULL) {
        parentNode = rightChild;
        rightChild = rightChild->right;
    }
    // Return the right subtree and its parent node
    NodePair pair;
    pair.currentNode = rightChild;
    pair.parentNode = parentNode;
    return pair;
}

// Helper function to remove function. It connects the parentNode with nodeToRemove
// left or right child if any then deallocates nodeToRemove.

template<class T>
void Tree<T>::removeNode(Node *nodeToRemove, Node *parentNode) {
    Node *childNode;
    // Find if nodeToRemove has either a left or right child
    if (nodeToRemove->left != NULL) {
        childNode = nodeToRemove->left;
    } else {
        childNode = nodeToRemove->right;
    }

    // If the node to delete is the root, just change it with its child
    // and delete the nodeToRemove
    if (nodeToRemove == root) {
        root = childNode; // Set it to NULL
    }// If the node to remove is the left child of parent, link nodeToRemove's
        // childNode to parentNode and delete nodeToRemove
    else if (parentNode->left == nodeToRemove) {
        parentNode->left = childNode;
    }// If the node to remove is the right child of parent, link nodeToRemove's
        // childNode to parentNode and delete nodeToRemove
    else {
        parentNode->right = childNode;
    }

    // Delete the node and decrease the size
    delete nodeToRemove;
    --size;

}

// Function provided by Dr. Mark Lehr. It issues an error and terminates the program if memory fails to allocate.

template<class T>
void Tree<T>::memError() const {
    std::cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

// Finds the node where an entry is located. If it is not found returns NULL

template<class T>
typename Tree<T>::Node* Tree<T>::location(Node* node, const T& entry) const {
    if (node != NULL) {
        // If we find it we exit the recursive call
        if (node->data == entry) {
            return node;
        }
        // If we don't find it in current node go to the subtrees
        else if (node->data > entry) {
            return location(node->left, entry);
        }// TODO remove if condition from else if
            // Can remove the if condition. Not necessary
        else {
            return location(node->right, entry);
        }
    }
    // We never found it
    return NULL;
}

#endif	/* TREE_H */

