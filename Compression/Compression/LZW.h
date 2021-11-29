#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <string>
#include <unordered_map>

using namespace std;

string convert_int_to_bin(int number);

void LZW_compress(string input);

void LZW_decompress(string input);
