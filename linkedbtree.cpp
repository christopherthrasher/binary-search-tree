#include "linkedbtree.h"

//PUBLIC FUNCTIONS

//constructor
template<class ItemType>
LinkedBTree<ItemType>::LinkedBTree() {
    rootPtr = nullptr;
}

//isEmpty
template<class ItemType>
bool LinkedBTree<ItemType>::isEmpty() const {
    return rootPtr == nullptr;
}

//getHeight
template<class ItemType>
int LinkedBTree<ItemType>::getHeight() const {
    return getHeightHelper(rootPtr);
}

//getNumberOfNodes
template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodes() const {
    return getNumberOfNodesHelper(rootPtr);
}

//getRootData
template<class ItemType>
ItemType LinkedBTree<ItemType>::getRootData() const {
    if (isEmpty()) {
        throw "getRootData() called on empty tree.";
    } else {
        return rootPtr->getItem();
    }
}

//add
template<class ItemType>
bool LinkedBTree<ItemType>::add(const ItemType& newData) {
    LinkedTreeNode<ItemType>* newNodePtr = new LinkedTreeNode<ItemType>(newData);
    rootPtr = balancedAdd(rootPtr, newNodePtr);
    return true;
}

//remove
template<class ItemType>
bool LinkedBTree<ItemType>::remove(const ItemType& data) {
    bool isSuccessful = false;
    rootPtr = removeValue(rootPtr, data, isSuccessful);
    return isSuccessful;
}

//clear
template<class ItemType>
void LinkedBTree<ItemType>::clear() {
    destroyTree(rootPtr);
    rootPtr = nullptr;
}

//getEntry
template<class ItemType>
ItemType LinkedBTree<ItemType>::getEntry(const ItemType& anEntry) const {
    bool isSuccessful = false;
    LinkedTreeNode<ItemType>* node = findNode(rootPtr, anEntry, isSuccessful);

    if (isSuccessful && node != nullptr) {
        return node->getItem();
    } else {
        throw "Entry not found in tree.";
    }
}

//contains
template<class ItemType>
bool LinkedBTree<ItemType>::contains(const ItemType& anEntry) const {
    bool isSuccessful = false;
    findNode(rootPtr, anEntry, isSuccessful);
    return isSuccessful;
}

//destructor
template<class ItemType>
LinkedBTree<ItemType>::~LinkedBTree() {
    clear();
}

//PROTECTED FUNCTIONS

//getHeightHelper (helper for getHeight)
template<class ItemType>
int LinkedBTree<ItemType>::getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
    if (subTreePtr == nullptr)
        return 0;
    
    int leftHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
    int rightHeight = getHeightHelper(subTreePtr->getRightChildPtr());

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

//getNumberOfNodesHelper (helper for getNumberOfNodes)
template<class ItemType>
int LinkedBTree<ItemType>::getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const {
    if (subTreePtr == nullptr)
        return 0;
    
    return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}

//balancedAdd (helper for add)
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::balancedAdd(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr) {
    if (subTreePtr == nullptr) {
        return newNodePtr;
    } else {
        int leftHeight = getHeightHelper(subTreePtr->getLeftChildPtr());
        int rightHeight = getHeightHelper(subTreePtr->getRightChildPtr());

        if (leftHeight <= rightHeight) {
            LinkedTreeNode<ItemType>* leftChild = balancedAdd(subTreePtr->getLeftChildPtr(), newNodePtr);
            subTreePtr->setLeftChildPtr(leftChild);
        } else {
            LinkedTreeNode<ItemType>* rightChild = balancedAdd(subTreePtr->getRightChildPtr(), newNodePtr);
            subTreePtr->setRightChildPtr(rightChild);
        }

        return subTreePtr;
    }
}

//removeValue (helper for remove)
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful) {
    if (subTreePtr == nullptr) {
        isSuccessful = false;
        return nullptr;
    }

    if (subTreePtr->getItem() == target) {
        subTreePtr = moveValuesUpTree(subTreePtr);
        isSuccessful = true;
    } else {
        LinkedTreeNode<ItemType>* tempLeft = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        subTreePtr->setLeftChildPtr(tempLeft);
        if (!isSuccessful) {
            LinkedTreeNode<ItemType>* tempRight = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
            subTreePtr->setRightChildPtr(tempRight);
        }
    }

    return subTreePtr;
}

//moveValuesUpTree
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::moveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr) {
    if (subTreePtr->isLeaf()) {
        delete subTreePtr;
        return nullptr;
    }

    if (subTreePtr->getLeftChildPtr() == nullptr) {
        LinkedTreeNode<ItemType>* rightChild = subTreePtr->getRightChildPtr();
        delete subTreePtr;
        return rightChild;
    }

    if (subTreePtr->getRightChildPtr() == nullptr) {
        LinkedTreeNode<ItemType>* leftChild = subTreePtr->getLeftChildPtr();
        delete subTreePtr;
        return leftChild;
    }

    LinkedTreeNode<ItemType>* current = subTreePtr->getRightChildPtr();
    LinkedTreeNode<ItemType>* parent = subTreePtr;

    while (current->getLeftChildPtr() != nullptr) {
        parent = current;
        current = current->getLeftChildPtr();
    }

    subTreePtr->setItem(current->getItem());

    if (parent == subTreePtr)
        parent->setRightChildPtr(moveValuesUpTree(current));
    else
        parent->setLeftChildPtr(moveValuesUpTree(current));

    return subTreePtr;
}

//findNode (contains helper)
template<class ItemType>
LinkedTreeNode<ItemType>* LinkedBTree<ItemType>::findNode(LinkedTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const {
    if (subTreePtr == nullptr) {
        isSuccessful = false;
        return nullptr;
    }

    if (subTreePtr->getItem() == target) {
        isSuccessful = true;
        return subTreePtr;
    }

    LinkedTreeNode<ItemType>* leftResult = findNode(subTreePtr->getLeftChildPtr(), target, isSuccessful);
    if (isSuccessful) return leftResult;

    return findNode(subTreePtr->getRightChildPtr(), target, isSuccessful);
}

//destroyTree
template<class ItemType>
void LinkedBTree<ItemType>::destroyTree(LinkedTreeNode<ItemType>* subTreePtr) {
    if (subTreePtr != nullptr) {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}
