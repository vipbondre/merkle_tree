A C++ implementation of a Merkle Tree, a cryptographic data structure used for efficient and secure data integrity verification. This project includes tree construction, Merkle path retrieval, and block validation, ensuring reliable integrity checks for large datasets in blockchain, distributed systems, and secure storage solutions.


Tree Building:

The buildTree function builds the tree level by level.
For each level, hashes of adjacent nodes are concatenated and hashed again to create the parent nodes.
Root:

The root is the final hash at the top level of the tree.
Merkle Path:

The getMerklePath function computes the sibling hashes required for verification.
Verification:

The verifyBlock function recalculates the hash starting from the block and its Merkle Path, comparing it with the Merkle Root.

Compile:
bash$ g++ -o merkle_tree merkle_tree.cpp -lcrypto

Run:
bash$ ./merkle_tree

Example Output
Merkle Root: d2d2fd8c7a7b1f3579cb1b9283d52a60d5392dbcc9e5277753d9308a6f0dc0b1

Merkle Path for block3: 6d0dc8bdf25b09b9ad0324ef7e70e6a6b40b46f30cb3e473a4a349a4dd04aaec d2c65bb0c7e8547e203ecf79d4e256b4eb708ee09b9ae587285fb7cf2e556497 

Verification result for 'block3': True

Advantages:

Efficient proof size for verification.
Strong integrity and tamper-proof mechanisms.
Can handle dynamic data (with slight modifications for incremental updates).

Complexity:

Building the tree: 𝑂(𝑛)
Proof verification: 𝑂(log 𝑛)

This C++ implementation is robust and well-suited for applications like blockchains or data integrity checks.


------------------------------------------------------------------------------------------------------------------

The error indicates that the OpenSSL library's development files (headers and libraries) are missing from your system. OpenSSL is used to provide the sha.h header for SHA-256 hashing.

Steps to Fix the Issue
Install OpenSSL Development Package

For most Linux distributions, install the OpenSSL development libraries using the following commands:

Debian/Ubuntu:

sudo apt update
sudo apt install libssl-dev


