#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Stats {
public:
	void AddMethod(string_view method) {
		string tmp_s(method);
		auto el = known_words.find(tmp_s);
		if(known_words[tmp_s] == 1){
			methods_[(*el).first]++;
		}
		else {
			auto el_ = known_words.find("UNKNOWN");
			methods_[(*el_).first]++;
		}
	}
	void AddUri(string_view uri) {
		
		string tmp_s(uri);
		auto el = known_words.find(tmp_s);
		if (known_words[tmp_s] == 1) {
			uris_[(*el).first]++;
		}
		else {
			auto el_ = known_words.find("unknown");
			uris_[(*el_).first]++;
		}
	}
	const map<string_view, int>& GetMethodStats() const {
		return methods_;
	}
	const map<string_view, int>& GetUriStats() const {
		return uris_;
	}
	Stats() {
		int co = 0;
		for (auto& i : tmp) {
			known_words[i]++;
			if (co < 5) {
				methods_[i];
			}
			else {
				uris_[i];
			}
			co++;
		}
	}
private:
	map<string_view, int> methods_;
	map<string_view, int> uris_;
	map<string_view, int> known_words;
	vector<string> tmp = { "GET", "POST", "PUT", "DELETE", "UNKNOWN", "/", "/order", "/product", "/basket", "/help", "unknown" };
};

HttpRequest ParseRequest(string_view line) {
	int pos = line.find_first_not_of(' ', 0);
	HttpRequest hr;
	int k = 0;
	while (true) {
		int pos1 = line.find(' ', pos);
		if (k == 0) {
			hr.method = line.substr(pos, pos1 -pos);
		}
		if (k == 1) {
			hr.uri = line.substr(pos, pos1 - pos);
		}
		if (k == 2) {
			hr.protocol = line.substr(pos, pos1 - pos);
			break;
		}
		k++;
		pos = pos1 + 1;
	}
	return hr;
}
