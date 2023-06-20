#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

vector<int> compressLZW(const string& data) {
    unordered_map<string, int> dictionary;
    int dictionarySize = 256;

    for (int i = 0; i < 256; i++) {
        dictionary[string(1, static_cast<char>(i))] = i;
    }

    string currentSequence;
    vector<int> compressedData;

    for (char c : data) {
        string sequence = currentSequence + c;

        if (dictionary.find(sequence) != dictionary.end()) {
            currentSequence = sequence;
        }
        else {
            compressedData.push_back(dictionary[currentSequence]);
            dictionary[sequence] = dictionarySize++;
            currentSequence = string(1, c);
        }
    }

    compressedData.push_back(dictionary[currentSequence]);

    return compressedData;
}

void printCompressionInfo(const string& data, const vector<int>& compressedData) {
    int initialBits = data.length() * 8;
    int compressedBits = compressedData.size() * sizeof(int) * 8;
    int bitsSaved = initialBits - compressedBits;
    float compressionRatio = (float)bitsSaved / initialBits * 100;

    cout << "Original bits: " << initialBits << endl;
    cout << "Compressed bits: " << compressedBits << endl;
    cout << "Bits saved: " << bitsSaved << endl;
    cout << "Compression ratio: " << compressionRatio << "%" << endl;

    cout << "Compressed data: ";
    for (int code : compressedData) {
        cout << code << " ";
    }
    cout << endl;
}

string decompressLZW(const vector<int>& compressedData) {
    unordered_map<int, string> dictionary;
    int dictionarySize = 256;

    for (int i = 0; i < 256; i++) {
        dictionary[i] = string(1, static_cast<char>(i));
    }

    int previousCode = compressedData[0];
    string output = dictionary[previousCode];
    string currentSequence = output;

    for (int i = 1; i < compressedData.size(); i++) {
        int currentCode = compressedData[i];

        string entry;
        if (dictionary.find(currentCode) != dictionary.end()) {
            entry = dictionary[currentCode];
        }
        else {
            entry = dictionary[previousCode] + currentSequence;
        }

        output += entry;
        currentSequence = entry[0];

        dictionary[dictionarySize++] = dictionary[previousCode] + currentSequence;
        previousCode = currentCode;
    }

    return output;
}

int main() {
    string test1 = "ABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABCABC";
    cout << "Test 1:" << endl;
    auto start1 = chrono::high_resolution_clock::now();
    vector<int> compressedData1 = compressLZW(test1);
    auto end1 = chrono::high_resolution_clock::now();
    printCompressionInfo(test1, compressedData1);
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end1 - start1).count() << " microseconds" << endl;

    auto startDecompress1 = chrono::high_resolution_clock::now();
    string decompressedData1 = decompressLZW(compressedData1);
    auto endDecompress1 = chrono::high_resolution_clock::now();
    cout << "Decompression time: " << chrono::duration_cast<chrono::microseconds>(endDecompress1 - startDecompress1).count() << " microseconds" << endl;
    cout << "Decompressed data: " << decompressedData1 << endl;
    cout << endl;

    string test2 = "HUYNHKHAHUYNHKHAHUYNHKHAHUYNHKHA";
    cout << "Test 2:" << endl;
    auto start2 = chrono::high_resolution_clock::now();
    vector<int> compressedData2 = compressLZW(test2);
    auto end2 = chrono::high_resolution_clock::now();
    printCompressionInfo(test2, compressedData2);
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << " microseconds" << endl;

    auto startDecompress2 = chrono::high_resolution_clock::now();
    string decompressedData2 = decompressLZW(compressedData2);
    auto endDecompress2 = chrono::high_resolution_clock::now();
    cout << "Decompression time: " << chrono::duration_cast<chrono::microseconds>(endDecompress2 - startDecompress2).count() << " microseconds" << endl;
    cout << "Decompressed data: " << decompressedData2 << endl;
    cout << endl;

    string test3 = "IAMHUYNHKHA,AFRESHERWEBDEVELOPER";
    cout << "Test 3:" << endl;
    auto start3 = chrono::high_resolution_clock::now();
    vector<int> compressedData3 = compressLZW(test3);
    auto end3 = chrono::high_resolution_clock::now();
    printCompressionInfo(test3, compressedData3);
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end3 - start3).count() << " microseconds" << endl;

    auto startDecompress3 = chrono::high_resolution_clock::now();
    string decompressedData3 = decompressLZW(compressedData3);
    auto endDecompress3 = chrono::high_resolution_clock::now();
    cout << "Decompression time: " << chrono::duration_cast<chrono::microseconds>(endDecompress3 - startDecompress3).count() << " microseconds" << endl;
    cout << "Decompressed data: " << decompressedData3 << endl;
    cout << endl;

    string test4 = "LOREMIPSUMDOLORSITAMET,CONSECTETURADIPISCINGELIT.NULLAMATFRINGILLAJUSTO,INTRISTIQUEMAURIS.FUSCESEMPEURISMODORCIVELLACINIA.VIVAMUSNONCONVALLISLECTUS,NONSEMPERAUGUE.PROINCONVALLIS,LECTUSASEMPERPOSUERE,ODIOMIELEIFENDMAURIS,NECALIQUETLIBEROSAPINONLIGULA.UTAUCTOR,ODIOIDHENDRERITGRAVIDA,ELITPURUSULLAMCORPERRISUS,IDELEIFENDMIESTSEDURNA.MORBINECSEMETTORTORMAXIMUSPULVINAR.INRHONCUSNIBHATERATVARIUS,ATSEMPERSAPIENMALESUADA.NULLAFACILISI.FUSCEALIQUETINTERDUMURNA,SEDAUCTORENIMALIQUETID.CURABITURFAUCIBCONGUETELLUS,ATRISTIQUEVELITRUTRUMA.NUNCVULPUTATEANTEAMAURISFACILISIS,APULVINARERATRHONCUS.SUSPENDISSESUSCIPITEULOREMIDRUTRUM.DONECAMETUSFEGIAT,ELEIFENDNEQUEAC,VULPUTATEELIT.SEDALIQUAMFERMENTUMLACUS,SEDHENDRERITJUSTODAPIBUSA.NULLAINAUGUEMAURIS.VESTIBULUMANTEIPSUMPRIMISINFAUCIBUSORCI.";
    cout << "Test 4:" << endl;
    auto start4 = chrono::high_resolution_clock::now();
    vector<int> compressedData4 = compressLZW(test4);
    auto end4 = chrono::high_resolution_clock::now();
    printCompressionInfo(test4, compressedData4);
    cout << "Compression time: " << chrono::duration_cast<chrono::microseconds>(end4 - start4).count() << " microseconds" << endl;

    auto startDecompress4 = chrono::high_resolution_clock::now();
    string decompressedData4 = decompressLZW(compressedData4);
    auto endDecompress4 = chrono::high_resolution_clock::now();
    cout << "Decompression time: " << chrono::duration_cast<chrono::microseconds>(endDecompress4 - startDecompress4).count() << " microseconds" << endl;
    cout << "Decompressed data: " << decompressedData4 << endl;

    return 0;
}
