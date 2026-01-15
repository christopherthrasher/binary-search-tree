//Linked Binary Search Tree Class

#ifndef LINKED_BSEARCHTREE
#define LINKED_BSEARCHTREE

#include "linkedtreenode.h"
#include "linkedbtree.h"

template<class ItemType>
class LinkedBSearchTree : public LinkedBTree<ItemType> {
public:
    LinkedBSearchTree();
    bool add(const ItemType& newData) override;
    bool remove(const ItemType& data) override;
    bool contains(const ItemType& anEntry) const override;
    void preorderTraverse(void visit(ItemType&)) const;
    void inorderTraverse(void visit(ItemType&)) const;
    void postorderTraverse(void visit(ItemType&)) const;
    ~LinkedBSearchTree();

protected:
    LinkedTreeNode<ItemType>* placeNode(LinkedTreeNode<ItemType>* subTreePtr, LinkedTreeNode<ItemType>* newNodePtr);
    LinkedTreeNode<ItemType>* removeValue(LinkedTreeNode<ItemType>* subTreePtr, const ItemType target, bool& isSuccessful);
    LinkedTreeNode<ItemType>* removeNode(LinkedTreeNode<ItemType>* nodePtr);
    LinkedTreeNode<ItemType>* removeLeftmostNode(LinkedTreeNode<ItemType>* nodePtr, ItemType& inorderSuccessor);
    LinkedTreeNode<ItemType>* findNode(LinkedTreeNode<ItemType>* treePtr, const ItemType& target, bool& isSuccessful) const;
    void preorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const;
    void inorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const;
    void postorder(void visit(ItemType&), LinkedTreeNode<ItemType>* treePtr) const;
};

#include "linkedbsearchtree.cpp"
#endif
