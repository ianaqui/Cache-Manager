/**
 * @author - Hugh Hui, Adrian Aquino
* @file TreeNode.h
* 1/14/2025 - H. Hui created file and added comments.
* 1/15/2025 - modified by H. Hui; modified remove methods; added comments
* 2/1/2025 - H. Hui added doxygen formatted comments
* 5/17/25 - Modified by Adrian Aquino; added red-black tree color field and parent pointer
*
 * @brief Declaration of the TreeNode structure used for Red-Black Tree.
 *
 * This header file defines the TreeNode structure which is used in the
 * construction of a red-black tree. Each TreeNode contains a key, the number of
 * nodes in its subtree, the height of the node, color, and pointers to its left,
 * right, and parent nodes.
 */

#ifndef TREENODE_H
#define TREENODE_H

#include "dll_node.h"

enum Color { RED = 0, BLACK = 1 };

 /**
  * @struct TreeNode
  * @brief Represents a node in a red-black tree.
  *
  * A TreeNode is the basic building block of the red-black tree. Each node
  * stores a key, the number of nodes in its subtree, its height in the tree,
  * its color, and pointers to its left, right, and parent nodes.
  */
struct TreeNode {
    int key;                /**< Key for the tree node. */
    int numberOfNodes;      /**< Total nodes in the subtree rooted at this node. */
    int height;             /**< Height of the node in the tree. */
    Color color;            /**< Color of the node (RED or BLACK). */
    TreeNode* left;         /**< Pointer to the left child. */
    TreeNode* right;        /**< Pointer to the right child. */
    TreeNode* parent;       /**< Pointer to the parent node. */
    DllNode* fifoNode;     /**< Pointer to the fifo node. */

    /**
     * @brief Constructor for TreeNode.
     *
     * This constructor initializes a TreeNode with the specified key, number
     * of nodes, height, color, and pointers to the left, right, and parent children. If no
     * values are provided, it initializes the node with default values.
     *
     * @param k The key of the node (default is 0).
     * @param numNodes The number of nodes in the subtree (default is 1).
     * @param h The height of the node (default is 0).
     * @param c The color of the node (default is RED).
     * @param l Pointer to the left child (default is nullptr).
     * @param r Pointer to the right child (default is nullptr).
     * @param p Pointer to the parent (default is nullptr).
     * @param f Pointer to the fifo node (default is nullptr).
     */
    TreeNode(int k = 0, int numNodes = 1, int h = 0, Color c = RED, TreeNode* l = nullptr, TreeNode* r = nullptr, TreeNode* p = nullptr, DllNode* f = nullptr);

    TreeNode(int k, DllNode* fifoNode);
};

#endif // TREENODE_H