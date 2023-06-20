#include <iostream>
#include <unordered_map>
#include <queue>
#include <chrono>

using namespace std;

class HuffmanNode {
public:
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }
};

class Compare {
public:
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

unordered_map<char, string> codeTable;

void buildCodeTable(HuffmanNode* root, string code) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        codeTable[root->data] = code;
    }

    buildCodeTable(root->left, code + "0");
    buildCodeTable(root->right, code + "1");
}

void compress(string data) {
    unordered_map<char, int> frequencyTable;
    for (char c : data) {
        frequencyTable[c]++;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto entry : frequencyTable) {
        pq.push(new HuffmanNode(entry.first, entry.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    HuffmanNode* root = pq.top();
    buildCodeTable(root, "");

    int initialBits = data.length() * 8;
    int compressedBits = 0;

    string compressedData = "";
    for (char c : data) {
        compressedData += codeTable[c];
        compressedBits += codeTable[c].length();
    }

    int bitsSaved = initialBits - compressedBits;
    float compressionRatio = (float)bitsSaved / initialBits * 100;

    cout << "Original bits: " << initialBits << endl;
    cout << "Compressed bits: " << compressedBits << endl;
    cout << "Bits saved: " << bitsSaved << endl;
    cout << "Compression ratio: " << compressionRatio << "%" << endl;

    // Compressed data
    cout << "Compressed data: " << compressedData << endl;

    // Decompression
    auto startDecompress = chrono::high_resolution_clock::now();
    string decompressedData = "";
    HuffmanNode* currentNode = root;
    for (char bit : compressedData) {
        if (bit == '0') {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }

        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            decompressedData += currentNode->data;
            currentNode = root;
        }
    }
    auto endDecompress = chrono::high_resolution_clock::now();
    cout << "Decompressed data: " << decompressedData << endl;

    // Calculate decompression time
    cout << "Decompression time: " << chrono::duration_cast<chrono::microseconds>(endDecompress - startDecompress).count() << " microseconds" << endl;
}

int main() {
    // Test 1: Long and repeating sequence
    string test1 = "ABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABC";
    cout << "Test 1:" << endl;
    auto start1 = chrono::high_resolution_clock::now();
    compress(test1);
    auto end1 = chrono::high_resolution_clock::now();
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end1 - start1).count() << " microseconds" << endl;
    cout << endl;

    // Test 2: Short and repeating sequence
    string test2 = "HUYNHKHAHUYNHKHAHUYNHKHAHUYNHKHA";
    cout << "Test 2:" << endl;
    auto start2 = chrono::high_resolution_clock::now();
    compress(test2);
    auto end2 = chrono::high_resolution_clock::now();
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << " microseconds" << endl;
    cout << endl;

    // Test 3: Short and non-repeating sequence
    string test3 = "IAMHUYNHKHA,AFRESHERWEBDEVELOPER";
    cout << "Test 3:" << endl;
    auto start3 = chrono::high_resolution_clock::now();
    compress(test3);
    auto end3 = chrono::high_resolution_clock::now();
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end3 - start3).count() << " microseconds" << endl;
    cout << endl;

    // Test 4: Long and non-repeating sequence
    string test4 = "LOREMIPSUMDOLORSITAMET,CONSECTETURADIPISCINGELIT.NULLAMATFRINGILLAJUSTO,INTRISTIQUEMAURIS.FUSCESEMPEURISMODORCIVELLACINIA.VIVAMUSNONCONVALLISLECTUS,NONSEMPERAUGUE.PROINCONVALLIS,LECTUSASEMPERPOSUERE,ODIOMIELEIFENDMAURIS,NECALIQUETLIBEROSAPINONLIGULA.UTAUCTOR,ODIOIDHENDRERITGRAVIDA,ELITPURUSULLAMCORPERRISUS,IDELEIFENDMIESTSEDURNA.MORBINECSEMETTORTORMAXIMUSPULVINAR.INRHONCUSNIBHATERATVARIUS,ATSEMPERSAPIENMALESUADA.NULLAFACILISI.FUSCEALIQUETINTERDUMURNA,SEDAUCTORENIMALIQUETID.CURABITURFAUCIBCONGUETELLUS,ATRISTIQUEVELITRUTRUMA.NUNCVULPUTATEANTEAMAURISFACILISIS,APULVINARERATRHONCUS.SUSPENDISSESUSCIPITEULOREMIDRUTRUM.DONECAMETUSFEGIAT,ELEIFENDNEQUEAC,VULPUTATEELIT.SEDALIQUAMFERMENTUMLACUS,SEDHENDRERITJUSTODAPIBUSA.NULLAINAUGUEMAURIS.VESTIBULUMANTEIPSUMPRIMISINFAUCIBUSORCI.";
    cout << "Test 4:" << endl;
    auto start4 = chrono::high_resolution_clock::now();
    compress(test4);
    auto end4 = chrono::high_resolution_clock::now();
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end4 - start4).count() << " microseconds" << endl;

    return 0;
}
