/**
*
* hash_node.cpp : Implementation file for HashNode, used in hash_table.cpp
*
* 01/16/25 - Created by H. Hui
* 05/07/25 - Modified by Adrian Aquino; Added hashCode initialization
*/

#include "dll_node.h"
#include "hash_node.h"

// Define a structure for a node in the hash table
HashNode::HashNode(int myKeyValue, DllNode* myDllNode) :
	key(myKeyValue),
	hashCode(0),
	fifoNode(myDllNode),
	prev(nullptr),
	next(nullptr) {}

DllNode* HashNode::getFifoNode() {
	return fifoNode;
}