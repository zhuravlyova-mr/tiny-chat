/* This file is part of the tiny-chat.
   Copyright (c) 2021 Marina G. Zhuravlyova
   Licensed under the zLib license.
   Refer to the LICENSE file included.
*/

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <string.h> 

using namespace std;

#define MSG 1000

class TinyParser {

public:
	TinyParser();
	TinyParser(vector<pair<string, string>>);
	TinyParser(char*);
	TinyParser& operator=(vector<pair<string, string>>);
	vector<pair<string, string>> GetData() const;
	int Parse(char*);
	char* UnParse();
	~TinyParser();
private:
	vector<pair<string, string>> data;
	char* str;
};