#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <bitset>
#include <string>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

string convert_int_to_bin(int number);

void compress(string input, int size, string filename);

void decompress(string input, int size, string filename);

string convert_char_to_string(const char* pCh, int arraySize);

int getInt(int min, int max);

int LZW(string str, char* mode);
