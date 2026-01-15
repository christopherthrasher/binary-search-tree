//Name: Christopher Thrasher
//Main driver

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "linkedbsearchtree.h"
using namespace std;

void visit(int& data);
void generateUniqueRandomNumbers(int arr[], int size);
void insertValuesIntoTree(LinkedBSearchTree<int>& tree, int arr[], int size);
void displayTreeStats(const LinkedBSearchTree<int>& tree);
void printInOrder(const LinkedBSearchTree<int>& tree);
void printPreOrder(const LinkedBSearchTree<int>& tree);
void printPostOrder(const LinkedBSearchTree<int>& tree);

int main() {
    srand(time(NULL));

    int arr[100];

    generateUniqueRandomNumbers(arr, 100);

    LinkedBSearchTree<int> tree;

    insertValuesIntoTree(tree, arr, 100);

    displayTreeStats(tree);

    printInOrder(tree);
    printPreOrder(tree);
    printPostOrder(tree);

    return 0;
}

void visit(int& data) {
    cout << data << " ";
}

void generateUniqueRandomNumbers(int arr[], int size) {
    int count = 0;

    while (count < size) {
        int num = rand() % 200 + 1;
        bool isUnique = true;

        for (int i = 0; i < count; i++) {
            if (arr[i] == num) {
                isUnique = false;
                break;
            }
        }

        if (isUnique) {
            arr[count] = num;
            count++;
        }
    }
}

void insertValuesIntoTree(LinkedBSearchTree<int>& tree, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        tree.add(arr[i]);
    }
}

void displayTreeStats(const LinkedBSearchTree<int>& tree) {
    cout << "Tree Height: " << tree.getHeight() << endl;
    cout << "Number of Nodes: " << tree.getNumberOfNodes() << endl;
    cout << "Root Value: " << tree.getRootData() << endl;
}

void printInOrder(const LinkedBSearchTree<int>& tree) {
    cout << "In-Order Traversal: ";
    tree.inorderTraverse(visit);
    cout << endl;
}

void printPreOrder(const LinkedBSearchTree<int>& tree) {
    cout << "Pre-Order Traversal: ";
    tree.preorderTraverse(visit);
    cout << endl;
}

void printPostOrder(const LinkedBSearchTree<int>& tree) {
    cout << "Post-Order Traversal: ";
    tree.postorderTraverse(visit);
    cout << endl;
}
