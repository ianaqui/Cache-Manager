/**
*
* @author - Adrian Aquino
* @file binary_search_tree.cpp - Implementation of the binary search tree
*
* 04/20/25 - Imported file from Milestone 4
* 04/21/25 - Added for Milestone 5: printReverseOrder, printRange methods
*/

#include <queue>
#include <algorithm>
#include "binary_search_tree.h"

extern void logToFileAndConsole(std::string message);

/**
 * @brief Default constructor for BinarySearchTree.
 *
 * Initializes an empty binary search tree.
 */
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

/**
 * @brief Destructor for BinarySearchTree.
 *
 * Frees the dynamically allocated memory by deleting all nodes in the tree.
 */
BinarySearchTree::~BinarySearchTree() {
    clear();
}

/**
 * @brief Adds a node with the specified key to the tree.
 *
 * @param key The key to be added to the tree.
 * @param dllNode Pointer to the DllNode to be linked with this tree node.
 */
void BinarySearchTree::addToTree(int key, DllNode* dllNode) {
    if (root == nullptr) {
        root = new TreeNode(key, 1, 0, nullptr, nullptr, dllNode);
        return;
    }

    TreeNode* current = root;
    TreeNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        current->numberOfNodes++;

        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            // Key already exists, update the FIFO node and restore node counts
            current->fifoNode = dllNode;
            current = root;
            while (current != nullptr) {
                if (current == parent) break;
                current->numberOfNodes--;
                if (key < current->key) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            return;
        }
    }

    TreeNode* newNode = new TreeNode(key, 1, 0, nullptr, nullptr, dllNode);
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Update heights throughout the tree
    current = root;
    while (current != nullptr) {
        int leftHeight = (current->left) ? current->left->height + 1 : 0;
        int rightHeight = (current->right) ? current->right->height + 1 : 0;
        current->height = std::max(leftHeight, rightHeight);

        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            break;
        }
    }
}

/**
 * @brief Removes a node with the specified key from the tree.
 *
 * @param key The key of the node to remove.
 * @return True if the node was removed, false if the key wasn't found.
 */
bool BinarySearchTree::removeNode(int key) {
    if (root == nullptr) return false;

    TreeNode* current = root;
    TreeNode* parent = nullptr;
    bool isLeftChild = false;

    // Find the node to remove
    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) {
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
    }

    // Node not found
    if (current == nullptr) return false;

    // Case 1: Node has no children
    if (current->left == nullptr && current->right == nullptr) {
        if (current == root) {
            delete root;
            root = nullptr;
        } else {
            if (isLeftChild) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
        }
    }
    // Case 2: Node has one child
    else if (current->left == nullptr) {
        if (current == root) {
            root = current->right;
        } else {
            if (isLeftChild) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
        }
        delete current;
    } else if (current->right == nullptr) {
        if (current == root) {
            root = current->left;
        } else {
            if (isLeftChild) {
                parent->left = current->left;
            } else {
                parent->right = current->left;
            }
        }
        delete current;
    }
    // Case 3: Node has two children
    else {
        TreeNode* successor = current->right;
        TreeNode* successorParent = current;

        // Find the inorder successor (smallest node in right subtree)
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // Link successor's right child
        if (successorParent != current) {
            successorParent->left = successor->right;
            successor->right = current->right;
        }

        // Replace current with successor
        if (current == root) {
            successor->left = root->left;
            root = successor;
        } else {
            successor->left = current->left;
            if (isLeftChild) {
                parent->left = successor;
            } else {
                parent->right = successor;
            }
        }
        delete current;
    }

    // Update tree heights and node counts
    if (root != nullptr) {
        TreeNode* temp = root;
        while (temp != nullptr) {
            int leftNodes = (temp->left) ? temp->left->numberOfNodes : 0;
            int rightNodes = (temp->right) ? temp->right->numberOfNodes : 0;
            temp->numberOfNodes = leftNodes + rightNodes + 1;

            int leftHeight = (temp->left) ? temp->left->height + 1 : 0;
            int rightHeight = (temp->right) ? temp->right->height + 1 : 0;
            temp->height = std::max(leftHeight, rightHeight);

            if (key < temp->key) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
    }

    return true;
}

/**
 * @brief Gets the height of the tree.
 *
 * The height of the tree is defined as the length of the longest path from
 * the root to a leaf node.
 *
 * @return The height of the tree.
 */
int BinarySearchTree::getHeightOfTree() const {
    if (root == nullptr) return 0;
    return getHeight(root);
}

/**
 * @brief Helper function to calculate the height of a node.
 *
 * This function is used by `getHeightOfTree` to calculate the height of the tree.
 *
 * @param node A pointer to the node whose height is to be calculated.
 * @return The height of the given node.
 */
int BinarySearchTree::getHeight(TreeNode* node) const {
    if (node == nullptr) return 0;
    return node->height + 1;
}

/**
 * @brief Gets the number of nodes in the tree.
 *
 * @return The number of nodes in the tree.
 */
int BinarySearchTree::getNumberOfTreeNodes() const {
    if (root == nullptr) return 0;
    return root->numberOfNodes;
}

/**
 * @brief Checks if the tree contains a node with the specified key.
 *
 * @param key The key to search for in the tree.
 * @return True if the key exists in the tree, false otherwise.
 */
bool BinarySearchTree::contains(int key) const {
    TreeNode* current = root;

    while (current != nullptr) {
        if (key == current->key) {
            return true;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

/**
 * @brief Gets the root node of the tree.
 *
 * @return A pointer to the root node of the tree.
 */
TreeNode* BinarySearchTree::getRoot() const {
    return root;
}

/**
 * @brief Checks if the tree is empty.
 *
 * @return True if the tree is empty, false otherwise.
 */
bool BinarySearchTree::isEmpty() const {
    return root == nullptr;
}

/**
 * @brief Clears the entire tree.
 *
 * Deletes all the nodes in the tree, freeing up memory.
 */
void BinarySearchTree::clear() {
    deleteTree(root);
    root = nullptr;
}

/**
 * @brief Deletes the tree starting from the specified node.
 *
 * Recursively deletes all nodes in the tree.
 *
 * @param node The starting node to begin deleting the tree.
 */
void BinarySearchTree::deleteTree(TreeNode* node) {
    if (node == nullptr) return;

    // Post-order traversal to delete nodes (children first, then parent)
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

/**
 * @brief Prints the data of a specific node.
 *
 * This function prints the key, number of nodes in the subtree, and height of the given node.
 *
 * @param node A pointer to the node whose data is to be printed.
 */
void BinarySearchTree::printNodeFromTree(TreeNode* node) const {
    if (node == nullptr) {
        logToFileAndConsole("Node is null");
        return;
    }

    logToFileAndConsole("Node key: " + std::to_string(node->key));

    // Print FIFO node details if available
    if (node->fifoNode != nullptr) {
        node->fifoNode->printNode();
    }
}

/**
 * @brief Performs an in-order traversal of the tree and prints the nodes.
 *
 * In-order traversal visits the left subtree, the node, and then the right subtree.
 */
void BinarySearchTree::printInOrder() const {
    logToFileAndConsole("Performing In-order traversal");
    printInOrderHelper(root);
}

/**
 * @brief Helper function for recursive in-order traversal.
 *
 * This function is called recursively to perform an in-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the in-order traversal.
 */
void BinarySearchTree::printInOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    printInOrderHelper(node->left);
    logToFileAndConsole("Node key: " + std::to_string(node->key));
    printInOrderHelper(node->right);
}

/**
 * @brief Performs a reverse traversal of the tree and prints the nodes.
 *
 * Reverse traversal visits the right subtree, the node, and then the left subtree.
 */
void BinarySearchTree::printReverseOrder() const {
    logToFileAndConsole("Performing reverse-order traversal");
    printReverseOrderHelper(root);
}

/**
 * @brief Helper function for recursive reverse in-order traversal.
 *
 * This function is called recursively to perform a reverse in-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the reverse in-order traversal.
 */
void BinarySearchTree::printReverseOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    printReverseOrderHelper(node->right);
    logToFileAndConsole("Node key: " + std::to_string(node->key));
    printReverseOrderHelper(node->left);
}

/**
 * @brief Performs a pre-order traversal of the tree and prints the nodes.
 *
 * Pre-order traversal visits the node, the left subtree, and then the right subtree.
 */
void BinarySearchTree::printPreOrder() const {
    logToFileAndConsole("Performing Pre-order traversal");
    printPreOrderHelper(root);
}

/**
 * @brief Helper function for recursive pre-order traversal.
 *
 * This function is called recursively to perform a pre-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the pre-order traversal.
 */
void BinarySearchTree::printPreOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    logToFileAndConsole("Node key: " + std::to_string(node->key));
    printPreOrderHelper(node->left);
    printPreOrderHelper(node->right);
}

/**
 * @brief Performs a post-order traversal of the tree and prints the nodes.
 *
 * Post-order traversal visits the left subtree, the right subtree, and then the node.
 */
void BinarySearchTree::printPostOrder() const {
    logToFileAndConsole("Performing Post-order traversal");
    printPostOrderHelper(root);
}

/**
 * @brief Helper function for recursive post-order traversal.
 *
 * This function is called recursively to perform a post-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the post-order traversal.
 */
void BinarySearchTree::printPostOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    printPostOrderHelper(node->left);
    printPostOrderHelper(node->right);
    logToFileAndConsole("Node key: " + std::to_string(node->key));
}

/**
 * @brief Performs a depth-first traversal (same as pre-order traversal) and prints the nodes.
 *
 * Depth-first traversal visits the node first, then the left subtree, and then the right subtree.
 */
void BinarySearchTree::printDepthFirst() const {
    logToFileAndConsole("Performing Depth First via PreOrder traversal");
    printPreOrder();
}

/**
 * @brief Performs a breadth-first traversal of the tree and prints the nodes.
 *
 * Breadth-first traversal visits nodes level by level, from left to right.
 */
void BinarySearchTree::printBreadthFirst() const {
    if (root == nullptr) {
        logToFileAndConsole("Tree is empty");
        return;
    }

    logToFileAndConsole("Performing Breadth First traversal");

    std::queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        TreeNode* current = nodeQueue.front();
        nodeQueue.pop();

        logToFileAndConsole("Node key: " + std::to_string(current->key));

        if (current->left != nullptr) {
            nodeQueue.push(current->left);
        }

        if (current->right != nullptr) {
            nodeQueue.push(current->right);
        }
    }
}

/**
 * @brief Prints the nodes in the tree within a given range of keys.
 *
 * @param low The lower bound (inclusive) of the range.
 * @param high The upper bound (inclusive) of the range.
 */
void BinarySearchTree::printRange(int low, int high) {
    logToFileAndConsole("Printing nodes in range [" + std::to_string(low) + ", " + std::to_string(high) + "]");
    printRangeHelper(root, low, high);
}

/**
 * @brief Helper function for printing nodes in a given range.
 *
 * This function is called recursively to print nodes with keys in the specified range.
 *
 * @param node A pointer to the current node being examined.
 * @param low The lower bound (inclusive) of the range.
 * @param high The upper bound (inclusive) of the range.
 */
void BinarySearchTree::printRangeHelper(TreeNode* node, int low, int high) {
    if (node == nullptr) return;

    // If node's key is greater than low, search in the left subtree
    if (low < node->key) {
        printRangeHelper(node->left, low, high);
    }

    // If node's key is in range, print it
    if (low <= node->key && node->key <= high) {
        logToFileAndConsole("Node key: " + std::to_string(node->key));
        if (node->fifoNode != nullptr) {
            node->fifoNode->printNode();
        }
    }

    // If node's key is less than high, search in the right subtree
    if (node->key < high) {
        printRangeHelper(node->right, low, high);
    }
}