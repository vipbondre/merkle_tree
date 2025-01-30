#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

// Function to compute hash using std::hash
size_t computeHash(const string& data) {
    return hash<string>{}(data);
}

// Convert size_t hash to a string representation
string hashToString(size_t hash) {
    return to_string(hash);
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
        return tree.empty() ? "" : hashToString(tree.back()[0]);
    }

    vector<string> getMerklePath(int index) const {
        vector<string> path;
        for (size_t level = 0; level < tree.size() - 1; ++level) {
            int siblingIndex = (index % 2 == 0) ? index + 1 : index - 1;
            if (siblingIndex < tree[level].size()) {
                path.push_back(hashToString(tree[level][siblingIndex]));
            }
            index /= 2;
        }
        return path;
    }

    bool verifyBlock(const string& block, int index, const string& merkleRoot, const vector<string>& proof) const {
        size_t currentHash = computeHash(block);
        for (const auto& siblingHashStr : proof) {
            size_t siblingHash = stoull(siblingHashStr);
            if (index % 2 == 0) {
                currentHash = computeHash(hashToString(currentHash) + hashToString(siblingHash));
            } else {
                currentHash = computeHash(hashToString(siblingHash) + hashToString(currentHash));
            }
            index /= 2;
        }
        return hashToString(currentHash) == merkleRoot;
    }

private:
    vector<string> dataBlocks;
    vector<size_t> leafNodes;
    vector<vector<size_t>> tree;

    void buildTree() {
        vector<size_t> currentLevel = leafNodes;
        while (currentLevel.size() > 1) {
            vector<size_t> nextLevel;
            for (size_t i = 0; i < currentLevel.size(); i += 2) {
                size_t left = currentLevel[i];
                size_t right = (i + 1 < currentLevel.size()) ? currentLevel[i + 1] : left;
                nextLevel.push_back(computeHash(hashToString(left) + hashToString(right)));
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

