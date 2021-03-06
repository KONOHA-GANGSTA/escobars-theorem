#include "ShannonFano.h"
#include <chrono>

void showAlphabet(map <char, vector<bool>> alphabet) {
    for (auto& i : alphabet) {
        cout << i.first << " : ";
        for (bool j : i.second)
            cout << j;
        cout << endl;
    }
}

map <char, unsigned int> getMapOfChars(string& text) {
    map <char, unsigned int> symbols;
    for (char& sym : text)
        symbols[sym]++;
    return symbols;
}

void splitNode(node& root, map <char, vector <bool>>& alphabet) {
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
    if (root.leftBranch->group.size() > 1)
        splitNode(*root.leftBranch, alphabet);
    if (root.rightBranch->group.size() > 1)
        splitNode(*root.rightBranch, alphabet);
}

string SFdecode(node& tree, string& code) {
    node uzel = tree;
    string result;
    for (char& i : code)
        if ((i == char(48)) & (uzel.leftBranch != NULL)) {
            uzel = *uzel.leftBranch;
            if ((uzel.leftBranch == NULL) & (uzel.rightBranch == NULL)) {
                for (auto& j : uzel.group)
                    result.push_back(j.second);
                uzel = tree;
            }
        }
        else if ((i == char(49)) & (uzel.rightBranch != NULL)) {
            uzel = *uzel.rightBranch;
            if ((uzel.leftBranch == NULL) & (uzel.rightBranch == NULL)) {
                for (auto& j : uzel.group)
                    result.push_back(j.second);
                uzel = tree;
            }
        }
    return result;
}

void SFencode(string& text) {
    compression MyCompression;
    map <char, unsigned int> mapOfChars = getMapOfChars(text);
    MyCompression.name = "Shannon-Fano";
    MyCompression.textSize = text.size();
    auto start = chrono::system_clock::now();
    multimap <double, char, greater<double>> mapOfProbability;
    map <char, vector <bool>> alphabet;

    for (auto& i : mapOfChars)
        mapOfProbability.emplace(((double)i.second / text.length()), i.first);

    node root;
    root.group = mapOfProbability;

    splitNode(root, alphabet);

    for (char i : text) {
        for (bool j : alphabet[i]) {
            MyCompression.code.append(to_string(j));
        }
    }
    auto finish = chrono::system_clock::now();
    auto    duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
    MyCompression.encodeDuration = duration;
    //showAlphabet(alphabet);
    start = chrono::system_clock::now();
    MyCompression.decodedText = SFdecode(root, MyCompression.code);
    finish = chrono::system_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
    MyCompression.decodeDuration = duration;
    MyCompression.report(8);
}