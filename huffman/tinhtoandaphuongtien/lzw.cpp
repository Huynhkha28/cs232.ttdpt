#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;



vector<int> compressLZW(string data) {
    unordered_map<string, int> dictionary;
    int nextCode = 256;

    vector<int> result;
    string currentSequence = "";

    for (char c : data) {
        string sequence = currentSequence + c;
        if (dictionary.count(sequence) > 0) {
            currentSequence = sequence;
        }
        else {
            result.push_back(dictionary[currentSequence]);
            dictionary[sequence] = nextCode++;
            currentSequence = string(1, c);
        }
    }

    if (!currentSequence.empty()) {
        result.push_back(dictionary[currentSequence]);
    }

    return result;
}

string decompressLZW(vector<int> compressedData) {
    unordered_map<int, string> dictionary;
    int nextCode = 256;

    string result = "";
    int previousCode = compressedData[0];
    result += static_cast<char>(previousCode);

    for (int i = 1; i < compressedData.size(); i++) {
        int code = compressedData[i];
        string sequence;

        if (dictionary.count(code) > 0) {
            sequence = dictionary[code];
        }
        else {
            sequence = dictionary[previousCode] + dictionary[previousCode][0];
        }

        result += sequence;
        dictionary[nextCode++] = dictionary[previousCode] + sequence[0];
        previousCode = code;
    }

    return result;
}

int main() {
    string data = "Hello, world!";

    auto startTime = chrono::high_resolution_clock::now();
    vector<int> compressedData = compressLZW(data);
    auto endTime = chrono::high_resolution_clock::now();

    string compressedDataString;
    for (int code : compressedData) {
        compressedDataString += to_string(code) + " ";
    }

    int initialBits = data.length() * 8;
    int compressedBits = compressedData.size() * 12;  // Assuming each code is 12 bits

    int bitsSaved = initialBits - compressedBits;
    float compressionRatio = static_cast<float>(bitsSaved) / initialBits * 100;

    cout << "Original bits: " << initialBits << endl;
    cout << "LZW Compressed bits: " << compressedBits << endl;
    cout << "Bits saved: " << bitsSaved << endl;
    cout << "Compression ratio: " << compressionRatio << "%" << endl;
    cout << "Compressed data: " << compressedDataString << endl;

    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "Compression time: " << duration << " microseconds" << endl;

    string decompressedData = decompressLZW(compressedData);
    cout << "Decompressed data: " << decompressedData << endl;

    return 0;
}
