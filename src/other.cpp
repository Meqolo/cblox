#include "cblox.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace cblox {
	json Other::GetGamePassInfo(int assetId) {
		std::string uid = std::to_string(assetId);
		string url = "http://api.roblox.com/marketplace/game-pass-product-info?gamePassId=" + uid;
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json Other::SearchGroups(string keyword) {
		string url = "https://www.roblox.com/search/groups/list-json?keyword=" + keyword;
		url = url + "&maxRows=2147483647";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}
	
	json Other::SearchUsers(string keyword) {
		string url = "https://www.roblox.com/search/users/results?keyword=" + keyword;
		url = url + "&maxRows=2147483646";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}
};
