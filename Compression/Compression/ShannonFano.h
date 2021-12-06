#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

void showAlphabet(map <char, vector<bool>> alphabet);

struct node {
    multimap <double, char, greater<double>> group;
    node* leftBranch = NULL;
    node* rightBranch = NULL;
};

struct compression {
    string name;
    int textSize;
    string code;
    string decodedText;
    double coef;
    double encodeDuration;
    double decodeDuration;

    void report(int k) {
        cout << "Encoded string is :" << endl << this->code << endl << endl;

        cout << "Encoding time is :" << endl << this->encodeDuration << " mks" << endl << endl;

        cout << "Decoded string is : " << endl << this->decodedText << endl << endl;

        cout << "Decoding time is :" << endl << this->decodeDuration << " mks" << endl << endl;

        cout << "Compression coefficient is : " << endl;
        this->coef = (double)(this->textSize * k) / this->code.size();
        cout << setiosflags(ios::fixed) << setprecision(2) << this->coef << endl << endl;
    }
};

map <char, unsigned int> getMapOfChars(string& text);

void splitNode(node& root, map <char, vector <bool>>& alphabet);

string SFdecode(node& tree, string& code);

void SFencode(string& text);