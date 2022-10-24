/* This file is part of the tiny-chat.
   Copyright (c) 2021 Marina G. Zhuravlyova
   Licensed under the zLib license.
   Refer to the LICENSE file included.
*/

#pragma once
#include "parser.h"

	TinyParser::TinyParser() {
		data.clear();
		str = new char[MSG];
	}
	
	TinyParser::TinyParser(vector<pair<string, string>> _data) : data(_data) {
		str = new char[MSG];
	}

	TinyParser::TinyParser(char* str) {
		Parse(str);
	}

	TinyParser& TinyParser::operator=(vector<pair<string, string>> _data) {
		data.clear();
		data.resize(_data.size());
		for (auto r = 0; r < _data.size(); ++r) {
			data[r] = _data[r];
		}
		return *this;
	}
	vector<pair<string, string>> TinyParser::GetData() const {
		return data;
	}

	int TinyParser::Parse(char* str) {
		data.clear();
		if (str == nullptr) return 0;
		int yes = 1;
		string s;
		char* tokens = strtok(str, " {},:");
		while (tokens != nullptr) {
			s = tokens;
			tokens = strtok(nullptr, " {},:");
			data.push_back({ s, tokens });
			yes = yes && tokens;
			tokens = strtok(nullptr, " {},:");
		}
		return yes;
	}

	char* TinyParser::UnParse() {
		if (data.size() == 0) return nullptr;
		string f = "{";
		for (auto r = 0; r < data.size(); ) {
			f += data[r].first + ":" + data[r].second;
			++r;
			if (r == data.size()) {
				f += '}';
				break;
			}
			else f += ',';
		}
		f += '\0';
		memset(str, 0, f.length() + 1);
		strcpy(str, f.c_str());
		return str;
	}

	TinyParser::~TinyParser() {
		delete [] str;
	}