#include <iostream>
#include <vector>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

using namespace std;

// Function to compute SHA-256 hash of a string
string computeHash(const string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)data.c_str(), data.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

class MerkleTree {
public:
    MerkleTree(const vector<string>& dataBlocks) {
        this->dataBlocks = dataBlocks;
        for (const auto& block : dataBlocks) {
            leafNodes.push_back(computeHash(block));
        }
        buildTree();
    }

    string getRoot() const {
        return tree.empty() ? "" : tree.back()[0];
    }

    vector<string> getMerklePath(int index) const {
        vector<string> path;
        for (size_t level = 0; level < tree.size() - 1; ++level) {
            int siblingIndex = (index % 2 == 0) ? index + 1 : index - 1;
            if (siblingIndex < tree[level].size()) {
                path.push_back(tree[level][siblingIndex]);
            }
            index /= 2;
        }
        return path;
    }

    bool verifyBlock(const string& block, int index, const string& merkleRoot, const vector<string>& proof) const {
        string currentHash = computeHash(block);
        for (const auto& siblingHash : proof) {
            if (index % 2 == 0) {
                currentHash = computeHash(currentHash + siblingHash);
            } else {
                currentHash = computeHash(siblingHash + currentHash);
            }
            index /= 2;
        }
        return currentHash == merkleRoot;
    }

private:
    vector<string> dataBlocks;
    vector<string> leafNodes;
    vector<vector<string>> tree;

    void buildTree() {
        vector<string> currentLevel = leafNodes;
        while (currentLevel.size() > 1) {
            vector<string> nextLevel;
            for (size_t i = 0; i < currentLevel.size(); i += 2) {
                string left = currentLevel[i];
                string right = (i + 1 < currentLevel.size()) ? currentLevel[i + 1] : left;
                nextLevel.push_back(computeHash(left + right));
            }
            tree.push_back(currentLevel);
            currentLevel = nextLevel;
        }
        if (!currentLevel.empty()) {
            tree.push_back(currentLevel);
        }
    }
};

int main() {
    // Example data blocks
    vector<string> data = {"block1", "block2", "block3", "block4"};
    MerkleTree merkleTree(data);

    // Get the Merkle Root
    string root = merkleTree.getRoot();
    cout << "Merkle Root: " << root << endl;

    // Verify a specific block
    int indexToVerify = 2; // Block index
    string blockToVerify = data[indexToVerify];
    vector<string> merklePath = merkleTree.getMerklePath(indexToVerify);

    cout << "\nMerkle Path for block" << (indexToVerify + 1) << ": ";
    for (const auto& hash : merklePath) {
        cout << hash << " ";
    }
    cout << endl;

    bool isValid = merkleTree.verifyBlock(blockToVerify, indexToVerify, root, merklePath);
    cout << "Verification result for '" << blockToVerify << "': " << (isValid ? "True" : "False") << endl;

    return 0;
}

