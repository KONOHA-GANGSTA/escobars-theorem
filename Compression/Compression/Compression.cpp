#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
#include "Huffman.h"
#include "LZW.h"
using namespace std;

void printLine() {
    for (int i = 0; i < 25; ++i)
        cout << "_";
    cout << endl;
}

void getString(string& text,string fileName) {

    ifstream file;
    file.open(fileName, ios::in);
    while (!file.eof()) {
        getline(file, text, '\0');
    }
    file.close();

}



void showAlphabet(map <char,vector<bool>> alphabet) {
    for (auto& i : alphabet) {
        cout << i.first << " : ";
        for (bool j : i.second)
            cout << j;
        cout << endl;
    }
}

struct node {
    multimap <double, char, greater<double>> group;
    node* leftBranch = NULL;
    node* rightBranch = NULL;
};

struct compression {
    string name;
    string text;
    string code;
    double coef;
    double encodeDuration;
    double decodeDuration;

    void report() {
        cout << endl;
        printLine();
        cout << this->name << endl;
        printLine();
        cout << "Encoded Text:" << endl;
        cout << this->code << endl;
        printLine();
        cout << "Compression time: " << this->encodeDuration << " ms" << endl;
        printLine();
        cout << "Decompression time: " << this->decodeDuration << " ms" << endl;
        printLine();
        cout << "Compression coefficient: ";
        this->coef = (double)(this->text.size() * 8) / this->code.size();
        cout << setiosflags(ios::fixed) << setprecision(2) << this->coef << endl;
        printLine();

    }

};

map <char, unsigned int> getMapOfChars(string& text) {
    map <char, unsigned int> symbols;
    for (char& sym : text)
        symbols[sym]++;
    return symbols;
}

void splitNode(node& root, map <char,vector <bool>>& alphabet) {
    node* left = new node;
    node* right = new node;
    double total = 0;
    for (auto& i : root.group)
        total += i.first;
    total = total / 2;
    double countProb = 0;
    for (auto& i : root.group) {
        if (countProb == 0) {
            left->group.insert(i);
            countProb += i.first;
            continue;
        }
        countProb += i.first;
        if (countProb > total) {
            right->group.insert(i);
        }
        else
        {
            left->group.insert(i);
        }
    }
    root.leftBranch = left;
    root.rightBranch = right;
    for (auto& i : root.leftBranch->group)
        alphabet[i.second].push_back(false);
    for (auto& i : root.rightBranch->group)
        alphabet[i.second].push_back(true);
    if (root.leftBranch->group.size()>1)
    splitNode(*root.leftBranch,alphabet);
    if (root.rightBranch->group.size() > 1)
    splitNode(*root.rightBranch,alphabet);
}

void SFdecode(node& tree, string& code) {
    node uzel = tree;
    for (char& i : code)        
        if ((i == char(48)) & (uzel.leftBranch != NULL)) {
            uzel = *uzel.leftBranch;
            if ((uzel.leftBranch == NULL) & (uzel.rightBranch == NULL)) {
                for (auto& j : uzel.group)
                    cout << j.second;
                uzel = tree;
            }
        }
        else if ((i == char(49)) & (uzel.rightBranch != NULL)) {
            uzel = *uzel.rightBranch;
            if ((uzel.leftBranch == NULL) & (uzel.rightBranch == NULL)) {
                for (auto& j : uzel.group)
                    cout << j.second;
                uzel = tree;
            }
        }
}

compression SFencode(map <char, unsigned int> mapOfChars, string& text) {
    compression MyCompression;
    MyCompression.name = "Shannon-Fano";
    MyCompression.text = text;
    auto start = chrono::system_clock::now();
    multimap <double,char, greater<double>> mapOfProbability;
    map <char, vector <bool>> alphabet;
   
    for (auto& i : mapOfChars)
        mapOfProbability.emplace(((double)i.second / text.length()), i.first);
    
    node root;
    root.group = mapOfProbability;

    splitNode(root,alphabet);

    for (char i : text) {
        for (bool j : alphabet[i]) {
            MyCompression.code.append(to_string(j));
        }
    }
    auto finish = chrono::system_clock::now();
    auto    duration = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    MyCompression.encodeDuration = duration;
    //showAlphabet(alphabet);
    start = chrono::system_clock::now();
    SFdecode(root, MyCompression.code);
    finish = chrono::system_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    MyCompression.decodeDuration = duration;
    return MyCompression;
}



int main()
{
    //setlocale(LC_CTYPE, "rus");
    string longText;
    getString(longText,"short text.txt");
    //SFencode(getMapOfChars(longText), longText).report();
    //buildHuffmanTree(longText);
    cout<< LZW_decompress(LZW_compress(longText));

}