#include "RLE.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

bool checkNext(queue <char>& ochered) {      
	if (ochered.size() == 1) return false;   
	queue <char> check = ochered;
	check.pop();
	return ochered.front() == check.front();
}

string RLEcompress(string& text) { 

	queue <char> ochered; 
	string result, currentString;     
	currentString.reserve(127);        
	int count = 0;                     
	bool repMark = true;               

	for (char& i : text)               
		ochered.push(i);

	currentString.push_back(ochered.front());  
	ochered.pop();                            
	count++;                                  

	while (!ochered.empty()) { 
		if (count == 127) {
			if (repMark == false) {
				result.append(to_string(count));
				result.append(currentString);
			}
			else {
				result.append(to_string(-count));
				result.append(currentString);
			}
			repMark == true;
			currentString.clear();
			currentString.push_back(ochered.front());
			count = 1;
			ochered.pop();
			continue;
		}

		if (currentString[currentString.size()-1] == ochered.front()) { /
			if (repMark == false) { 
				count++;
			}
			else { 
				if (checkNext(ochered) == true) { repMark=false; continue; } 
				if (currentString.size() == 1) { repMark = false; continue; } 
				result.append(to_string(-count)); 
				result.append(currentString);
				currentString.clear();
				count = 1;
				currentString.push_back(ochered.front());
				repMark = false;
			}
		}
		else { 
			if (repMark == false) {
				(currentString.size()>1)? result.append(to_string(-count)): result.append(to_string(count)); 
				result.append(currentString);                                                                
				currentString.clear();
				currentString.push_back(ochered.front());
				count = 1;
				repMark = true;
			}
			else {
				if (checkNext(ochered) == true) { repMark = false; continue; }
				count++;
				currentString.push_back(ochered.front());
			}
		}
		ochered.pop(); 
	}


	if (repMark == false) {
		result.append(to_string(count));
		result.append(currentString);
	}
	else {
		result.append(to_string(-count));
		result.append(currentString);
	}
	return result;
}

string RLEdecompress(string code) {
	string number;
	number.reserve(3);
	string currentString;
	currentString.reserve(127);
	string result;
	bool numMark  = false;
	for (char current : code) { 
		if (current == char(45) | (current >= char(48) & current <= char(57))) {
			if (numMark) {
				number.clear();
				numMark = false;
			}
			number.push_back(current);
			continue;
		}
		currentString.push_back(current);
		if (stoi(number) > 0) {
			for (int i = 0; i < stoi(number); ++i) {
				result.append(currentString);
			}
			currentString.clear();
			number.clear();
		}
		else { 
			result.push_back(current);
			currentString.clear();
			numMark = true;
			}
		}
	return result;
}