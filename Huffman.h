#pragma once

using namespace std;
using namespace std::chrono;

struct Node;

Node* getNode(char ch, int freq, Node* left, Node* right);

struct comp;

void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode);

void decode(Node* root, int& index, string str);

void buildHuffmanTree(string text);