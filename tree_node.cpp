/**
* @author - Hugh Hui, Adrian Aquino
* @file TreeNode.cpp
* @brief Constructor for the TreeNode class.
*
* 1/14/2025 - H. Hui created file and added comments.
* 1/15/2025 - modified by H. Hui; modified remove methods; added comments
* 2/1/2025 - H. Hui added doxygen formatted comments
* 5/17/25 - Modified by Adrian Aquino; added red-black tree color field and parent pointer
*
* This constructor initializes a TreeNode object with the provided key, number of nodes,
* height, color, and pointers to the left, right, and parent children.
*
* @param k The key of the node.
* @param numNodes The total number of nodes in the subtree rooted at this node.
* @param h The height of the node in the tree.
* @param c The color of the node.
* @param l Pointer to the left child node.
* @param r Pointer to the right child node.
* @param p Pointer to the parent node.
* @param f Pointer to the fifo node.
*
*/
#include "tree_node.h"

TreeNode::TreeNode(int k, int numNodes, int h, Color c, TreeNode* l, TreeNode* r, TreeNode* p, DllNode* f)
    : key(k), numberOfNodes(numNodes), height(h), color(c), left(l), right(r), parent(p), fifoNode(f) {}

TreeNode::TreeNode(int k, DllNode* f) {
    key = k;
    numberOfNodes = 1;
    height = 0;
    color = RED;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    fifoNode = f;
}