//Linked Binary Tree Class

#ifndef LINKED_BTREE
#define LINKED_BTREE

#include "tree.h"
#include "linkedtreenode.h"

template<class ItemType>
class LinkedBTree : public TreeInterface<ItemType> {
public:
    LinkedBTree();
    bool isEmpty() const override;
    int getHeight() const override;
    int getNumberOfNodes() const override;
    ItemType getRootData() const override;
    bool add(const ItemType& newData) override;
    bool remove(const ItemType& data) override;
    void clear() override;
    ItemType getEntry(const ItemType& anEntry) const;
    bool contains(const ItemType& anEntry) const override;
    ~LinkedBTree();

protected:
    LinkedTreeNode<ItemType>* rootPtr;
    int getHeightHelper(LinkedTreeNode<ItemType>* subTreePtr) const;
    int getNumberOfNodesHelper(LinkedTreeNode<ItemType>* subTreePtr) const;
    LinkedTreeNode<ItemType>* balancedAdd(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr);
    LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful);
    LinkedTreeNode<ItemType>* moveValuesUpTree(LinkedTreeNode<ItemType>* subTreePtr);
    LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>* subTreePtr, const ItemType& target, bool& isSuccessful) const;
    void destroyTree(LinkedTreeNode<ItemType>* subTreePtr);
};

#include "linkedbtree.cpp"
#endif
