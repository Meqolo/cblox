#include "cblox.h"
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <typeinfo>
using namespace std;

namespace cblox {
	json User::GetGroups(int userId) {
		std::string uid = std::to_string(userId);
		string url = "http://api.roblox.com/users/" + uid;
		url = url + "/groups";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetFriends(int userId) {
		std::string uid = std::to_string(userId);
		string url = "http://api.roblox.com/users/" + uid;
		url = url + "/friends";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUserFromId(int userId) {
		std::string uid = std::to_string(userId);
		string url = "http://api.roblox.com/users/" + uid;
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUserFromName(string name) {
		string url = "http://api.roblox.com/users/get-by-username?username=" + name;
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}

	json User::GetUserAvatar(int userId) {
		std::string uid = std::to_string(userId);
		string url = "https://avatar.roblox.com/v1/users/" + uid;
		url = url + "/avatar";
		std::string strdat = Http::Get(url);
		json data = json::parse(strdat);
		return data;
	}
};
