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





int main()
{
    //setlocale(LC_CTYPE, "rus");
    string longText;
    getString(longText,"short text.txt");
    SFencode(getMapOfChars(longText), longText).report();
    //buildHuffmanTree(longText);
    //cout << longText << endl << LZW_decompress(LZW_compress(longText));
}