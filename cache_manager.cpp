/**
*
* @author - Adrian Aquino
* @file cache_manager.cpp - Implementation of the cache manager
*
* 04/20/25 - Imported file from Milestone 3
* 04/21/25 - Added missing methods: getBst, printRange, sort; fixed output formatting
* 05/17/25 - Modified by Adrian Aquino; changed getBst() to return SelfBalancingTree*
* 05/21/25 - Modified by Adrian Aquino; updated for corrected red-black tree implementation
*
*/

#include <iostream>
#include <string>
#include <fstream>
#include "cache_manager.h"

extern void logToFileAndConsole(std::string msg);
extern std::ofstream& getOutFile();

/**
*
* getTable
*
* Method to return the hash table
*
* @param    none
*
* @return	the hash table
*/
HashTable* CacheManager::getTable() {
    return hashTable;
}

/**
*
* getList
*
* Method to return the FIFO list
*
* @param    none
*
* @return	the FIFO list
*/
DoublyLinkedList* CacheManager::getList() {
    return doublyLinkedList;
}

/**
*
* getBst
*
* Method to return the BST
*
* @param    none
*
* @return	the BST
*/
SelfBalancingTree* CacheManager::getBst() {
    return binarySearchTree;
}

/**
*
* getSize
*
* Method to return the number of items in the CacheManager
*
* @param    none
*
* @return	number of items in the CacheManager
*/
int CacheManager::getSize() {
    return hashTable->getNumberOfItems();
}

/**
*
* isEmpty
*
* Method to check if CacheManager is empty
*
* @param    none
*
* @return   true if the CacheManager has zero entries, false otherwise
*/
bool CacheManager::isEmpty() {
    return hashTable->isEmpty();
}

/**
*
* add
*
* Method to add a node to the CacheManager
*
* @param    curKey    key for this node
* @param    myNode    new node to add to the table
*
* @return   true if success, false otherwise
*/
bool CacheManager::add(int curKey, DllNode* myNode) {
    if (contains(curKey)) {
        remove(curKey);
    }

    if (doublyLinkedList->getSize() >= maxCacheSize) {
        if (!doublyLinkedList->isEmpty()) {
            int oldestKey = doublyLinkedList->tail->key;
            remove(oldestKey);
        }
    }

    HashNode* newHashNode = new HashNode(curKey, myNode);
    bool addedToHash = hashTable->add(curKey, newHashNode);

    doublyLinkedList->insertAtHead(curKey, myNode);

    binarySearchTree->addToTree(curKey, myNode);

    return addedToHash;
}

/**
*
* remove
*
* Method to remove node with curKey
*
* @param    key     key of node to remove
*
* @return   true if success, false otherwise
*/
bool CacheManager::remove(int curKey) {
    if (!hashTable->contains(curKey)) {
        return false;
    }

    doublyLinkedList->remove(curKey);

    binarySearchTree->removeNode(curKey);

    return hashTable->remove(curKey);
}

/**
*
* clear
*
* Method to remove all entries from the CacheManager
*
* @param    none
*
* @return   nothing, but will delete all entries from the CacheManager
*/
void CacheManager::clear() {
    doublyLinkedList->clear();
    hashTable->clear();
    binarySearchTree->clear();
}

/**
*
* getItem
*
* Method to retrieve item from the CacheManager
*
* @param    curKey  retrieve node from CacheManager with curKey value
*
* @return   pointer to the DllNode
*/
DllNode* CacheManager::getItem(int curKey) {
    HashNode* hashNode = hashTable->getItem(curKey);
    if (hashNode == nullptr) {
        return nullptr;
    }

    doublyLinkedList->moveNodeToHead(curKey);

    return hashNode->getFifoNode();
}

/**
*
* getMaxCacheSize
*
* Method to retrieve max size of cache from the CacheManager
*
* @param    none
*
* @return   max size of cache manager
*/
int CacheManager::getMaxCacheSize() {
    return maxCacheSize;
}

/**
*
* contains
*
* Method to determine if a key value is in the cache
*
* @param    curKey  retrieve node from cacheManager with curKey value
*
* @return   true if exists, false otherwise
*/
bool CacheManager::contains(int curKey) {
    bool result = hashTable->contains(curKey);

    if (result) {
        doublyLinkedList->moveNodeToHead(curKey);
    }

    return result;
}

/**
*
* printCache
*
* Method to print out the cache information
*
* @param    none
*
* @return   nothing, but prints out the cache information
*/
void CacheManager::printCache() {
    std::ofstream& outFile = getOutFile();

    std::cout << "Printing out the cache: " << std::endl;
    outFile << "Printing out the cache: " << std::endl;

    std::cout << "Here are the FIFO List contents: " << std::endl;
    outFile << "Here are the FIFO List contents: " << std::endl;

    if (doublyLinkedList->isEmpty()) {
        std::cout << "Empty list" << std::endl;
        outFile << "Empty list" << std::endl;
    } else {
        DllNode* current = doublyLinkedList->head;
        while (current != nullptr) {
            std::cout << current->key << " " << std::endl;
            outFile << current->key << " " << std::endl;
            current = current->next;
        }
    }

    std::cout << "End of FIFO List" << std::endl;
    outFile << "End of FIFO List" << std::endl;

    hashTable->printTable();
}

/**
*
* printRange
*
* Method to traverse and print out the cache information given a low and high value.
*
* @param    low    the lower bound (inclusive) of the range to print
* @param    high   the higher bound (inclusive) of the range to print
*
* @return   nothing, but prints out the keys for the cache between low and high
*/
void CacheManager::printRange(int low, int high) {
    binarySearchTree->printRange(low, high);
}

/**
*
* sort
*
* Method to print out the cache information in sorted order
*
* @param    ascending   true, if output is to be in ascending order, false for descending order
*
* @return   nothing, but prints out the keys for the cache in sorted order
*/
void CacheManager::sort(bool ascending) {
    if (ascending) {
        binarySearchTree->printInOrder();
    } else {
        binarySearchTree->printReverseOrder();
    }

    binarySearchTree->printBreadthFirst();
}