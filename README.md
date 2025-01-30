# Merkle Tree Implementation in C++

A C++ implementation of a **Merkle Tree**, a cryptographic data structure used for efficient and secure data integrity verification. This project includes tree construction, Merkle path retrieval, and block validation, ensuring reliable integrity checks for large datasets in blockchain, distributed systems, and secure storage solutions.

## Features
- **Tree Construction**: Builds the Merkle Tree level by level.
- **Merkle Root**: Computes the final hash at the top level.
- **Merkle Path**: Retrieves the sibling hashes required for verification.
- **Verification**: Validates data integrity using the Merkle Root.

## How It Works

### **Tree Building**
- The `buildTree` function constructs the tree level by level.
- For each level, hashes of adjacent nodes are concatenated and hashed again to create the parent nodes.

### **Root**
- The **Merkle Root** is the final hash computed at the top level of the tree.

### **Merkle Path**
- The `getMerklePath` function computes the **sibling hashes** required for verification.

### **Verification**
- The `verifyBlock` function recomputes the hash from the block and its Merkle Path.
- It compares the computed hash with the stored Merkle Root for validation.

## Installation and Usage

### **Compile the Code**
```bash
$ g++ -o merkle_tree merkle_tree.cpp -lcrypto
```

### **Run the Program**
```bash
$ ./merkle_tree
```

## Example Output
```bash
Merkle Root: d2d2fd8c7a7b1f3579cb1b9283d52a60d5392dbcc9e5277753d9308a6f0dc0b1

Merkle Path for block3: 6d0dc8bdf25b09b9ad0324ef7e70e6a6b40b46f30cb3e473a4a349a4dd04aaec d2c65bb0c7e8547e203ecf79d4e256b4eb708ee09b9ae587285fb7cf2e556497

Verification result for 'block3': True
```

## Advantages
- **Efficient proof size** for verification.
- **Strong integrity and tamper-proof** mechanisms.
- **Can handle dynamic data** (with slight modifications for incremental updates).

## Complexity Analysis
- **Building the tree**: \(O(n)\)
- **Proof verification**: \(O(\log n)\)

This C++ implementation is robust and well-suited for applications like **blockchains** and **data integrity checks**.

## Troubleshooting: OpenSSL Issues

If you encounter the following error:
```bash
fatal error: openssl/sha.h: No such file or directory
```
It means the OpenSSL development files are missing from your system.

### **Fix for Linux (Debian/Ubuntu)**
```bash
sudo apt update
sudo apt install libssl-dev
```
This will install the required OpenSSL libraries needed for SHA-256 hashing.

