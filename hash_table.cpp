/**
*
* @author - Adrian Aquino
* @file hash_table.cpp - Implementation of hash table
*
* 4/20/25 - Imported from Milestone 3
* 5/7/25 - Modified to work without needing to include iostream in header file
*/

#include <iostream>
#include <string>
#include "hash_table.h"

extern void logToFileAndConsole(std::string msg);

HashTable::HashTable() : numberOfBuckets(0), numberOfItems(0), table(nullptr) {}

/**
*
* getTable
*
* Method to return the hash table
*
* @param    none
*
* @return   pointer to the hash table array
*/
HashNode** HashTable::getTable() {
    return table;
}

/**
*
* getSize
*
* Method to return the size of the hash table
*
* @param    none
*
* @return	size of the hash table array
*/
int HashTable::getSize() {
    return numberOfBuckets;
}

/**
*
* calculateHashCode
*
* Method to calculate the hashCode
*
* @param    currentKey     hash table size
*
* @return   hashcode for currentKey
*/
int HashTable::calculateHashCode(int currentKey) {
    return currentKey % numberOfBuckets;
}

/**
*
* isEmpty
*
* Method to check if HashTable is empty
*
* @param    none
*
* @return   true if the table has zero entries, false otherwise
*/
bool HashTable::isEmpty() {
    return numberOfItems == 0;
}

/**
*
* getNumberOfItems
*
* Method to return number of items in the hash table
*
* @param    none
*
* @return   number of items in the table
*/
int HashTable::getNumberOfItems() {
    return numberOfItems;
}

/**
*
* add
*
* Method to add a node to the hash table
*
* @param    curKey    key for this node
* @param    myNode    new node to add to the table
*
* @return   true if success, false otherwise
*/
bool HashTable::add(int curKey, HashNode* myNode) {
    int hashCode = calculateHashCode(curKey);
    myNode->hashCode = hashCode;

    if (contains(curKey)) {
        return false;
    }

    if (table[hashCode] == nullptr) {
        table[hashCode] = myNode;
    } else {
        myNode->next = table[hashCode];
        table[hashCode]->prev = myNode;
        table[hashCode] = myNode;
    }

    numberOfItems++;
    return true;
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
bool HashTable::remove(int curKey) {
    if (!contains(curKey)) {
        return false;
    }

    int hashCode = calculateHashCode(curKey);

    HashNode* current = table[hashCode];
    while (current != nullptr && current->key != curKey) {
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }

    if (current->prev == nullptr) {
        table[hashCode] = current->next;
        if (table[hashCode] != nullptr) {
            table[hashCode]->prev = nullptr;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
    }

    delete current;
    numberOfItems--;
    return true;
}

/**
*
* clear
*
* Method to remove all entries from the table
*
* @param    none
*
* @return   nothing, but will delete all entries from the table
*/
void HashTable::clear() {
    for (int i = 0; i < numberOfBuckets; i++) {
        HashNode* current = table[i];

        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }

        table[i] = nullptr;
    }

    numberOfItems = 0;
}

/**
*
* getItem
*
* Method to retrieve item from the hash table
*
* @param    curKey  retrieve node from hash table with curKey value
*
* @return   pointer to the HashNode
*/
HashNode* HashTable::getItem(int curKey) {
    int hashCode = calculateHashCode(curKey);

    HashNode* current = table[hashCode];
    while (current != nullptr && current->key != curKey) {
        current = current->next;
    }

    return current;
}

/**
*
* contains
*
* Method to verify if a key is in the hash table
*
* @param    curKey  check key for hash table with curKey value
*
* @return   true if found, false otherwise
*/
bool HashTable::contains(int curKey) {
    int hashCode = calculateHashCode(curKey);

    HashNode* current = table[hashCode];
    while (current != nullptr) {
        if (current->key == curKey) {
            return true;
        }
        current = current->next;
    }

    return false;
}

/**
*
* printTable
*
* Method to print out the contents of table
*
* @param    none
*
* @return   nothing, but output is sent to console and to file
*/
void HashTable::printTable() {
    for (int i = 0; i < numberOfBuckets; i++) {
        if (table[i] == nullptr) {
            logToFileAndConsole("Empty bucket: " + std::to_string(i));
        } else {
            logToFileAndConsole("\nBucket " + std::to_string(i) + ": ");

            HashNode* current = table[i];
            while (current != nullptr) {
                if (current->fifoNode != nullptr) {
                    current->fifoNode->printNode();
                } else {
                    logToFileAndConsole("Hash node with key: " + std::to_string(current->key));
                }
                current = current->next;
            }
        }
    }
}