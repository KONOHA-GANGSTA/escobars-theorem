#include <iostream>
#include <sstream>
#include <fstream>
#include <bitset>
#include <string>
#include <unordered_map>
#include "LZW.h"

#define MAX_DEF 4096

using namespace std;

string convert_int_to_bin(int number)
{
    string result = bitset<12>(number).to_string();
    return result;
}

string LZW_compress(string& input) {
    unordered_map<string, int> compress_dictionary(MAX_DEF);
    //Dictionary initializing with ASCII
    for (int unsigned i = 0; i < 256; i++) {
        compress_dictionary[string(1, i)] = i;
    }
    string current_string;
    string result;
    unsigned int code;
    unsigned int next_code = 256;

    for (char& c : input) {
        current_string = current_string + c;
        if (compress_dictionary.find(current_string) == compress_dictionary.end()) {
            if (next_code <= MAX_DEF)
                compress_dictionary.insert(make_pair(current_string, next_code++));
            current_string.erase(current_string.size() - 1);
            result = result + convert_int_to_bin(compress_dictionary[current_string]);
            current_string = c;
        }
    }
    if (current_string.size())
        result = result+ convert_int_to_bin(compress_dictionary[current_string]);

    return result;
}



string LZW_decompress(string& input) {
    unordered_map<unsigned int, string> dictionary(MAX_DEF);
    //Dictionary initializing with ASCII
    for (int unsigned i = 0; i < 256; i++) {
        dictionary[i] = string(1, i);
    }
    int size;
    string previous_string;
    string result;
    unsigned int code;
    unsigned int next_code = 256;
    size = input.size();

    int i = 0;
    while (i < size) {
        //Extracting 12 bits and converting binary to decimal
        string subinput = input.substr(i, 12);
        bitset<12> binary(subinput);
        code = binary.to_ullong();
        i += 12;

        if (dictionary.find(code) == dictionary.end())
            dictionary.insert(make_pair(code, (previous_string + previous_string.substr(0, 1))));
        result = result + dictionary[code];
        if (previous_string.size())
            dictionary.insert(make_pair(next_code++, previous_string + dictionary[code][0]));
        previous_string = dictionary[code];
    }
    return result;
}