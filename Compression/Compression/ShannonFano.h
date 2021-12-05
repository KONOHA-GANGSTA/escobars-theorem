#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

void showAlphabet(map <char, vector<bool>> alphabet);

void printLine();

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
        cout << "Compression time: " << this->encodeDuration << " mks" << endl;
        printLine();
        cout << "Decompression time: " << this->decodeDuration << " mks" << endl;
        printLine();
        cout << "Compression coefficient: ";
        this->coef = (double)(this->text.size() * 8) / this->code.size();
        cout << setiosflags(ios::fixed) << setprecision(2) << this->coef << endl;
        printLine();

    }

};

struct node {
    multimap <double, char, greater<double>> group;
    node* leftBranch = NULL;
    node* rightBranch = NULL;
};

map <char, unsigned int> getMapOfChars(string& text);

void splitNode(node& root, map <char, vector <bool>>& alphabet);

void SFdecode(node& tree, string& code);

compression SFencode(map <char, unsigned int> mapOfChars, string& text);
