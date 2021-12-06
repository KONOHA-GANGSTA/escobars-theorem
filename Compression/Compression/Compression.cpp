#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
#include "Huffman.h"
#include "LZW.h"
#include "RLE.h"
#include "ShannonFano.h"
using namespace std;

void getString(string& text,string fileName) {

    ifstream file;
    file.open(fileName, ios::in);
    while (!file.eof()) {
        getline(file, text, '\0');
    }
    file.close();

}

void printLine() {
    for (int i = 0; i < 25; ++i)
        cout << "_";
    cout << endl;
}

void RUN(void(*treeFunction)(string&),string& text,string name) {
    printLine();
    cout << name << endl;
    printLine();
    treeFunction(text);
    printLine();
    cout << endl;
}

void RUN(string(*encodeFunction)(string&), string(*decodeFunction)(string&), string& text, int weightOfSymbol,string name) {
    printLine();
    cout << name << endl;
    printLine();
    compression MyCompression;
    auto start = chrono::system_clock::now();
    MyCompression.code = encodeFunction(text);
    auto finish = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
    MyCompression.encodeDuration = duration;
    start = chrono::system_clock::now();
    MyCompression.decodedText = decodeFunction(MyCompression.code);
    finish = chrono::system_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
    MyCompression.decodeDuration = duration;
    MyCompression.textSize = text.size();
    MyCompression.report(weightOfSymbol);
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    string shortText,longText,image,frekuent;
    getString(longText,"long text.txt");
    getString(shortText,"short text.txt");
    getString(image, "image.txt");
    getString(frekuent, "frekuent.txt");

    cout << "TEXT :" << endl << shortText << endl << endl;
    RUN(SFencode, shortText, "ShannonFano");
    RUN(buildHuffmanTree, shortText, "Huffman");
    RUN(LZW_compress, LZW_decompress, shortText, 8, "LZW");
    RUN(RLEcompress, RLEdecompress, shortText, 1, "RLE");

    cout << "TEXT :" << endl << longText << endl << endl;
    RUN(SFencode, longText, "ShannonFano");
    RUN(buildHuffmanTree, longText, "Huffman");
    RUN(LZW_compress, LZW_decompress, longText, 8, "LZW");
    RUN(RLEcompress, RLEdecompress, longText, 1, "RLE");

    cout << "TEXT :" << endl << image << endl << endl;
    RUN(SFencode, image, "ShannonFano");
    RUN(buildHuffmanTree, image, "Huffman");
    RUN(LZW_compress, LZW_decompress, image, 8, "LZW");
    RUN(RLEcompress, RLEdecompress, image, 1, "RLE");

    cout << "TEXT :" << endl << frekuent << endl << endl;
    RUN(SFencode, frekuent, "ShannonFano");
    RUN(buildHuffmanTree, frekuent, "Huffman");
    RUN(LZW_compress, LZW_decompress, frekuent, 8, "LZW");
    RUN(RLEcompress, RLEdecompress, frekuent, 1, "RLE");
}