#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <chrono>
#include "Huffman.h"
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

void encode(Node* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str, string &decoded)
{
	if (root == nullptr) {
		return;
	}

	if (!root->left && !root->right)
	{
		decoded += root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str, decoded);
	else
		decode(root->right, index, str, decoded);


}

void buildHuffmanTree(string& text)
{
	auto original_size = text.length()*8;
	auto start = system_clock::now();
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	priority_queue<Node*, vector<Node*>, comp> pq;

	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	Node* root = pq.top();

	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}
    auto finish = system_clock::now();
	cout << "\nEncoded string is :\n" << str << '\n';
	
	auto duration = duration_cast<microseconds>(finish - start).count();
	cout << "\nEncoding time is :\n" << duration << " mks" << endl;
	int encoded_size = str.length();

	string decoded;
	int index = -1;
	cout << "\nDecoded string is: \n";
	start = system_clock::now();
	while (index < (int)str.size() - 2) {
		decode(root, index, str, decoded);
	}
	finish = system_clock::now();
	duration = duration_cast<microseconds>(finish - start).count();
	cout << decoded;
	cout << "\n\nDecoding time is :\n" << duration << " mks" << endl;
	float coef = static_cast<float>(original_size) / encoded_size;
	cout << "\nCompression coefficient is :\n" << setiosflags(ios::fixed) << setprecision(2) << coef << endl;
}