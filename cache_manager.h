/**
*
* cache_manager.h : This is the header file for cache_manager.cpp.
*
* 09/23/24 - Created by ChatGPT
* 10/17/24 - Modified by jhui
* 01/11/25 - Modified by hhui; 1) added calculateHashCode, 2) modified methods to include hash table size parameter
* 01/16/2025 - Modified by hhui; created separate node structure file
* 01/27/2025 - Modified by hhui; added getMaxCacheSize
* 05/17/2025 - Modified by Adrian Aquino; changed to use SelfBalancingTree instead of BinarySearchTree for Milestone 6
* 05/21/2025 - Modified by Adrian Aquino; updated for updated red-black tree implementation
*/

#ifndef _CACHE_MANAGER
#define _CACHE_MANAGER

#include "hash_table.h"
#include "doubly_linked_list.h"
#include "self_balancing_tree.h"

class CacheManager {
private:
	HashTable* hashTable;
	DoublyLinkedList* doublyLinkedList;
	SelfBalancingTree* binarySearchTree;

	int maxCacheSize;

public:
	CacheManager(int myMaxCacheSize, int myHashTableSize) {
		if (myHashTableSize > myMaxCacheSize) {
			myMaxCacheSize = myHashTableSize;
			std::cout << "Resetting MaxCacheSize, " << myMaxCacheSize << ", to match myHashTableSize of : " << myHashTableSize << "!  Reconsider your life choices!!!" << std::endl;

		}

		hashTable = new HashTable(myHashTableSize);
		doublyLinkedList = new DoublyLinkedList();
		binarySearchTree = new SelfBalancingTree();

		maxCacheSize = myHashTableSize;
	}

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
	HashTable* getTable();

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
	DoublyLinkedList* getList();

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
	SelfBalancingTree* getBst();

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
	int getSize();

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
	bool isEmpty();

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
	bool add(int curKey, DllNode* myNode);

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
	bool remove(int curKey);

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
	void clear();

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
	DllNode* getItem(int curKey);

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
	int getMaxCacheSize();

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
	bool contains(int curKey);

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
	void printCache();

	/**
	*
	* range
	*
	* Method to traverse and print out the cache information given a low and high value.
	*
	* @param    low			the lower bound (inclusive) of the range to print
	* @param	high		the higher bound (inclusive) of the range to print
	*
	* @return   nothing, but prints out the keys for the cache between low and high
	*/
	void printRange(int low, int high);

	/**
	*
	* sort
	*
	* Method to print out the cache information in sorted order
	*
	* @param    ascending	true, if output is to be in ascending order, false for descending order
	*
	* @return   nothing, but prints out the keys for the cache in sorted order
	*/
	void sort(bool ascending);

};

#endif