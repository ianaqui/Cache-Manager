# 🚀 Cache Manager with Red-Black Tree

## 🎯 Intro:
A high-performance C++ cache management system that combines three sophisticated data structures for optimal caching operations. This implementation features a Red-Black Tree for self-balancing operations, hash table for O(1) lookups, and doubly linked list for LRU (Least Recently Used) cache behavior.

## 🛠️ Tech Stack:
* **C++17** - Modern C++ with advanced features
* **CMake** - Cross-platform build system
* **nlohmann/json** - JSON parsing and configuration
* **Red-Black Tree** - Self-balancing binary search tree
* **Hash Table** - Separate chaining collision resolution
* **Doubly Linked List** - Bi-directional node traversal
* **Command Line Interface** - Text-based interaction

## 💫 Features:

### 🌳 Red-Black Tree Implementation:
* **Self-Balancing Operations**: Automatic tree rebalancing on insertion/deletion
* **Color-Based Balancing**: RED/BLACK node coloring with proper invariants
* **Rotation Operations**: Left and right rotations for tree restructuring
* **Parent Pointer Support**: Bidirectional tree navigation
* **Traversal Methods**: In-order, pre-order, post-order, breadth-first, depth-first
* **Range Queries**: Efficient range-based data retrieval
* **Tree Statistics**: Height calculation and node counting

### ⚡ Hash Table System:
* **Separate Chaining**: Collision resolution with linked lists
* **Dynamic Hashing**: Modulo-based hash code calculation
* **O(1) Operations**: Average-case constant-time lookup/insertion/deletion
* **Load Factor Management**: Efficient space utilization
* **Bucket Visualization**: Complete hash table state printing

### 🔗 Doubly Linked List Cache:
* **LRU Implementation**: Least Recently Used eviction policy
* **Bi-directional Navigation**: Forward and reverse traversal
* **Head/Tail Operations**: Efficient insertion at both ends
* **Node Movement**: Dynamic repositioning for cache optimization
* **Memory Management**: Automatic cleanup and deallocation

### 🎯 Cache Manager Features:
* **Multi-Structure Synchronization**: Keeps all three data structures in sync
* **Capacity Management**: Automatic eviction when cache reaches limit
* **Access Pattern Optimization**: Moves frequently accessed items to front
* **Comprehensive Operations**: Add, remove, contains, clear, sort
* **Data Persistence**: Stores user information (name, address, city, state, zip)

### 🧪 Testing & Configuration:
* **JSON-Driven Testing**: Configurable test cases via JSON files
* **Multiple Test Scenarios**: Comprehensive edge case coverage
* **Flexible Configuration**: Adjustable cache size and hash table parameters
* **Output Logging**: Detailed operation logging to files and console

## 📝 Process:
Developed this advanced cache system to demonstrate the integration of multiple data structures working harmoniously. The main development aspects included:

* **Red-Black Tree Implementation**: Built from scratch with proper color balancing algorithms
* **Cache Coherency**: Ensuring all three data structures remain synchronized
* **Memory Management**: Careful pointer management and cleanup procedures
* **Performance Optimization**: Balancing speed vs. memory usage across operations
* **JSON Integration**: Creating flexible testing and configuration systems
* **Modular Design**: Separating concerns across multiple header/implementation files

## 📚 Learnings:

### Data Structure Mastery:
* **Red-Black Tree Algorithms**: Understanding rotation, insertion, and deletion balancing
* **Hash Table Optimization**: Implementing efficient collision resolution strategies
* **Cache Algorithms**: LRU policy implementation and access pattern optimization

### C++ Advanced Concepts:
* **Memory Management**: Dynamic allocation, deallocation, and leak prevention
* **Object-Oriented Design**: Class hierarchies and encapsulation principles
* **Template Programming**: Generic data structure implementations
* **File I/O Operations**: JSON parsing and file output management

### System Design:
* **Multi-Structure Coordination**: Keeping complex systems synchronized
* **Performance Analysis**: Understanding time/space complexity trade-offs
* **Testing Methodologies**: JSON-driven automated testing frameworks
* **Build Systems**: CMake configuration and cross-platform compilation

## ⭐ Improvement:
Future enhancements could include:

### Performance Optimizations:
* **Thread Safety**: Multi-threaded access with read-write locks
* **Memory Pool**: Custom allocators for reduced fragmentation
* **SIMD Operations**: Vectorized hash calculations
* **Cache-Friendly Memory Layout**: Improved CPU cache utilization

### Enhanced Functionality:
* **Generic Templates**: Support for any key/value types
* **Multiple Eviction Policies**: LFU, FIFO, Random eviction options
* **Persistent Storage**: Database integration for cache persistence
* **Network Interface**: REST API for remote cache operations

### Advanced Features:
* **Cache Statistics**: Hit rates, performance metrics, usage analytics
* **Dynamic Resizing**: Automatic hash table expansion/contraction
* **Compression**: Data compression for memory efficiency
* **Monitoring Dashboard**: Real-time cache performance visualization

### Additional Data Structures:
* **B+ Trees**: For disk-based caching scenarios
* **Skip Lists**: Alternative to Red-Black trees
* **Consistent Hashing**: For distributed cache systems

## 🚀 Running the Project:

### Prerequisites:
```bash
# Required tools
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher
- nlohmann/json library
```

### Build Instructions:
```bash
# Clone the repository
git clone <repository-url>
cd cache-manager

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the executable
./milestone6
```

### Configuration:
Edit `milestone6_config.json` to customize cache parameters:
```json
{
    "Milestone6": [{
        "files": [{
            "inputFile": "milestone6.json",
            "outputFile": "generatedOutputFile.txt",
            "errorLogFile": "logFile.txt"
        }],
        "defaultVariables": [{
            "FIFOListSize": 5,
            "hashTableSize": 101
        }]
    }]
}
```

### Test Cases:
Modify `milestone6.json` to add custom test scenarios:
```json
{
    "cacheManager": [{
        "testCase1": [
            {"add": {"key": 42, "fullName": "John Doe", "address": "123 Main St", "city": "Oakland", "state": "CA", "zip": "94612"}},
            {"contains": {"key": 42}},
            {"sort": {"ascending": "true"}},
            {"printRange": {"low": 1, "high": 100}}
        ]
    }]
}
```

## 🖼️ Sample Output:
```bash
Processing testCase1:

add key to cacheManager: 42
contains(42): 1
sort ascending cacheManager
Performing In-order traversal
Node key: 42, Color: BLACK
FIFO info from cacheManager: key: 42

Printing out the cache:
Here are the FIFO List contents:
42
End of FIFO List

Here are the Hash Table contents (1 entries):
Empty bucket: 0
Empty bucket: 1
...
Bucket 42:
FIFO info from cacheManager: key: 42
...
End of table

Performing reverse-order traversal
Node key: 42, Color: BLACK

printRange with low: 1 and high: 100
Printing nodes in range [1, 100]
Node key: 42, Color: BLACK
FIFO info from cacheManager: key: 42
```

## 📊 Architecture Diagram:

```
Hash Table (Milestone 2)                Red-Black Tree (Milestone 6)
┌──────┬─────────────────────────────────┐ ┌─────────────────────────┐
│ [0]  │ □                               │ │         42(B)           │
│ [1]  │ [34]──→[67]──→[23]──→ ∅         │ │       /       \         │
│ [2]  │ □                               │ │    23(R)     67(R)      │
│ [3]  │ [80]──→ ∅                       │ │   /    \    /     \     │
│ [4]  │ □                               │ │ 9(B)  34(B) 53(B) 80(B) │
│ ...  │ □                               │ │              \      \   │
│ [9]  │ [9]──→[86]──→[53]──→[42]──→ ∅   │ │             (R)    86(R)│
│ [10] │ □                               │ └─────────────────────────┘
└──────┴─────────────────────────────────┘               │
              │ │ │ │ │ │ │ │                Points to same data
              ▼ ▼ ▼ ▼ ▼ ▼ ▼ ▼                         │
        ┌───────────────────────────────────────────────────┐
        │      FIFO Doubly Linked List (Milestone 1)        │
        │  ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐  ┌───┐         │
        │  │ 9 │◄─│34 │◄─│86 │◄─│53 │◄─│80 │◄─│42 │         │
        │  └───┘  └───┘  └───┘  └───┘  └───┘  └───┘         │
        │ Newest                           Oldest           │
        │ (Head)                           (Tail)           │
        └───────────────────────────────────────────────────┘

Milestone Evolution:
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Milestone 1   │    │   Milestone 2   │    │   Milestone 3   │
│ Doubly Linked   │ +  │   Hash Table    │ =  │  M1 + M2 Cache  │
│     List        │    │  (Separate      │    │   Management    │
│   (FIFO/LRU)    │    │   Chaining)     │    │                 │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Milestone 4   │    │   Milestone 5   │    │   Milestone 6   │
│  M3 + Binary    │    │ Integrated All  │    │ Self-Balancing  │
│  Search Tree    │    │   Structures    │    │  Red-Black Tree │
│                 │    │ Cache Manager   │    │   (Current)     │
└─────────────────┘    └─────────────────┘    └─────────────────┘

Data Flow & Operations:
• Hash Table: O(1) average lookup, insertion, deletion
• FIFO List: O(1) head/tail operations, LRU maintenance  
• Red-Black Tree: O(log n) balanced operations, range queries
• All structures synchronized and point to same DllNode data
```

## 🏆 Key Achievements:
* ✅ **Complete Red-Black Tree**: Full implementation with all balancing operations
* ✅ **LRU Cache Behavior**: Proper least-recently-used eviction policy
* ✅ **Multi-Structure Sync**: Perfect synchronization across three data structures
* ✅ **Comprehensive Testing**: JSON-driven automated test framework
* ✅ **Memory Safe**: No memory leaks with proper cleanup procedures
* ✅ **Performance Optimized**: Efficient algorithms for all operations
* ✅ **Extensible Design**: Modular architecture for easy enhancements
