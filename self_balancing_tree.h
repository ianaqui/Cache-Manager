/**
* @author - Hugh Hui, Adrian Aquino
* @file self_balancing_tree.h  -  This header file declares the methods in the self_balancing_tree.cpp file.
* 1/14/2025 - H. Hui created file and added comments.
* 1/15/2025 - modified by H. Hui; modified remove methods; added comments
* 2/1/2025 - H. Hui added doxygen formatted comments
* 5/17/2025 - Modified by Adrian Aquino; renamed binary_search_tree.h to self_balancing_tree.h and added red-black tree functionality
* 5/21/2025 - Modified by Adrian Aquino; updated red-black tree implementation with proper color handling and parent pointers
*/

#ifndef SELFBALANCING_TREE_H
#define SELFBALANCING_TREE_H

#include "tree_node.h"

/**
 * @class SelfBalancingTree
 * @brief A class representing a Self-Balancing Tree using Red-Black algorithm.
 *
 * This class provides methods to manipulate and traverse a self-balancing tree.
 * It supports operations like adding and removing nodes, checking if a key exists,
 * calculating the height of the tree, and printing the tree in various traversal orders.
 */
class SelfBalancingTree {
public:
    /**
     * @brief Default constructor for SelfBalancingTree.
     *
     * Initializes an empty self-balancing tree.
     */
    SelfBalancingTree();

    /**
     * @brief Destructor for SelfBalancingTree.
     *
     * Frees the dynamically allocated memory by deleting all nodes in the tree.
     */
    ~SelfBalancingTree();

    /**
     * @brief Adds a node with the specified key to the tree.
     *
     * @param key The key to be added to the tree.
     * @param dllNode Pointer to the DllNode to be linked with this tree node.
     */
    void addToTree(int key, DllNode* dllNode);

    /**
     * @brief Removes a node with the specified key from the tree.
     *
     * @param key The key of the node to remove.
     * @return True if the node was removed, false if the key wasn't found.
     */
    bool removeNode(int key);

    /**
     * @brief Gets the height of the tree.
     *
     * The height of the tree is defined as the length of the longest path from
     * the root to a leaf node.
     *
     * @return The height of the tree.
     */
    int getHeightOfTree() const;

    /**
     * @brief Gets the number of nodes in the tree.
     *
     * @return The number of nodes in the tree.
     */
    int getNumberOfTreeNodes() const;

    /**
     * @brief Checks if the tree contains a node with the specified key.
     *
     * @param key The key to search for in the tree.
     * @return True if the key exists in the tree, false otherwise.
     */
    bool contains(int key) const;

    /**
     * @brief Gets the root node of the tree.
     *
     * @return A pointer to the root node of the tree.
     */
    TreeNode* getRoot() const;

    /**
     * @brief Checks if the tree is empty.
     *
     * @return True if the tree is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Clears the entire tree.
     *
     * Deletes all the nodes in the tree, freeing up memory.
     */
    void clear();

    /**
     * @brief Prints the data of a specific node.
     *
     * This function prints the key, number of nodes in the subtree, and height of the given node.
     *
     * @param node A pointer to the node whose data is to be printed.
     */
    void printNodeFromTree(TreeNode* node) const;

    /**
     * @brief Performs an in-order traversal of the tree and prints the nodes.
     *
     * In-order traversal visits the left subtree, the node, and then the right subtree.
     */
    void printInOrder() const;

    /**
     * @brief Performs an reverse traversal of the tree and prints the nodes.
     *
     * Reverse traversal visits the right subtree, the node, and then the left subtree.
     */
    void printReverseOrder() const;

    /**
     * @brief Performs a pre-order traversal of the tree and prints the nodes.
     *
     * Pre-order traversal visits the node, the left subtree, and then the right subtree.
     */
    void printPreOrder() const;

    /**
     * @brief Performs a post-order traversal of the tree and prints the nodes.
     *
     * Post-order traversal visits the left subtree, the right subtree, and then the node.
     */
    void printPostOrder() const;

    /**
     * @brief Performs a depth-first traversal (same as pre-order traversal) and prints the nodes.
     *
     * Depth-first traversal visits the node first, then the left subtree, and then the right subtree.
     */
    void printDepthFirst() const;

    /**
     * @brief Performs a breadth-first traversal of the tree and prints the nodes.
     *
     * Breadth-first traversal visits nodes level by level, from left to right.
     */
    void printBreadthFirst() const;

    /**
    *
    * printRange
    *
    * Method to traverse and print out the cache information given a low and high value.
    *
    * @param    low			the lower bound (inclusive) of the range to print
    * @param	high		the higher bound (inclusive) of the range to print
    *
    * @return   nothing, but prints out the keys for the cache between low and high
    */
    void printRange(int low, int high);

private:
    TreeNode* root; /**< Pointer to the root node of the tree */

    /**
     * @brief Deletes the tree starting from the specified node.
     *
     * Recursively deletes all nodes in the tree.
     *
     * @param node The starting node to begin deleting the tree.
     */
    void deleteTree(TreeNode* node);

    /**
     * @brief Helper function to calculate the height of a node.
     *
     * This function is used by `getHeightOfTree` to calculate the height of the tree.
     *
     * @param node A pointer to the node whose height is to be calculated.
     * @return The height of the given node.
     */
    int getHeight(TreeNode* node) const;

    /**
     * @brief Helper function for recursive in-order traversal.
     *
     * This function is called recursively to perform an in-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the in-order traversal.
     */
    void printInOrderHelper(TreeNode* node) const;

    /**
     * @brief Helper function for recursive in-order traversal.
     *
     * This function is called recursively to perform an in-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the in-order traversal.
     */
    void printReverseOrderHelper(TreeNode* node) const;

    /**
     * @brief Helper function for recursive pre-order traversal.
     *
     * This function is called recursively to perform a pre-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the pre-order traversal.
     */
    void printPreOrderHelper(TreeNode* node) const;

    /**
     * @brief Helper function for recursive post-order traversal.
     *
     * This function is called recursively to perform a post-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the post-order traversal.
     */
    void printPostOrderHelper(TreeNode* node) const;

    /**
    *
    * printRange
    *
    * Method to traverse and print out the cache information given a low and high value.
    *
    * @param    node        the current node being examined
    * @param    low			the lower bound (inclusive) of the range to print
    * @param	high		the higher bound (inclusive) of the range to print
    *
    * @return   nothing, but prints out the keys for the cache between low and high
    */
    void printRangeHelper(TreeNode* node, int low, int high);

    /**
     * @brief Rotates a subtree left
     *
     * @param x Root of subtree to rotate
     * @return TreeNode* New root after rotation
     */
    TreeNode* rotateLeft(TreeNode* x);

    /**
     * @brief Rotates a subtree right
     *
     * @param y Root of subtree to rotate
     * @return TreeNode* New root after rotation
     */
    TreeNode* rotateRight(TreeNode* y);

    /**
     * @brief Inserts node and returns new subtree root
     *
     * @param root Current subtree root
     * @param key Key to insert
     * @param dllNode FIFO node to link
     * @return TreeNode* New subtree root
     */
    TreeNode* insertRB(TreeNode* root, int key, DllNode* dllNode);

    /**
     * @brief Removes node and returns new subtree root
     *
     * @param root Current subtree root
     * @param key Key to remove
     * @return TreeNode* New subtree root
     */
    TreeNode* removeRB(TreeNode* root, int key);

    /**
     * @brief Finds minimum key node in subtree
     *
     * @param node Root of subtree
     * @return TreeNode* Node with minimum key
     */
    TreeNode* findMin(TreeNode* node) const;

    /**
     * @brief Finds node with specified key
     *
     * @param node Root of subtree to search
     * @param key Key to find
     * @return TreeNode* Node with key, or nullptr
     */
    TreeNode* findNode(TreeNode* node, int key) const;

    /**
     * @brief Updates node counts for a given node
     *
     * @param node Node to update
     */
    void updateNodeCounts(TreeNode* node);

    /**
     * @brief Checks if node is red
     *
     * @param node Node to check
     * @return bool True if red, false if black or null
     */
    bool isRed(TreeNode* node) const;

    /**
     * @brief Gets color of a node
     *
     * @param node The node to check
     * @return Color Color of the node
     */
    Color getColor(TreeNode* node) const;

    /**
     * @brief Sets color of a node
     *
     * @param node The node to modify
     * @param color Color to set
     */
    void setColor(TreeNode* node, Color color);

    /**
     * @brief Fixes Red-Black properties after insertion
     *
     * @param node Node that was inserted
     */
    void fixInsertion(TreeNode* node);

    /**
     * @brief Fixes Red-Black properties after deletion
     *
     * @param node Node being fixed
     */
    void fixDeletion(TreeNode* node);
};

#endif // SELFBALANCING_TREE_H