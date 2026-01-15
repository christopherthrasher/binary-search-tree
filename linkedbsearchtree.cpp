#include "linkedbsearchtree.h"

//PUBLIC FUNCTIONS

//constructor
template<class ItemType>
LinkedBSearchTree<ItemType>::LinkedBSearchTree() : LinkedBTree<ItemType>() { }

//add
template<class ItemType>
bool LinkedBSearchTree<ItemType>::add(const ItemType& newData) {
    LinkedTreeNode<ItemType>* newNodePtr = new LinkedTreeNode<ItemType>(newData);
    LinkedTreeNode<ItemType>* updatedRoot = placeNode(this->rootPtr, newNodePtr);
    this->rootPtr = updatedRoot;
    return true;
}

//remove
template<class ItemType>
bool LinkedBSearchTree<ItemType>::remove(const ItemType& target) {
    bool isSuccessful = false;
    this->rootPtr = removeValue(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}

//contains
template<class ItemType>
bool LinkedBSearchTree<ItemType>::contains(const ItemType& anEntry) const {
    bool isSuccessful = false;
    findNode(this->rootPtr, anEntry, isSuccessful);
    return isSuccessful;
}

//preorderTraverse
template<class ItemType>
void LinkedBSearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const {
    preorder(visit, this->rootPtr);
}

//inorderTraverse
template<class ItemType>
void LinkedBSearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const {
    inorder(visit, this->rootPtr);
}

//postordertraverse
template<class ItemType>
void LinkedBSearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const {
    postorder(visit, this->rootPtr);
}

//destructor
template<class ItemType>
LinkedBSearchTree<ItemType>::~LinkedBSearchTree() {
    this->clear();
}

//PROTECTED FUNCTIONS

//placeNode (add helper)
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::placeNode(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr) {
    if (subTreePtr == nullptr) {
        return newNodePtr;
    }

    if (newNodePtr->getItem() < subTreePtr->getItem()) {
        LinkedTreeNode<ItemType>* leftChild = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(leftChild);
    } else {
        LinkedTreeNode<ItemType>* rightChild = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(rightChild);
    }

    return subTreePtr;
}

//removeValue (remove helper)
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful) {

    if (subTreePtr == nullptr) {
        isSuccessful = false;
        return nullptr;
    }

    if (target == subTreePtr->getItem()) {
        subTreePtr = removeNode(subTreePtr);
        isSuccessful = true;
    } else if (target < subTreePtr->getItem()) {
        LinkedTreeNode<ItemType>* leftChild = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        subTreePtr->setLeftChildPtr(leftChild);
    } else {
        LinkedTreeNode<ItemType>* rightChild = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
        subTreePtr->setRightChildPtr(rightChild);
    }

    return subTreePtr;
}

//removeNode
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeNode(LinkedTreeNode<ItemType>* nodePtr) {
    if (nodePtr->isLeaf()) {
        delete nodePtr;
        return nullptr;
    }

    if (nodePtr->getLeftChildPtr() == nullptr) {
        LinkedTreeNode<ItemType>* rightChild = nodePtr->getRightChildPtr();
        delete nodePtr;
        return rightChild;
    }

    if (nodePtr->getRightChildPtr() == nullptr) {
        LinkedTreeNode<ItemType>* leftChild = nodePtr->getLeftChildPtr();
        delete nodePtr;
        return leftChild;
    }

    ItemType successorValue;
    LinkedTreeNode<ItemType>* rightSubtree = removeLeftmostNode(nodePtr->getRightChildPtr(), successorValue);
    nodePtr->setRightChildPtr(rightSubtree);
    nodePtr->setItem(successorValue);

    return nodePtr;
}

//removeLeftMostNode
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::removeLeftmostNode(LinkedTreeNode<ItemType>* subTreePtr, ItemType& inorderSuccessor) {
    if (subTreePtr->getLeftChildPtr() == nullptr) {
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }

    LinkedTreeNode<ItemType>* newLeft = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
    subTreePtr->setLeftChildPtr(newLeft);
    return subTreePtr;
}

//findNode (contains helper)
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBSearchTree<ItemType>::findNode(LinkedTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const {
    if (subTreePtr == nullptr) {
        isSuccessful = false;
        return nullptr;
    }

    if (target == subTreePtr->getItem()) {
        isSuccessful = true;
        return subTreePtr;
    } else if (target < subTreePtr->getItem()) {
        return findNode(subTreePtr->getLeftChildPtr(), target, isSuccessful);
    } else {
        return findNode(subTreePtr->getRightChildPtr(), target, isSuccessful);
    }
}

//preorder (preorderTraverse helper)
template<class ItemType>
void LinkedBSearchTree<ItemType>::preorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        ItemType item = treePtr->getItem();
        visit(item);
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }
}

//inorder (inorderTraverse helper)
template<class ItemType>
void LinkedBSearchTree<ItemType>::inorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType item = treePtr->getItem();
        visit(item);
        inorder(visit, treePtr->getRightChildPtr());
    }
}

//postorder (postorderTraverse helper)
template<class ItemType>
void LinkedBSearchTree<ItemType>::postorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType item = treePtr->getItem();
        visit(item);
    }
}
