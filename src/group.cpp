#include "cblox.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace cblox {

	//Group Class

	json Group::GetGroupInfo(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "http://api.roblox.com/groups/" + uid;
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json Group::GetGroupAllies(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "http://api.roblox.com/groups/" + uid;
		url = url + "/allies";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json Group::GetGroupGames(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "https://games.roblox.com/v2/groups/" + uid;
		url = url + "/games?limit=100";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json Group::GetWallPosts(int groupId) {
		std::string uid = std::to_string(groupId);
		string url = "https://groups.roblox.com/v2/groups/" + uid;
		url = url + "/wall/posts?limit=100";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}
};
