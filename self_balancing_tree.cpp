/**
*
* @author - Adrian Aquino
* @file self_balancing_tree.cpp - Implementation of the self-balancing tree
*
* 04/20/25 - Imported file from Milestone 4
* 04/21/25 - Added for Milestone 5: printReverseOrder, printRange methods
* 05/17/25 - Modified by Adrian Aquino; renamed binary_search_tree.cpp to self_balancing_tree.cpp and added red-black tree functionality
* 05/21/25 - Modified by Adrian Aquino; updated red-black tree implementation with proper color handling and parent pointers
*/

#include <queue>
#include <algorithm>
#include "self_balancing_tree.h"

extern void logToFileAndConsole(std::string message);

/**
 * @brief Default constructor for SelfBalancingTree.
 *
 * Initializes an empty self-balancing tree.
 */
SelfBalancingTree::SelfBalancingTree() : root(nullptr) {}

/**
 * @brief Destructor for SelfBalancingTree.
 *
 * Frees the dynamically allocated memory by deleting all nodes in the tree.
 */
SelfBalancingTree::~SelfBalancingTree() {
    clear();
}

/**
 * @brief Gets color of a node
 *
 * @param node The node to check
 * @return Color Color of the node
 */
Color SelfBalancingTree::getColor(TreeNode* node) const {
    if (node == nullptr) return BLACK;
    return node->color;
}

/**
 * @brief Sets color of a node
 *
 * @param node The node to modify
 * @param color Color to set
 */
void SelfBalancingTree::setColor(TreeNode* node, Color color) {
    if (node != nullptr) {
        node->color = color;
    }
}

/**
 * @brief Checks if node is red
 *
 * @param node Node to check
 * @return bool True if red, false if black or null
 */
bool SelfBalancingTree::isRed(TreeNode* node) const {
    return node != nullptr && node->color == RED;
}

/**
 * @brief Updates node counts for a given node
 *
 * @param node Node to update
 */
void SelfBalancingTree::updateNodeCounts(TreeNode* node) {
    if (node == nullptr) return;

    int leftCount = (node->left) ? node->left->numberOfNodes : 0;
    int rightCount = (node->right) ? node->right->numberOfNodes : 0;
    node->numberOfNodes = leftCount + rightCount + 1;
}

/**
 * @brief Rotates a subtree left
 *
 * @param x Root of subtree to rotate
 * @return TreeNode* New root after rotation
 */
TreeNode* SelfBalancingTree::rotateLeft(TreeNode* x) {
    if (x == nullptr || x->right == nullptr) return x;

    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    y->parent = x->parent;
    x->parent = y;
    if (T2 != nullptr) T2->parent = x;

    updateNodeCounts(x);
    updateNodeCounts(y);

    return y;
}

/**
 * @brief Rotates a subtree right
 *
 * @param y Root of subtree to rotate
 * @return TreeNode* New root after rotation
 */
TreeNode* SelfBalancingTree::rotateRight(TreeNode* y) {
    if (y == nullptr || y->left == nullptr) return y;

    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->parent = y->parent;
    y->parent = x;
    if (T2 != nullptr) T2->parent = y;

    updateNodeCounts(y);
    updateNodeCounts(x);

    return x;
}

/**
 * @brief Fixes Red-Black properties after insertion
 *
 * @param node Node that was inserted
 */
void SelfBalancingTree::fixInsertion(TreeNode* node) {
    if (node == nullptr || node == root) {
        if (root != nullptr) {
            root->color = BLACK;
            root->parent = nullptr;
        }
        return;
    }

    TreeNode* parent = node->parent;
    if (parent == nullptr || !isRed(parent)) {
        return;
    }

    TreeNode* grandparent = parent->parent;
    if (grandparent == nullptr) {
        parent->color = BLACK;
        return;
    }

    TreeNode* uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;

    if (isRed(uncle)) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixInsertion(grandparent);
    } else {
        if (parent == grandparent->left) {
            if (node == parent->right) {
                parent = rotateLeft(parent);
                grandparent->left = parent;
                parent->parent = grandparent;
            }
            parent->color = BLACK;
            grandparent->color = RED;
            TreeNode* newSubRoot = rotateRight(grandparent);

            if (grandparent->parent != nullptr) {
                if (grandparent->parent->left == grandparent) {
                    grandparent->parent->left = newSubRoot;
                } else {
                    grandparent->parent->right = newSubRoot;
                }
            } else {
                root = newSubRoot;
            }
        } else {
            if (node == parent->left) {
                parent = rotateRight(parent);
                grandparent->right = parent;
                parent->parent = grandparent;
            }
            parent->color = BLACK;
            grandparent->color = RED;
            TreeNode* newSubRoot = rotateLeft(grandparent);

            if (grandparent->parent != nullptr) {
                if (grandparent->parent->left == grandparent) {
                    grandparent->parent->left = newSubRoot;
                } else {
                    grandparent->parent->right = newSubRoot;
                }
            } else {
                root = newSubRoot;
            }
        }
    }
}

/**
 * @brief Inserts node and returns new subtree root
 *
 * @param root Current subtree root
 * @param key Key to insert
 * @param dllNode FIFO node to link
 * @return TreeNode* New subtree root
 */
TreeNode* SelfBalancingTree::insertRB(TreeNode* node, int key, DllNode* dllNode) {
    if (node == nullptr) {
        TreeNode* newNode = new TreeNode(key, 1, 0, RED, nullptr, nullptr, nullptr, dllNode);
        return newNode;
    }

    if (key == node->key) {
        node->fifoNode = dllNode;
        return node;
    }

    if (key < node->key) {
        node->left = insertRB(node->left, key, dllNode);
        if (node->left != nullptr) {
            node->left->parent = node;
        }
    } else {
        node->right = insertRB(node->right, key, dllNode);
        if (node->right != nullptr) {
            node->right->parent = node;
        }
    }

    updateNodeCounts(node);
    return node;
}

/**
 * @brief Adds a node with the specified key to the tree.
 *
 * @param key The key to be added to the tree.
 * @param dllNode Pointer to the DllNode to be linked with this tree node.
 */
void SelfBalancingTree::addToTree(int key, DllNode* dllNode) {
    root = insertRB(root, key, dllNode);

    TreeNode* newNode = findNode(root, key);
    if (newNode != nullptr) {
        fixInsertion(newNode);
    }

    if (root != nullptr) {
        root->color = BLACK;
        root->parent = nullptr;
    }
}

/**
 * @brief Finds node with specified key
 *
 * @param node Root of subtree to search
 * @param key Key to find
 * @return TreeNode* Node with key, or nullptr
 */
TreeNode* SelfBalancingTree::findNode(TreeNode* node, int key) const {
    if (node == nullptr) return nullptr;

    if (key == node->key) return node;

    if (key < node->key)
        return findNode(node->left, key);
    else
        return findNode(node->right, key);
}

/**
 * @brief Finds minimum key node in subtree
 *
 * @param node Root of subtree
 * @return TreeNode* Node with minimum key
 */
TreeNode* SelfBalancingTree::findMin(TreeNode* node) const {
    if (node == nullptr) return nullptr;

    while (node->left != nullptr)
        node = node->left;

    return node;
}

/**
 * @brief Fixes Red-Black properties after deletion
 *
 * @param node Node being fixed
 */
void SelfBalancingTree::fixDeletion(TreeNode* node) {
    if (node == nullptr || node == root) return;

    TreeNode* parent = node->parent;
    if (parent == nullptr) return;

    TreeNode* sibling = (node == parent->left) ? parent->right : parent->left;

    if (isRed(sibling)) {
        setColor(parent, RED);
        setColor(sibling, BLACK);
        if (node == parent->left) {
            TreeNode* newSubRoot = rotateLeft(parent);
            if (parent->parent != nullptr) {
                if (parent->parent->left == parent) {
                    parent->parent->left = newSubRoot;
                } else {
                    parent->parent->right = newSubRoot;
                }
            } else {
                root = newSubRoot;
            }
        } else {
            TreeNode* newSubRoot = rotateRight(parent);
            if (parent->parent != nullptr) {
                if (parent->parent->left == parent) {
                    parent->parent->left = newSubRoot;
                } else {
                    parent->parent->right = newSubRoot;
                }
            } else {
                root = newSubRoot;
            }
        }
        sibling = (node == parent->left) ? parent->right : parent->left;
    }

    if (!isRed(sibling) && !isRed(sibling->left) && !isRed(sibling->right)) {
        setColor(sibling, RED);
        if (getColor(parent) == BLACK) {
            fixDeletion(parent);
        } else {
            setColor(parent, BLACK);
        }
        return;
    }

    if ((node == parent->left && isRed(sibling->left) && !isRed(sibling->right)) ||
        (node == parent->right && isRed(sibling->right) && !isRed(sibling->left))) {

        if (node == parent->left) {
            setColor(sibling->left, BLACK);
            setColor(sibling, RED);
            parent->right = rotateRight(sibling);
            if (parent->right != nullptr) parent->right->parent = parent;
            sibling = parent->right;
        } else {
            setColor(sibling->right, BLACK);
            setColor(sibling, RED);
            parent->left = rotateLeft(sibling);
            if (parent->left != nullptr) parent->left->parent = parent;
            sibling = parent->left;
        }
    }

    setColor(sibling, getColor(parent));
    setColor(parent, BLACK);

    if (node == parent->left) {
        setColor(sibling->right, BLACK);
        TreeNode* newSubRoot = rotateLeft(parent);
        if (parent->parent != nullptr) {
            if (parent->parent->left == parent) {
                parent->parent->left = newSubRoot;
            } else {
                parent->parent->right = newSubRoot;
            }
        } else {
            root = newSubRoot;
        }
    } else {
        setColor(sibling->left, BLACK);
        TreeNode* newSubRoot = rotateRight(parent);
        if (parent->parent != nullptr) {
            if (parent->parent->left == parent) {
                parent->parent->left = newSubRoot;
            } else {
                parent->parent->right = newSubRoot;
            }
        } else {
            root = newSubRoot;
        }
    }
}

/**
 * @brief Removes node and returns new subtree root
 *
 * @param root Current subtree root
 * @param key Key to remove
 * @return TreeNode* New subtree root
 */
TreeNode* SelfBalancingTree::removeRB(TreeNode* node, int key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        node->left = removeRB(node->left, key);
        if (node->left != nullptr) node->left->parent = node;
    } else if (key > node->key) {
        node->right = removeRB(node->right, key);
        if (node->right != nullptr) node->right->parent = node;
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            if (getColor(node) == BLACK) {
                fixDeletion(node);
            }
            delete node;
            return nullptr;
        }

        if (node->left == nullptr) {
            TreeNode* temp = node->right;
            if (getColor(node) == BLACK && getColor(temp) == RED) {
                setColor(temp, BLACK);
            }
            temp->parent = node->parent;
            delete node;
            return temp;
        }
        if (node->right == nullptr) {
            TreeNode* temp = node->left;
            if (getColor(node) == BLACK && getColor(temp) == RED) {
                setColor(temp, BLACK);
            }
            temp->parent = node->parent;
            delete node;
            return temp;
        }

        TreeNode* successor = findMin(node->right);
        node->key = successor->key;
        node->fifoNode = successor->fifoNode;
        node->right = removeRB(node->right, successor->key);
        if (node->right != nullptr) node->right->parent = node;
    }

    updateNodeCounts(node);
    return node;
}

/**
 * @brief Removes a node with the specified key from the tree.
 *
 * @param key The key of the node to remove.
 * @return True if the node was removed, false if the key wasn't found.
 */
bool SelfBalancingTree::removeNode(int key) {
    if (!contains(key)) return false;

    root = removeRB(root, key);

    if (root != nullptr) {
        setColor(root, BLACK);
        root->parent = nullptr;
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
int SelfBalancingTree::getHeightOfTree() const {
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
int SelfBalancingTree::getHeight(TreeNode* node) const {
    if (node == nullptr) return 0;

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    return std::max(leftHeight, rightHeight) + 1;
}

/**
 * @brief Gets the number of nodes in the tree.
 *
 * @return The number of nodes in the tree.
 */
int SelfBalancingTree::getNumberOfTreeNodes() const {
    if (root == nullptr) return 0;
    return root->numberOfNodes;
}

/**
 * @brief Checks if the tree contains a node with the specified key.
 *
 * @param key The key to search for in the tree.
 * @return True if the key exists in the tree, false otherwise.
 */
bool SelfBalancingTree::contains(int key) const {
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
TreeNode* SelfBalancingTree::getRoot() const {
    return root;
}

/**
 * @brief Checks if the tree is empty.
 *
 * @return True if the tree is empty, false otherwise.
 */
bool SelfBalancingTree::isEmpty() const {
    return root == nullptr;
}

/**
 * @brief Clears the entire tree.
 *
 * Deletes all the nodes in the tree, freeing up memory.
 */
void SelfBalancingTree::clear() {
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
void SelfBalancingTree::deleteTree(TreeNode* node) {
    if (node == nullptr) return;

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
void SelfBalancingTree::printNodeFromTree(TreeNode* node) const {
    if (node == nullptr) {
        logToFileAndConsole("Node is null");
        return;
    }

    std::string color = (node->color == RED) ? "RED" : "BLACK";
    logToFileAndConsole("Node key: " + std::to_string(node->key) + ", Color: " + color);

    if (node->fifoNode != nullptr) {
        node->fifoNode->printNode();
    }
}

/**
 * @brief Helper function for recursive in-order traversal.
 *
 * This function is called recursively to perform an in-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the in-order traversal.
 */
void SelfBalancingTree::printInOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    printInOrderHelper(node->left);

    std::string color = (node->color == RED) ? "RED" : "BLACK";
    logToFileAndConsole("Node key: " + std::to_string(node->key) + ", Color: " + color);

    printInOrderHelper(node->right);
}

/**
 * @brief Performs an in-order traversal of the tree and prints the nodes.
 *
 * In-order traversal visits the left subtree, the node, and then the right subtree.
 */
void SelfBalancingTree::printInOrder() const {
    logToFileAndConsole("Performing In-order traversal");
    printInOrderHelper(root);
}

/**
 * @brief Helper function for recursive reverse in-order traversal.
 *
 * This function is called recursively to perform a reverse in-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the reverse in-order traversal.
 */
void SelfBalancingTree::printReverseOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    printReverseOrderHelper(node->right);

    std::string color = (node->color == RED) ? "RED" : "BLACK";
    logToFileAndConsole("Node key: " + std::to_string(node->key) + ", Color: " + color);

    printReverseOrderHelper(node->left);
}

/**
 * @brief Performs a reverse traversal of the tree and prints the nodes.
 *
 * Reverse traversal visits the right subtree, the node, and then the left subtree.
 */
void SelfBalancingTree::printReverseOrder() const {
    logToFileAndConsole("Performing reverse-order traversal");
    printReverseOrderHelper(root);
}

/**
 * @brief Helper function for recursive pre-order traversal.
 *
 * This function is called recursively to perform a pre-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the pre-order traversal.
 */
void SelfBalancingTree::printPreOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    std::string color = (node->color == RED) ? "RED" : "BLACK";
    logToFileAndConsole("Node key: " + std::to_string(node->key) + ", Color: " + color);

    printPreOrderHelper(node->left);
    printPreOrderHelper(node->right);
}

/**
 * @brief Performs a pre-order traversal of the tree and prints the nodes.
 *
 * Pre-order traversal visits the node, the left subtree, and then the right subtree.
 */
void SelfBalancingTree::printPreOrder() const {
    logToFileAndConsole("Performing Pre-order traversal");
    printPreOrderHelper(root);
}

/**
 * @brief Helper function for recursive post-order traversal.
 *
 * This function is called recursively to perform a post-order traversal starting from the given node.
 *
 * @param node A pointer to the node from which to begin the post-order traversal.
 */
void SelfBalancingTree::printPostOrderHelper(TreeNode* node) const {
    if (node == nullptr) return;

    printPostOrderHelper(node->left);
    printPostOrderHelper(node->right);

    std::string color = (node->color == RED) ? "RED" : "BLACK";
    logToFileAndConsole("Node key: " + std::to_string(node->key) + ", Color: " + color);
}

/**
 * @brief Performs a post-order traversal of the tree and prints the nodes.
 *
 * Post-order traversal visits the left subtree, the right subtree, and then the node.
 */
void SelfBalancingTree::printPostOrder() const {
    logToFileAndConsole("Performing Post-order traversal");
    printPostOrderHelper(root);
}

/**
 * @brief Performs a depth-first traversal (same as pre-order traversal) and prints the nodes.
 *
 * Depth-first traversal visits the node first, then the left subtree, and then the right subtree.
 */
void SelfBalancingTree::printDepthFirst() const {
    logToFileAndConsole("Performing Depth First via PreOrder traversal");
    printPreOrder();
}

/**
 * @brief Performs a breadth-first traversal of the tree and prints the nodes.
 *
 * Breadth-first traversal visits nodes level by level, from left to right.
 */
void SelfBalancingTree::printBreadthFirst() const {
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

        std::string color = (current->color == RED) ? "RED" : "BLACK";
        logToFileAndConsole("Node key: " + std::to_string(current->key) + ", Color: " + color);

        if (current->left != nullptr) {
            nodeQueue.push(current->left);
        }

        if (current->right != nullptr) {
            nodeQueue.push(current->right);
        }
    }
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
void SelfBalancingTree::printRangeHelper(TreeNode* node, int low, int high) {
    if (node == nullptr) return;

    if (low < node->key) {
        printRangeHelper(node->left, low, high);
    }

    if (low <= node->key && node->key <= high) {
        std::string color = (node->color == RED) ? "RED" : "BLACK";
        logToFileAndConsole("Node key: " + std::to_string(node->key) + ", Color: " + color);

        if (node->fifoNode != nullptr) {
            node->fifoNode->printNode();
        }
    }

    if (node->key < high) {
        printRangeHelper(node->right, low, high);
    }
}

/**
 * @brief Prints the nodes in the tree within a given range of keys.
 *
 * @param low The lower bound (inclusive) of the range.
 * @param high The upper bound (inclusive) of the range.
 */
void SelfBalancingTree::printRange(int low, int high) {
    logToFileAndConsole("Printing nodes in range [" + std::to_string(low) + ", " + std::to_string(high) + "]");
    printRangeHelper(root, low, high);
}